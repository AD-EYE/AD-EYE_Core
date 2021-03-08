classdef ReadDataBlockMask
    %This class is for internal use only. It may be removed in the future.
    
    %ReadDataBlockMask - Block mask callbacks for Read Data block
    
    %   Copyright 2017-2018 The MathWorks, Inc.
    
    properties (Constant, Hidden)
        %MaskType Type of block mask
        %   Retrieve it with get_param(gcb, 'MaskType')
        MaskType = 'Read Data'
        
        %SysObjBlockName Name of the system object block inside the masked 
        %   subsystem
        SysObjBlockName = 'SourceBlock';
        
        % Logfile data will apply model-wide, and some data will be stored
        % in the workspace for extraction by each logfile reading block
        
        %LogfilePathVarName Name of the variable in the workspace that 
        %   contains the logfile file path in the workspace
        LogfilePathVarName = 'Logfile_Path';
        
        %DataObjectVarName Name of the variable in the workspace that 
        %   contains the object containing or allowing access to the 
        %   logfile data
        DataObjectVarName = 'Logfile_Data_Object';
        
        %PlaybackOffsetVarName Name of the variable in the workspace that 
        %   contains the value of the time to skip from the beginning of 
        %   the logfile
        PlaybackOffsetVarName = 'Logfile_Playback_Offset';
        
        %PlaybackDurationVarName Name of the variable in the workspace that 
        %   contains the value of the duration to play back the logfile
        PlaybackDurationVarName = 'Logfile_Playback_Duration';
    end

    methods (Static)
        %% Initialization function
        function blockInitFcn(block)
        %blockInitFcn Perform update tasks for block
        %   Determine the model parameters to use, and set block
            
            % Model name is dependent on model containing block
            modelName = bdroot(block);
            set_param(block, 'modelName', modelName)
            
            % Message type is dependent on topic, and data object
            msgType = '';   % Default value
            topic = get_param(block, 'topic');
            dataobj = robotics.ros.BagSelection.empty;
            dataobj = robotics.slros.internal.block.ReadDataBlockMask.getDataFromWS(...
                robotics.slros.internal.block.ReadDataBlockMask.DataObjectVarName, ...
                dataobj, modelName);
            if ~isempty(dataobj) && ...
                    contains(topic, dataobj.AvailableTopics.Row)
                msgType = ...
                    char(dataobj.AvailableTopics{topic, 'MessageType'});
            end
            set_param(block, 'msgType', msgType)
        end
        
        %% Cleanup function
        function modelCloseFcn(block)
        %modelCloseFcn Clean up model of open or existing items
        %   Delete artifacts left in base workspace from logfile reading
        %   and close associated dialogs
            
            % Bus definitions in base workspace
            robotics.slros.internal.bus.clearBusesOnModelClose(block);
            
            % Load logfile dialog associated with model
            modelName = bdroot(block);
            robotics.slros.internal.dlg.LogfileDataLoader.closeDialog(modelName);
        end
        
        %% Dialog-related functions
        function loadLogfileLink(block)
        %loadLogfileLink Open the logfile data loader dialog
            
            try
                modelName = bdroot(block);
                set_param(block, 'modelName', modelName)
                robotics.slros.internal.dlg.LogfileDataLoader.retrieveDialog(modelName);
            catch ME
                % Send error to Simulink diagnostic viewer rather than a
                % DDG dialog.
                % NOTE: This does NOT stop execution.
                reportAsError(MSLDiagnostic(ME));
            end
        end
        
        function topicSelectButton(block)
        %topicSelectButton Open the logfile topic selector dialog
            
            try
                modelName = bdroot(block);
                set_param(block, 'modelName', modelName)
                topicName = get_param(block, 'topic');
                dataobj = robotics.ros.BagSelection.empty;
                dataobj = robotics.slros.internal.block.ReadDataBlockMask.getDataFromWS(...
                    robotics.slros.internal.block.ReadDataBlockMask.DataObjectVarName, ...
                    dataobj, modelName);
                
                % Requires valid logfile selected to select the topic
                if isempty(dataobj)
                    error(message('robotics:robotslros:readlog:InvalidLogData'))
                end
                
                msgDlg = robotics.slros.internal.dlg.LogfileTopicSelector(...
                    dataobj, topicName);
                openDialog(msgDlg, ...
                    @(topic) dialogCloseCallback(block, topic));
            catch ME
                % Send error to Simulink diagnostic viewer rather than a
                % DDG dialog.
                % NOTE: This does NOT stop execution.
                reportAsError(MSLDiagnostic(ME));
            end
            
            function dialogCloseCallback(block, selectedTopic)
                % React to the topic selection dialog closing
                set_param(block, 'topic', selectedTopic)
            end
        end
        
        %% Helper functions
        function val = getDataFromWS(varName, defaultVal, modelName)
        %getDataFromWS Get data from a model's workspace
        %   Return the default value if unable to get data
        %   varName - name of variable to extract from the workspace
        %   defaultVal - value to return if not valid
        %   modelName - Name of model whos workspace to use
        %               Empty indicates to use base workspace
            
            val = defaultVal;
            
            % Base Workspace
            if isempty(modelName)
                if evalin('base', ['exist(''' varName ''', ''var'')'])
                    val = evalin('base', varName);
                end
            % Model Workspace
            elseif ischar(modelName)
                ws = get_param(modelName, 'ModelWorkspace');
                if ~isempty(ws) && hasVariable(ws, varName)
                    val = getVariable(ws, varName);
                end
            end
        end
        
        function setDataInWS(varName, val, modelName)
        %setDataInWS Set data in a model's workspace
        %   varName - name of variable to modify in the workspace
        %   val - value to set
        %   modelName - Name of model whos workspace to use
        %               Empty indicates to use base workspace
            
            % Determine workspace
            if isempty(modelName)
                ws = 'base';
            else
                ws = get_param(modelName, 'ModelWorkspace');
            end
            
            % Assign values
            if ~isempty(ws)
                assignin(ws, varName, val)
            end
        end
        
        function [logPath, logData, offset, duration] = getAllDataFromWS(modelName)
        %getDataFromWS - Get all logfile-related data from model workspace
        %   modelName - Name of model whos workspace to use
        %               Empty indicates to use base workspace
        %   logPath - Logfile file path
        %   logData - Object containing or allowing access to logfile data
        %   offset - Time to skip from beginning of logfile
        %   duration - Duration to play back the logfile
            
            % Logfile path
            logPath = '';
            logPath = ...
                robotics.slros.internal.block.ReadDataBlockMask.getDataFromWS(...
                robotics.slros.internal.block.ReadDataBlockMask.LogfilePathVarName, ...
                logPath, modelName);
            
            % Logfile data
            logData = robotics.ros.BagSelection.empty;
            logData = ...
                robotics.slros.internal.block.ReadDataBlockMask.getDataFromWS(...
                robotics.slros.internal.block.ReadDataBlockMask.DataObjectVarName, ...
                logData, modelName);
            
            % Playback offset
            offset = NaN;
            offset = ...
                robotics.slros.internal.block.ReadDataBlockMask.getDataFromWS(...
                robotics.slros.internal.block.ReadDataBlockMask.PlaybackOffsetVarName, ...
                offset, modelName);
            
            % Playback duration
            duration = NaN;
            duration = ...
                robotics.slros.internal.block.ReadDataBlockMask.getDataFromWS(...
                robotics.slros.internal.block.ReadDataBlockMask.PlaybackDurationVarName, ...
                duration, modelName);
        end
        
        function setAllDataInWS(modelName, logPath, logData, offset, duration)
        %setAllDataInWS - Set all logfile-related data in model workspace
        %   modelName - Name of model whos workspace to use
        %               Empty indicates to use base workspace
        %   logPath - Logfile file path
        %   logData - Object containing or allowing access to logfile data
        %   offset - Time to skip from beginning of logfile
        %   duration - Duration to play back the logfile
            
            % Logfile path
            robotics.slros.internal.block.ReadDataBlockMask.setDataInWS(...
                robotics.slros.internal.block.ReadDataBlockMask.LogfilePathVarName, ...
                logPath, modelName);
            
            % Logfile data
            if nargin > 2
                robotics.slros.internal.block.ReadDataBlockMask.setDataInWS(...
                    robotics.slros.internal.block.ReadDataBlockMask.DataObjectVarName, ...
                    logData, modelName);
            end
            
            % Playback offset
            if nargin > 3
                robotics.slros.internal.block.ReadDataBlockMask.setDataInWS(...
                    robotics.slros.internal.block.ReadDataBlockMask.PlaybackOffsetVarName, ...
                    offset, modelName);
            end
            
            % Playback duration
            if nargin > 4
                robotics.slros.internal.block.ReadDataBlockMask.setDataInWS(...
                    robotics.slros.internal.block.ReadDataBlockMask.PlaybackDurationVarName, ...
                    duration, modelName);
            end
        end
        
        function tGap = getMinNonzeroMsgGap(dataObj)
        %getMinNonzeroMsgGap Return the smallest non-zero time difference between messages
        %   Will error if there are no messages.
        %   Will return empty if there is only one message, or all 
        %   messages arrive at the same time.
            
            validateattributes(dataObj, {'robotics.ros.BagSelection'}, ...
                {'nonempty', 'scalar'})
            validateattributes(dataObj.MessageList, {'table'}, ...
                {'nonempty'});
            dt = diff(dataObj.MessageList.Time);
            dt(dt <= 0) = [];
            tGap = min(dt);
        end
        
    end
end
