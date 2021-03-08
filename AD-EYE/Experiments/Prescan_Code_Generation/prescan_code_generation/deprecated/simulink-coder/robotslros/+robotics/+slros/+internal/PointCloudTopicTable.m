classdef PointCloudTopicTable < robotics.slros.internal.TopicTable 
    %This class is for internal use only. It may be removed in the future.
    
    %PointCloudTopicTable
    
    %   Copyright 2017 The MathWorks, Inc.
    
    properties (Constant)
        %AdditionalColumns
        AdditionalColumns = {'PointCloudSize'}
        
        %ValidMessageTypes
        ValidMessageTypes = {'sensor_msgs/PointCloud2'}
        
        %NoTopicsAvailableMsgId - MsgID to use if there are no topics
        %   advertised for any of the ValidMessageTypes.
        NoTopicsAvailableMsgId = ...
            'robotics:robotslros:topicselector:NoPointCloudTopicsAvailable'
    end
    
    methods
        
        function obj = PointCloudTopicTable(varargin)
            %PointCloudTopicTable Constructor
            %   OBJ = PointCloudTopicTable(NODE) creates an PointCloudTopicTable
            %   using the robotics.ros.Node object, NODE. The table will stop
            %   updating and kill all remaining subscribers if 30 seconds elapse
            %   without a message being received by any subscriber.  If no point
            %   cloud topics are found on the ROS network, the constructor will
            %   error out.
            %
            %   OBJ = PointCloudTopicTable(NODE, infoChangeFcn) creates an
            %   PointCloudTopicTable that invokes infoChangeFcn each time the
            %   table is updated.
            %
            %   OBJ = PointCloudTopicTable(NODE, infoChangeFcn, TIMEOUT) creates
            %   an PointCloudTopicTable that stops updating and kills all
            %   subscribers if TIMEOUT seconds elapse without a message being
            %   received by any subscriber.
            %
            %   OBJ = PointCloudTopicTable(NODE, infoChangeFcn, TIMEOUT,
            %   allowEmptyTable) creates an PointCloudTopicTable with zero rows
            %   if allowEmptyTable is true and no point cloud topics are found.
            obj = obj@robotics.slros.internal.TopicTable(varargin{:});
        end
        
        function [status, cloudSize] = extractData(obj,msg)
            [cloudSize, hasField, hasCorrectDataType] = ...
                extractPointCloud2Data(obj, msg);
            
            cloudSize = sprintf('[%d, %d]', cloudSize);
            statusFields = string.empty();
            if ~(hasField.x && hasField.y && hasField.z)
                status = message('robotics:ros:pointcloud:InvalidXYZData').getString();
                cloudSize = obj.UnknownValueString;
                return;
            end
            if ~(hasCorrectDataType.x && hasCorrectDataType.y && hasCorrectDataType.z)
                status = message('robotics:ros:pointcloud:InvalidXYZType','float32').getString();
                cloudSize = obj.UnknownValueString;
                return;
            end
            statusFields(end+1) = "xyz";
            if hasField.rgb
                statusFields(end+1) = "rgb";
            end
            if hasField.intensity
                statusFields(end+1) = "intensity";
            end
            status = char( ...
                message('robotics:robotslros:topicselector:Valid').string ...
                + " (" + join(statusFields,", ") + ")");
        end
        
        function [cloudSize, hasField, hasCorrectDataType] = ...
                extractPointCloud2Data(~, msg)
            cloudSize = [msg.Height, msg.Width];
            fieldNames = lower({msg.Fields.Name});
            for name = ["x", "y", "z", "rgb", "intensity"]
                [hasField.(char(name)), fieldIdx] = ismember(name, fieldNames);
                if name == "rgb"
                    allowedDataTypes = [ ...
                        robotics.ros.msg.sensor_msgs.internal.PointCloud2Types.matlabToROSType('single'), ...
                        robotics.ros.msg.sensor_msgs.internal.PointCloud2Types.matlabToROSType('uint32'), ...
                        robotics.ros.msg.sensor_msgs.internal.PointCloud2Types.matlabToROSType('int32')];
                else
                    allowedDataTypes = ...
                        robotics.ros.msg.sensor_msgs.internal.PointCloud2Types.matlabToROSType('single');
                end
                if hasField.(char(name))
                    hasCorrectDataType.(char(name)) = ...
                        ismember(msg.Fields(fieldIdx).Datatype, allowedDataTypes);
                else
                    hasCorrectDataType.(char(name)) = false;
                end
            end
        end        
    end
end
