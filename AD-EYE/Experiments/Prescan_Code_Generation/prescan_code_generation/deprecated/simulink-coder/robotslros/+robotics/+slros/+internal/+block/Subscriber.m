classdef Subscriber < matlab.System & matlab.system.mixin.Propagates
    %This class is for internal use only. It may be removed in the future.
    
    %Subscribe to a topic on a ROS network
    %
    %   H = robotics.slros.internal.block.Subscriber creates a system
    %   object, H, that subscribes to a topic on a ROS network and
    %   receives messages on that topic.
    %   
    %   This system object is intended for use with the MATLAB System
    %   block. In order to access the ROS functionality from MATLAB, see
    %   ROSSUBSCRIBER.
    %
    %   See also robotics.slros.internal.block.Publisher
    
    %   Copyright 2014-2018 The MathWorks, Inc.
    
    %#codegen
    
    properties (Nontunable)
        %ROSTopic Topic to subscribe to
        %  This system object will use ROSTopic as specified in both
        %  simulation and code generation. In particular, it will not add a
        %  "/" in front of topic, as that forces the topic to be in the
        %  absolute namespace.        
        ROSTopic = '/my_topic'
        
        %ROSMessageType Message type of topic
        %  e.g., 'std_msgs/Int32'
        ROSMessageType = 'std_msgs/Int32'
        
        %MessageQueueLen Length of subscribe callback queue 
        %   Only used in generated code        
        MessageQueueLen = 1
    end
    
    % The following should ideally not show up in the MATLAB System block
    % dialog. However, setting them as 'Hidden' will prevent them from 
    % being accessible via set_param & get_param.
    % 
    %   ModelName is needed for managing the node instance
    %   BlockId is needed to generate a unique identifier in codegen
    properties(Nontunable)
        %SLBusName Simulink Bus Name for message type
        SLBusName = 'SL_Bus'
        
        %ModelName Name of Simulink model
        %   Used for managing node instance
        ModelName = 'untitled'
        
        %BlockId Simulink Block Identifier
        %  Used to generate unique identifier for the block during code
        %  generation. This should be obtained using Simulink.ID.getSID()
        %  on the library block (*not* the MATLAB system block). The
        %  SID has the format '<modelName>:<blocknum>'
        BlockId = 'sub1'
        
        %InputStreamWSVar Receive message from variable in base workspace
        %  Used to redirect Subscriber to receive messages from a workspace
        %  variable instead of from ROS network (used for testing only).
        %  The workspace variable should be created like this:
        %
        %   workspaceVar =  robotics.slros.internal.sim.MsgListInputStream(rostopic, msgtype);
        %   workspaceVar.setMessageList( {msg1, msg2, msg3} );
        %   
        % This capability of using workspace variables is only used in
        % internal testing, and is not documented for Simulink users. 
        InputStreamWsVar = ''
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
        MessageCatalogName = message("robotics:robotslros:blockmask:SubscriberMaskTitle").getString
    end      
        
    properties (Access=private, Transient)
        % Converter - Handle to object that encapsulates converting a MATLAB ROS
        % message to a Simulink bus struct. It is initialized to indicate
        % the class of the object
        Converter = robotics.slros.internal.sim.ROSMsgToBusStructConverter.empty
        
        % InputStream - Handle to object that implements robotics.slros.internal.sim.MsgInputStream
        %  This can be a sim.MsgNetInputStream (for getting messages off
        %  the ROS network) or sim.MsgListInputStream (for getting messages
        %  from an object in the base workspace (used in conjunction with
        %  InputStreamWsVar property)
        InputStream
        
        % LastConvertedMsg - Handle to last received "new" message
        LastConvertedMsg = []
        
        % ROSMaster - Handle to an object that encapsulates interaction
        % with the ROS master. It is initialized to indicate the class of
        % the object.
        ROSMaster = robotics.slros.internal.sim.ROSMaster.empty
    end
    
    methods
        function obj = Subscriber(varargin)
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
            validateattributes(val, {'char'}, {'nonempty'}, '', 'SLBusName');
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
        
        function set.InputStreamWsVar(obj, val)
            validateattributes(val, {'char'}, {}, '', 'InputStreamWsVar');
            obj.InputStreamWsVar = val;
        end            
    end
    
    methods (Access = protected)

        function num = getNumInputsImpl(~)
            num = 1;
        end
        
        function num = getNumOutputsImpl(~)
            num = 2;
        end
        
        function varargout = getOutputSizeImpl(~)
            varargout = {[1 1], [1 1]};
        end
        
        function varargout = isOutputFixedSizeImpl(~)
            varargout =  {true, true};
        end
        
        function varargout = getOutputDataTypeImpl(obj)            
            varargout =  {'logical', obj.SLBusName};
        end
        
        function varargout = isOutputComplexImpl(~)
            varargout = {false, false};
        end
    end
    
    
    methods (Access = protected)
        %% Common functions

        function out = constantSampleTimePropagationImpl(~)
            % Enable this system object to inherit constant ('inf') sample times
            out = 'Allow';
        end
        
        % We don't save SimState, since there is no way save & restore
        % the Subscriber object. However, saveObjectImpl and x`Impl
        % are required since we have private properties.
        function s = saveObjectImpl(obj)
            % The errorIf() below will ensure that FastRestart cannot be used
            % in a model with ROS blocks
            coder.internal.errorIf(true, 'robotics:robotslros:sysobj:SubscriberSimStateNotSupported');
            s = saveObjectImpl@matlab.System(obj);
        end
                
        function loadObjectImpl(obj,s,wasLocked)            
            loadObjectImpl@matlab.System(obj,s,wasLocked);
        end
    
        
        %%        
        function setupImpl(obj)
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
                    if ~isempty(obj.InputStreamWsVar)
                        % Use a variable in MATLAB Workspace as source of messages.
                        obj.InputStream = robotics.slros.internal.evalinGlobalScope(obj.ModelName, obj.InputStreamWsVar);
                        validateattributes(obj.InputStream, {'robotics.slros.internal.sim.MsgListInputStream'}, {'scalar'});
                    else
                        % Use ROS network as a source of messages.
                        if isempty(modelState.ROSNode) || ~isvalid(modelState.ROSNode)
                            obj.ROSMaster = robotics.slros.internal.sim.ROSMaster();
                            %  verifyReachable() errors if ROS master is unreachable
                            obj.ROSMaster.verifyReachable();
                            % createNode() errors if unable to create node
                            % (e.g., if node with same name already exists)               
                            uniqueName = obj.ROSMaster.makeUniqueName(obj.ModelName);
                            modelState.ROSNode = obj.ROSMaster.createNode(uniqueName);
                        end
                        obj.InputStream = robotics.slros.internal.sim.MsgNetInputStream(...
                            obj.ROSTopic, obj.ROSMessageType, modelState.ROSNode);
                    end
                    %--
                    
                    modelState.incrNodeRefCount(); 
                    nodeRefCountIncremented = true;
                    
                    obj.Converter = robotics.slros.internal.sim.ROSMsgToBusStructConverter(...
                        obj.ROSMessageType, obj.ModelName);                
                catch ME
                    if nodeRefCountIncremented
                        modelState.decrNodeRefCount();
                    end
                    obj.InputStream = [];                    
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
                coder.internal.errorIf(true, 'robotics:robotslros:sysobj:SubscriberRapidAccelNotSupported');
                
            elseif coder.target('Rtw')                
                coder.cinclude(obj.HeaderFile);
                % Append 0 to obj.ROSTopic, since MATLAB doesn't
                % automatically zero-terminate strings in generated code
                zeroDelimTopic = [obj.ROSTopic 0];                
                coder.ceval([obj.BlockId '.createSubscriber'], ...
                    zeroDelimTopic, obj.MessageQueueLen);
                
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
        
        
        %%
        function [isNewData, msg] = stepImpl(obj, busstruct) 
            % <busstruct> is a blank (empty) bus structure. It is necessary
            % since there is no convenient way to create the (arbitrarily
            % complex and nested) bus structure.
            
            isNewData = false;
            msg = coder.nullcopy(busstruct);
            
            % If isNewData is true, msg holds the new message (SL bus layout).
            %
            % If isNewData is false, msg is unmodified from busstruct
            %   (i.e., it is an empty bus). The rationale is that we want
            %   to avoid overhead of converting a message to bus.
            %   In this case, MATLAB system block output needs to be 
            %   latched, so that the user sees the most-recent-valid
            %   message. (This latching could have been done inside
            %   get_latest_msg, but it is better to let Simulink do it, as
            %   that allows it to generate more optimized code).
            
            if coder.target('MATLAB')
                [isNewData, rosmsg] = obj.InputStream.getLatestMessage();
                if isNewData || isempty(obj.LastConvertedMsg)
                    msg = obj.Converter.convert(rosmsg);
                    obj.LastConvertedMsg = msg;
                else
                    % There is no performance saving to assigning busstruct
                    % instead of obj.LastConvertedMsg, but we do so for
                    % compatibility with codegen behavior.
                    msg = busstruct;
                end
                
            elseif coder.target('Rtw')                                
                isNewData = coder.ceval([obj.BlockId '.getLatestMessage'], coder.wref(msg));
            end
                        
        end

        %%
        function releaseImpl(obj)
            if coder.target('MATLAB')
                % We need to release all the InputStreams (which hold the
                % Subscriber) before releasing the node. If the order is
                % reversed, the Subscriber tries to connect to the  master
                % to unregister & waits for this operation to succeed (w/ a
                % time out), which  causes a delay during model termination.
                
                st = robotics.slros.internal.sim.ModelStateManager.getState(obj.ModelName);
                st.decrNodeRefCount();
                
                % This following command takes ~0.5s, due to a blocking
                % wait in the destructor for ros.Subscriber
                obj.InputStream = [];  % release publisher
                
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
