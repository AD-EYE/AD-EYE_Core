classdef DeviceParameterSpecifier < handle
    %This class is for internal use only. It may be removed in the future.
    
    %  DeviceParameterSpecifier opens a DDG dialog that lets the user
    %  specify the parameters for connecting to a ROS device, e.g. user
    %  name, password, device address.
    %
    %  Example:
    %    userDlg = robotics.slros.internal.dlg.DeviceParameterSpecifier
    %    userDlg.openDialog
    
    %   Copyright 2016-2018 The MathWorks, Inc.
    
    properties (Access = private)
        %Parser - The parsing helper object
        Parser 
        
        %CloseFcnHandle - The user-specified function handle called when the dialog closes
        %   This function handle is invoked when the user clicks "OK" or
        %   "Cancel".
        CloseFcnHandle = function_handle.empty
        
        %Hostname - The hostname or IP address of the device
        %   This is part of the 'DeviceAddress' property.
        Hostname
        
        %SSHPort - SSH port used to connect to the device (default is 22)
        %   This is part of the 'DeviceAddress' property.
        SSHPort
        
        %IsSticky - Is dialog sticky with respect to other DDG windows
        %   If this is set to true, the user will not be able to interact 
        %   with any other DDG dialogs or the model explorer until he 
        %   dismisses the sticky dialog.        
        IsSticky = false
        
        %PreventCloseCallback - If TRUE, ignore callbacks received through the dialog CloseMethod
        %   Since we are using custom buttons in this dialog, we are
        %   handling the dialog closing ourselves, so this flag gives us
        %   more control.
        PreventCloseCallback = false        
    end
    
    properties (SetObservable = true)
        %ModelName - The name of the Simulink model associated with this device connection
        ModelName = ''
        
        %DeviceAddress - Contents of the device address edit field
        %   Note that device addresses can also contain the SSH port, e.g.
        %   '192.168.1.1:40763'. The individual elements are stored in the
        %   'Hostname' and 'SSHPort' properties.
        DeviceAddress@asciiString
        
        %Username - Contents of the user name edit field
        Username@asciiString
        
        %Password - Contents of the password edit field
        Password@asciiString
        
        %ROSInstallFolder - Contents of the ROS folder edit field
        ROSInstallFolder@asciiString
        
        %CatkinWorkspace - Contents of the Catkin workspace edit field
        CatkinWorkspace@asciiString
        
        %RememberPassword - State of the "Remember my password" checkbox
        RememberPassword@logical scalar
        
    end
    
    properties (Dependent, SetAccess = private)
        %DialogTag - Unique tag for dialog
        %   This can be used to find the dialog with the findDDGByTag
        %   function.
        DialogTag
    end
    
    methods (Static)
        function deviceParamDlg = openDialogForModel(modelName, varargin)
            %openDialogForModel Convenience function for opening a dialog for a Simulink model
            [deviceParamDlg, dlg] = robotics.slros.internal.dlg.DeviceParameterSpecifier.getCurrentInstance(modelName);
            if isempty(deviceParamDlg)
                deviceParamDlg = robotics.slros.internal.dlg.DeviceParameterSpecifier;
                deviceParamDlg.ModelName = modelName;
                deviceParamDlg.openDialog(varargin{:});
            else
                dlg.show();
            end
        end
        
        function [out, dlg] = getCurrentInstance(modelName)
            %getCurrentInstance Current instance of open dialog window.
            %    This is used by the 'fixit' functionality. The function
            %    returns [] if the dialog window is not open.
            tag = robotics.slros.internal.dlg.DeviceParameterSpecifier.getDialogTag(modelName);
            dlgs = findDDGByTag(tag);
            if ~isempty(dlgs)
                dlg = dlgs(end);
                out = dlg.getDialogSource;
            else
                out = [];
                dlg = [];
            end
        end
        
        function tag = getDialogTag(modelName)
            %getDialogTag Get dialog tag corresponding to a Simulink model.
            %    Return tag for a global instance if no model is specified.
            base = robotics.slros.internal.dlg.DeviceParameterSpecifier.DialogTagBase;
            if isempty(modelName)
                tag = base;
            else
                tag = [base, '_', modelName];
            end
        end
        
        function setROSInstallFolder(modelName, rosFolder)
            %setROSInstallFolder Set ROS install folder for a specified
            %    model. If the dialog is open for the given model, it will
            %    set the dialog's folder. Otherwise, it will set the global
            %    DeviceParameters folder.
            dlg = robotics.slros.internal.dlg.DeviceParameterSpecifier.getCurrentInstance(modelName);
            if ~isempty(dlg)
                % Set for dialog if it exists and allow user to accept or reject
                dlg.ROSInstallFolder = rosFolder;
            else
                % Set globally otherwise
                robotics.codertarget.internal.DeviceParameters.setROSInstallFolder(rosFolder);
            end
        end
    end
    
    methods
        function obj = DeviceParameterSpecifier
            %DeviceParameterSpecifier Standard constructor
            
            obj.Parser = robotics.slros.internal.DeviceParameterParser;
        end
        
        function tag = get.DialogTag(obj)
            tag = robotics.slros.internal.dlg.DeviceParameterSpecifier.getDialogTag(obj.ModelName);
        end
        
        function dlg = openDialog(obj, closeFcnHandle, isSticky)
            %openDialog Open the dialog window
            %   openDialog(OBJ) opens the dialog window
            %
            %   openDialog(OBJ, CLOSEFCNHANDLE) allows you to specify a
            %   function handle that will be called when the dialog is
            %   closed (user clicks OK or Cancel).
            %   CLOSEFCNHANDLE is a function handle that takes 6 arguments,
            %   e.g.
            %
            %   closeFcn(closeAction, deviceAddress, hostname, sshport, username, password, rosfolder, catkinws)
            %      closeAction - Either 'ok' or 'cancel' to indicate what button the user pressed
            %      deviceAddress - Last value for device address (combination of hostname and sshport)
            %      hostname - Hostname or IP address
            %      sshport - SSH port used for connection
            %      username - Last value for username
            %      password - Last value for password
            %      rosFolder - Last value for ROS folder
            %      catkinWs - Last value for Catkin workspace
            %
            %   openDialog(OBJ, CLOSEFCNHANDLE, ISSTICKY) lets you indicate
            %   if the dialog should be sticky (modal) or not. ISSTICKY is
            %   a logical scalar.
            
            if exist('closeFcnHandle', 'var')
                validateattributes(closeFcnHandle, {'function_handle'}, {'scalar'});
                obj.CloseFcnHandle = closeFcnHandle;
            else
                obj.CloseFcnHandle = function_handle.empty;
            end
            
            if exist('isSticky', 'var')
                validateattributes(isSticky, {'logical'}, {'scalar'});
                obj.IsSticky = isSticky;
            end
            
            % Reset close callback handling
            obj.PreventCloseCallback = false;
            
            % Initialize the data from the MATLAB preferences
            obj.Hostname = robotics.codertarget.internal.DeviceParameters.getHostname;
            obj.SSHPort = robotics.codertarget.internal.DeviceParameters.getSSHPort;
            
            % Assign the values of the properties associated with dialog
            % widgets
            obj.DeviceAddress = robotics.codertarget.internal.DeviceParameters.getDeviceAddress;
            obj.Username = robotics.codertarget.internal.DeviceParameters.getUsername;
            obj.Password = robotics.codertarget.internal.DeviceParameters.getPassword;
            obj.RememberPassword = robotics.codertarget.internal.DeviceParameters.getSavePassword;
            obj.CatkinWorkspace = robotics.codertarget.internal.DeviceParameters.getCatkinWorkspace;
            obj.ROSInstallFolder = robotics.codertarget.internal.DeviceParameters.getROSInstallFolder;
            
            % Bring up the dialog window
            dlg = DAStudio.Dialog(obj);
        end
        
        function [isAccepted, hostname, sshPort, username, password, rosFolder, catkinWs] = ...
                openDialogAndWait(obj)
            %openDialogAndWait Open dialog and wait until the user closes it
            %   This function is blocking. This window is not model
            %   (sticky), because we want the user to interact with the
            %   diagnostic window when testing device parameters.
            %
            %   The function will return the final value of all internal
            %   device parameters.
            
            % Bring up the dialog window
            dlg = obj.openDialog(@closeDialog, false);
            
            % Wait for dialog to be closed (closeDialog callback is
            % executed at that point)
            waitfor(dlg);
            
            % All output values have already been assigned in the callback
            % Note that the device parameters have to be stored in this
            % callback. If we wait until the code gets here, the dialog has
            % already been deleted and the obj properties are not in a
            % valid state anymore.
            
            function closeDialog(finalaction, ~, hname, ssh, uname, pw, rosdir, ws)
                
                % Set all output value
                isAccepted = isequal(finalaction, 'ok');                
                hostname = hname;
                sshPort = ssh;
                username = uname;
                password = pw;
                rosFolder = rosdir;
                catkinWs = ws;
            end            
        end
    end
    
    methods (Hidden)
        
        function okayButtonPressed(obj, dlg)
            %okayButtonPressed Callback that is executed when the OK button is pressed
            
            try
                % Always save device address, user name, remember password
                % selection, catkin workspace, and ROS install folder when
                % user clicks "OK
                robotics.codertarget.internal.DeviceParameters.setHostname(obj.Hostname);
                robotics.codertarget.internal.DeviceParameters.setSSHPort(obj.SSHPort);
                robotics.codertarget.internal.DeviceParameters.setUsername(obj.Username);
                robotics.codertarget.internal.DeviceParameters.setSavePassword(obj.RememberPassword);
                robotics.codertarget.internal.DeviceParameters.setCatkinWorkspace(obj.CatkinWorkspace);
                robotics.codertarget.internal.DeviceParameters.setROSInstallFolder(obj.ROSInstallFolder);
                
                % Only save password if user selected "Remember my password"
                if obj.RememberPassword
                    robotics.codertarget.internal.DeviceParameters.setPassword(obj.Password);
                else
                    % Reset any saved password if the user selects to not save it
                    robotics.codertarget.internal.DeviceParameters.setPassword('');
                end
                
                % Evaluate function handle for closing
                obj.evaluateCloseFcn('ok');
                
                % Close dialog. To prevent additional callbacks through
                % dlgClose, set a flag.
                obj.PreventCloseCallback = true;
                dlg.delete
                
            catch ex
                % Convert all errors to warnings. If they are propagated back to
                % DDG, this causes MATLAB to crash
                
                warning(ex.identifier, '%s', ex.message)
            end
        end
        
        
        function cancelButtonPressed(obj, dlg)
            %cancelButtonPressed Callback that is executed when the Cancel button is pressed
            
            try
                % Evaluate function handle for closing
                obj.evaluateCloseFcn('cancel');
                
                % Close dialog without applying any changes.
                % To prevent additional callbacks through dlgClose, set a
                % flag.
                obj.PreventCloseCallback = true;
                dlg.delete
                
            catch ex
                % Convert all errors to warnings. If they are propagated back to
                % DDG, this causes MATLAB to crash
                
                warning(ex.identifier, '%s', ex.message)
            end
        end
        
        function testButtonPressed(obj, ~)
            %testButtonPressed Callback that is executed when the Test button is pressed
            
            try
                % Run a check on all the user settings
                tester = robotics.slros.internal.diag.DeviceDiagnostics(obj.ModelName);
                tester.runDiagnostics(obj.Hostname, obj.SSHPort, obj.Username, obj.Password, obj.ROSInstallFolder, obj.CatkinWorkspace);
                
            catch ex
                % Convert all errors to warnings. If they are propagated back to
                % DDG, this causes MATLAB to crash
                
                warning(ex.identifier, '%s', ex.message)
            end
        end
        
        function dlgClose(obj, closeaction)
            %dlgClose Callback executed when dialog is closed
            %   This callback is executed if the dialog gets deleted or
            %   the user clicks the X to close the dialog.
            %   We are using custom OK and Cancel buttons and in their
            %   callbacks, the dialog is deleted as well. To prevent double
            %   callbacks, use the PreventCloseCallback flag to indicate if
            %   additional actions should be performed in dlgClose.
            %
            %   CLOSEACTION is always 'cancel', since we do not use the
            %   standard OK button.
            
            try
                if obj.PreventCloseCallback
                    % Do not do anything if this callback was triggered by
                    % our custom OK or Cancel buttons. They already handled
                    % all necessary actions.
                    return;
                end
                
                % Evaluate function handle for closing
                obj.evaluateCloseFcn(closeaction);
                
            catch ex
                % Convert all errors to warnings. If they are propagated back to
                % DDG, this causes MATLAB to crash
                
                warning(ex.identifier, '%s', ex.message)
            end
        end
        
        function evaluateCloseFcn(obj, closeaction)
            %evaluateCloseFcn Evaluate the CloseFcnHandle callback
            
            if ~isempty(obj.CloseFcnHandle)
                feval(obj.CloseFcnHandle, closeaction, obj.DeviceAddress, ...
                    obj.Hostname, obj.SSHPort, obj.Username, obj.Password, ...
                    obj.ROSInstallFolder, obj.CatkinWorkspace);
            end
        end
        
        function validateDeviceAddress(obj, deviceAddress, argName)
            %validateDeviceAddress Validate the device address string
            %   Also separate the host name / IP address from the SSH port.
            %   Some examples of valid device addresses:
            %      localhost
            %      somehost:225
            %      192.168.2.1
            %      192.168.2.1:40763
            
            [validHost, validSSHPort] = obj.Parser.validateDeviceAddress(deviceAddress, '', argName);
            
            obj.Hostname = validHost;
            obj.SSHPort = validSSHPort;
        end
    end
    
    properties (Constant, Access = ?matlab.unittest.TestCase)
        %% Tags for all widget elements.
        %  Make the tags accessible to unit tests to verify settings.
        
        DialogTagBase = 'DeviceParameterSpecifierDialog'
        TextHeaderTag = 'textHeader'
        EditDeviceAddressTag = 'editDeviceAddress'
        EditUsernameTag = 'editUsername'
        EditPasswordTag = 'editPassword'
        CheckboxRememberTag = 'checkboxRememberPw'
        EditROSFolderTag = 'editROSFolder'
        EditCatkinWorkspaceTag = 'editCatkinWs'
        ButtonHelpTag = 'buttonHelp'
        ButtonOKTag = 'buttonOK'
        ButtonCancelTag = 'buttonCancel'
        ButtonTestTag = 'buttonTest'
        ButtonPanelTag = 'panelButtonSet'
    end
    
    methods (Hidden)
        function dlgstruct = getDialogSchema(obj)
            %getDialogSchema Specify the DDG schema of the dialog
            
            % Widget for header text
            header.Name = message('robotics:robotslros:deviceparams:DialogHeader').getString;
            header.Type = 'text';
            header.Tag = obj.TextHeaderTag;
            header.MinimumSize = [0 50];
            header.RowSpan = [1 1];
            header.ColSpan = [2 2];
            header.HideName = true;
            header.WordWrap = true;
            
            % Widget for device address
            deviceAddressLabel = message('robotics:robotslros:deviceparams:DeviceAddress').getString;
            deviceAddress.Name = [deviceAddressLabel ': '];
            deviceAddress.Type = 'edit';
            deviceAddress.Tag = obj.EditDeviceAddressTag;
            deviceAddress.RowSpan = [2 2];
            deviceAddress.ColSpan = [2 2];
            deviceAddress.ObjectProperty = 'DeviceAddress';     % Use an object property to store the value of the edit field
            deviceAddress.Mode = true;                          % Update the property in immediate mode
            deviceAddress.ValidationCallback = @(~,~,deviceAddress,~) ...
                obj.validateDeviceAddress(deviceAddress, deviceAddressLabel);
            deviceAddress.ToolTip = message('robotics:robotslros:deviceparams:DeviceAddressTooltip').getString;
            
            % Widget for username
            usernameLabel = message('robotics:robotslros:deviceparams:Username').getString;
            username.Name = [usernameLabel ': '];
            username.Type = 'edit';
            username.Tag = obj.EditUsernameTag;
            username.RowSpan = [3 3];
            username.ColSpan = [2 2];
            username.ObjectProperty = 'Username';
            username.Mode = true;
            username.ValidationCallback = @(~,~,username,~) obj.Parser.validateUsername(username, '', usernameLabel);
            username.ToolTip = message('robotics:robotslros:deviceparams:UsernameTooltip').getString;
            
            % Widget for password
            passwordLabel = message('robotics:robotslros:deviceparams:Password').getString;
            password.Name = [passwordLabel ': '];
            password.Type = 'edit';
            password.Tag = obj.EditPasswordTag;
            password.EchoMode = 'password';         % Obfuscate password characters
            password.RowSpan = [4 4];
            password.ColSpan = [2 2];
            password.ObjectProperty = 'Password';
            password.Mode = true;
            password.ValidationCallback = @(~,~,pw,~) obj.Parser.validatePassword(pw, '', passwordLabel);
            password.ToolTip = message('robotics:robotslros:deviceparams:PasswordTooltip').getString;
            
            % Widget for remember password checkbox
            rememberPw.Name = message('robotics:robotslros:deviceparams:RememberPassword').getString;
            rememberPw.Type = 'checkbox';
            rememberPw.Tag = obj.CheckboxRememberTag;
            rememberPw.MinimumSize = [0 50];
            rememberPw.RowSpan = [5 5];
            rememberPw.ColSpan = [2 2];
            rememberPw.ObjectProperty = 'RememberPassword';
            rememberPw.Mode = true;
            rememberPw.ToolTip = message('robotics:robotslros:deviceparams:RememberPasswordTooltip').getString;
            
            % Widget for Catkin workspace
            catkinWsLabel = message('robotics:robotslros:deviceparams:CatkinWorkspace').getString;
            catkinWs.Name = [catkinWsLabel ': '];
            catkinWs.Type = 'edit';
            catkinWs.Tag = obj.EditCatkinWorkspaceTag;
            catkinWs.RowSpan = [7 7];
            catkinWs.ColSpan = [2 2];
            catkinWs.ObjectProperty = 'CatkinWorkspace';
            catkinWs.Mode = true;
            catkinWs.ValidationCallback = @(~,~,ws,~) obj.Parser.validateCatkinWorkspace(ws, '', catkinWsLabel);
            catkinWs.ToolTip = message('robotics:robotslros:deviceparams:CatkinWorkspaceTooltip').getString;
            
            % Widget for ROS folder
            rosFolderLabel = message('robotics:robotslros:deviceparams:ROSFolder').getString;
            rosFolder.Name = [rosFolderLabel ': '];
            rosFolder.Type = 'edit';
            rosFolder.Tag = obj.EditROSFolderTag;
            rosFolder.RowSpan = [6 6];
            rosFolder.ColSpan = [2 2];
            rosFolder.ObjectProperty = 'ROSInstallFolder';
            rosFolder.Mode = true;
            rosFolder.ValidationCallback = @(~,~,dir,~) obj.Parser.validateROSFolder(dir, '', rosFolderLabel);
            rosFolder.ToolTip = message('robotics:robotslros:deviceparams:ROSFolderTooltip').getString;
            
            % Custom help button
            helpButton.Name = message('robotics:robotslros:deviceparams:HelpButton').getString;
            helpButton.Type = 'pushbutton';
            helpButton.MatlabMethod = 'robotics.slros.internal.helpview';
            helpButton.MatlabArgs = {'deviceParamsDlg'};  % doc topic id
            helpButton.RowSpan = [1 1];
            helpButton.ColSpan = [4 4];
            helpButton.Tag = obj.ButtonHelpTag;
            
            % Custom test button
            testButton.Name = message('robotics:robotslros:deviceparams:TestButton').getString;
            testButton.Type = 'pushbutton';
            testButton.RowSpan = [1 1];
            testButton.ColSpan = [3 3];
            testButton.Tag = obj.ButtonTestTag;
            testButton.ObjectMethod = 'testButtonPressed';
            testButton.MethodArgs = {'%dialog'}; % object handle is implicit first arg
            testButton.ArgDataTypes = {'handle'}; % 'handle' is type of %dialog
            testButton.ToolTip = message('robotics:robotslros:deviceparams:TestButtonTooltip').getString;
            
            % Custom OK button
            okButton.Name = message('robotics:robotslros:deviceparams:OKButton').getString;
            okButton.Type = 'pushbutton';
            okButton.RowSpan = [1 1];
            okButton.ColSpan = [1 1];
            okButton.Tag = obj.ButtonOKTag;
            okButton.ObjectMethod = 'okayButtonPressed';
            okButton.MethodArgs = {'%dialog'}; % object handle is implicit first arg
            okButton.ArgDataTypes = {'handle'}; % 'handle' is type of %dialog
            
            % Custom Cancel button
            cancelButton.Name = message('robotics:robotslros:deviceparams:CancelButton').getString;
            cancelButton.Type = 'pushbutton';
            cancelButton.RowSpan = [1 1];
            cancelButton.ColSpan = [2 2];
            cancelButton.Tag = obj.ButtonCancelTag;
            cancelButton.ObjectMethod = 'cancelButtonPressed';
            cancelButton.MethodArgs = {'%dialog'}; % object handle is implicit first arg
            cancelButton.ArgDataTypes = {'handle'}; % 'handle' is type of %dialog
            
            % Construct custom button panel
            % We cannot use the standard StandaloneButtonSet, because we want
            % to add the custom "Test" button to the same panel.
            buttonPanel.Type = 'panel';
            buttonPanel.LayoutGrid = [1 4];
            buttonPanel.Items = {okButton, cancelButton, helpButton, testButton};
            buttonPanel.Tag = obj.ButtonPanelTag;
            
            % Main dialog structure
            dlgstruct.DialogTitle = message('robotics:robotslros:deviceparams:DialogTitle').getString;
            dlgstruct.DialogTag = obj.DialogTag;
            dlgstruct.LayoutGrid = [7, 3];
            dlgstruct.ColStretch = [1, 10, 1];
            dlgstruct.StandaloneButtonSet = buttonPanel;        % Use custom button panel
            dlgstruct.Items = { header, deviceAddress, username, password, rememberPw, rosFolder, catkinWs};
            dlgstruct.Sticky = obj.IsSticky;
            dlgstruct.CloseMethod = 'dlgClose';            
            dlgstruct.CloseMethodArgs = {'%closeaction'};
            dlgstruct.CloseMethodArgsDT = {'string'};
        end
    end
end
