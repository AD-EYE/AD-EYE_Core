classdef DeploymentHooks < robotics.slros.internal.InternalAccess
    %This class is for internal use only. It may be removed in the future.
    
    %DeploymentHooks Code hooks for deployment of Simulink model to ROS target
    %   Hooks are callbacks that are executed by the coder targets 
    %   infrastructure when the ROS node is generated. For example, there is 
    %   a callback when the build starts (`buildEntry`) and 
    %   a callback that is executed once the node archive is created and should 
    %   be loaded to the ROS target (`loadCommand`).
    
    %   Copyright 2016-2018 The MathWorks, Inc.
    
    methods (Static)
        function loadCommand(modelName,varargin)
            %LOADCOMMAND Executes as the load command for ROS model build.
            %   At this point, the source code archive and the build shell script are
            %   both available.
            %   The load command will copy these files to the ROS device, build the ROS
            %   node there, and (optionally) run the ROS node.
            %   Note that this function is not called if the user selected the
            %   "Code Generation Only" checkbox.
            
            validateattributes(modelName, {'char'}, {'nonempty', 'row'}, 'loadCommand', 'modelName');
            
            expectedTargetHardware = robotics.slros.internal.Constants.TargetHardware;
            
            % Get all config set data
            data = codertarget.data.getData(getActiveConfigSet(modelName));
            if ~isequal(data.TargetHardware, expectedTargetHardware)
                error(message('robotics:robotslros:deploy:UnknownTargetHardware', expectedTargetHardware, data.TargetHardware));
            end
            
            % Retrieve build action. This can either be "None", "Build and load", or "Build and run"
            buildAction = data.Runtime.BuildAction;
            if ~string(buildAction).startsWith('build', 'IgnoreCase', true)
                % If the user did not request a build, do not connect to the ROS
                % device. The final artifacts are the tgz and sh files.
                return;
            end
            
            % Verify connection settings
            [validHost, validSSH, validUser, validPassword, validCatkin] = ...
                robotics.codertarget.internal.DeploymentHooks.verifyConnectionSettings(modelName, buildAction);
            
            % Open new stage in diagnostic viewer and close it when function exits or
            % if an error occurs
            buildStage = sldiagviewer.createStage(buildAction, 'ModelName', modelName);
            stageCleanup = onCleanup(@() delete(buildStage));
            
            % Load and run if necessary
            disp(message('robotics:robotslros:deploy:ConnectToDevice', validHost).getString);
            rosTarget = rosdevice(validHost, validUser, validPassword, validSSH);
            
            disp(message('robotics:robotslros:deploy:UseCatkin', validCatkin).getString);
            rosTarget.CatkinWorkspace = validCatkin;
            
            disp(robotics.slros.internal.diag.DeviceDiagnostics.StepSeparator);
            
            % We need to first kill any instance(s) of the ROS node with
            % the same name before building. Otherwise the executable will be
            % locked.
            if isNodeRunning(rosTarget, modelName)
                disp(message('robotics:robotslros:deploy:StopRunningNode', modelName).getString);
                disp(robotics.slros.internal.diag.DeviceDiagnostics.StepSeparator);
                
                try
                    stopNode(rosTarget, modelName);
                catch
                end
            end
            
            % Find all archives for main model and all model references
            modelNames = {modelName};
            modelRefNames = find_mdlrefs(modelName);
            
            % Ignore the last name, since it's the top-level model name
            modelRefNames(end) = [];
            
            hasModelRefs = ~isempty(modelRefNames);
            mdlRefListFile = strcat(modelName, 'ModelRefs.txt');
            
            modelNames = [modelNames; modelRefNames];
            archives = fullfile('..', strcat(modelNames, '.tgz'));
            
            % Create file listing all the model references
            if hasModelRefs
                mdlRefList = StringWriter;
                for i = 1:numel(modelRefNames)
                    mdlRefList.addcr(strcat(modelRefNames{i}, '.tgz'));
                end
                mdlRefList.write(mdlRefListFile);
            end
            
            % If model did not change and node executable exists on target,
            % there is no need to regenerate it.
            if ~robotics.codertarget.internal.hasModelChanged
                nodeExistsOnTarget = string(rosTarget.AvailableNodes).contains(lower(modelName));
                if nodeExistsOnTarget
                    disp(message('robotics:robotslros:deploy:NodeUpToDate', modelName).getString);
                    
                    % Still run node, if specified by user build action
                    robotics.codertarget.internal.DeploymentHooks.runROSNode(rosTarget, modelName, buildAction);
                    return;
                end
            end
            
            % 1. Transfer build script and the Simulink model to the Catkin workspace
            % 2. Build Simulink node
            % If the "rosTarget.CatkinWorkspace" folder contains spaces, they are
            % already escaped, so I can simply concatenate it with our file names.
            
            % Transfer build scripts
            disp(message('robotics:robotslros:deploy:TransferCode', modelName).getString);
            shellScriptWildcard = 'deploy_*.sh';
            backgroundScript = [rosTarget.CatkinWorkspace '/deploy_background_build.sh'];
            buildScript = [rosTarget.CatkinWorkspace '/deploy_build_ros_model.sh'];
            
            buildScripts = fullfile(toolboxdir('robotics'), 'robotsimulink',...
                'robotslros', 'src', shellScriptWildcard);
            putFile(rosTarget, buildScripts, rosTarget.CatkinWorkspace);
            
            % Make the shell scripts executable
            system(rosTarget, ['chmod u+x ' rosTarget.CatkinWorkspace '/' shellScriptWildcard]);
            
            % Transfer all Simulink model archives (main model + model references)
            for i = 1:numel(archives)
                putFile(rosTarget, archives{i}, rosTarget.CatkinWorkspace);
            end
            
            % Transfer text file listing all model references
            if hasModelRefs
                putFile(rosTarget, mdlRefListFile, rosTarget.CatkinWorkspace);
            end

            % Start build process and get the pid
            buildLog = [rosTarget.CatkinWorkspace '/' modelName '_build.log'];
            buildStat = [rosTarget.CatkinWorkspace '/' modelName '_build.stat'];
            
            % Without redirecting stdout and stderr to /dev/null,
            % the command does not return
            disp(message('robotics:robotslros:deploy:StartBuild').getString);
            disp(robotics.slros.internal.diag.DeviceDiagnostics.StepSeparator);
            
            pid = system(rosTarget, ['source ' rosTarget.CatkinWorkspace '/devel/setup.bash; ' backgroundScript ' ' buildScript ' ' ...
                [rosTarget.CatkinWorkspace '/' modelName] ' ' validCatkin ' &>/dev/null & echo $!']);
            logSize = 0;
            done = false;
            while ~done
                try
                    % Kill -0 checks for existence of the process ID (it does not do
                    % any killing)
                    system(rosTarget, ['kill -0 ' pid]);
                catch
                    % The process does not exist anymore
                    done = true;
                end
                
                try
                    % Get the output of the buildLog (this is executed continuously)
                    output = system(rosTarget, ['stat --format=%s ' buildLog]);
                catch
                    % Log file is deleted
                    continue;
                end
                
                % Display running log in the diagnostic viewer
                currLogSize = str2double(output);
                if ~isnan(currLogSize) && (currLogSize > logSize)
                    try
                        % Print out new characters output to the log file since last
                        % visit
                        logOut = system(rosTarget,sprintf('tail -c +%d %s',logSize,buildLog));
                        logSize = logSize + numel(logOut);
                        disp(logOut);
                    catch
                    end
                end
                
                % Update build status every second
                pause(1);
            end
            
            try
                status = str2double(system(rosTarget,['cat ' buildStat]));
            catch
                % Something went seriously wrong if the buildStat file does not exist
                status = 1;
            end
            
            if ~isnan(status) && (status ~= 0)
                error(message('robotics:robotslros:deploy:BuildError', modelName))
            end
            
            % Delete the build scripts if there were no build errors
            robotics.codertarget.internal.DeploymentHooks.systemNoException(rosTarget, ['rm -f ' backgroundScript ' ' buildScript ' ' buildLog ' ' buildStat]);
                        
            % Run node, if specified by user build action
            robotics.codertarget.internal.DeploymentHooks.runROSNode(rosTarget, modelName, buildAction);
            
        end
    end
    
    methods (Static, Access = private)
        function [validHost, validSSH, validUser, validPassword, validCatkin] = ...
                verifyConnectionSettings(modelName, buildAction)
            %verifyConnectionSettings Verify the connection settings to the ROS device
            %   Return valid settings that can be used for the actual deployment step.
            
            % Get the latest parameters from MATLAB preferences
            deviceParams = robotics.codertarget.internal.DeviceParameters;
            [hostname, sshPort, username, password, ~, catkinWs, rosFolder] = deviceParams.getDeviceParameters;
            
            % Run the diagnostics in build mode. Each high-priority warning will result
            % in an error.
            diag = robotics.slros.internal.diag.DeviceDiagnostics(modelName);
            switch lower(buildAction)
                case 'build and load'
                    diag.RunMode = 'build';
                case 'build and run'
                    % The user explicitly requested to run the resulting ROS node
                    diag.RunMode = 'buildrun';
                otherwise
                    % By default, stick with the build mode
                    diag.RunMode = 'build';
            end
            
            % Now run a loop until we have valid connection settings.
            % If there are problems, display the connection dialog and let the user
            % make adjustments to the settings.
            
            notDone = true;
            while notDone
                
                % Run the diagnostics
                hasError = diag.runDiagnostics(hostname, sshPort, username, password, rosFolder, catkinWs);
                if ~hasError
                    % If diagnostics run without problems, get out of this loop
                    break;
                end
                
                % If there are diagnostic errors, pop up the settings dialog and let
                % the user make adjustments.
                % This call is blocking until the user closes the dialog.
                userDlg = robotics.slros.internal.dlg.DeviceParameterSpecifier;
                userDlg.ModelName = modelName;
                [isAccepted, hostname, sshPort, username, password, rosFolder, catkinWs] = ...
                    userDlg.openDialogAndWait;
                
                if ~isAccepted
                    % If the user hit "Cancel" or closed the dialog, abort the build.
                    error(message('robotics:robotslros:deploy:NoValidSettings', hostname, modelName))
                end
                
                % Retry the settings that the user made in the next loop iteration
                notDone = hasError;
            end
            
            % Initial settings have been validated. Store them.
            validHost = hostname;
            validSSH = sshPort;
            validUser = username;
            validPassword = password;
            validCatkin = diag.handleSpaces(catkinWs);
            
        end
        
        
        function runROSNode(rosTarget, modelName, buildAction)
            if contains(buildAction, 'run')
                disp(robotics.slros.internal.diag.DeviceDiagnostics.StepSeparator);
                disp(message('robotics:robotslros:deploy:RunNode').getString);
                
                % Run Simulink node. Set MasterURI automatically for now
                rosMasterURI = robotics.slros.internal.sim.defaultSimMasterURI(rosTarget.DeviceAddress);
                
                disp(robotics.slros.internal.diag.DeviceDiagnostics.StepSeparator);
                disp(message('robotics:robotslros:deploy:NodeMasterHostConnection', ...
                    rosMasterURI, rosTarget.DeviceAddress).getString);
                disp(message('robotics:robotslros:deploy:UseRosdevice').getString);
                
                port = codertarget.attributes.getExtModeData('Port', getActiveConfigSet(bdroot(gcs)));
                rosTarget.runNodeInternal(modelName, rosMasterURI, rosTarget.DeviceAddress, [' -port ' num2str(port)]);
            end
        end
        
        function output = systemNoException(hw,cmd,varargin)
            %systemNoException Make a system call and swallow all exceptions
            
            try
                output = system(hw,cmd,varargin{:});
            catch
            end
        end
        
    end
end
