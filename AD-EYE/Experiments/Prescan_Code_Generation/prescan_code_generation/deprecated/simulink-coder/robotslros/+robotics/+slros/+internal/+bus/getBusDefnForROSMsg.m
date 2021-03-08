function requiredBuses = getBusDefnForROSMsg(emptyRosMsg, model)
%This function is for internal use only. It may be removed in the future.

%getBusDefnForROSMsg - Create Simulink bus object corresponding to a ROS message
%
%    getBusDefnForROSMsg(MSG) returns an array of Simulink.Bus objects
%    corresponding to ROS message MSG and any nested messages inside it.
%    MSG should be an empty message (i.e., created using ROSMESSAGE without
%    any subsequent assignments), since the only way to determine if a
%    property is a variable-length array is to check if its value is []. 
%
%    Note:
%    * This function does not create the bus objects in the global scope.
%      Consequently, this function does not define the "name" of the bus
%      (i.e., the name of the bus in the global scope).
%
%    * If the ROS message has variable-size array properties, these are
%      converted to fixed-length arrays (with length of 1), and the
%      associated metadata element is added to the bus object.
%
%    * This function returns a bus object (which is a bus definition), &
%      not an instance of a bus (a bus signal). 

%   Copyright 2014-2018 The MathWorks, Inc.

% Good test for this function:
%  getBusDefnForROSMsg( rosmessage('calibration_msgs/RobotMeasurement') )

map = containers.Map;
processBus(emptyRosMsg, model, map);
requiredBusesCellArray = values(map);
requiredBuses = [requiredBusesCellArray{:}];

end

%%
function processBus(emptyRosMsg, model, map)
if isempty(emptyRosMsg)
   % nothing to do
   return;
end

% should not be making any recursive calls with arrays of messages
assert(numel(emptyRosMsg)==1);

if robotics.slros.internal.ROSUtil.isROSTimeEntityObj(emptyRosMsg)
    msgType = robotics.slros.internal.bus.Util.rosTimeToQuasiMsgType(class(emptyRosMsg));
else
    assert(all(isprop(emptyRosMsg, 'MessageType')));
    msgType = emptyRosMsg.MessageType;
end

if isKey(map, msgType)
    % nothing to do
    return;
end

propertyList = fieldnames(emptyRosMsg);

% During a simulation, we will use msg.toStruct() to convert the ROS
% message to a Simulink bus struct. Consequently, it is important for the
% **order of elements** in the bus struct to be as close as possible to the
% order of fields returned by msg.toStruct(). Hence, call toStruct() here
% to get a "canonical order", and add elements to the bus definition in
% that order.

isRosTimeEntity = robotics.slros.internal.ROSUtil.isROSTimeEntityObj(emptyRosMsg);
if isRosTimeEntity
    % no toStruct() method defined for time entities
    canonicalOrder = propertyList; 
else
    canonicalOrder = fieldnames(toStruct(emptyRosMsg));
    % The toStruct() leaves out some fields. Splice these back in (though
    % these will likely just be MessageType and Constant properties, which
    % will be discarded later on anyway).
    canonicalOrder = [setdiff(propertyList, canonicalOrder) ; canonicalOrder];
end

% Use metaclass, as we need to distinguish Constant properties below
rosmsgMetaClass = metaclass(emptyRosMsg);
rosmsgAllProps = {rosmsgMetaClass.PropertyList.Name};

busElements = Simulink.BusElement.empty;

if robotics.slros.internal.ROSUtil.isStdEmptyMsgType(msgType) || ...
    (numel(canonicalOrder) == 1) && strcmpi(canonicalOrder{1}, 'MessageType')
    
    % The only field in an empty message should be 'MessageType'
    % Add in the dummy field (the loop below over canonicalOrder is effectively a no-op)
    elem = robotics.slros.internal.bus.Util.getDummyElementForStdEmptyMsg;
    busElements(end+1) = elem; 
end

nameChecker = robotics.slros.internal.bus.ReservedNamesChecker.getInstance;

for i =1:length(canonicalOrder)
    propertyName = canonicalOrder{i};
    
    if strcmp(propertyName,'MessageType')
        continue;
    end
        
    metaprop = rosmsgMetaClass.PropertyList(strcmp(propertyName, rosmsgAllProps));
    isConstant = metaprop.Constant;
    if isConstant
        % Constants are not yet supported
        continue;
    end 

    [elemName,isReservedName] = nameChecker.mangleNameIfNeeded(propertyName);
    
    elem = Simulink.BusElement;
    elem.Name = elemName;
    elem.Dimensions = 1;
    elem.SampleTime = -1;
    elem.Complexity = 'real';
    elem.SamplingMode = 'Sample based';
    elem.Min = [];
    elem.Max = [];
    elem.DocUnits = '';
    elem.Description = '';
    elemInfo = robotics.slros.internal.bus.BusItemInfo;
    
    if isReservedName
        % remember the original (unmangled) name
        elemInfo.ROSPropName = propertyName;
    end
    
    data = emptyRosMsg.(propertyName);
    
    isLogicalOrNumericType = isa(data,'logical') || isa(data,'numeric');
    isStringType = isa(data, 'char');
    isStringArrayType = isa(data, 'cell');    
    isRosTimeEntity = robotics.slros.internal.ROSUtil.isROSTimeEntityObj(data);
    % isROSMsgObj returns true even if data is zero-length array of expected type
    isRosMessage = robotics.slros.internal.ROSUtil.isROSMsgObj(data);
    
    %------
    % Handle primitive and complex message properties
    
    if isStringArrayType        
        % Variable or fixed-length array of strings.
        % Replace the 'data' cell array with an array of std_msgs/String        
        numStrings = numel(data);
        tmpStringMsg = robotics.slros.internal.ROSUtil.getStdStringObj();
        if numStrings == 0
            % variable-length array of strings
            data = tmpStringMsg.empty(0,1);
        else
            % fixed-length array of strings
            % Note
            % 1) We are only using the 'data' variable to set up datatypes; 
            % the actual content of 'data' is not used or modified.
            % 2) We can't just assign to data(1:numStrings,1); that syntax
            % requires LHS and RHS to have matching types, whereas here we
            % are replacing a cell array with a new data type.
            data = tmpStringMsg;
            data(2:numStrings,1) = tmpStringMsg;
        end
        rosMessageType = tmpStringMsg.MessageType;
        dataTypeStr = robotics.slros.internal.bus.Util.rosMsgTypeToDataTypeStr(rosMessageType, model);
        elem.DataType = dataTypeStr;
        elemInfo.MsgType = rosMessageType;
        elemInfo.PrimitiveROSType = 'string[]';
        processBus(tmpStringMsg, model, map); % recursive call        
        
    elseif isLogicalOrNumericType
        if isa(data,'logical')
            elem.DataType = 'boolean';
        elseif isa(data, 'int64') || isa(data, 'uint64')
            elem.DataType = 'double';
            elemInfo.Int64Type = class(data);
            robotics.internal.warningNoBacktrace(...
                message('robotics:robotslros:busconvert:Int64NotSupported', ...
                propertyName, msgType, class(data), 'double'));
        else
            elem.DataType = class(data);
        end
        
    elseif isStringType
        elem.DataType = 'uint8'; 
        elemInfo.PrimitiveROSType = 'string';  % remember that this uint8 array is a string
                
    elseif isRosTimeEntity
        datainstance = getDataInstance(data);
        [dataTypeStr, ~, timeMsgType] = robotics.slros.internal.bus.Util.rosTimeToDataTypeStr(class(data), model);
        elem.DataType = dataTypeStr;    
        elemInfo.MsgType = timeMsgType;
        processBus(datainstance, model, map); % recursive call
        
    elseif isRosMessage
        datainstance = getDataInstance(data);
        assert(isprop(datainstance, 'MessageType'));
        rosMessageType = datainstance.MessageType;
        dataTypeStr = robotics.slros.internal.bus.Util.rosMsgTypeToDataTypeStr(rosMessageType, model);
        elem.DataType = dataTypeStr;      
        elemInfo.MsgType = rosMessageType;
        processBus(datainstance, model, map); % recursive call
        
    else         
        assert(false);
    end
    
    %------
    % Add metadata related to variable vs. fixed-length arrays    
    
    isVarsizeArray = isempty(data) || isStringType;    
    if isVarsizeArray
        elemInfo.IsVarLen = true;
        elem.DimensionsMode = 'Variable';
        % SL buses require non-zero value for dimensions, so set it to 1
        % for now. Conversion from Variable-length to Fixed-length array
        % will be done later (after getting user data on maximum lengths)
        elem.Dimensions = max(numel(data),1);        
        elem.Description = elemInfo.toDescription(); 
        % Add the array and the corresponding SL_Info element to the bus
        [elem, arrayInfoElem] = addArrayInfoElement(elem);
        busElements(end+1:end+2) = [elem ; arrayInfoElem];
        
    else
        elemInfo.IsVarLen = false;
        elem.DimensionsMode = 'Fixed';
        elem.Dimensions = max(numel(data),1);        
        elem.Description = elemInfo.toDescription(); 
        busElements(end+1) = elem; %#ok<AGROW>
    end
    
end
   
businfo = robotics.slros.internal.bus.BusItemInfo;
businfo.MsgType = msgType;
mybus = Simulink.Bus;
mybus.HeaderFile = '';
mybus.Description = businfo.toDescription();
mybus.DataScope = 'Auto';
mybus.Alignment = -1;
mybus.Elements = busElements;

map(msgType) = struct('MessageType', msgType, 'Bus', mybus); %#ok<NASGU>

end


%%
function [arrayElem, arrayInfoElem] = addArrayInfoElement(arrayElem)
assert(strcmp(arrayElem.DimensionsMode, 'Variable'));

infoElemName = robotics.slros.internal.bus.Util.getArrayInfoElementName(arrayElem.Name);

busItemInfo = robotics.slros.internal.bus.BusItemInfo(arrayElem.Description);
busItemInfo.IsVarLen = true;
busItemInfo.VarLenCategory = 'data';
busItemInfo.VarLenElem = infoElemName;
arrayElem.Dimensions = 1;  % temporary length
arrayElem.DimensionsMode = 'Fixed';
arrayElem.Description = busItemInfo.toDescription();

busItemInfo2 = robotics.slros.internal.bus.BusItemInfo;
busItemInfo2.IsVarLen = true;
busItemInfo2.VarLenCategory = 'length';
busItemInfo2.VarLenElem = arrayElem.Name;

arrayInfoElem = Simulink.BusElement;
arrayInfoElem.Name = infoElemName;
arrayInfoElem.DataType = robotics.slros.internal.bus.Util.varlenInfoBusDataTypeStr();
arrayInfoElem.DimensionsMode = 'Fixed';
arrayInfoElem.Dimensions = 1;
arrayInfoElem.SamplingMode = 'Sample based';
arrayInfoElem.Description = busItemInfo2.toDescription();
end
    
%%
function datainstance = getDataInstance(data)
if isempty(data)
    datainstance = feval(class(data));
else
    datainstance = data(1);
end
end
