% nb_runs = 240;
% nb_runs = 480;
% 
% folderNames = ["W15_Road_Side_Parking\W15_Road_Side_Parking_no_camera"];
% prescanExperimentTemplates = ["W15_Road_Side_Parking"];
% TARosParametersTemplates = ["AutowareConfigTemplate.xlsx"];
% TASimulinkParametersTemplates = ["SimulinkEmptyConfig.xlsx"];
% TASimulinkParametersTemplates = repelem(TASimulinkParametersTemplates, nb_runs);
% 
% egoNameArray = ["BMW_X5_SUV_1"];
% tagsConfigs = [""];
% SSHConfig = "Configurations/SSHConfig.csv";
% 
% TACombinations(folderNames, prescanExperimentTemplates, egoNameArray, TARosParametersTemplates, TASimulinkParametersTemplates, tagsConfigs, SSHConfig)
% 
% 
% 
% TA('Configurations/TAOrder.xlsx', 1, 5000, 1, false)


[device, hostname] = getSSHDevice(SSHConfig); % Cofiguration of the Ubuntu computer

system(device,'/home/adeye/AD-EYE_Core/AD-EYE/ROS_Packages/src/AD-EYE/sh/killROS.sh');
rosshutdown;


ta_progress_bar = waitbar(0,'Initializing test automation','Name','TA progress');
cleanup = onCleanup(@()(delete(ta_progress_bar)));

nb_runs = 500;

for run_index = 1:nb_runs
    waitbar((run_index) / (nb_runs), ta_progress_bar,['Run index ' num2str(run_index) '    ' num2str(run_index) '/' num2str(nb_runs)]);

    cd("C:\Users\adeye\AD-EYE_Core\AD-EYE\Experiments\W15_Road_Side_Parking\W15_Road_Side_Parking_no_camera\");
    runCore(device) % Start roscore
    rosinit(hostname) % Start Matlab node
    launchROS(device);
    simulink_name = "C:\Users\adeye\AD-EYE_Core\AD-EYE\Experiments\W15_Road_Side_Parking\W15_Road_Side_Parking_no_camera\W15_Road_Side_Parking_cs.slx";
    try
        sim(simulink_name, [0 600]);
    catch ME
        switch ME.identifier
            case 'SL_SERVICES:utils:CNTRL_C_INTERRUPTION' % if the user interruped the code
                rethrow(ME) % we throw the Matlab Exception
            case 'Simulink:SFunctions:SFcnErrorStatus' % most likely a PreScan federate issue, in that case we will kill all federates, log and try to run again
                warning("Failed to start experiment. Other attemps will be made until success.")
            otherwise % if there was a PreScan issue such as missing federates then we can try to run again
                disp(ME.identifier)
                rethrow(ME)
        end
    end
    system(device,'/home/adeye/AD-EYE_Core/AD-EYE/ROS_Packages/src/AD-EYE/sh/killROS.sh');
    rosshutdown;
    killPrescanFederates('C:\Users\adeye\AD-EYE_Core\AD-EYE\TA');
end



    

function [device, hostname] = getSSHDevice(SSHConfig)
    SSHConfigFile = SSHConfig;
    if(~isfile(SSHConfigFile))
        error('The SSH configuration files was not found. A template can be found, copied and modified in AD-EYE/TA/Configurations/SSHConfigTemplate.csv')
    end
    SSHConfig = readtable(SSHConfigFile, 'ReadRowNames',true,'ReadVariableNames',false, 'Delimiter', ',');
    ipaddress = SSHConfig{'ipaddress',1}{1};
    user = SSHConfig{'user',1}{1};
    password = SSHConfig{'password',1}{1};
    catkin_workspace = SSHConfig{'catkin_workspace',1}{1};
    ROS_folder = SSHConfig{'ROS_folder',1}{1};
    hostname = SSHConfig{'hostname',1}{1};
    device = rosdevice(ipaddress,user,password); %setting up the device
    device.CatkinWorkspace = catkin_workspace; %setting up the catkin workspace
    device.ROSFolder = ROS_folder; %setting up the ROS folder
end


function launchROS(device)
    sh_folder_path = '/home/adeye/AD-EYE_Core/AD-EYE/ROS_Packages/src/AD-EYE/sh';
    manager_file_launch = strcat(sh_folder_path, '/', 'launchManagerFile.sh'); %contains command to launch manager file in adeye package
    disp('Launching the manager file')
    system(device, manager_file_launch);
end

function killPrescanFederates(ta_path)
    dir = pwd;
    cd(ta_path);
    !KillAllFederates.bat
    cd(dir);
    clear dir;
end