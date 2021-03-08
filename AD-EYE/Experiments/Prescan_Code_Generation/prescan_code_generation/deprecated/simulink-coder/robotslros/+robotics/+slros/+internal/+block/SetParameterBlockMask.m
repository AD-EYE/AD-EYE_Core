classdef SetParameterBlockMask < robotics.slros.internal.block.CommonParameterMask
    %This class is for internal use only. It may be removed in the future.
    
    %SetParameterBlockMask Block mask callbacks for SetParameter block
    %   Note that we are using a mask-on-mask on top of the SetParameter
    %   system object. This has the advantage of easy customization.
    
    %   Copyright 2014-2018 The MathWorks, Inc.
    
    properties (Constant)
        %MaskType - Type of block mask
        %   Retrieve is with get_param(gcb, 'MaskType')
        MaskType = 'ROS Set Parameter'
        
        %MaskParamIndex - Struct specifying index of various parameters
        MaskParamIndex = struct( ...
            'ParamSourceDropdown', 1, ...
            'ParamNameEdit', 2, ...
            'ParamDataTypeDropdown', 3 ...
            );
        
        %MaskParamIndex - Struct specifying index of various widgets
        MaskDlgIndex = struct( ...
            'ParamSelect', [2 1 3] ...  % "Parameters" Container > "ROS Parameter" tab > "Select" Button
            )
    
        SysObjBlockName = '';
    end
    
    methods
        function updateSubsystem(~, block)
            %updateSubsystem Update the Block ID and Model Name
            blockId = robotics.slros.internal.block.getCppIdentifierForBlock(block, 'ParamSet_');
            modelName = bdroot(block);
            
            set_param(block, 'ModelName', modelName);
            set_param(block, 'BlockId', blockId);
        end
    end    
        
    methods(Static)        
        function dispatch(methodName, varargin)
            %dispatch Static dispatch method for callbacks
            
            obj = robotics.slros.internal.block.SetParameterBlockMask();
            obj.(methodName)(varargin{:});
        end
        
    end    
end
