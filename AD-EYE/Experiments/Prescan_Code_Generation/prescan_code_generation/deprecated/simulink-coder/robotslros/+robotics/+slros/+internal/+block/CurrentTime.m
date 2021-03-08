classdef CurrentTime < ...
        matlab.System & ...
        matlab.system.mixin.Propagates & ...
        matlab.system.mixin.internal.CustomIcon & ...
        matlab.system.mixin.SampleTime & ...
        robotics.slros.internal.block.mixin.NodeDependent
    
    %This class is for internal use only. It may be removed in the future.
    
    %CurrentTime Return the current ROS time
    %
    %   t = robotics.slros.internal.block.CurrentTime creates a system
    %   object, t, that retrieves the current ROS time on step. If the
    %   /use_sim_time ROS parameter is true, the most recent time from the
    %   /clock topic is returned. Otherwise, step will return the system
    %   time.
    %
    %   The system time in ROS follows the Unix / POSIX time standard. POSIX
    %   time is defined as the time that has elapsed since 00:00:00 Coordinated
    %   Universal Time (UTC), 1 January 1970, not counting leap seconds.
    %
    %   See also rostime.
    
    %   Copyright 2018 The MathWorks, Inc.
    
    %#codegen
    
    properties (Nontunable)
        %OutputFormat - Output format
        %   The output format for the "Time" output.
        %   Default: 'bus'.
        OutputFormat = 'bus'
        
        %SampleTime - Sample time
        %   Default: -1 (inherited)
        SampleTime = -1
    end
    
    properties (Nontunable)                
        %StreamWSVar - Workspace stream
        %   Used to redirect system object to get time from a workspace
        %   variable instead of from ROS network (used for testing only).
        %   The workspace variable should be created like this:
        %
        %   workspaceVar = robotics.slros.internal.sim.TimeListStream;
        %   workspaceVar.TimeList = {rostime(5)};
        %
        %   This capability of using workspace variables is only used in
        %   internal testing, and is not documented for Simulink users.
        StreamWSVar = ''

        %ModelName - Name of model for this block
        ModelName = robotics.slros.internal.block.mixin.NodeDependent.DefaultModelName
    end
    
    properties(Constant, Hidden)
        %OutputFormatSet - Valid dropdown choices for OutputFormat
        OutputFormatSet = matlab.system.StringSet({'bus', 'double'});
    end
    
    properties (Constant, Access=?robotics.slros.internal.block.mixin.NodeDependent)
        %MessageCatalogName - Name of this block used in message catalog
        %   This property is used by the NodeDependent base class to
        %   customize error messages with the block name.
        MessageCatalogName = message("robotics:robotslros:rostime:MaskTitle").getString
    end
    
    properties (Access = ...
            {?robotics.slros.internal.block.CurrentTime, ...
            ?matlab.unittest.TestCase})
        
        %Converter - Message to bus structure converter
        Converter
        
        %SampleTimeHandler - Object for validating sample time settings
        SampleTimeHandler
    end
    
    properties (Constant, Access = ...
            {?robotics.slros.internal.block.CurrentTime, ...
            ?matlab.unittest.TestCase})
        
        %IconName - Name of block icon
        IconName = "Current" + newline + "Time"
        
        %TimeMessageType - Pseudo Message Type for time structure
        TimeMessageType = string(robotics.slros.internal.bus.Util.TimeMessageType)
    end
    
    properties (Access = protected, Transient)
        %TimeStream - Handle to object that implements robotics.slros.internal.sim.TimeStream
        %   This can be a sim.TimeNetStream (for getting time off
        %   the ROS network) or sim.TimeListStream (for getting messages
        %   from an object in the global scope; used in conjunction with
        %   StreamWsVar property)
        TimeStream
    end
    
    methods
        function obj = CurrentTime(varargin)
            %CurrentTime Standard constructor
            
            % Support name-value pair arguments when constructing the object.
            setProperties(obj, nargin, varargin{:});
            
            % Initialize sample time validation object
            obj.SampleTimeHandler = robotics.slcore.internal.block.SampleTimeImpl;
        end
        
        function set.SampleTime(obj, sampleTime)
            %set.SampleTime Validate sample time specified by user
            obj.SampleTime = obj.SampleTimeHandler.validate(sampleTime); %#ok<MCSUP>
        end
        
    end
    
    methods(Access = protected)
        function setupImpl(obj)
            %setupImpl Perform one-time setup of system object
            
            obj.setupNodeDependent;
            
            if coder.target("MATLAB")
                % Execute in interpreted mode
                
                % Initialize converter to bus structure
                obj.createBusIfNeeded;
                obj.Converter = robotics.slros.internal.sim.ROSMsgToBusStructConverter(...
                    char(obj.TimeMessageType), char(obj.ModelName));
            elseif coder.target("Rtw")
                % Execute in ROS node generation
                
                headerFile = coder.const(robotics.slros.internal.cgen.Constants.InitCode.HeaderFile);
                coder.cinclude(headerFile);
            end  
        end
        
        function timeOut = stepImpl(obj)
            %stepImpl Retrieve and output current ROS time
            
            % Preallocate output
            if obj.OutputFormat == "double"
                timeOut = double(0.0);
            else
                timeOut.Sec = 0.0;
                timeOut.Nsec = 0.0;
            end
            
            if coder.target("MATLAB")
                % Execute in interpreted mode
                
                currentTime = obj.TimeStream.getTime;
                
                if obj.OutputFormat == "double"
                    timeOut = seconds(currentTime);
                else
                    timeOut = obj.Converter.convert(currentTime);
                end
            elseif coder.target("Rtw")
                % Execute in ROS node generation
                
                if obj.OutputFormat == "double"
                    coder.ceval("currentROSTimeDouble", coder.wref(timeOut));
                else
                    coder.ceval("currentROSTimeBus", coder.wref(timeOut));
                end               
            end
        end
        
        function releaseImpl(obj)
            %releaseImpl Release all resources
            
            obj.releaseNodeDependent;            
        end
    end
    
    methods (Access = protected)
        function num = getNumInputsImpl(~)
            %getNumInputsImpl Define total number of inputs
            %   Since this is a source block, it has no input ports.
            num = 0;
        end
        
        function num = getNumOutputsImpl(~)
            %getNumOutputsImpl Define total number of outputs
            num = 1;
        end
        
        function timeOutputName = getOutputNamesImpl(~)
            %getOutputNamesImpl Return output port names for System block
            timeOutputName = "Time";
        end
        
        function maskDisplay = getMaskDisplayImpl(obj)
            %getMaskDisplayImpl Customize the mask icon display
            %   This method is inherited from matlab.system.mixin.internal.CustomIcon
            %   and allows the customization of the mask display code. Note
            %   that this works both for the base mask and for the
            %   mask-on-mask.
            
            % Construct the input labels based on the number of inputs
            numOutputs = obj.getNumOutputsImpl;
            [outputNames{1:numOutputs}] = obj.getOutputNamesImpl;
            for i = 1:length(outputNames)
                portLabelText = ['port_label(''output'', ' num2str(i) ', ''' char(outputNames{i}) ''')'];
            end
            
            % The system block always uses autoscale mask units, so fix the
            % minimum and maximum x,y co-ordinates to have repeatable
            % appearance.
            maskDisplay = { ...
                ['color(''white'');', newline], ...
                ['plot([100,100,100,100],[100,100,100,100]);', newline], ...
                ['plot([0,0,0,0],[0,0,0,0]);', newline],...
                'color(''blue'')', ...
                'text(20, 90, ''ROS'', ''horizontalAlignment'', ''right'')', ...
                'color(''black'')', ...
                ['text(50, 55, ''', 'Current\nTime', ''', ''horizontalAlignment'', ''center'');'], ...
                portLabelText};  %#ok<*CHARTEN>
        end
        
        function timeSize = getOutputSizeImpl(~)
            %getOutputSizeImpl Return size for each output port
            
            % The Time output port is always a scalar - either a double or
            % a scalar bus.
            timeSize = [1 1];
        end
        
        function timeType = getOutputDataTypeImpl(obj)
            %getOutputDataTypeImpl Return data type for each output port
            
            busName = obj.createBusIfNeeded;
            
            if obj.OutputFormat == "double"
                timeType = 'double';
            else
                % Return a bus name
                timeType = busName;
            end
        end
        
        function timeComplex = isOutputComplexImpl(~)
            %isOutputComplexImpl Return true for each output port with complex data
            timeComplex = false;
        end
        
        function timeFixed = isOutputFixedSizeImpl(~)
            %isOutputFixedSizeImpl Return true for each output port with fixed size
            timeFixed = true;
        end
    end
    
    methods (Access = protected)
        %% Inherited from matlab.system.mixin.SampleTime
        function sts = getSampleTimeImpl(obj)
            %getSampleTimeImpl Return sample time specification
            
            sts = obj.SampleTimeHandler.createSampleTimeSpec();
        end
    end
    
    methods (Access = protected)
        %% Methods that are implementations of abstract NodeDependent mixin
        function initializeDataStream(obj, modelState)
            %initializeDataStream Initialize data stream
            %   The stream is either connected to the ROS network or
            %   connected to a workspace variable.
            
            if ~isempty(obj.StreamWSVar)
                % Use a variable in MATLAB Workspace as source of messages.
                if strcmp(obj.ModelName, obj.DefaultModelName)
                    modelName = '';
                else
                    modelName = obj.ModelName;
                end
                obj.TimeStream = robotics.slros.internal.evalinGlobalScope(modelName, obj.StreamWSVar);
                validateattributes(obj.TimeStream, {'robotics.slros.internal.sim.TimeListStream'}, {'scalar'}, ...
                    'initializeDataStream', 'TimeStream');
            else
                % Use ROS network as a source of parameters.
                if isempty(modelState.ROSNode) || ~isvalid(modelState.ROSNode)
                    obj.ROSMaster = robotics.slros.internal.sim.ROSMaster;
                    %  verifyReachable() errors if ROS master is unreachable
                    obj.ROSMaster.verifyReachable;
                    % createNode() errors if unable to create node
                    % (e.g., if node with same name already exists)
                    uniqueName = obj.ROSMaster.makeUniqueName(obj.ModelName);
                    modelState.ROSNode = obj.ROSMaster.createNode(uniqueName);
                end
                
                % Initialize the time stream
                obj.TimeStream = robotics.slros.internal.sim.TimeNetStream(...
                    modelState.ROSNode);
            end
        end
        
        function name = modelName(obj)
            %modelName Retrieve model name
            
            name = obj.ModelName;
        end
    end
    
    methods (Access = private)
        function busName = createBusIfNeeded(obj)
            %createBusIfNeeded Create a bus time object in the global workspace
            %   Only create it if it does not exist yet
            
            [busExists, busName] = robotics.slros.internal.bus.Util.checkForBus(...
                char(obj.TimeMessageType), char(obj.ModelName));
            if busExists
                return;
            end
            
            % Create the object
            emptyROSMsg = robotics.ros.msg.Time;
            robotics.slros.internal.bus.createBusDefnInGlobalScope(emptyROSMsg, char(obj.ModelName));
        end
    end
    
    
    methods(Access = protected, Static)
        function simMode = getSimulateUsingImpl
            %getSimulateUsingImpl Restrict simulation mode to interpreted execution
            simMode = "Interpreted execution";
        end
        
        function flag = showSimulateUsingImpl
            %showSimulateUsingImpl Do now show simulation execution mode dropdown in block mask
            flag = false;
        end
        
        function header = getHeaderImpl
            %getHeaderImpl Define header panel for System block dialog
            
            header = matlab.system.display.Header(mfilename("class"), ...
                "Title", message("robotics:robotslros:rostime:MaskTitle").getString, ...
                "Text", message("robotics:robotslros:rostime:MaskDescription").getString,...
                "ShowSourceLink", false);
        end        
    end
end
