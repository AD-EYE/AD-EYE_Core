classdef Publisher < matlab.System
    %This class is for internal use only. It may be removed in the future.
    
    %Publish messages to a ROS network
    %
    %   H = robotics.slros.internal.block.Publisher creates a system
    %   object, H, that advertises a topic to a ROS network and publishes
    %   messages to that topic.
    %   
    %   This system object is intended for use with the MATLAB System
    %   block. In order to access the ROS functionality from MATLAB, see
    %   ROSPUBLISHER.
    %
    %   See also robotics.slros.internal.block.Subscriber
    
    %   Copyright 2014-2018 The MathWorks, Inc.
    
    %#codegen
    
    properties (Nontunable)
        %ROSTopic Topic to publish to
        %  This system object will use ROSTopic as specified in both
        %  simulation and code generation. In particular, it will not add a
        %  "/" in front of topic, as that forces the topic to be in the
        %  absolute namespace.
        ROSTopic = '/my_topic'
        
        %ROSMessageType Message type of topic
        %  e.g., 'std_msgs/Int32'
        ROSMessageType = 'std_msgs/Int32'
        
        %MessageQueueLen Length of publish queue 
        %   Only used in generated code
        MessageQueueLen = 1
    end
    
    % The following should ideally not show up in the MATLAB System block
    % dialog. However, setting them as 'Hidden' will prevent them from 
    % being accessible via set_param & get_param.
    properties(Nontunable)
        %SLBusName Simulink Bus Name for message type
        %   Not really used; only maintained for symmetry with Subscriber
        SLBusName = ''
        
        %ModelName Name of Simulink model
        %   Used for managing node instance
        ModelName = 'untitled'
        
        %BlockId Simulink Block Identifier
        %  Used to generate unique identifier for the block during code
        %  generation. This should be obtained using Simulink.ID.getSID()
        %  on the library block (*not* the MATLAB system block). The
        %  SID has the format '<modelName>:<blocknum>'
        BlockId = 'pub1'
        
        %OutputStreamWsVar Output message to variable in base workspace
        %  Used to redirect Publisher to send messages to a workspace
        %  variable instead of to ROS network (used for testing only).
        %  The workspace variable should be created like this:
        %
        %   workspaceVar =  robotics.slros.internal.sim.MsgListOutputStream(rostopic, msgtype);
        %   
        % After simulation, workspaceVar.MessageList has the list of
        % messages that have been sent to MsgListOutputStream object.
        % This capability of using workspace variables is only used in
        % internal testing, and is not documented for Simulink users.         
        OutputStreamWsVar = ''
    end
        
    properties(Constant,Access=private)
        % Name of header file with declarations for variables and types
        % referred to in code emitted by setupImpl and stepImpl.
        HeaderFile = robotics.slros.internal.cgen.Constants.InitCode.HeaderFile
    end
    
    properties (Constant, Access=?robotics.slros.internal.block.mixin.NodeDependent)
        %MessageCatalogName - Name of this block used in message catalog
        %   This property is used by the NodeDependent base class to
        %   customize error messages with the block name.
        MessageCatalogName = message("robotics:robotslros:blockmask:PublisherMaskTitle").getString
    end    
    
    properties (Access=private, Transient)
        % Converter - Handle to object that encapsulates converting a
        % Simulink bus struct to a MATLAB ROS message. It is initialized to
        % indicate the class of the object
        Converter = robotics.slros.internal.sim.BusStructToROSMsgConverter.empty
        
        % OutputStream - Handle to object that implements robotics.slros.internal.sim.MsgOutputStream
        %  This can be a sim.MsgNetOutputStream (for sending messages to 
        %  the ROS network) or sim.MsgListOutputStream (for sending messages
        %  to an object in the base workspace (used in conjunction with
        %  OutputStreamWsVar property)        
        OutputStream
        
        % ROSMaster - Handle to an object that encapsulates interaction
        % with the ROS master. It is initialized to indicate the class of
        % the object.        
        ROSMaster = robotics.slros.internal.sim.ROSMaster.empty
    end
    
    methods
        function obj = Publisher(varargin)
            % Enable code to be generated even this file is p-coded
            coder.allowpcode('plain');
            
            % Support name-value pair arguments when constructing the object.
            setProperties(obj,nargin,varargin{:});
        end
        
        function set.ROSTopic(obj, val)
            validateattributes(val, {'char'}, {'nonempty'}, '', 'ROSTopic');
            if coder.target('MATLAB')
                robotics.ros.internal.Namespace.canonicalizeName(val); % throws error
            end
            obj.ROSTopic = val; 
        end

        function set.ROSMessageType(obj, val)
            validateattributes(val, {'char'}, {'nonempty'}, '', 'ROSMessageType');
            if coder.target('MATLAB')
                robotics.ros.internal.Namespace.canonicalizeName(val); % throws error
            end
            obj.ROSMessageType = val;
        end

        function set.MessageQueueLen(obj, val)
            validateattributes(val, ...
                {'numeric'}, {'positive', 'integer', 'scalar'}, '', 'MessageQueueLen');
            obj.MessageQueueLen = int32(val);
        end
        
        function set.SLBusName(obj, val)
            validateattributes(val, {'char'}, {}, '', 'SLBusName');
            obj.SLBusName = val;
        end
        
        function set.ModelName(obj, val)
            validateattributes(val, {'char'}, {'nonempty'}, '', 'ModelName');
            obj.ModelName = val;
        end
        
        function set.BlockId(obj, val)
            validateattributes(val, {'char'}, {'nonempty'}, '', 'BlockId');
            obj.BlockId = val;
        end
        
        function set.OutputStreamWsVar(obj, val)
            validateattributes(val, {'char'}, {}, '', 'OutputStreamWsVar');
            obj.OutputStreamWsVar = val;
        end              
    end
    
    methods (Access = protected)

        function num = getNumInputsImpl(~)
            num = 1;
        end
        
        function num = getNumOutputsImpl(~)
            num = 0;
        end

    end
        
    methods (Access = protected)
        %% Common functions
        
        function out = constantSampleTimePropagationImpl(~)
            % Enable this system object to inherit constant ('inf') sample times
            out = 'Allow';
        end
        
        % We don't save SimState, since there is no way save & restore
        % the Publisher object. However, saveObjectImpl and loadObjectImpl
        % are required since we have private properties.
        function s = saveObjectImpl(obj)
            % The errorIf() below will ensure that FastRestart cannot be used
            % in a model with ROS blocks
            coder.internal.errorIf(true, 'robotics:robotslros:sysobj:PublisherSimStateNotSupported');
            s = saveObjectImpl@matlab.System(obj);
        end

        
        function loadObjectImpl(obj,s,wasLocked)            
            loadObjectImpl@matlab.System(obj,s,wasLocked);
        end
        
        
        function setupImpl(obj, ~)
            % setupImpl is called when model is being initialized at the
            % start of a simulation
            
            if coder.target('MATLAB')
                % Executing in MATLAB interpreted mode
                modelHasPriorState = robotics.slros.internal.sim.ModelStateManager.hasState(obj.ModelName);
                nodeRefCountIncremented = false;
                
                try 
                    modelState = robotics.slros.internal.sim.ModelStateManager.getState(obj.ModelName, 'create');

                    % The following could be a separate method, but system
                    % object infrastructure doesn't appear to allow it
                    %--
                    if ~isempty(obj.OutputStreamWsVar)
                        % Use a variable in MATLAB Workspace as the recipient of messages.
                        obj.OutputStream = robotics.slros.internal.evalinGlobalScope(obj.ModelName, obj.OutputStreamWsVar);
                        validateattributes(obj.OutputStream, {'robotics.slros.internal.sim.MsgListOutputStream'}, {'scalar'});
                    else
                        % Use ROS network as a recipient of messages.
                        if isempty(modelState.ROSNode) || ~isvalid(modelState.ROSNode)
                            obj.ROSMaster = robotics.slros.internal.sim.ROSMaster();
                            %  verifyReachable() errors if ROS master is unreachable
                            obj.ROSMaster.verifyReachable();
                            % createNode() errors if unable to create node
                            % (e.g., if node with same name already exists)
                            uniqueName = obj.ROSMaster.makeUniqueName(obj.ModelName);
                            modelState.ROSNode = obj.ROSMaster.createNode(uniqueName);
                        end
                        obj.OutputStream = robotics.slros.internal.sim.MsgNetOutputStream(...
                            obj.ROSTopic, obj.ROSMessageType, modelState.ROSNode);
                    end
                    %--
                    
                    modelState.incrNodeRefCount();
                    nodeRefCountIncremented = true;
                    
                    obj.Converter = robotics.slros.internal.sim.BusStructToROSMsgConverter(...
                        obj.ROSMessageType, obj.ModelName);
                catch ME
                    if nodeRefCountIncremented
                        modelState.decrNodeRefCount();
                    end
                    obj.OutputStream = [];
                    if ~modelHasPriorState || ~modelState.nodeHasReferrers()
                        robotics.slros.internal.sim.ModelStateManager.clearState(obj.ModelName);
                    end
                    % RETHROW will generate a hard-to-read stack trace, so
                    % use THROW instead.
                    throw(ME);
                end

            elseif coder.target('RtwForRapid')
                % Rapid Accelerator. In this mode, coder.target('Rtw')
                % returns true as well, so it is important to check for
                % 'RtwForRapid' before checking for 'Rtw'
                coder.internal.errorIf(true, 'robotics:robotslros:sysobj:PublisherRapidAccelNotSupported');
            
            elseif coder.target('Rtw')
                coder.cinclude(obj.HeaderFile);
                % Append 0 to obj.ROSTopic, since MATLAB doesn't
                % automatically zero-terminate strings in generated code
                zeroDelimTopic = [obj.ROSTopic 0];
                coder.ceval([obj.BlockId '.createPublisher'], ...
                    zeroDelimTopic, int32(obj.MessageQueueLen));
            
            elseif  coder.target('Sfun')
                % 'Sfun'  - SimThruCodeGen target
                % Do nothing. MATLAB System block first does a pre-codegen
                % compile with 'Sfun' target, & then does the "proper"
                % codegen compile with Rtw or RtwForRapid, as appropriate.
            
            else
                % 'RtwForSim' - ModelReference SIM target
                % 'MEX', 'HDL', 'Custom' - Not applicable to MATLAB System block
                coder.internal.errorIf(true, 'robotics:robotslros:sysobj:UnsupportedCodegenMode', coder.target);
            end            
        end
       
        
        function stepImpl(obj,busstruct)            
            % Buses are treated as structures 
            
            if coder.target('MATLAB')
                % executing in MATLAB
                rosmsg = obj.Converter.convert(busstruct);
                obj.OutputStream.sendMessage(rosmsg);
                
            elseif coder.target('Rtw')
                % The datatype of msg will be derived from the input to the block
                coder.ceval([obj.BlockId '.publish'], coder.rref(busstruct));
            end
            
        end
        
        %%
        function releaseImpl(obj)
            if coder.target('MATLAB')
                % We need to release all the OutputStreams (which hold the
                % publisher) before releasing the node. If the order is
                % reversed, the Publisher tries to connect to the  master
                % to unregister & waits for this operation to succeed (w/ a
                % time out), which  causes a delay during model termination.
                
                st = robotics.slros.internal.sim.ModelStateManager.getState(obj.ModelName);
                st.decrNodeRefCount();
                obj.OutputStream = [];  % release publisher
                
                if  ~st.nodeHasReferrers()
                    robotics.slros.internal.sim.ModelStateManager.clearState(obj.ModelName);
                end
            else % coder.target('Rtw')
                
                % Nothing to do. The system object will never be released
                % in the generated node.
            end
        end
        
    end
   
end
