%% gitPush
system('git checkout dev')
system('git push')


%% gitPull

% This part is already included in TA.m
table = '.\TAsetup.xlsx';
setupVariableTable = readtable(table,'ReadRowNames',false);
for h = 1:height(setupVariableTable)
    assignin('base', char(setupVariableTable.VarName(h)), char(setupVariableTable.VarValue(h)));
end

device = rosdevice(ipaddress,user,password); %setting up the device
device.CatkinWorkspace = catkin_workspace; %setting up the catkin workspace
device.ROSFolder = ROS_folder; %setting up the ROS folder

% This is the new part
shFolderPath = '/home/adeye/AD-EYE_Core/AD-EYE/ROS_Packages/src/AD-EYE/sh';
gitPull = strcat(shFolderPath, '/' , 'gitPull.sh');