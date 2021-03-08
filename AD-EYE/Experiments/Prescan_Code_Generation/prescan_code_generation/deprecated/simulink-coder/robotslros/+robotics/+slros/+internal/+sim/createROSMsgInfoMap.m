function map = createROSMsgInfoMap(params)
%This function is for internal use only. It may be removed in the future.

%createROSMsgInfoMap - Analyze & gather information for ROS<->Bus conversions
%
%   MAP = createROSMsgInfoMap(PARAMS) analyzes a ROS message type and
%   gathers information for converting ROS messages to Simulink buses, and
%   vice versa.
%
%    Inputs:
%     PARAMS is a struct with the following fields:
%       MessageType : The ROS message type to analyze (e.g., 'nav_msgs/Path')
%       ModelName   : The name of the Simulink model using this message type
%       MapKeyType  : Required to be 'msgtype'
%       Recurse     : If true, nested messages are analyzed as well
%
%    Outputs:
%     MAP is a containers.Map object; the key is a ROS message type
%     and the corresponding value is a struct with a number of fields. See
%     processBus subfunction for a list.

%   Copyright 2014-2019 The MathWorks, Inc.

    validateattributes(params.MessageType, {'char'}, {'nonempty'});
    validateattributes(params.ModelName, {'char'}, {'nonempty'});
    validateattributes(params.MapKeyType, {'char'}, {'nonempty'});
    validateattributes(params.Recurse, {'logical'}, {'scalar'});

    % Require caller to specify the MapKeyType (even though there is only one
    % option) so that the key type is explicit
    validatestring(params.MapKeyType, {'msgtype'});

    busName = robotics.slros.internal.bus.Util.createBusIfNeeded(...
        params.MessageType, params.ModelName);

    emptyMsg = robotics.slros.internal.bus.Util.newMessageFromSimulinkMsgType(params.MessageType);

    map = containers.Map;
    processBus(busName, emptyMsg, map, params.Recurse, params.ModelName);
end

%%
function processBus(busname, rosmsg, map, doRecurse, modelName)

    bus = robotics.slros.internal.bus.Util.getBusObjectFromBusName(busname, modelName);
    businfo = robotics.slros.internal.bus.BusItemInfo( bus.Description );

    s.BusName = busname;
    s.ROSMessageType = businfo.MsgType;

    % General approach: Each set of cell arrays with common prefix (VarLen*,
    % VarLenMsg*) capture info about properties with certain attributes.
    % All the cell arrays in the set have the same length, so for a given index
    % idx,
    %   VarLenArrays(idx)
    %   VarLenArrayInfoProps(idx)
    %   VarLenMaxLen(idx)
    %   ...
    % all give info about a single property.
    %
    % An alternative data structure is a array of structs or classes, but this
    % ends up being time-consuming to work with when doing ROS<->Simulink
    % conversions. A better organization (for future consideration) may be a
    % class that wraps the cell arrays and applies some validation.


    % Info about variable-length arrays (include both primitive type & arrays
    % of messages)
    s.VarLenArrays = {};         % Name of variable-length property
    s.VarLenArrayInfoProps = {}; % Name of corresponding SL_Info property
    s.VarLenMaxLen = {};         % Max length of the var-length array
    s.VarLenDataType = {};       % Datatype of the array element
    s.VarLenTruncateAction = {}; % Truncate action of the array

    % Info about variable-length arrays of messages
    % Note: The single instance of the ROS message (VarLenMsgEmpty) is needed
    % to pad the Simulink bus arrays in case the incoming message has zero
    % length.
    s.VarLenMsgArrays = {};      % Name of variable-length message array property
    s.VarLenMsgMaxLen = {};      % Max length of the variable-length message array property
    s.VarLenMsgEmpty = {};       % struct of a single instance of the ROS message

    % Info about variable-length arrays of primitive type
    s.VarLenPrimitiveArrays = {}; % Name of variable-length primitive array property
    s.VarLenPrimitiveMaxLen = {}; % Max length of the variable-length primitive array property

    % Info about nested ROS message properties (includes scalar and arrays)
    s.NestedMsgs = {};            % Name of nested ROS message property
    s.NestedMsgType = {};         % Type of the nested ROS message

    % Info about string properties
    s.StringProps = {};           % Name of string property

    % Info about string array (string[]) properties
    s.StringArrayProps = {};      % Name of string array (string[]) property
    s.StringArrayInfoProps = {};  % Name of corresponding SL_Info property
    s.StringArrayLen = {};        % Number of elements of string array (0 indicates variable-length)

    % Info about Int64 & uint64 properties
    s.Int64Props = {};            % Name of int64 property

    % Info about std_msgs/Empty
    % If this message is a std_msgs/Empty, StdEmptyMsgProp has the name of the
    % dummy property to be spliced into it (as a Simulink bus needs to
    % at least one element).
    s.StdEmptyMsgProp = {};       % Name of the dummy std_msgs/Empty property

    % Info about how to reorder the properties (e.g., so that the SL_Info
    % properties are next to the corresponding variable-length arrays)
    s.propertyReorderInfo = [];


    % When a property uses a reserved name, remember the actual ROS property
    % name (RosName) and the corresponding mangled name in the Bus (Busname)
    s.ReservedWordProp = struct('BusName', {}, 'RosName', {});
    s.ReservedWordInfo = struct.empty;

    % Insert a dummy element if message has no properties.
    % This prevents empty bus definitions (not allowed by Simulink). Note that
    % there are two cases that have to be covered here:
    %   1. If we deal with a message of type std_msgs/Empty or std_srvs/EmptyRequest
    %   2. If we deal with another message that has no properties. In that
    %      case, the message type is not predictable, since it might be an
    %      empty service response, action request, etc. Simply check if the ROS
    %      message has any properties besides MessageType.
    if (robotics.slros.internal.ROSUtil.isStdEmptyMsgType(businfo.MsgType) || ...
        isempty(setdiff(fields(rosmsg), {'MessageType'})))

        s.StdEmptyMsgProp = {robotics.slros.internal.bus.Util.getDummyElementNameForStdEmptyMsg};
    end

    % Don't call assert() logic in production code
    % assertOnlyConstantsAndReservedWordsExcluded(bus, rosmsg);

    varlenInfoDataType = robotics.slros.internal.bus.Util.varlenInfoBusDataTypeStr;

    for i=1:numel(bus.Elements)
        elem = bus.Elements(i);
        busName = elem.Name; % name of property in the bus

        elemInfo = robotics.slros.internal.bus.BusItemInfo( elem.Description );
        if isempty(elemInfo.ROSPropName)
            % not a reserved name, so rosName is same as busName
            rosName = busName;
        else
            % reserved name, so busName is the mangled name
            rosName = elemInfo.ROSPropName;
            s.ReservedWordProp(end+1) = struct('BusName', busName, 'RosName', rosName);
        end

        % Note: all the subsequent logic works with busName, so the other
        % info fields (e.g., Int64Props, StringArrayProps) would record the
        % possibly-mangled busName.

        isStringArrayProp = strcmpi(elemInfo.PrimitiveROSType, 'string[]');
        isStringProp = strcmpi(elemInfo.PrimitiveROSType, 'string');
        isNestedBusProp = strncmpi(elem.DataType, 'Bus:', 4);
        isInt64Prop = ~isempty(elemInfo.Int64Type);
        isVarLenArrayProp = elemInfo.IsVarLen && strcmpi(elemInfo.VarLenCategory, 'data');
        isVarLenArrayInfoProp = strcmpi(elem.DataType, varlenInfoDataType);

        assert(strcmp(elem.DimensionsMode, 'Fixed'));

        if isInt64Prop
            s.Int64Props{end+1} = busName;

        elseif isStringProp
            s.StringProps{end+1} = busName;

        elseif isStringArrayProp
            s.StringArrayProps{end+1} = busName;
            s.StringArrayInfoProps{end+1} = elemInfo.VarLenElem;
            s.StringArrayLen{end+1} = numel(rosmsg.(rosName));
            % string arrays are mapped to nested arrays of std_msgs/String
            % Note that a string array is not always a variable-length array
            % (can be a fixed-length array of strings)
            assert(isNestedBusProp);
        end


        if isNestedBusProp && ~isVarLenArrayInfoProp
            % Nested bus (corresponding to nested ROS message)

            rosmsgProp = getROSMsgInstance(rosmsg, rosName, isStringArrayProp);
            nestedBusName = robotics.slros.internal.bus.Util.getBusNameFromDataTypeStr(elem.DataType);
            assert(~isempty(nestedBusName));

            s.NestedMsgs{end+1} = busName;
            s.NestedMsgType{end+1} = elemInfo.MsgType;
            if doRecurse
                processBus(nestedBusName, rosmsgProp, map, doRecurse, modelName);
            end
        end

        % For variable-length array elements, make a note of the extra field
        % Note -
        %  1. a nested bus could also be variable length
        %  2. this includes both primitive and nested-msg datatypes

        if isVarLenArrayProp
            s.VarLenArrays{end+1} = busName;
            s.VarLenArrayInfoProps{end+1} = elemInfo.VarLenElem;

            assert(all(size(elem.Dimensions) == [1 1]), 'Expecting a scalar');
            s.VarLenMaxLen{end+1} = elem.Dimensions(1);

            if strcmpi(elemInfo.TruncateAction, 'warn')
                s.VarLenTruncateAction{end+1} = robotics.slros.internal.bus.VarLenArrayTruncationAction.EmitWarning;
            else
                s.VarLenTruncateAction{end+1} = robotics.slros.internal.bus.VarLenArrayTruncationAction.DoNothing;
            end

            if isNestedBusProp
                % variable-length array of messages

                dataInstance = getROSMsgInstance(rosmsg, rosName, isStringArrayProp);
                s.VarLenMsgArrays{end+1} = busName;
                s.VarLenMsgMaxLen{end+1} = elem.Dimensions(1);
                s.VarLenMsgEmpty{end+1} = toStruct( dataInstance );
                s.VarLenDataType{end+1} = elemInfo.MsgType;
            else
                % variable-length array of primitive Simulink type
                s.VarLenPrimitiveArrays{end+1} = busName;
                s.VarLenPrimitiveMaxLen{end+1} = elem.Dimensions(1);
                s.VarLenDataType{end+1} = elem.DataType;
            end
        end

    end

    rosPropNames = fieldnames(toStruct(rosmsg));

    if numel(s.ReservedWordProp) > 0
        % Cache info about ReservedWords for use during bus<->rosmsg conversion
        wordsInfo.BusNames = {s.ReservedWordProp(:).BusName}; % mangled names
        wordsInfo.RosNames = {s.ReservedWordProp(:).RosName}; % ROS names
        [~, indices] = ismember(wordsInfo.RosNames, rosPropNames);
        fieldNames = rosPropNames;
        fieldNames(indices) = wordsInfo.BusNames;
        wordsInfo.AdjustedFieldNames = fieldNames;
        s.ReservedWordInfo = wordsInfo;
        adjustedPropNames = fieldNames;
    else
        adjustedPropNames = rosPropNames;
    end

    % Figure out how to fields in the busstruct should be reordered so that
    % VarLenArrayInfoProps are adjacent to the corresponding VarlenArrays
    s.propertyReorderInfo = robotics.slros.internal.sim.computeMsgStructReordering(...
        adjustedPropNames, s.VarLenArrays, s.VarLenArrayInfoProps);

    map(s.ROSMessageType) = s; %#ok<NASGU>

end


%%
function rosMsgInstance = getROSMsgInstance(rosmsg, propertyName, isStringArray)
    if isStringArray
        % string array (string[]) that is mapped to a std_msgs/String[]
        rosMsgInstance = robotics.slros.internal.ROSUtil.getStdStringObj();
    else
        % regular nested bus
        if isempty(rosmsg.(propertyName))
            % variable-length array
            rosMsgInstance = feval(class(rosmsg.(propertyName)));
        else
            rosMsgInstance = rosmsg.(propertyName)(1);
        end
    end

end


%%
% Sanity check:
% Verify that the only ROS Message properties missing from the Bus
% are Constants and reserved words.
function assertOnlyConstantsAndReservedWordsExcluded(bus, rosmsg) %#ok<DEFNU>

    rosmsgFlds = fieldnames(rosmsg);
    busElementNames = {bus.Elements.Name};
    fldsOnlyInRosMsg = setdiff(rosmsgFlds, busElementNames);
    rosmsgMetaClass = metaclass(rosmsg);
    rosmsgAllProps = {rosmsgMetaClass.PropertyList.Name};
    nameChecker = robotics.slros.internal.bus.ReservedNamesChecker.getInstance();
    for i=1:numel(fldsOnlyInRosMsg)
        propertyName = fldsOnlyInRosMsg{i};
        if strcmp(propertyName, 'MessageType')
            continue;
        end
        if nameChecker.isReserved(propertyName)
            continue;
        end
        metaprop = rosmsgMetaClass.PropertyList(strcmpi(propertyName, rosmsgAllProps));
        assert(metaprop.Constant);
    end

end
