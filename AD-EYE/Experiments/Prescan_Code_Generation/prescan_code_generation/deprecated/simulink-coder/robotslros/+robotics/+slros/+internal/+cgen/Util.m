classdef Util
    %This class is for internal use only. It may be removed in the future.
    
    %CGEN.UTIL - Utility functions for generating ROS C++ code
    
    %   Copyright 2014-2018 The MathWorks, Inc.
    
    methods (Static)

        function nativeStr = cleanupUnicodeAndWhitespace(str)
            % cleanupUnicodeAndWhitespace(S) converts an arbitrary Unicode
            % string S to a  to a printable ASCII string without newlines.
            %
            % Rationale: Simulink subsystem and block names can have
            % arbitrary characters (including Unicode characters, newlines
            % and tabs), and these can be included in comment strings that
            % will be printed to the generated C++ files.
            
            nativeStr = char(unicode2native(str, 'US-ASCII'));
            % convert any whitespace sequences to a single space
            nativeStr = regexprep(nativeStr, '\s+', ' ');            
            % keep only printable characters
            nativeStr = nativeStr(isstrprop(nativeStr, 'print'));
        end
        
        
        function [cppRosClass, msgType] = rosObjToCppClass(rosObj)
            msgIsRosTimeEntity = robotics.slros.internal.ROSUtil.isROSTimeEntityObj(rosObj);
            msgIsRosMessage = robotics.slros.internal.ROSUtil.isROSMsgObj(rosObj);
            className = class(rosObj);
            
            if msgIsRosTimeEntity
                msgType = robotics.slros.internal.bus.Util.rosTimeToQuasiMsgType(className);
                timeEntity = robotics.slros.internal.ROSUtil.getTimeEntityType(className);
                cppRosClass = ['ros::' timeEntity];
            elseif msgIsRosMessage
                msgType = rosObj.MessageType;
                cppRosClass = robotics.slros.internal.cgen.Util.rosMsgTypeToCppClass(msgType);
            else
                assert(false, 'Unknown class name: %s', class(rosObj));
            end
        end        
        
        
        function cppRosClass = rosMsgTypeToCppClass(msgType)
            %rosMsgTypeToCppClass Convert ROS message or service type to C++ class
            %   Only works with "real" ROS Message and Service types (not Time Entities)
            
            validateattributes(msgType, {'char'}, {'nonempty'});
            % msgType should have ROS msg type format (.../...)
            assert(contains(msgType, '/'));
            cppRosClass = strrep(msgType,'/','::');
        end          
        
        
        function header = rosCppClassToCppMsgHeader(cppClass)
            validateattributes(cppClass, {'char'}, {'nonempty'});
            assert(contains(cppClass, '::'));
            header = [strrep(cppClass,'::', '/') '.h'];
        end
    end
            
end
