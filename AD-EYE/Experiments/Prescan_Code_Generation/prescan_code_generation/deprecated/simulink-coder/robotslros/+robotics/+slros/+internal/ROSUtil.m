classdef ROSUtil
    %This class is for internal use only. It may be removed in the future.
    
    %ROSUTIL - Utility functions for working with MATLAB ROS messages    
    
    %   Copyright 2014-2018 The MathWorks, Inc.
    
    
    methods (Static)
        function out = isROSClass(classname)
            out = strncmp(classname, 'robotics.ros.', 13);
        end
        
        
        function out = isROSMsgObj(rosobj)
            out = isa(rosobj, 'robotics.ros.Message');
        end        
        
        function out = isROSTimeEntityObj(rosobj)
            out = isa(rosobj, 'robotics.ros.msg.internal.TimeEntity');
        end
        
        function isFixed = isFixedSizeArray(msgType, rosPropName)
            %isFixedSizeArray Determine if a property in a message is a fixed-size array
            %   MSGTYPE is the ROS message type, for example
            %   'std_msgs/String'
            %   ROSPROPNAME is the property name in the original msg file
            %   (not the MATLAB-yfied version), for example 'data'.           
            
            % Use persistent variable for parsed message definitions, since
            % the process is expensive.
            persistent parsedArrayMap
            if isempty(parsedArrayMap)
                parsedArrayMap = containers.Map;
            end                        
            
            isFixed = false;
            
            if strcmp(msgType, robotics.slros.internal.bus.Util.TimeMessageType) || ...
                    strcmp(msgType, robotics.slros.internal.bus.Util.DurationMessageType)
                return;
            end
            
            if isKey(parsedArrayMap, msgType)
                % This is fast. Simply use the already parsed list of
                % arrays.
                parsedArrays = parsedArrayMap(msgType);
            else
                % This is more expensive. Have to parse the message
                % definition.
                
                % Get message definition
                fac = robotics.ros.internal.NodeConfigurationFactory;
                nodeConfig = fac.newPrivate;
                msgDef = char(com.mathworks.toolbox.robotics.ros.message.MessageInfo.getDefinition(nodeConfig, msgType));
                
                % Parse definition to extract type of all properties
                parser = robotics.ros.msg.internal.gen.DefaultMessageParser;
                parser.parseDefinition(msgType, msgDef);
                                
                parsedArrays = parser.Lists;
                parsedArrayMap(msgType) = parsedArrays;
            end
            
            if isempty(parsedArrays)
                % This message type doesn't have any arrays, so return.
                return;
            end
            
            % Determine if property is a fixed-size array
            propIdx = ismember(parsedArrays.FieldName, rosPropName);
            if any(propIdx)
                % Property name found. Extract the associated array size
                % If size is -1 it's variable-sized. If size is another
                % number, it's fixed-size.
                arraySize = parsedArrays.ArraySize(propIdx);
                assert(numel(arraySize) == 1);
                
                % Found a fixed-size array property if arraySize is a
                % positive scalar.
                isFixed = arraySize{1} ~= -1;
            end
        end
        
        function obj = getStdStringObj()
            obj = robotics.ros.msggen.std_msgs.String;
        end
        
        function out = isStdEmptyMsgType(msgType)
            isEmptyMsg = strcmpi(msgType, 'std_msgs/Empty');
            isEmptySrvMsg = any( strcmpi(msgType, {['std_srvs/Empty', 'Request'], ['std_srvs/Empty', 'Response']}) );
            out = any([isEmptyMsg, isEmptySrvMsg]);
        end
        
        
        % Note that following won't work (messages 
        % are derived from robotics.ros.Message so ISA works
        % but classname comparison will not)
        %
        % function out = isROSMsgClass(classname)
        %      out = strcmp(classname, 'robotics.ros.Message');
        %  end
        %
        % function out = isROSTimeEntityClass(classname)
        %    out = strcmp(classname, 'robotics.ros.msg.TimeEntity');
        % end          
        
        function out = isROSObj(rosobj)
            out = isa(rosobj, 'robotics.ros.Message') || isa(rosobj, 'robotics.ros.msg.internal.TimeEntity');
        end
        
        
        function entity = getTimeEntityType(classname)
              switch classname
                  case 'robotics.ros.msg.Time'
                      entity = 'Time';
                  case 'robotics.ros.msg.Duration'
                      entity = 'Duration';
                  otherwise
                      entity = '';
              end % switch
        end % function
                
        
        function [propList, rosPropList] = getPropertyLists(rosmsg)
            mc = metaclass(rosmsg);
            % these lists do not include constants
            idx1 = strcmp({mc.PropertyList.Name}, 'PropertyList');
            idx2 = strcmp({mc.PropertyList.Name}, 'ROSPropertyList');
            propList = mc.PropertyList(idx1).DefaultValue;
            rosPropList = mc.PropertyList(idx2).DefaultValue;
        end
        
        
        function nonServiceTypes = getMessageTypesWithoutServices()
            % getMessageTypesWithoutServices returns the list of available 
            % ROS message types, excluding service-related types.
            
            % Rationale:
            % rostype.getMessageList includes types like the following, 
            % which are only used by services.
            %   1. gazebo_msgs/JointRequest
            %   2. gazebo_msgs/JointRequestRequest
            %   3. gazebo_msgs/JointRequestResponse
            %
            % (1) is actually an alias for (2), i.e., 
            % rosmessage('gazebo_msgs/JointRequest') returns a message of
            % type gazebo_msgs/JointRequestRequest. In addition, some of
            % the service response messages are empty. Both of these 
            % characteristics cause issues in Simulink ROS, so it is 
            % preferable to filter out the service types.
            
            basicServiceTypes = rostype.getServiceList;
            allServiceTypes = [...
                basicServiceTypes;
                strcat(basicServiceTypes, 'Request'); 
                strcat(basicServiceTypes, 'Response')];
            
            % Note: SETDIFF output is automatically sorted
            nonServiceTypes = setdiff(rostype.getMessageList, allServiceTypes);
        end
    end
    
end
