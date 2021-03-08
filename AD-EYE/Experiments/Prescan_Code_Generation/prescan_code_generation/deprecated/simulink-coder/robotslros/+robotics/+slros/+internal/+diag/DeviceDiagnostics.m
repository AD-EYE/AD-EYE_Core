classdef DeviceDiagnostics < handle
    %This class is for internal use only. It may be removed in the future.
    
    %DeviceDiagnostics Helper class for running diagnostics on device parameter settings
    %   This class can be invoked in a MATLAB and a Simulink context.
    %
    %   When invoked from MATLAB, construct the object without the modelName
    %   input. All errors, warnings, and high-priority warnings are
    %   displayed on the MATLAB command line.
    %
    %   When invoked from Simulink, construct the object with the modelName
    %   input. All errors, warnings, and high-priority warnings are
    %   displayed in the Simulink Diagnostic Viewer.
    %
    %
    %   Examples:
    %      % Run a diagnostic test
    %      tester = robotics.slros.internal.diag.DeviceDiagnostics(modelName);
    %      tester.runDiagnostics(hostname, sshPort, username, password, rosFolder, catkinWs);
    %
    %      % Use the diagnostic object without running a full test suite
    %      tester = robotics.slros.internal.diag.DeviceDiagnostics(modelName);
    %      tester.connect(hostname, sshPort, username, password);
    %      rosFolder = tester.recoverROSFolderFromCatkinWorkspace(catkinWs);
    
    %   Copyright 2016 The MathWorks, Inc.

    properties (Dependent)
        %RunMode - The run mode for the device diagnostics
        %   Possible values:
        %   'test'  - For testing purposes, print out all information,
        %             warnings, and errors.
        %   'build'    - At build time, do not print information and convert
        %                all high-priority warnings to errors. The user did
        %                not request to run the model.
        %   'buildrun' - At build time, do not print information and convert
        %                all high-priority warnings to errors. The user
        %                requested to run the model.
        %
        %   Default: 'test'
        RunMode
    end
    
    properties (SetAccess = private)
        %ModelName - The Simulink model associated with this
        ModelName
        
        %DiagnosticStream - The object streaming messages to an output
        DiagnosticStream
    end
    
    properties (Constant)
        %StepSeparator - Separator in output between diagnostic steps
        StepSeparator = '---'        
    end
    
    properties (Constant, Access = ?matlab.unittest.TestCase)
        %ValidRunModes - Valid strings for the RunMode property
        ValidRunModes = [robotics.slros.internal.diag.IDiagnosticStream.ValidRunModes, ...
            'buildrun']
    end
    
    properties (Access = ?matlab.unittest.TestCase)        
        %StandardROSDistributions - List of standard ROS distributions that we search for
        StandardROSDistributions = {'hydro', 'indigo', 'jade', 'kinetic'}
        
        %StandardInstallRoot - Root folder for standard ROS installation
        StandardInstallRoot = '/opt/ros'
        
        %SSHClient - The SSH client. It needs to be initialized via connectToDevice
        SSHClient
        
        %InternalRunMode - Internal storage for the run mode
        InternalRunMode = 'test'
    end
           
    properties (Dependent, Access = private)
        %IsSimulinkContext - Are the diagnostics invoked from Simulink context?
        %   This is just a convenience wrapper around the ModelName
        IsSimulinkContext
    end
    
    
    %% Main public interface
    methods
        function obj = DeviceDiagnostics(modelName)
            %DeviceDiagnostics Constructor
            
            narginchk(0,1)
            
            if nargin > 0
                validateattributes(modelName, {'char'}, {}, 'DeviceDiagnostics', 'modelName');
            else
                modelName = '';
            end
            
            if ~isempty(modelName)
                % Invoked from Simulink context. Use diagnostic viewer output.
                % Note that the modelName has to be non-empty to avoid
                % problems with obj.DiagnosticStream.
                obj.ModelName = modelName;
                
                % Use diagnostic viewer
                obj.DiagnosticStream = robotics.slros.internal.diag.DiagnosticViewerStream(modelName, true);
            else
                % Invoked from MATLAB context. Use command-line output.
                obj.ModelName = '';
                
                % Use command-line stream
                obj.DiagnosticStream = robotics.slros.internal.diag.CommandLineStream;
            end
        end
        
        function hasErrors = runDiagnostics(obj, deviceAddress, sshPort, username, password, rosFolder, catkinWs)
            %runDiagnostics Run the diagnostics on the ROS device
            
            % Synchronously execute the diagnostic run
            hasErrors = obj.runDiagnosticsImpl(deviceAddress, sshPort, username, password, rosFolder, catkinWs);
            
            % For asynchronous execution of the diagnostic run, consider
            % executing a timer call instead.
            %robotics_tests.ROSUtils.scheduleTimerCallback(0.1, ...
            %    @() obj.runDeviceDiagnosticsImpl(deviceAddress, username, password, rosFolder, catkinWs))
        end
        
        function sshClient = connect(obj, hostname, sshPort, username, password)
            %connect Connect to the ROS device with the given settings
            %   CONNECT(OBJ, HOSTNAME, SSHPORT, USERNAME, PASSWORD)
            %   connects to the ROS device with the given parameters
            %
            %   CONNECT(OBJ, SSHCLIENT) uses the initialized SSHCLIENT
            %   object to connect to the target device.
            %
            %   This function does two things:
            %   1. It initializes the internal SSHClient object
            %   2. It returns a handle to the SSHClient object
            
            if isa(hostname, 'robotics.codertarget.internal.ssh2client')
                % Syntax: CONNECT(OBJ, SSHCLIENT)
                obj.SSHClient = hostname;
            else
                % Syntax: CONNECT(OBJ, HOSTNAME, SSHPORT, USERNAME, PASSWORD)
                obj.SSHClient = robotics.codertarget.internal.ssh2client(hostname, username, password, sshPort);
            end
                        
            sshClient = obj.SSHClient;
        end
        
        function isSimulink = get.IsSimulinkContext(obj)
            isSimulink = ~isempty(obj.ModelName);
        end
    end
    
    %% Property getters and setters
    methods
        function runMode = get.RunMode(obj)
            %get.RunMode Custom getter for dependent RunMode property
            
            runMode = obj.InternalRunMode;
        end
        
        function set.RunMode(obj, runMode)
            %set.RunMode Custom setter for dependent RunMode property
            
            validateattributes(runMode, {'char'}, {'nonempty','row'}, 'DeviceDiagnostics', 'RunMode');
            validRunMode = validatestring(runMode, obj.ValidRunModes, ...
                'DeviceDiagnostics', 'RunMode');
            
            obj.InternalRunMode = validRunMode;
            
            % Adjust the diagnostic stream behavior
            switch validRunMode
                case 'test'
                    obj.DiagnosticStream.RunMode = 'test';
                case {'build', 'buildrun'}
                    obj.DiagnosticStream.RunMode = 'build';
            end
        end
    end
    
    %% Additional public methods
    methods
        function [hasSudo, requiresPassword] = hasSudoAccess(obj, password)
            %hasSudoAccess Determines if a user has sudo access
            %   HASSUDO is TRUE if the user has sudo access and FALSE
            %   otherwise. If HASSUDO is TRUE, then REQUIRESPASSWORD
            %   indicates if sudo calls require a password or not. If
            %   REQUIRESPASSWORD is FALSE, it is password-less sudo.

            % Initialize default return values
            hasSudo = false;
            requiresPassword = true;
            
            % Try password-less sudo first (-n means non-interactive sudo)
            try
                obj.SSHClient.execute('sudo -n true');
                hasSudo = true;
                requiresPassword = false;
                return;
            catch
                % Did not work
            end
            
            % Try sudo with password
            try
                obj.SSHClient.execute(['echo ' password '| sudo -S true']);
                hasSudo = true;
                requiresPassword = true;
                return;
            catch
                % This did not work either. The user is probably not part
                % of the sudoer list.
            end            
            
        end
        
        function folderExists = doesFolderExist(obj, folderName)
            %doesFolderExist Checks if folder with given name exists
            %   Returns TRUE if folder exists and FALSE otherwise.
            
            try 
                % Use the '-d' option to check for directory existence
                obj.SSHClient.execute(['[ -d ' obj.handleSpaces(folderName) ' ]']);
                
                % If the command executes successfully, the folder exists
                folderExists = true;
            catch ex        
                % If something unexpected goes wrong, e.g. SSH connection fails, 
                % rethrow the associated exception                
                if ~strcmp(ex.identifier, 'utils:sshclient:system')
                    rethrow(ex);
                end
                    
                % Directory does not exist
                folderExists = false;
            end
        end
        
        function fileExists = doesFileExist(obj, fileName)
            %doesFileExist Checks if file with given name exists
            %   Returns TRUE if file exists and FALSE otherwise.
            
            try 
                % Use the '-f' option to check for existence of regular files
                obj.SSHClient.execute(['[ -f ' obj.handleSpaces(fileName) ' ]']);
                
                % If the command executes successfully, the folder exists
                fileExists = true;
            catch ex                
                % If something unexpected goes wrong, e.g. SSH connection fails, 
                % rethrow the associated exception
                if ~strcmp(ex.identifier, 'utils:sshclient:system')
                    rethrow(ex);
                end
                    
                % File does not exist if exception 'utils:sshclient:system' is thrown                
                fileExists = false;
            end
        end
        
        function fileWritable = isFileWritable(obj, fileName)
            %isFileWritable Checks if file/folder with given name is writable by the user
            %   Returns TRUE if file/folder is writable and FALSE otherwise.
            %   Note that this function works for both files as well as
            %   folders.
            
            try 
                % Call with the '-w' option to check if file/folder is
                % writable
                obj.SSHClient.execute(['[ -w ' obj.handleSpaces(fileName) ' ]']);
                
                % If the command executes successfully, the folder exists
                fileWritable = true;
            catch ex              
                % If something unexpected goes wrong, e.g. SSH connection fails, 
                % rethrow the associated exception                
                if ~strcmp(ex.identifier, 'utils:sshclient:system')
                    rethrow(ex);
                end
                    
                % File does not exist
                fileWritable = false;
            end
       end
        
        function escapedPath = handleSpaces(~, filePath)
            %handleSpaces Handle spaces in file or folder path
            %   In the system command that we send over SSH, spaces in the
            %   path to a file or a folder need to be escaped with a backslash.
            
            escapedPath = strrep(filePath, ' ', '\ ');
            
            % If the spaces were already escaped, we should undo the
            % double-escaping
            escapedPath = strrep(escapedPath, '\\ ', '\ ');
        end
        
        function retValue = safeSSHExecute(obj, command)
            %safeSSHExecute Safe execution of SSH command
            %   Returns empty if the command execution triggered an error.
            
            try
                retValue = obj.SSHClient.execute(command);
            catch
                retValue = '';
            end
        end
        
        function isFolderValid = isROSFolderValid(obj, rosFolder)
            %isROSFolderValid Check if given folder contains a ROS distribution
            %   This is a simple test that only checks if the setup.bash
            %   file exists in the right place.
            
            % The existence test can handle multiple forward slashes,
            % so it is safe to concatenate.
            isFolderValid = obj.doesFolderExist(rosFolder) && ...
                obj.doesFileExist([rosFolder '/setup.bash']);
        end
        
        function isWsValid = isCatkinWorkspaceValid(obj, catkinWs)
            %isCatkinWorkspaceValid Check if given folder contains a valid Catkin workspace
            %   The user creates the Catkin workspace with
            %   catkin_init_workspace inside the <workspace_root>/src
            %   folder. This will create the src/CMakeLists.txt file. Check
            %   for the existence of that file.
            %   We also enforce that the user called catkin_make on top of
            %   the workspace, since we rely on the "setup.bash" sourcing
            %   at deployment time.
            
            isWsValid = obj.doesFileExist([catkinWs '/src/CMakeLists.txt']) && ...
                obj.doesFileExist([catkinWs '/devel/setup.bash']);
        end
        
        function rosFolder = recoverROSFolderFromCatkinWorkspace(obj, catkinWs)
            %recoverROSFolderFromCatkinWorkspace Get ROS base folder from Catkin workspace
            %   Each Catkin workspace is linked to its ROS installation and
            %   we can recover the ROS base folder
            %   This function returns an empty string if the operation is unsuccessful.
            
            % This only works if the Catkin workspace is valid
            setupUtilFile = obj.handleSpaces([catkinWs '/devel/_setup_util.py']);
            
            % The Python script contains a line similar to this ("indigo" being the ROS distro):
            %    CMAKE_PREFIX_PATH = '/opt/ros/indigo'.split(';')
            % Extract the ROS path by calling sed with a regular expression.
            rosFolder = obj.safeSSHExecute( ...
                ['sed -n ''s/.*CMAKE_PREFIX_PATH\s=\s''\''''\(.*\)''\''''.split.*/\1/p'' ' setupUtilFile]);
            rosFolder = strtrim(rosFolder);
        end
        
        function rosFolders = recoverROSFolderFromStandardLocations(obj)
            %recoverROSFolderFromStandardLocations Search standard folders for ROS installations
            %   Typically, ROS is installed under /opt/ros/*
            %   This function returns a cell array of ROS folders, as there
            %   might be multiple matches (if multiple ROS distributions
            %   are installed).
            
            rosFolders = {};
            for i = 1:length(obj.StandardROSDistributions)
                dist = obj.StandardROSDistributions{i};
                
                folderCandidate = [obj.StandardInstallRoot '/' dist];
                if obj.doesFolderExist(folderCandidate)
                    rosFolders{end+1} = folderCandidate; %#ok<AGROW>
                end
            end
        end
        
        function distName = getROSDistribution(obj, rosFolder)
            %getROSDistribution Get official ROS distribution name from ROS base folder
            %   This function returns an empty string if the operation is unsuccessful.
            
            % Recover distribution name from profile file
            profileFile = obj.handleSpaces([rosFolder '/etc/catkin/profile.d/10.ros.sh']);
            
            % The profile file contains a line similar to this:
            %    export ROS_DISTRO=indigo
            distName = obj.safeSSHExecute(['sed -n ''s/.*ROS_DISTRO=//p'' ' profileFile]);
            distName = strtrim(distName);
        end
        
        function createFolder(obj, folderPath)
            %createFolder Create a folder at the given path
            %   All intermediate folders will also be created.
            
            if ~obj.doesFolderExist(folderPath)
                obj.SSHClient.execute(['mkdir -p ' obj.handleSpaces(folderPath)]);
            end
        end
        
        function createCatkinWorkspace(obj, rosFolder, catkinWs)
            %createCatkinWorkspace Create a Catkin workspace in a given folder
            %   If the folder does not exist yet, it will be created.
            
            catkinWs = obj.handleSpaces(catkinWs);
            catkinSrcDir = [catkinWs '/src'];
            rosFolder = obj.handleSpaces(rosFolder);
            
            % Create folder if it does not exist yet
            obj.createFolder(catkinSrcDir);
            
            % Initialize the Catkin workspace. Note that you have to
            % execute the source call, catkin_init_workspace, and catkin_make
            % in one system command. Otherwise, the environment variables are not
            % persistent.
            cmd = ['source ' rosFolder '/setup.bash' ...
                ';' ...
                'catkin_init_workspace ' catkinSrcDir];
            
            try
                obj.SSHClient.execute(cmd);
            catch
                % This error might be okay if the Catkin workspace has
                % already been initialized, but catkin_make has not been
                % called.
                % Continue for now.
            end
            
            
            cmd = ['source ' rosFolder '/setup.bash' ...
                ';' ...
                'catkin_make -C ' catkinWs];
            obj.SSHClient.execute(cmd);
        end
        
        function taskingMode = modelTaskingMode(obj)
            %modelTaskingMode Return tasking mode for Simulink model
            %   There are two possible tasking modes: single-tasking and
            %   multi-tasking. Simulink also has an "Auto" mode. If the
            %   diagnostics are executed during build, we can resolve the
            %   "Auto" to the actual selected tasking mode.
            %
            %   TASKINGMODE is one of {'SingleTasking', 'MultiTasking',
            %   'Auto', ''}. If the tasking mode cannot be determined or if
            %   the diagnostics run in the MATLAB context return ''.
            
            taskingMode = '';
            
            if ~obj.IsSimulinkContext
                return;
            end

            % Get the solver mode setting from the current model name
            try
                acs         = getActiveConfigSet(obj.ModelName);
                taskingMode = getProp(acs, 'SolverMode');
            catch
                % Swallow the exception. This could happen if the model
                % name is no longer valid.
            end
            
            if isequal(obj.RunMode, 'test')
                return;
            end
            
            % If diagnostics are in build mode, then we can resolve the
            % 'Auto' tasking mode of the current model.
            % Typically, this check is expensive, since the model has be
            % updated, but since we are in build mode, the model update
            % already succeeded, so we can resolve 'Auto' to the actual
            % mode.
            try
                if strcmpi(taskingMode, 'auto')
                    if checkSingleTaskingSolver({obj.ModelName})
                        taskingMode = 'SingleTasking';
                    else
                        taskingMode = 'MultiTasking';
                    end
                end
            catch
                % Swallow the exception. This could happen if the model
                % name is not valid.                
            end
        end
    end
    
    
    %% Private methods that are used during the diagnostic run
    methods (Access = private)
        function hasErrors = runDiagnosticsImpl(obj, hostname, sshPort, username, password, rosFolder, catkinWs)
            %runDiagnosticsImpl Run diagnostics on the given device parameters
            
            runName = message('robotics:robotslros:devicediag:DiagRunName').getString;
            obj.DiagnosticStream.open(runName);
            
            % Close diagnostic stream when function exits or errors
            closeStream = onCleanup(@() obj.DiagnosticStream.close);
            
            % Try to ping device
            obj.pingDevice(hostname);
            
            % Try to connect SSH client
            obj.DiagnosticStream.reportInfo(obj.StepSeparator);
            sshClient = obj.connectToDevice(hostname, sshPort, username, password);
            if isempty(sshClient)
                hasErrors = true;
                return;
            end
            
            % Testing user privileges
            obj.DiagnosticStream.reportInfo(obj.StepSeparator);
            obj.userPrivileges(username, password);
            
            % Testing ROS distribution
            obj.DiagnosticStream.reportInfo(obj.StepSeparator);
            obj.detectROSDistribution(hostname, sshPort, username, password, rosFolder, catkinWs);
            
            % Testing Catkin workspace
            obj.DiagnosticStream.reportInfo(obj.StepSeparator);
            obj.checkCatkinWorkspace(hostname, sshPort, username, password, rosFolder, catkinWs);
            
            % Disconnect from the target
            obj.DiagnosticStream.reportInfo(obj.StepSeparator);
            obj.DiagnosticStream.reportInfo(['6. ' message('robotics:robotslros:devicediag:Disconnect', hostname).getString]);
            
            obj.DiagnosticStream.reportInfo(message('robotics:robotslros:devicediag:DiagnosticsDone').getString);
            
            % Shut down SSH connection
            sshClient.delete;
            
            hasErrors = obj.DiagnosticStream.ErrorCount > 0;            
        end
        
        function pingDevice(obj, hostname)
            %pingDevice Test if the device can be pinged
            
            obj.DiagnosticStream.reportInfo(['1. ' message('robotics:robotslros:devicediag:PingDevice', hostname).getString]);
            if ispc
                cmd = ['ping -n 1 ' hostname];
            else
                cmd = ['ping -c 1 ' hostname];
            end
            [st, msg] = system(cmd);
            if (st == 0) && ~isempty(regexpi(msg, '\sTTL='))
                obj.DiagnosticStream.reportInfo(message('robotics:robotslros:devicediag:PingDeviceSuccess').getString);
            else
                % If ping does not succeed, show a warning. It is likely
                % that subsequent operations will fail.
                obj.DiagnosticStream.reportHighPriorityWarning(message('robotics:robotslros:devicediag:PingDeviceFailure'));
            end
        end
        
        function sshClient = connectToDevice(obj, hostname, sshPort, username, password)
            %connectToDevice Connect to device over SSH
            %   The test will display an error and abort if it cannot
            %   connect to the device.
            
            obj.DiagnosticStream.reportInfo(['2. ' message('robotics:robotslros:devicediag:ConnectDevice', hostname, sshPort, username).getString]);
            try
                sshClient = obj.connect(hostname, sshPort, username, password);
                obj.DiagnosticStream.reportInfo(message('robotics:robotslros:devicediag:ConnectDeviceSuccess').getString);
            catch
                % A connection failure is a fatal error
                sshClient = [];
                obj.DiagnosticStream.reportError(message('robotics:robotslros:devicediag:ConnectDeviceFailure'));
            end
        end
        
        function userPrivileges(obj, username, password)
            %userPrivileges Confirm if user has admin privileges or not
            
            obj.DiagnosticStream.reportInfo(['3. ' message('robotics:robotslros:devicediag:SudoCheck', username).getString]);
            
            [hasSudo, requiresPassword] = obj.hasSudoAccess(password);
            if hasSudo
                if requiresPassword
                    sudoMsg = message('robotics:robotslros:devicediag:SudoWithPassword').getString;
                else
                    sudoMsg = message('robotics:robotslros:devicediag:SudoWithoutPassword').getString;
                end
               
                % Report positive result to user and return
                obj.DiagnosticStream.reportInfo(message('robotics:robotslros:devicediag:SudoCheckSuccess', sudoMsg).getString);
                return;
            end
            
            % The sudo call failed, so user has no admin rights
            % Determine the current model's tasking mode
            taskingMode = obj.modelTaskingMode;
            
            diag = message('robotics:robotslros:devicediag:SudoCheckFailure', obj.ModelName, taskingMode);
            
            % If tasking mode is 'MultiTasking', the severity is dependent
            % on the run mode. If not, use a standard warning.
            if strcmpi(taskingMode, 'multitasking')
                switch lower(obj.RunMode)
                    case 'build'
                        % If the user does not want to run the model, this
                        % is only a warning.
                        obj.DiagnosticStream.reportWarning(diag);
                    case 'buildrun'
                        % If the user wants to run the model, this
                        % is a high-priority warning.
                        obj.DiagnosticStream.reportHighPriorityWarning(diag);
                    otherwise
                        obj.DiagnosticStream.reportHighPriorityWarning(diag);
                end
            else
                obj.DiagnosticStream.reportWarning(diag);
            end
        end
        
        function detectROSDistribution(obj, hostname, sshPort, username, password, rosFolder, catkinWs)
            %detectROSDistribution Checking the validity of ROS distribution folder
            
            obj.DiagnosticStream.reportInfo(['4. ' message('robotics:robotslros:devicediag:ROSFolder').getString]);
            
            % Check first if the folder exists and if so, if it contains a
            % ROS installation.
            isFolderValid = false;
            if ~isempty(rosFolder)
                obj.DiagnosticStream.reportInfo(message('robotics:robotslros:devicediag:ROSFolderExist', rosFolder).getString);
                
                isFolderValid = obj.isROSFolderValid(rosFolder);
            end
            
            if isFolderValid
                % Best case: Folder contains ROS. Recover distribution name
                % and return.
                distName = obj.getROSDistribution(rosFolder);
                obj.DiagnosticStream.reportInfo(message('robotics:robotslros:devicediag:ROSFolderExistSuccess', upper(distName), rosFolder).getString);
                return
            end
            
            % Folder is not valid or does not contain a ROS distribution.
            % Give the user some options to recover the correct folder.
            if isempty(catkinWs)
                % No Catkin workspace is given, so that restricts the FixIt
                % options.
                obj.DiagnosticStream.reportHighPriorityWarning(message('robotics:robotslros:devicediag:ROSFolderExistFailureNoCatkin', ...
                    rosFolder, hostname, sshPort, username, password, obj.ModelName));
            else
                % With a Catkin workspace, we have another option for
                % recovering the ROS installation folder
                obj.DiagnosticStream.reportHighPriorityWarning(message('robotics:robotslros:devicediag:ROSFolderExistFailure', ...
                    rosFolder, hostname, sshPort, username, password, catkinWs, obj.ModelName));
            end
        end
        
        
        function checkCatkinWorkspace(obj, hostname, sshPort, username, password, rosFolder, catkinWs)
            %checkCatkinWorkspace Check the validity of the Catkin workspace
            
            obj.DiagnosticStream.reportInfo(['5. ' message('robotics:robotslros:devicediag:CatkinWs', catkinWs).getString]);
            
            % Check if folder exists
            if ~obj.doesFolderExist(catkinWs)
                % If not, give the user the option to create it
                
                if obj.isROSFolderValid(rosFolder)
                    % If we have a valid ROS folder, we can create the
                    % folder AND initialize the Catkin workspace
                    diag = message('robotics:robotslros:devicediag:FolderDoesNotExistWithCatkin', catkinWs, hostname, sshPort, username, password, rosFolder);
                else
                    % We can only create the folder, since we do not know
                    % where ROS is installed.
                    diag = message('robotics:robotslros:devicediag:FolderDoesNotExistNoCatkin', catkinWs, hostname, sshPort, username, password);
                end
                
                obj.DiagnosticStream.reportHighPriorityWarning(diag);
                
                % No point in continuing. Return.
                return;
            end
            
            % Folder exists
            obj.DiagnosticStream.reportInfo(message('robotics:robotslros:devicediag:FolderExists').getString);
            
            % Test if folder is writable
            if ~obj.isFileWritable(catkinWs)
                % If not, show a warning and return.
                obj.DiagnosticStream.reportHighPriorityWarning(message('robotics:robotslros:devicediag:FolderWritableFailure', username));
                return;
            end
            
            % Folder is writable
            obj.DiagnosticStream.reportInfo(message('robotics:robotslros:devicediag:FolderWritableSuccess').getString);
            
            % Check if Catkin workspace is set up correctly.
            if ~obj.isCatkinWorkspaceValid(catkinWs)
                if obj.isROSFolderValid(rosFolder)
                    % If we have a valid ROS folder, so we can
                    % initialize the Catkin workspace
                    diag = message('robotics:robotslros:devicediag:CatkinWsNotValid', catkinWs, hostname, sshPort, username, password, rosFolder);
                else
                    % We cannot initialize the workspace, because we do not
                    % know where ROS is located.
                    diag = message('robotics:robotslros:devicediag:CatkinWsNotValidNoROS', catkinWs);
                end
                
                obj.DiagnosticStream.reportHighPriorityWarning(diag);
                
                return;
            end
            
            % All checks passed successfully
            obj.DiagnosticStream.reportInfo(message('robotics:robotslros:devicediag:CatkinWsValid').getString);
        end
    end
    
end

