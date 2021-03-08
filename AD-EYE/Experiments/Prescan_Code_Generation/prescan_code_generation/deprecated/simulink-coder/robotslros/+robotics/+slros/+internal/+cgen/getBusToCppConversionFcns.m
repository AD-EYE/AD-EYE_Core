function [bus2cppFcnMap, cpp2busFcnMap] = getBusToCppConversionFcns(emptyROSMsg, model)
%This function is for internal use only. It may be removed in the future.

%getBusToCppConversionFcns - Generate C++ conversion code for a message type
%
%   [BUS2CPP, CPP2BUS] = getBusToCppConversionFcns(MSG, MODEL) generates
%   the C++ code for converting ROS->Bus and Bus->ROS for a single ROS
%   message MSG and any nested messages inside it, using the
%   variable-length array size information from MODEL. MSG should  be an
%   empty message (i.e., created using ROSMESSAGE without any subsequent
%   assignments), since the only way to determine if a property is a
%   variable-length array is to check if its value is [].
%
%    Outputs
%      BUS2CPP, CPP2BUS : containers.Map objects that map a message type to
%         corresponding StringWriter objects with generated C++ code for
%         Bus->ROS (or ROS->Bus).

%   Copyright 2014-2018 The MathWorks, Inc.

params.ConvertFromBusFcnStr = 'convertFromBus';
params.ConvertToBusFcnStr = 'convertToBus';
params.Indent = 2;
params.ModelName = model;

bus2cppFcnMap = containers.Map;
generateConversionFcns('bus2cpp', emptyROSMsg, params, bus2cppFcnMap);

cpp2busFcnMap = containers.Map;
generateConversionFcns('cpp2bus', emptyROSMsg, params, cpp2busFcnMap);

% There should be a 1-1 relation between 
% bus2cpp and cpp2bus conversion functions
assert(all(strcmp(sort(keys(bus2cppFcnMap)), sort(keys(cpp2busFcnMap)))), ...
       'Mismatch detected for %s', class(emptyROSMsg));

end

%%
function generateConversionFcns(direction, emptyROSMsg, params, fcnInfoMap)

convertFromBus2Cpp = strcmp(direction, 'bus2cpp');

[cppRosClass, msgType] = robotics.slros.internal.cgen.Util.rosObjToCppClass(emptyROSMsg);
if fcnInfoMap.isKey(cppRosClass)
    % information already present
    return;
end
params.MsgType = msgType;

[bus, slBusName] = robotics.slros.internal.bus.Util.getBusObjectFromMsgType(...
    msgType, params.ModelName);
busElementNames = {bus.Elements.Name};

% -- Generate function signature
fcnSignature = StringWriter;
if convertFromBus2Cpp
    fcnSignature.add('void %s(%s* msgPtr, %s const* busPtr)', ...
        params.ConvertFromBusFcnStr, cppRosClass, slBusName);
else
    fcnSignature.add('void %s(%s* busPtr, %s const* msgPtr)', ...
        params.ConvertToBusFcnStr, slBusName, cppRosClass);
end

% -- Generate function body
fcnBody = StringWriter;
fcnBody.addcr('{');
fcnBody.Indent = params.Indent;
upstreamDependencies = {};

nameChecker = robotics.slros.internal.bus.ReservedNamesChecker.getInstance();

[propList, rosPropList] = robotics.slros.internal.ROSUtil.getPropertyLists(emptyROSMsg);

fcnBody.addcr('const std::string rosMessageType("%s");', params.MsgType);
fcnBody.addcr;

for idx=1:numel(propList)
    matlabPropName = propList{idx};    
    propinfo.MATLABPropName = matlabPropName;
    
    % If matlabPropName is reserved name, then the bus name has to be mangled
    propinfo.BusPropName = nameChecker.mangleNameIfNeeded(matlabPropName);
    propinfo.CppPropName = rosPropList{idx};  % property name used in C++ object
        
    busIdx = strcmpi(propinfo.BusPropName, busElementNames);
    assert(find(length(busIdx)) == 1); % should find exactly one element
    busElement = bus.Elements(busIdx);
    elemInfo = robotics.slros.internal.bus.BusItemInfo(busElement.Description);
    
    data = emptyROSMsg.(propinfo.MATLABPropName);   
    
    propinfo.IsLogicalOrNumericType = isa(data,'logical') || isa(data,'numeric');
    propinfo.IsStringType = strcmpi(elemInfo.PrimitiveROSType, 'string');
    propinfo.IsStringArray = strcmpi(elemInfo.PrimitiveROSType, 'string[]');
    propinfo.IsRosEntity = robotics.slros.internal.ROSUtil.isROSObj(data);
    propinfo.Int64Type = elemInfo.Int64Type;
        
    % Determine if this is an array property or not
    propinfo.IsVarsizeArray = elemInfo.IsVarLen;
    propinfo.IsFixedLenArray = robotics.slros.internal.ROSUtil.isFixedSizeArray(msgType, propinfo.CppPropName);
    if elemInfo.IsVarLen && strcmpi(elemInfo.VarLenCategory, 'data')
        propinfo.ArrayInfoPropName = elemInfo.VarLenElem;
    else
        propinfo.ArrayInfoPropName = '';
    end
    propinfo.WarnOnTruncate = strcmpi(elemInfo.TruncateAction, 'warn');
    
    % Determine if the value is a scalar type or not. All properties that
    % are neither a fixed-length array nor a variable-length array are
    % scalar.
    propinfo.IsScalar = ~propinfo.IsFixedLenArray && ~propinfo.IsVarsizeArray;
    
    if propinfo.IsRosEntity
        % Get an instance of the ROS entity so that it can be used for
        % recursion. If data is an empty-variable length array,
        % getDataInstance will create an instance.
        %
        % Note: a string array is specifically not a ROS entity (i.e., a
        % nested ROS message). In Simulink it is mapped to an array of
        % std_msgs/String, but in ROS C++ there is no corresponding
        % std_msgs/String object. 
        upstreamDependencies{end+1} = getDataInstance(data); %#ok<AGROW>
    end
    
    assert(all(size(busElement.Dimensions) == [1 1]), 'Expecting a scalar');
    propinfo.BusArrayMaxLength = busElement.Dimensions;
        
    if propinfo.IsStringType
        % string (treated as variable-length array of uint8)
        copyArray(convertFromBus2Cpp, propinfo, params, fcnBody, 'PrimitiveArray');
    
    elseif propinfo.IsStringArray
        % string[] is treated as a variable-length array of std_msgs/String        
        % In the MATLAB ROS message, string[] is not a ROS message
        assert(~propinfo.IsRosEntity);        
        copyArray(convertFromBus2Cpp, propinfo, params, fcnBody, 'StringArray');
            
    elseif propinfo.IsScalar
        % Scalar property: numeric, logical or nested message
        simpleAssignment(convertFromBus2Cpp, propinfo, params, fcnBody);
    
    elseif propinfo.IsLogicalOrNumericType
        % Array of primitive type (fixed or variable-length)
        copyArray(convertFromBus2Cpp, propinfo, params, fcnBody, 'PrimitiveArray');
    
    else
        % Array of nested messages (fixed or variable-length)
        assert(propinfo.IsRosEntity);
        copyArray(convertFromBus2Cpp, propinfo, params, fcnBody, 'NestedArray');
    end
end
fcnBody.Indent = fcnBody.Indent - params.Indent;
fcnBody.addcr('}');

fcnInfo.FcnSignature = fcnSignature;
fcnInfo.FcnBody = fcnBody;
fcnInfo.CppRosClass = cppRosClass;
fcnInfo.SLBusName = slBusName;

fcnInfoMap(cppRosClass) = fcnInfo;

for i=1:numel(upstreamDependencies)
    generateConversionFcns(direction, upstreamDependencies{i}, params, fcnInfoMap);
end
end


%%
function datainstance = getDataInstance(data)
% Return need an instance of a ROS message. If data is empty (indicating a
% empty variable-length array), construct an instance of the message.
if isempty(data)
    datainstance = feval(class(data));
else
    datainstance = data(1);
end
end

%%
function [from,to] = getFromAndTo(convertFromBus2Cpp, propinfo, params)

to.assignmentCastStr = '';
if convertFromBus2Cpp
    from.PtrStr = 'busPtr';
    from.PropName = propinfo.BusPropName;
    to.PtrStr = 'msgPtr';
    to.PropName = propinfo.CppPropName;
    to.conversionFcnStr = params.ConvertFromBusFcnStr;
    if ~isempty(propinfo.Int64Type)
        if strcmpi(propinfo.Int64Type, 'int64') 
            to.assignmentCastStr = '(int64_t)';
        else
            to.assignmentCastStr = '(uint64_t)';
        end       
    end  
else % cpp2bus
    from.PtrStr = 'msgPtr';
    from.PropName = propinfo.CppPropName;
    to.PtrStr = 'busPtr';
    to.PropName = propinfo.BusPropName;
    to.conversionFcnStr = params.ConvertToBusFcnStr;
    if propinfo.IsStringType
        to.assignmentCastStr = '(uint8_T)';
    end
    if ~isempty(propinfo.Int64Type)
       to.assignmentCastStr = '(real_T)'; % real_T is 64-bit float
    end    
end
end

%%
function simpleAssignment(convertFromBus2Cpp, propinfo, params, buf)
[from,to] = getFromAndTo(convertFromBus2Cpp, propinfo, params);

if propinfo.IsLogicalOrNumericType
    buf.addcr('%s->%s = %s %s->%s;', to.PtrStr, to.PropName, to.assignmentCastStr, from.PtrStr, from.PropName);
elseif propinfo.IsRosEntity
    % nested message
    buf.addcr('%s(&%s->%s, &%s->%s);', to.conversionFcnStr, ...
        to.PtrStr, to.PropName, from.PtrStr, from.PropName);
else
    assert(false);
end
end

%%
% Called for either fixed-length arrays (length > 1), or variable-length arrays
function copyArray(convertFromBus2Cpp, propinfo, params, buf, fcnNameSuffix)
validatestring(fcnNameSuffix, {'PrimitiveArray', 'StringArray', 'NestedArray'});

% This function will generate one of the following functions (these are
% explicitly listed here for findability in a code search):
%
% For PrimitiveArray
%   convertToBusFixedPrimitiveArray
%   convertToBusVariablePrimitiveArray
%   convertFromBusFixedPrimitiveArray
%   convertFromBusVariablePrimitiveArray
%
% For StringArray
%   convertToBusFixedStringArray
%   convertToBusVariableStringArray
%   convertFromBusFixedStringArray
%   convertFromBusVariableStringArray
%
% For NestedArray
%   convertToBusFixedNestedArray
%   convertToBusVariableNestedArray
%   convertFromBusFixedNestedArray
%   convertFromBusVariableNestedArray

[from,to] = getFromAndTo(convertFromBus2Cpp, propinfo, params);
if convertFromBus2Cpp
    % convert from bus to roscpp
    if propinfo.IsVarsizeArray
        % Variable-length array
        buf.addcr('convertFromBusVariable%s(%s->%s, %s->%s, %s->%s);', ...
            fcnNameSuffix, ...
            to.PtrStr, to.PropName, ...
            from.PtrStr, from.PropName, ...
            from.PtrStr, propinfo.ArrayInfoPropName);
    else
        % Fixed-size array
        buf.addcr('convertFromBusFixed%s(%s->%s, %s->%s);', ...
            fcnNameSuffix, ...
            to.PtrStr, to.PropName, ...
            from.PtrStr, from.PropName);
    end
    
else
    % convert from roscpp to bus
    if propinfo.IsVarsizeArray
        % Variable-length array
        if propinfo.WarnOnTruncate
            warnStr = sprintf('slros::EnabledWarning(rosMessageType, "%s")', propinfo.CppPropName);
        else
            warnStr = 'slros::DisabledWarning()';
        end   
        buf.addcr('convertToBusVariable%s(%s->%s, %s->%s, %s->%s, %s);', ...
            fcnNameSuffix, ...
            to.PtrStr, to.PropName, ...
            to.PtrStr, propinfo.ArrayInfoPropName, ...
            from.PtrStr, from.PropName, ...
            warnStr);
    else
        % Fixed-size array
        warnStr = 'slros::NoopWarning()';
        buf.addcr('convertToBusFixed%s(%s->%s, %s->%s, %s);', ...
            fcnNameSuffix, ...
            to.PtrStr, to.PropName, ...
            from.PtrStr, from.PropName, ...
            warnStr);
    end
    
end

end



