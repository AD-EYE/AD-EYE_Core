classdef PublishBlockMask < robotics.slros.internal.block.CommonMessageMask
    %This class is for internal use only. It may be removed in the future.
    
    %PublishBlockMask - Block mask callbacks for Publish block
    
    %   Copyright 2014-2018 The MathWorks, Inc.
    
    properties (Constant)
        %MaskType - Type of block mask
        %   Retrieve is with get_param(gcb, 'MaskType')
        MaskType = 'ROS Publish'
        
        MaskParamIndex = struct( ...
            'TopicSourceDropdown', 1, ...
            'TopicEdit', 2, ...
            'MessageTypeEdit', 3 ...
            );
        
        MaskDlgIndex = struct( ...
            'TopicSelect', [2 1 3], ...  % Tab Container > "Main" tab > Topic Select Button
            'MessageTypeSelect', [2 1 5] ... % Tab Container > "Main" tab > Msg Select Button
            );
        
        SysObjBlockName = 'SinkBlock';        
    end
    
    methods
        
        function updateSubsystem(obj, block)
            sysobj_block = [block '/' obj.SysObjBlockName];
            sigspec_block = [block '/SignalSpecification'];
            
            % Do not canonicalize the topic name (i.e., if user entered
            % "foo", don't convert it to "/foo"). This enables user to
            % control whether to have a relative or absolute topic name in
            % generated code.
            
            topic = get_param(block, 'topic');
            rosMessageType = get_param(block, 'messageType');
            [busDataType, slBusName] = robotics.slros.internal.bus.Util.rosMsgTypeToDataTypeStr(rosMessageType, bdroot(block));
            
            % note: we use the block id of the parent, not the sys_obj block
            blockId = robotics.slros.internal.block.getCppIdentifierForBlock(block, 'Pub_'); 
            modelName = bdroot(block);
            
            set_param(sysobj_block, 'SLBusName', slBusName);
            set_param(sysobj_block, 'ROSMessageType', rosMessageType);
            set_param(sysobj_block, 'ROSTopic', topic);
            set_param(sysobj_block, 'ModelName', modelName);
            set_param(sysobj_block, 'BlockId', blockId);
            set_param(sigspec_block, 'OutDataTypeStr', busDataType);                        
        end
        
    end    
        
    methods(Static)
        
        function dispatch(methodName, varargin)
            obj = robotics.slros.internal.block.PublishBlockMask();
            obj.(methodName)(varargin{:});
        end
        
    end        
end
