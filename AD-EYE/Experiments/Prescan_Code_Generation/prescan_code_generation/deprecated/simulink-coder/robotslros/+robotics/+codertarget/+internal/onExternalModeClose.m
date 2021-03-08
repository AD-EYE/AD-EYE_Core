function onExternalModeClose(hCS)
%This function is for internal use only. It may be removed in the future.

%onExternalModeClose Close function for one click external mode
%   This function is called under the following conditions:
%   - The external mode model reached the end of its simulation time
%   - The user pressed "Stop" during the external mode simulation
%   - An error occurred during the external mode simulation

%   Copyright 2016 The MathWorks, Inc.

modelName = robotics.codertarget.internal.getModelName(hCS);
diagStage = robotics.slros.internal.diag.DiagnosticViewerStream(modelName, false);
diagStage.open(message('robotics:robotslros:extmode:ExternalModeStage').getString);
    
diagStage.reportInfo(message('robotics:robotslros:extmode:ExternalModeClose', ...
    codertarget.attributes.getExtModeData('IPAddress', hCS)).getString)

% Re-enable external mode warnings about unsupported bus signals
warning('on', 'Simulink:Engine:ExtModeCannotDownloadParamBecauseNoHostToTarget');

end



