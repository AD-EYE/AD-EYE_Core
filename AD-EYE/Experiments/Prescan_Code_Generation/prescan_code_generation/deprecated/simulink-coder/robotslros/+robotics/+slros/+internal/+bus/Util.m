classdef Util
    %This class is for internal use only. It may be removed in the future.
    
    %BUS.UTIL - Utility functions for working with Simulink buses
    
    %   Copyright 2014-2018 The MathWorks, Inc.
    
    properties(Constant)
        BusNamePrefix = 'SL_Bus_'
        VarlengthInfoBusName = 'SL_Bus_ROSVariableLengthArrayInfo'
        
        %TimePackage - Pseudo ROS package for Time and Duration structures        
        TimePackage = 'ros_time'
        
        %TimeMessage - Message name for time data in TimePackage
        TimeMessage = 'Time'
        
        %DurationMessage - Message name for duration data in TimePackage
        DurationMessage = 'Duration'
        
        %TimeMessageType - Full pseudo message type for time
        %   Note that ROS does not have a dedicated message type for time,
        %   but it uses a standard structure. From the Simulink perspective
        %   each time structure corresponds to a pseudo message type, just
        %   to keep uniform code.
        TimeMessageType = [robotics.slros.internal.bus.Util.TimePackage '/' ...
            robotics.slros.internal.bus.Util.TimeMessage]
        
        %DurationMessageType - Full pseudo message type for duration
        %   Note that ROS does not have a dedicated message type for duration,
        %   but it uses a standard structure. From the Simulink perspective
        %   each duration structure corresponds to a pseudo message type, just
        %   to keep uniform code.
        DurationMessageType = [robotics.slros.internal.bus.Util.TimePackage '/' ...
            robotics.slros.internal.bus.Util.DurationMessage]
    end
    
    %% Utility functions related to variable-length arrays
    methods (Static)

        function out = setMaxLength(modelName, messageType, prop, newLength)
            store = robotics.slros.internal.bus.VarlenArraySizeStore(modelName);
            arrayInfo = robotics.slros.internal.bus.VarLenArrayInfo(messageType, modelName);
            store.applyMaxLengths(arrayInfo);
            arrayInfo.setMaxLength(prop, newLength);
            store.setUserSpecifiedArrayInfo(messageType, arrayInfo);
            store.updateModel();
            out = message('robotics:robotslros:busconvert:ArrayLengthIncreased', ...
                newLength).getString;
        end
        
        function [datatype,busName] = varlenInfoBusDataTypeStr()
            busName = robotics.slros.internal.bus.Util.VarlengthInfoBusName;
            datatype = ['Bus: ' busName];
        end
        
        
        function s = getVarlenInfoStruct(curlen, recvdlen)
            s.CurrentLength = uint32(curlen);
            s.ReceivedLength = uint32(recvdlen);
        end
        
        
        function createVarlenInfoBusIfNeeded(modelName)
            busName = robotics.slros.internal.bus.Util.VarlengthInfoBusName;
            busExists = robotics.slros.internal.existsInGlobalScope(modelName, busName);
            if ~busExists                
                elems(1) = Simulink.BusElement;
                elems(1).Name = 'CurrentLength';
                elems(1).Dimensions = 1;
                elems(1).DimensionsMode = 'Fixed';
                elems(1).DataType = 'uint32';
                elems(1).Complexity = 'real';
                elems(1).SamplingMode = 'Sample based';
                elems(1).Description = '';
                
                elems(2) = Simulink.BusElement;
                elems(2).Name = 'ReceivedLength';
                elems(2).Dimensions = 1;
                elems(2).DimensionsMode = 'Fixed';
                elems(2).DataType = 'uint32';
                elems(2).Complexity = 'real';
                elems(2).SamplingMode = 'Sample based';
                elems(2).Description = '';
                
                bus = Simulink.Bus;
                bus.Description = '';
                bus.Elements = elems;
                robotics.slros.internal.assigninGlobalScope(modelName, busName, bus);
            end
        end

        
        function infostruct = getArrayInfoStructMetadata()
            infostruct.PropertySuffix = '_SL_Info';
            infostruct.CurLengthProp = 'CurrentLength';
            infostruct.RcvdLengthProp = 'ReceivedLength';            
            infostruct.LengthTypeSL = 'uint32';
            infostruct.LengthTypeCpp = 'uint32_T';  
        end

        
        function arrayInfoElemName = getArrayInfoElementName(arrayElemName)
            infostruct = robotics.slros.internal.bus.Util.getArrayInfoStructMetadata();
            arrayInfoElemName = [arrayElemName infostruct.PropertySuffix];            
        end        
    end

    
    %%  Utility functions for handling std_msgs/Empty
    methods (Static)
       
        function name = getDummyElementNameForStdEmptyMsg()
            name = 'SL_DummyData';
        end

        
        function elem = getDummyElementForStdEmptyMsg()
            elem = Simulink.BusElement;
            elem.Name = robotics.slros.internal.bus.Util.getDummyElementNameForStdEmptyMsg;
            elem.Dimensions = 1;
            elem.DimensionsMode = 'Fixed';
            elem.DataType = 'boolean';
            elem.Complexity = 'real';
            elem.SamplingMode = 'Sample based';
            elem.Description = '';            
        end        
        
    end
    
    %%  General Bus-related utilities
    methods (Static)
        function allMsgsMap = getAllMessageInfoMapForModel(model)
            validateattributes(model, {'char'}, {'nonempty'});
            topLevelMsgTypes = robotics.slros.internal.bus.Util.getBlockLevelMessageTypesInModel(model);
            allMsgsMap = containers.Map;
            for i=1:numel(topLevelMsgTypes)
                map = robotics.slros.internal.sim.createROSMsgInfoMap(struct(...
                    'MessageType', topLevelMsgTypes{i}, ...
                    'ModelName', model, ...
                    'MapKeyType', 'msgtype', ...
                    'Recurse', true));
                requiredMsgs = keys(map);
                for j=1:numel(requiredMsgs)
                    if ~isKey(allMsgsMap, requiredMsgs{j})
                        allMsgsMap(requiredMsgs{j}) = map(requiredMsgs{j});
                    end
                end
            end
        end

        
        function msgTypes = getBlockLevelMessageTypesInModel(model)
            %getBlockLevelMessageTypesInModel Get all message types used in model
            %   Please note that this includes any ROS service requests or
            %   response message types.
            validateattributes(model, {'char'}, {'nonempty'});
            blockMsgTypes = robotics.slros.internal.bus.Util.getROSBlocksInModel(model);
            msgTypes = unique( blockMsgTypes );
        end

        function [topLevelMsgTypes, topLevelSvcTypes, ...
                pubSubMsgBlockList, paramBlockList, ...
                imageBlockList, timeBlockList, ...
                svcCallBlockList, logfileBlockList] = getROSBlocksInModel(model)
            %getROSBlocksInModel Get a list of ROS blocks and associated message types
            %   Note that the entries in TOPLEVELMSGTYPES and TOPLEVELSVCTYPES 
            %   might not be unique.
            
            validateattributes(model, {'char'}, {'nonempty'});
            
            topLevelMsgTypes = {};
            topLevelSvcTypes = {};
            
            % Find Publish, Subscribe, and Blank Message Blocks
            pubSubMsgBlockList = ...
                robotics.slros.internal.bus.Util.listBlocks(model, ...                
                ['(' ...
                robotics.slros.internal.block.PublishBlockMask.MaskType, '|', ...
                robotics.slros.internal.block.SubscribeBlockMask.MaskType, '|', ...
                robotics.slros.internal.block.MessageBlockMask.MaskType ...
                ')']);
            if ~isempty(pubSubMsgBlockList)
                topLevelMsgTypes = [topLevelMsgTypes; get_param(pubSubMsgBlockList,'messageType')];
            end
            
            % Find Parameter Blocks
            paramBlockList = ...
                robotics.slros.internal.bus.Util.listBlocks(model, ...
                ['(' ...
                robotics.slros.internal.block.SetParameterBlockMask.MaskType, '|', ...
                robotics.slros.internal.block.GetParameterBlockMask.MaskType ...
                ')']);
            
            % Find Read Image Blocks
            imageBlockList = ...
                robotics.slros.internal.bus.Util.listBlocks(model, ...
                robotics.slros.internal.block.ReadImageBlockMask.MaskType);
            
            % Find Current Time Blocks
            timeBlockList = ...
                robotics.slros.internal.bus.Util.listBlocks(model, ...
                robotics.slros.internal.block.CurrentTimeBlockMask.MaskType);  
            hasBusOutput = cellfun(@(block) strcmp(get_param(block, 'OutputFormat'), 'bus'), timeBlockList);
            if any(hasBusOutput)
                topLevelMsgTypes = [topLevelMsgTypes; robotics.slros.internal.bus.Util.TimeMessageType];
            end
            
            % Find Service Call Blocks
            svcCallBlockList = ...
                robotics.slros.internal.bus.Util.listBlocks(model, ...
                robotics.slros.internal.block.ServiceCallBlockMask.MaskType);  
            
            if ~isempty(svcCallBlockList)
                % We need two message types for each service.
                topLevelSvcTypes = get_param(svcCallBlockList, 'serviceType');
                topLevelMsgTypes = [topLevelMsgTypes; ...
                    strcat(topLevelSvcTypes,'Request');
                    strcat(topLevelSvcTypes,'Response')];
            end
            
            % Find Logfile Blocks
            logfileBlockList = ...
                robotics.slros.internal.bus.Util.listBlocks(model, ...                
                ['(' ...
                robotics.slros.internal.block.ReadDataBlockMask.MaskType ...
                ')']);
            if ~isempty(logfileBlockList)
                % Only append messages if message type is set
                logfileMsgTypes = get_param(logfileBlockList,'msgType');
                logfileMsgTypes = logfileMsgTypes(~cellfun(@isempty, logfileMsgTypes));
                topLevelMsgTypes = [topLevelMsgTypes; logfileMsgTypes];
            end
        end
        
        function blockList = listBlocks(model, maskType)
            %listBlocks List blocks of a specific mask type in a model
            %   Note that MASKTYPE can contain regular expressions, e.g.
            %   'ROS (Publish|Subscribe)'.
            %   BLOCKLIST is returned as a column vector
            
            lbdata = libinfo(bdroot(model), ...
                'LookUnderMasks', 'all', ...
                'Regexp', 'on', ...
                'MaskType', maskType);
            blockList = {lbdata(:).Block};
            blockList = blockList(:);
        end
                
        
        function clearSLBusesInGlobalScope(model)
            robotics.slros.internal.evalinGlobalScope(model, ['clear ' robotics.slros.internal.bus.Util.BusNamePrefix '*']);
        end
      
        
        function bus = getBusObjectFromBusName(busName, model)
            bus = robotics.slros.internal.evalinGlobalScope(model, busName);
        end
                
        
        function [bus,busName] = getBusObjectFromMsgType(rosMsgType, model)
            busName = robotics.slros.internal.bus.Util.createBusIfNeeded(rosMsgType, model);
            bus = robotics.slros.internal.evalinGlobalScope(bdroot(model), busName);
        end
        
        
        function busname = getBusNameFromDataTypeStr(dataTypeStr)
            matches = regexp(dataTypeStr, 'Bus:[ ]\s*(.*)', 'tokens');
            if ~isempty(matches)
                busname = matches{1}{1};
            else
                busname = '';
            end
        end
        
        
        function [busExists,busName] = checkForBus(rosMsgType, model)
            busName = robotics.slros.internal.bus.Util.rosMsgTypeToBusName(rosMsgType, model);
            busExists = robotics.slros.internal.existsInGlobalScope(bdroot(model), busName);
        end

        
        function busName = createBusIfNeeded(rosMsgType, model)
            validateattributes(rosMsgType, {'char'}, {'nonempty'});
            validateattributes(model, {'char'}, {});
            
            [busExists,busName] = robotics.slros.internal.bus.Util.checkForBus(rosMsgType, model);
            if busExists
                return;
            end            
            
            % If message class does not exist, rosmessage will error
            % (robotics:ros:message:NoMatlabClass).
            emptyRosMsg = robotics.slros.internal.bus.Util.newMessageFromSimulinkMsgType(rosMsgType);
            
            robotics.slros.internal.bus.createBusDefnInGlobalScope(emptyRosMsg, model);
        end
                
        
        %%
        function [datatype, busName, msgType] = rosTimeToDataTypeStr(rosClassName, model)
            msgType = robotics.slros.internal.bus.Util.rosTimeToQuasiMsgType(rosClassName);
            [datatype, busName] = robotics.slros.internal.bus.Util.rosMsgTypeToDataTypeStr(msgType, model);
        end
                
        
        function quasiMsgType = rosTimeToQuasiMsgType(rosClassName)
            entity = robotics.slros.internal.ROSUtil.getTimeEntityType(rosClassName);
            if ~isempty(entity)
                quasiMsgType = [robotics.slros.internal.bus.Util.TimePackage ...
                    '/' entity]; % can be Time or Duration
            else
                assert(false, 'Unexpected classname: %s', rosClassName);
            end        
        end
        
        function rosMsg = newMessageFromSimulinkMsgType(rosMsgType)
            %newMessageFromSimulinkMsgType Create a new ROS message from message type
            %   Please note that ROSMSGTYPE could refer to a standard ROS
            %   message type, or to a pseudo-message type used only in
            %   Simulink, for example time and duration types.
            
            if strcmp(rosMsgType, robotics.slros.internal.bus.Util.TimeMessageType)
                rosMsg = robotics.ros.msg.Time;
            elseif strcmp(rosMsgType, robotics.slros.internal.bus.Util.DurationMessageType)
                rosMsg = robotics.ros.msg.Duration;
            else
                rosMsg = rosmessage(rosMsgType);
            end
        end
        
        
        %%
        function [datatype,busName] = rosMsgTypeToDataTypeStr(rosMsgType, model)
            % This is used wherever a Simulink DataTypeStr is required
            % (e.g., for specifying the output datatype of a Constant block)
            % ** DOES NOT CREATE A BUS **
            busName = robotics.slros.internal.bus.Util.rosMsgTypeToBusName(rosMsgType, model);
            datatype = ['Bus: ' busName];
        end
                   
        
        function busName = rosMsgTypeToBusName(rosMsgType, model)
            %
            % rosMsgTypeToBusName(MSGTYPE,MODEL) returns the bus name
            % corresponding to a ROS message type MSGTYPE (e.g.,
            % 'std_msgs/Int32') and a Simulink model MODEL. The function
            % uses the following rules:
            % 
            % Rule 1 - Generate a name using the format:
            %    SL_Bus_<modelname>_<msgtype>
            %
            % Rule 2 - If the result of Rule 1 is longer than 60
            % characters, use the following general format: 
            %    SL_Bus_<modelname(1:25)>_<msgtype(end-25:end)>_<hash>
            % where <hash> is a base 36 hash of the full name (output of
            % rule #1). 
            %
            % ** THIS FUNCTION DOES NOT CREATE A BUS OBJECT **
            
            validateattributes(rosMsgType, {'char'}, {'nonempty'});
            assert(ischar(model));
            
            if isempty(model)
                modelnameSuffix = '';
            else
                modelnameSuffix = '_';
            end
            
            maxlen = 60; choplen=25;
            assert(maxlen <= namelengthmax);
            
            busName = [robotics.slros.internal.bus.Util.BusNamePrefix ...
                       model modelnameSuffix rosMsgType];                        
            if length(busName) < maxlen
                busName = matlab.lang.makeValidName(busName, 'ReplacementStyle', 'underscore');                
            else 
                % add a trailing hash string (5-6 chars) to make the busname unique 
                hashStr = robotics.slros.internal.bus.Util.hashString(busName);
                
                idx = strfind(rosMsgType, '/');
                if isempty(idx)
                    idx = 0;
                else
                    idx = idx(1);
                end
                model = model(1:min(end,choplen));  % get first 25 chars
                rosMsgType = rosMsgType(idx+1:min(idx+choplen,end));  % get first 25 chars
                busName = matlab.lang.makeValidName(...
                    [robotics.slros.internal.bus.Util.BusNamePrefix ...
                     model modelnameSuffix rosMsgType '_' hashStr], ...
                    'ReplacementStyle', 'underscore');
            end
        end
        
        function [srvReqBusName, srvRespBusName] = rosServiceTypeToBusNames(rosSrvType, model)
            %rosServiceTypeToBusNames - Get the bus names corresponding to service type
            %   Note that there are two buses associated with each service
            %   type: one bus for the request and one bus for the response.
            
            srvReqBusName = robotics.slros.internal.bus.Util.rosMsgTypeToBusName(strcat(rosSrvType,'Request'), model);
            srvRespBusName = robotics.slros.internal.bus.Util.rosMsgTypeToBusName(strcat(rosSrvType,'Response'), model);
        end           
        
        function [srvReqBusType, srvReqBusName, srvRespBusType, srvRespBusName] = ...
            rosServiceTypeToDataTypeStr(rosSrvType, model)
            %rosServiceTypeToDataTypeStr - Get the data type strings corresponding to service type
            %   Note that there are two buses associated with each service
            %   type: one bus for the request and one bus for the response.
            
            rosReqMessageType = strcat(rosSrvType, 'Request');
            [srvReqBusType,srvReqBusName] = robotics.slros.internal.bus.Util.rosMsgTypeToDataTypeStr(rosReqMessageType, model);
            rosRespMessageType = strcat(rosSrvType, 'Response');
            [srvRespBusType, srvRespBusName] = robotics.slros.internal.bus.Util.rosMsgTypeToDataTypeStr(rosRespMessageType, model);            
        end    
                        
    end

    
    methods(Static, Access=private)
        
        function hashStr = hashString(str)
            javaStr = java.lang.String(str);
            hashStr = lower(dec2base(uint64(abs(javaStr.hashCode)), 36)); % usually 5-6 chars
        end
 
        
    end
        
end

