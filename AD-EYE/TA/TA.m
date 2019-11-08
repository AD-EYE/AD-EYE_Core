function TA(TAOrderFile)
%setting up experiment
BasePath = pwd;

SSHConfigFile = 'SSHConfig.csv';
SSHConfig = readtable(SSHConfigFile, 'ReadRowNames',true,'ReadVariableNames',false, 'Delimiter', ',');
ipaddress = SSHConfig{'ipaddress',1}{1};
user = SSHConfig{'user',1}{1};
password = SSHConfig{'password',1}{1};
catkin_workspace = SSHConfig{'catkin_workspace',1}{1};
ROS_folder = SSHConfig{'ROS_folder',1}{1};
hostname = SSHConfig{'hostname',1}{1};

shFolderPath = '/home/adeye/AD-EYE_Core/AD-EYE/ROS_Packages/src/AD-EYE/sh';
launchTemplateModifier = strcat(shFolderPath, '/' , 'launchTemplateModifier.sh'); ...
    ...%contains command to run the python node which receives ros parameters and modifies launch files 
managerFileLaunch = strcat(shFolderPath, '/', 'managerFileLaunch.sh'); ...
...%contains command to launch manager file in adeye package
killRosNodes = strcat(shFolderPath, '/', 'killRosNodes.sh'); ...
...%contains command to kill all the ros nodes and consecutively rosmaster 
ExeName = 'PreScan.CLI.exe';
max_duration = '120'; %variable in current matlab script
goal = '/move_base_simple/goal';
poseStamped = 'geometry_msgs/PoseStamped';

%setting test automation feature tags
clear Results Run; %clear any earlier tags or values

%'fl', 'fog', etc. are the tags assigned to parameters in PreScan experiment,go to ...
...Experiment > Test Automation Settings > Open Test Automation dialog box  

TAOrder = readtable(TAOrderFile, 'ReadRowNames',true,'ReadVariableNames',false);

for c = 1:width(TAOrder)
    Run(c).ExpName = TAOrder{'ExpName',c}{1};
    Run(c).AutowareExpName = TAOrder{'AutowareExpName',c}{1};
    Run(c).EgoName = TAOrder{'EgoName',c}{1};
    Run(c).AutowareConfig = TAOrder{'AutowareConfig',c}{1};
    Run(c).SimulinkConfig = ['../../../TA/', TAOrder{'SimulinkConfig',c}{1}];
    Run(c).GoalConfig = TAOrder{'GoalConfig',c}{1};
    Run(c).TagsConfig = TAOrder{'TagsConfig',c}{1};
end

%Run(1).TagsConfig ={
%    }; 
%Run(1).ExpDir = '.././Experiments/W01_Base_Map/Simulation';
%Run(1).AutowareConfig = 'TArosparam.xlsx';
%Run(1).GoalConfig = './TAgoal.xlsx';
%Run(1).ExpName = 'W01_Base_Map';
%Run(1).ExpPexName = 'W01_Base_Map.pex';
%Run(1).ExpSlxName = 'W01_Base_Map_cs.slx';
%Run(1).SimulinkConfig = './TAconstant.xlsx';

disp('Setting-up variables...');
NrOfRuns = length(Run); % Number of simulations

%% running the simulation
device = rosdevice(ipaddress,user,password); %setting up the device
device.CatkinWorkspace = catkin_workspace; %setting up the catkin workspace
device.ROSFolder = ROS_folder; %setting up the ROS folder
Results(NrOfRuns).Data = []; % Preallocate results structure.
disp(['Scheduling ' num2str(NrOfRuns) ' simulations...']);

for run = 1:NrOfRuns
    runCore(device) %start roscore
    rosinit(hostname) %initialise
    %cd(Run(run).ExpDir);
    %MainExperiment = pwd; 
    disp('Setting ros parameters from TArosparam Table');
    rosparamScript(Run(run).AutowareConfig, Run(run).AutowareExpName); %function (runs a MATLAB script...
    ...to send all the ros parameters to the linux computer)
    disp('Setting up goal for actor in simulation');
    [pub, msg] = rospublisher(goal ,poseStamped);
    goalpoints(pub, msg, Run(run).GoalConfig);
    disp('Python node recieving the ros parameters and modifying launch files');
    system(device, launchTemplateModifier); 
    disp('Launching the manager file')
    system(device, managerFileLaunch);

    cd(['.././Experiments/',Run(run).ExpName,'/Simulation']);
    MainExperiment = pwd;
    load_system([Run(run).ExpName,'_cs.slx']);
    disp('Setting up constant blocks in Simulink model');
    simconstantSet(Run(run).SimulinkConfig, Run(run).ExpName, Run(run).EgoName);
    save_system([Run(run).ExpName,'_cs.slx']);
    ResultsDir = [MainExperiment '\Results\Run_' sprintf('%04.0f%02.0f%02.0f_%02.0f%02.0f%02.0f',clock)]; %save the name of the ...
    ...experiment folder in the format '\Results\Run_YearMonthDate_HourMinuteSeconds' 
    disp(['Run: ' num2str(run) '/' num2str(NrOfRuns)]);
    RunName = ['Run_' num2str(run, '%01i')]; %name of the experiment(for eg. 'Run_1'); also visible in VisViewer
    RunModel = [RunName '_cs']; %model name (for eg. 'Run_1_cs')
    ResultDir = [ResultsDir '\' RunName]; %creating a folder in ResultsDir named 'Run_1' containing all the files 

    % Create the complete command.
    Settings = cellstr('Altered Settings:'); %takes all the parameter tags and its values from Run.TagsConfig() ...
    ...and save it in cell array named 'Settings'
    Command = ExeName; %all the commands in 'Command' variable ...
    ...are concatenated and executed using a dos function in the end
    CurrentExperiment = strcat(MainExperiment, '/', Run(run).ExpName, '.pex');
    Command = [Command ' -load ' '"' CurrentExperiment '"']; %load the MainExperiment in PreScan
    Command = [Command ' -save ' '"' ResultDir '"']; %save it in ResultDir created    
    
    for setting=1:size(Run(run).TagsConfig,1) %size of each cell in ...
        ...Run.TagsConfig() consisting test automation tags and its values
        tag = Run(run).TagsConfig{setting,1};
        val = num2str(Run(run).TagsConfig{setting,2}, '%50.50g');
        Command = [Command ' -set ' tag '=' val];
        Settings(end+1) = cellstr([tag ' = ' val]);
    end
    
    
    Command = [Command ' -realignPaths']; %unknown use from PreScan
    Command = [Command ' -build']; %build the experiment    
    Command = [Command ' -close'];
    
    % Execute the command (creates altered PreScan experiment).
    errorCode = dos(Command); %takes all the above commands in 'Command' variable and execute
    if errorCode ~= 0
        disp(['Failed to perform command: ' Command]);
        continue;
    end

    % Navigate to new experiment.
    cd(ResultDir); %the matlab path changes from C:\Users\Radhika\Desktop\RUT\main_experiment_folder to ...
    ...C:\Users\Radhika\Desktop\RUT\main_experiment_folder\Results\current_experiment_folder\Run_i 
    open_system(RunModel); %opens the simulink model
        

    % Regenerate compilation sheet.
    regenButtonHandle = find_system(RunModel, 'FindAll', 'on', 'type', 'annotation','text','Regenerate'); %find the 'regenerate'...
    ...command block in simulink model
    regenButtonCallbackText = get_param(regenButtonHandle,'ClickFcn'); %execute the command
    eval(regenButtonCallbackText); %regenerates the compilation sheet
    
    % Determine simulation start and end times (avoid infinite durations).
    activeConfig = getActiveConfigSet(RunModel);
    startTime = str2double(get_param(activeConfig, 'StartTime')); %'StartTime'always set to 0
    endTime = str2double(get_param(activeConfig, 'StopTime'));
    duration = endTime - startTime;
    if (duration >= max_duration)
        endTime = startTime + max_duration;
    end
    
    % Simulate the new model.
    sim(RunModel, [startTime endTime]); %running the simulation
    %Results(i).Data = 'simout';
    
    % Store current settings to file.
    fileID = fopen([ResultDir '\settings.txt'],'wt');
    for line=1:length(Settings)
        fprintf(fileID, '%s\n',char(Settings(line)));
    end
    fclose(fileID);
    
    % Store results to file.
    %ResultFileDir = [ResultDir '\Results\'];
    %[mkDirStatus,mkDirMessage,mkDirMessageid] = mkdir(ResultFileDir);
    %resultFileName = [ResultFileDir 'simout.mat'];
    %save(resultFileName,'simout');
        
    %Close the experiment
    save_system(RunModel); %save the model
    close_system(RunModel); %close the model
    
    disp('Killing all the ros nodes');
    system(device,killRosNodes); 
    rosshutdown
    cd(BasePath);
end
%% simulations

for run = 1:NrOfRuns
    runResult = Results(run).Data;
    
    % Skip non-existant results.
    if isempty(runResult)
        continue;
    end
end
%% restoring experiment repository
cd(MainExperiment); %MATLAB file path returns back to the last running Experiment directory
Command = ExeName;
%Command = [Command ' -load ' '"' CurrentExperiment '"' ' -close']; %loads last running experiment again
%dos(Command);
cd(BasePath);
%% clean up workspace
clear Command ExeName MainExperiment ResultDir RunModel RunName activeConfig duration endTime startTime ...
    errorCode fileID i j line regenButtonCallbackText regenButtonHandle runResult simout tag val Settings tout;
clear()
end

%% function rosparam script
function rosparamScript(table, worldName)
%% function
%[pnames,pvalues]=search(ptree, paramname)
isaninteger = @(p)isfinite(p) & p==floor(p);
%% Setup the Import Options
opts = spreadsheetImportOptions("NumVariables", 7);

% Specify sheet and range
opts.Sheet = "Sheet1";
opts.DataRange = "A2";

% Specify column names and types
opts.VariableNames = ["Area", "Node", "Variable", "Type", "Min", "Max", "Nominal"];
opts.SelectedVariableNames = ["Area", "Node", "Variable", "Type", "Min", "Max", "Nominal"];
opts.VariableTypes = ["string", "string", "string", "string", "double", "double", "string"];
opts = setvaropts(opts, [1, 2, 3, 4, 7], "WhitespaceRule", "preserve");
opts = setvaropts(opts, [1, 2, 3, 4, 7], "EmptyFieldRule", "auto");

% Import the data
rosparamTable = readtable(table, opts, "UseExcel", false);

%% set parameters and evaluate the table for range
ptree = rosparam;
set(ptree, 'adeye/config/manager/WorldName', worldName); %for the parameters-
...map/points_map_loader/PointCloud_Files_Folder, map/vector_map_loader/VectorMap_files_Folder,
...SSMP/GridMapCreator/Vector_Map_Folder, SSMP/GridMapCreator/Pex_Folder, SSMP/GridMapCreator/filePex
for h = 1: height(rosparamTable)
    ros_param_name = 'adeye/' + rosparamTable.Area(h) + '/' + rosparamTable.Node(h) + '/' + rosparamTable.Variable(h);
    set(ptree, ros_param_name, rosparamTable.Nominal(h));
    if rosparamTable.Type(h) == "string"
        if isempty(rosparamTable.Nominal(h))
            warning("value of '%s'should be a string, line(%s)", ros_param_name, double(h))
            warning on backtrace
        end
    elseif rosparamTable.Type(h) == "bool"
        if rosparamTable.Nominal(h) ~= "true" && rosparamTable.Nominal(h) ~= "false"
            warning("value of '%s' should be either 'true' or 'false'", ros_param_name)
            warning on backtrace
        end
    elseif rosparamTable.Type(h) == "float"
        if double(rosparamTable.Nominal(h))<rosparamTable.Min(h) || double(rosparamTable.Nominal(h))>rosparamTable.Max(h)
            warning("value of '%s' should be in the range (%s,%s)", ros_param_name, rosparamTable.Min(h), rosparamTable.Max(h))
            warning on backtrace
        end
    elseif rosparamTable.Type(h) == "int"
        if ~isaninteger(double(rosparamTable.Nominal(h))) || double(rosparamTable.Nominal(h))<rosparamTable.Min(h) || double(rosparamTable.Nominal(h))>rosparamTable.Max(h)
            warning("value of '%s' should be an integer and in the range (%s,%s)", ros_param_name, rosparamTable.Min(h), rosparamTable.Max(h))
            warning on backtrace
        end
    else
        warning("DataType of '%s' not defined", ros_param_name)
        warning on backtrace
    end
end
%% Clear temporary variables
clear opts
end

%% function simconstantset
function simconstantSet(table, expname, EgoName)
simconstantTable = readtable(table,'ReadRowNames',false);
for h = 1:height(simconstantTable)
    constant_block_name = strcat(expname, '_cs', '/', EgoName, '/', char(simconstantTable.BlockName(h)));
    set_param(constant_block_name, 'Value', string(simconstantTable.Value(h)));
end
end

%% function goalpoints
function goalpoints(pub, msg, table)
TAgoal = readtable(table,'ReadRowNames',true);
for w = 1 : width(TAgoal)
    msg.Header.Seq = typecast(uint32(w), 'int32');
    msg.Pose.Position.X = str2double(table2array(TAgoal(1, w)));
    msg.Pose.Position.Y = str2double(table2array(TAgoal(2, w)));
    msg.Pose.Position.Z = str2double(table2array(TAgoal(3, w)));
    msg.Pose.Orientation.X = str2double(table2array(TAgoal(4, w)));
    msg.Pose.Orientation.Y = str2double(table2array(TAgoal(5, w)));
    msg.Pose.Orientation.Z = str2double(table2array(TAgoal(6, w)));
    msg.Pose.Orientation.W = str2double(table2array(TAgoal(7, w)));
    msg.Header.FrameId = string(table2array(TAgoal(8, w)));  
    send(pub,msg);
    pause(1);
end
%msg.Header.Stamp =
%msg.Header.FrameId_SL_Info.CurrentLength = typecast(uint8('world'), 'int8');
%send(pub,msg);
end

%% kill the ssh sever, rosmaster and ros shutdown the process in case of error
function killall()
rosshutdown;
device = evalin('base', 'device');
killAllScript = '/home/adeye/AD-EYE_Core/AD-EYE/ROS_Packages/src/AD-EYE/sh/killall.sh';
system(device, killAllScript);
%evalin('base', 'clear');
end