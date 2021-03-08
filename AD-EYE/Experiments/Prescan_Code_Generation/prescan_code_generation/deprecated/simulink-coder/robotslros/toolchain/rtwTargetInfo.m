function rtwTargetInfo(tr)
%RTWTARGETINFO Register toolchain
if exist('codertarget.TargetRegistry', 'class') == 8
    codertarget.TargetRegistry.addToTargetRegistry(@loc_registerThisTarget);
    codertarget.TargetBoardRegistry.addToTargetBoardRegistry(@loc_registerBoardsForThisTarget);
end 
% Copyright 2014-2017 The MathWorks, Inc.
tr.registerTargetInfo(@loc_createToolchain);

end

%--------------------------------------------------------------------------
function config = loc_createToolchain
rootDir = fileparts(mfilename('fullpath'));
config = coder.make.ToolchainInfoRegistry; % initialize
archName = computer('arch');

% LINARO GNUARM 4.8
config(end+1).Name              = 'Catkin';
config(end).Alias               = ['CATKIN_', upper(archName)];
config(end).TargetHWDeviceType	= {'*'};
config(end).FileName            = fullfile(rootDir, ['catkin_toolchain_gmake_', archName, '_v1.0.mat']);
config(end).Platform            = {archName};
end
% [EOF]
function ret = loc_registerThisTarget()
ret.Name = 'Robot Operating System (ROS)';
[targetFilePath, ~, ~] = fileparts(fileparts(mfilename('fullpath')));
ret.TargetFolder = fullfile(targetFilePath);

% TargetType=2 indicates that code may be generated with just Simulink Coder
ret.TargetType = 2;
end

% -------------------------------------------------------------------------
function boardInfo = loc_registerBoardsForThisTarget()
target = 'Robot Operating System (ROS)';
[targetFolder, ~, ~] = fileparts(fileparts(mfilename('fullpath')));
targetFolder = fullfile(targetFolder);
boardFolder = codertarget.target.getTargetHardwareRegistryFolder(targetFolder);
boardInfo = codertarget.target.getTargetHardwareInfo(targetFolder, boardFolder, target);
end

%% ------------------------------------------------------------------------
function isConfigSetCompatible = i_isConfigSetCompatible(configSet) %#ok<DEFNU>
isConfigSetCompatible = false;
if configSet.isValidParam('CoderTargetData')
    data = configSet.getParam('CoderTargetData');
    isConfigSetCompatible = isequal(data.TargetHardware, 'Robot Operating System (ROS)');
end
end