classdef (Abstract) ReadXBase <  matlab.System & ...
        matlab.system.mixin.Propagates...
        & matlab.system.mixin.internal.CustomIcon
    %This class is for internal use only. It may be removed in the future.
        
    %ReadXBase Abstract base class for ROS bus -> array signal blocks
    
    %   Copyright 2017-2018 The MathWorks, Inc.
    
    %#codegen
    
    properties(Nontunable, Logical)
        %ShowErrorCodeOutput Show error code output port
        ShowErrorCodeOutput = true;
        
        %VariableSizeOutputs - Output variable-size signals
        VariableSizeOutputs = false;
    end
    
    properties(Abstract, Access=protected)        
        %IconInfo - Block icon information
        IconInfo
    end
        
    properties (Abstract, Constant, Access = {...
            ?robotics.slros.internal.block.ReadXBase, ...
            ?matlab.unittest.TestCase})        
       
        %IconName - Name of block icon
        IconName
        
        %ValidMessageTypes - Message types that are valid inputs to block
        ValidMessageTypes
        
        %InvalidTypeID - Error ID if an invalid message is used as input
        InvalidTypeID
    end
    
    properties(Constant,Access=private)
        % Name of header file with declarations for variables and types
        % referred to in code emitted by setupImpl and stepImpl.
        HeaderFile = robotics.slros.internal.cgen.Constants.InitCode.HeaderFile
    end
    
    methods (Access = protected)
        %% Common functions
        function setupImpl(obj)
            if coder.target('MATLAB')
                % Executing in MATLAB interpreted mode
                % No setup needed
            elseif coder.target('RtwForRapid')
                % Rapid Accelerator. In this mode, coder.target('Rtw')
                % returns true as well, so it is important to check for
                % 'RtwForRapid' before checking for 'Rtw'
                coder.internal.error('robotics:robotslros:sysobj:RapidAccelNotSupported', ['ROS ', obj.IconName, ' Block']);
            elseif coder.target('Rtw')
                % 'Rtw' is executed during model build
                % Include the header file with the C++ declarations
                coder.cinclude(obj.HeaderFile);
            elseif  coder.target('Sfun')
                % 'Sfun'  - SimThruCodeGen target
                % Do nothing. MATLAB System block first does a pre-codegen
                % compile with 'Sfun' target, & then does the "proper"
                % codegen compile with Rtw or RtwForRapid, as appropriate.
            else
                % 'RtwForSim' - ModelReference SIM target
                % 'MEX', 'HDL', 'Custom' - Not applicable to MATLAB System block
                coder.internal.error('robotics:robotslros:sysobj:UnsupportedCodegenMode', coder.target);
            end
        end
        
        
        function out = constantSampleTimePropagationImpl(~)
            % Enable this system object to inherit constant ('inf') sample times
            out = 'Allow';
        end
        
        %% validation of the input to Step functions
        
        function validateInputsImpl(obj,varargin)
            %validateInputsImpl validate the inputs step*h == data length etc
            %   Only valid message types are allowed.
            if coder.target('MATLAB')
                inType = obj.propagatedInputDataType(1);
                validTypes = cellfun(@(type) robotics.slros.internal.bus.Util.rosMsgTypeToBusName(type, bdroot(gcb)), ...
                    obj.ValidMessageTypes, ...
                    'UniformOutput', false);
                
                % Display an error if input message type is not supported
                if ~ismember(inType, validTypes)
                    error(message(obj.InvalidTypeID, strjoin(obj.ValidMessageTypes, ', ')));
                end
            end
        end
        
        %% Output configuration
        
        function varargout = getOutputSizeImpl(obj)
            %getOutputSizeImpl Return Size for each output port
            %   It is set to the maximum allowed size specified by the User
            varargout = cell(1, nargout);
            if obj.ShowErrorCodeOutput
                varargout{end} = 1;
            end
            
        end
        
        function varargout = getOutputDataTypeImpl(obj)
            %getOutputDataTypeImpl Return data type for each output port
            varargout = cell(1, nargout);
            if obj.ShowErrorCodeOutput
                varargout{end} = 'uint8';
            end
        end
        
        function varargout = isOutputComplexImpl(obj)
            %isOutputComplexImpl Return true for each output port with complex data
            varargout = cell(1, nargout);
            if obj.ShowErrorCodeOutput
                varargout{end} = false;
            end
        end
        
        function varargout = isOutputFixedSizeImpl(obj)
            %isOutputFixedSizeImpl Return true for each output port with fixed size
            % Converted image is not fixed size
            varargout = cell(1, nargout);
            if obj.ShowErrorCodeOutput
                varargout{end} = true;
            end
        end
        
        %% Input Port and Output port Naming configuration
        
        function varargout = getOutputNamesImpl(obj)
            %getOutputNamesImpl Return output port names for System block
            varargout = cell(1, nargout);
            if obj.ShowErrorCodeOutput
                varargout{end} = 'ErrorCode';
            end
        end
        
        
        %% Display control for Simulink block
        
        function maskDisplay = getMaskDisplayImpl(obj)
            %getMaskDisplayImpl Customize the mask icon display
            %   This method is inherited from matlab.system.mixin.internal.CustomIcon
            %   and allows the customization of the mask display code. Note
            %   that this works both for the base mask and for the
            %   mask-on-mask.
            
            % Construct the input labels based on the number of inputs
            numInputs = obj.getNumInputsImpl;
            [inputNames{1:numInputs}] = obj.getInputNamesImpl;
            
            portLabelText = {};
            for i = 1:length(inputNames)
                portLabelText = [portLabelText ['port_label(''input'', ' num2str(i) ', ''' inputNames{i} ''')']]; %#ok<AGROW>
            end
            
            numOutputs = obj.getNumOutputsImpl;
            [outputNames{1:numOutputs}] = obj.getOutputNamesImpl;
            for i = 1:length(outputNames)
                portLabelText = [portLabelText ['port_label(''output'', ' num2str(i) ', ''' outputNames{i} ''')']]; %#ok<AGROW>
            end
            
            maskDisplay = { ...
                ['color(''white'');', char(10)], ...                                     % Fix min and max x,y co-ordinates for autoscale mask units
                ['plot([100,100,100,100],[100,100,100,100]);', char(10)], ...
                ['plot([0,0,0,0],[0,0,0,0]);', char(10)],...
                'color(''blue'')', ...
                'text(13, 90, ''ROS'', ''horizontalAlignment'', ''right'')', ...
                'color(''black'')', ...
                ['text(52, 60, ''', obj.IconName, ''', ''horizontalAlignment'', ''center'');'], ...
                ['text(52, 12, ''', obj.IconInfo, ''', ''horizontalAlignment'', ''center'');'], ...
                portLabelText{:}};  %#ok<*CHARTEN>
        end
        
        function num = getNumInputsImpl(~)
            %getNumInputsImpl Get number of inputs
            num = 1;
        end
        
        function num = getNumOutputsImpl(obj)
            %getNumOutputsImpl Define number of outputs for system with optional outputs
            
            if obj.ShowErrorCodeOutput
                num = 1;
            else
                num = 0;
            end
        end
        
        function s = saveObjectImpl(obj)
            % Set properties in structure s to values in object obj
            
            % Set public properties and states
            s = saveObjectImpl@matlab.System(obj);
        end

        function loadObjectImpl(obj,s,wasLocked)
            % Set properties in object obj to values in structure s
            
            % Set public properties and states
            loadObjectImpl@matlab.System(obj,s,wasLocked);
        end
        
    end
    
    methods(Access = protected, Static)
        function simMode = getSimulateUsingImpl
            % Return only allowed simulation mode in System block dialog
            simMode = 'Interpreted execution';
        end
        
        function flag = showSimulateUsingImpl
            %showSimulateUsingImpl Do not show simulation execution mode dropdown in block mask
            flag = false;
        end
        
        function group = getOutputPropertyGroup(props)
            %getHiddenPropertyGroup Property group for output settings
            %   Child classes should call this in getPropertyGroupsImpl
            key = 'robotics:robotslros:blockmask:OutputSettingsPrompt';
            propList = [props, {'ShowErrorCodeOutput', 'VariableSizeOutputs'}];
            group = matlab.system.display.Section( ...
                'Title', getString(message(key)), ...
                'PropertyList', propList);
        end
    end
    
end
