function returnInfo = recoverROSFolderFromWorkspace( hostname, sshPort, username, password, catkinWs, modelName )
%This function is for internal use only. It may be removed in the future.

%recoverROSFolderFromWorkspace Recover the ROS installation folder from a Catkin workspace
%   This function is called by the "FixIt" diagnostic action if the ROS
%   folder is not valid and the user wants to use the Catkin workspace
%   to recover it.

%   Copyright 2016 The MathWorks, Inc.
if nargin < 6
    modelName = '';
end

% Connect to device
diag = robotics.slros.internal.diag.DeviceDiagnostics(modelName);
diag.connect(hostname, sshPort, username, password);

% Recover the ROS folder. This will return empty if the operation fails.
rosFolder = diag.recoverROSFolderFromCatkinWorkspace(catkinWs);

if ~isempty(rosFolder)
    % Found ROS installation folder
    distName = diag.getROSDistribution(rosFolder);
    robotics.slros.internal.dlg.DeviceParameterSpecifier.setROSInstallFolder(modelName, rosFolder);
    returnInfo = message('robotics:robotslros:devicediag:ROSFolderRecoverySuccess', upper(distName), rosFolder).getString;
else
    % Did not find a install ROS folder. Throw an exception.
    error(message('robotics:robotslros:devicediag:ROSFolderCatkinRecoveryFailure', catkinWs));
end

end

