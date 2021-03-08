classdef BusStructToROSMsgConverter < handle
    %This class is for internal use only. It may be removed in the future.
    
    %  BusStructToROSMsgConverter(MSGTYPE, MODEL) creates an object that
    %  converts a Simulink bus struct, corresponding to a ROS message type
    %  MSGTYPE, to a MATLAB ROS message. This conversion uses the maximum
    %  sizes of variable-length properties that is specific to MODEL.
    %
    %  Example:
    %   msg2bus = robotics.slros.internal.sim.ROSMsgToBusStructConverter('nav_msgs/Path');
    %   bus2msg = robotics.slros.internal.sim.BusStructToROSMsgConverter('nav_msgs/Path');
    %   busstruct = msg2bus.convert(pathMsg);
    %   msg2 = bus2msg.convert(busstruct); % convert back
    %
    % See also: sim.ROSMsgToBusStructConverter
    
    %   Copyright 2014-2016 The MathWorks, Inc.

    properties
        ROSMessageType
        Model
        MsgInfoMap
    end
    
    methods
        function obj = BusStructToROSMsgConverter(msgtype, model)
            assert(ischar(msgtype) && ~isempty(msgtype));            
            
            obj.ROSMessageType = msgtype;
            obj.Model = model;
            obj.MsgInfoMap = robotics.slros.internal.sim.createROSMsgInfoMap(struct(...
                'MessageType', obj.ROSMessageType, ...
                'ModelName', model, ...
                'MapKeyType', 'msgtype', ...
                'Recurse', true));
            assertInfoStructNames();
        end
        
        
        function rosmsg = convert(obj, busstruct)
            busstruct = processStruct(busstruct, obj.MsgInfoMap, obj.ROSMessageType);            
            rosmsg = rosmessage(obj.ROSMessageType); % blank message
            rosmsg.fromStruct(busstruct);
        end
        
    end
    
end

%%
%%
function assertInfoStructNames()
% processStruct() assumes the the variable-array info struct has a field
% name  named 'CurrentLength' (doesn't look up the fieldname at runtime). 
% Verify that this assumption is valid.
infostruct = robotics.slros.internal.bus.Util.getArrayInfoStructMetadata();
assert(strcmp(infostruct.CurLengthProp, 'CurrentLength'));
end

%%
function busstruct = processStruct(busstruct, map, msgtype)

info = map(msgtype);

% For list of expected fields in info, see
% createROSMsgInfoMap:processBus()

% if ~isempyt(info.StdEmptyMsgProp)
%   Nothing to do. We silently ignore (throw away) the dummy property
% end

% Ensure variable-length array information is captured in the 
% metadata (_SL_Info) field
for i=1:numel(info.VarLenArrays)
    prop = info.VarLenArrays{i};
    infoprop = info.VarLenArrayInfoProps{i};
    
    maxlen = info.VarLenMaxLen{i};
    actuallen = numel(busstruct.(prop));
    validlen = busstruct.(infoprop).CurrentLength;
    
    % Note: 
    % 1) busstruct.(lengthprop).ReceivedLength will be discarded 
    %    (not meaningful during bus -> ROS message conversion)
    %
    % 2) In practice, actuallen will be equal to validlen (there is no 
    %    way in Simulink to extend the max length of an array during a
    %    simulation). However, this function receives an anonymous struct
    %    & can't make this assumption, so we handle the case where 
    %    actuallen > validlen 

    assert((validlen <= actuallen) && (actuallen <= maxlen));
    
    if validlen < actuallen
         busstruct.(prop)(validlen+1:actuallen) = []; % remove extra elements
    end
end

% Uint64 and Int64 values will be handled by fromStruct() for the ROS
% Message (i.e., it will cast them appropriately, so no need for explicit
% casts back to double)

% convert strings to uint8
for i=1:numel(info.StringProps)
   prop = info.StringProps{i};
   busstruct.(prop) = reshape(char(busstruct.(prop)), 1, []); % ensure it is row-vector
end

% no need to remove "CurrentLength" fields; they are ignored

% Future optimization: we don't have to process all arrays, only those 
% with a variable-length array under them (and this is discoverable through
% static analysis)

% note that we've already trimmed the length of variable-length arrays, so
% they have the correct length.
for i=1:numel(info.NestedMsgs)
   prop = info.NestedMsgs{i};
   nestedMsgType = info.NestedMsgType{i};
   len = numel(busstruct.(prop));  % how about multi-dimensional arrays?
   
   substructs = struct.empty;
   for j=1:len
       tmpout = processStruct( ...
           busstruct.(prop)(j), ...
           map, ...
           nestedMsgType);           
       if isempty(substructs)
           substructs = tmpout;
       else
           substructs(j) = tmpout; % extend as row or column?
       end
   end
   
   busstruct.(prop) = substructs;
end

% map back to a cell array of strings
for i=1:numel(info.StringArrayProps)
     prop = info.StringArrayProps{i};
     proplen = info.StringArrayLen{i};

     if proplen == 0
         % variable-length array
         infoprop = info.StringArrayInfoProps{i};
         validlen = busstruct.(infoprop).CurrentLength;
     else
         % fixed-length array
         validlen = proplen;
     end
          
     % Note that busstruct.(prop) has already been trimmed to the correct
     % length, and the busstruct.(prop).Data has already been converted to
     % a MATLAB string -- this is just the standard processing for any
     % array of std_msgs/String[].
         
     if validlen == 0
         busstruct.(prop) = {};
     else
         busstruct.(prop) = {busstruct.(prop).Data};
     end    
end

% If there are reserved names, make sure to have non-mangled 
% property names and remove the mangled property names.
for i=1:numel(info.ReservedWordProp)
    busName = info.ReservedWordProp(i).BusName;
    rosName = info.ReservedWordProp(i).RosName;
    % Copy the content to the non-mangled property name, so it can be used
    % to reconstruct the ROS message object
    busstruct.(rosName) = busstruct.(busName);
    % Remove the mangled property name
    busstruct = rmfield(busstruct, busName);
end

end
