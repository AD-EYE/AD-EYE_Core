classdef CurrentTimeBlockMask
    %This class is for internal use only. It may be removed in the future.
    
    %CurrentTimeBlockMask - Block mask callbacks for Current Time ROS block
    
    %   Copyright 2018 The MathWorks, Inc.

    properties (Constant)
        %MaskType - Type of block mask
        %   Retrieve is with get_param(gcb, 'MaskType')
        MaskType = 'robotics.slros.internal.block.CurrentTime'
    end
    
    methods
        
        function maskInitialize(obj, block) %#ok<INUSD>
            %maskInitialize Initialize the block mask
            % It is invoked when the user: 
            % * Changes the value of a mask parameter by using the block dialog box or set_param.
            % * Changes any of the parameters that define the mask
            % * Causes the icon to be redrawn
            % * Copies the block
        end   
        
        function initFcn(~, block)
            %initFcn Called when the model initializes the block
            
            modelName = bdroot(block);
            
            % Do not mark the model dirty when mode name is updated, since
            % that information is only transient.
            preserveDirty = Simulink.PreserveDirtyFlag(bdroot(block),'blockDiagram');
            set_param(block, 'ModelName', modelName);
            delete(preserveDirty);
        end
        
        function modelCloseFcn(~, block)
            %modelCloseFcn Called when the model is closed
            
            % Delete all message buses for this particular model
            robotics.slros.internal.bus.clearBusesOnModelClose(block);
        end
        
    end  
        
    methods(Static)
        
        function dispatch(methodName, varargin)
            %dispatch Dispatch to static methods in this class
            obj = robotics.slros.internal.block.CurrentTimeBlockMask;
            obj.(methodName)(varargin{:});
        end
        
    end        
end
