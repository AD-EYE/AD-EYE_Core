function openCredentialsDialog(hObj, hDlg, ~, ~)
%This function is for internal use only. It may be removed in the future.

%openCredentialsDialog Open dialog for user to specify credentials
%   This function is called when the user presses the "Edit" buttons in the
%   ROS configuration parameter pane.
%   The 4 input arguments are:
%     hObj - The coder target SettingsController objects
%     hDlg - The DAStudio.Dialog associated with the config params
%     tag  - The unique tag of the widget, e.g. 'Tag_ConfigSet_CoderTarget_SetDeviceInfo2'
%     widgetType - The type of the DDG widget, e.g. 'pushbutton'

%   Copyright 2016-2017 The MathWorks, Inc.

% Only a single instance of the window is allowed to be open
mdlName = robotics.codertarget.internal.getModelName(hObj);
existingDlg = findDDGByTag(robotics.slros.internal.dlg.DeviceParameterSpecifier.getDialogTag(mdlName));
if ~isempty(existingDlg)
    % Bring existing dialog to foreground and return
    existingDlg(1).show;
    
    % Close all other dialogs (this is a degenerate condition)
    for i = 2:length(existingDlg)
        existingDlg(i).delete;
    end
    
    return;
end

% Create dialog and assign close callback

userDlg = robotics.slros.internal.dlg.DeviceParameterSpecifier.openDialogForModel(...
        mdlName, @(varargin) closeDialog(hDlg, varargin{:}));   %#ok<NASGU>

    function closeDialog(hDlg, closeAction, deviceAddress, ~, ~, userName, ~, rosFolder, catkinWs)
        %closeDialog Executed when the dialog is closed
        %   closeAction will be one of {'ok', 'cancel'}
        
        % Only execute this function if the dialog closed with an "OK"
        % button press
        if ~strcmpi(closeAction, 'ok')
            return;
        end
        
        % Reflect device parameter changes in the configuration parameter
        % pane.
        if isa(hDlg, 'ConfigSet.DDGWrapper') || isa(hDlg, 'qeConfigSet.Dialog')
            % Only set widget value if config parameters are still open
            
            hDlg.setWidgetValue(robotics.slros.internal.Constants.TagCSDeviceAddress, deviceAddress);
            hDlg.setWidgetValue(robotics.slros.internal.Constants.TagCSUsername, userName);
            hDlg.setWidgetValue(robotics.slros.internal.Constants.TagCSInstallFolder, rosFolder);
            hDlg.setWidgetValue(robotics.slros.internal.Constants.TagCSCatkinWorkspace, catkinWs);
        end
    end

end

