%% set-up variables
%setting up experiment
setupVariableTable = "C:\Users\adeye\AD-EYE_Core\AD-EYE\TA\TAsetup.xlsx"; ...
    ...%Table containing all the variables required for setting up the device
setupVariables(setupVariableTable);
launchTemplateModifier = '/home/adeye/AD-EYE_Core/AD-EYE/ROS_Packages/src/AD-EYE/sh/launchTemplateModifier.sh'; ...
    ...%contains command to run the python node which receives ros parameters and modifies launch files 
managerFileLaunch = '/home/adeye/AD-EYE_Core/AD-EYE/ROS_Packages/src/AD-EYE/sh/managerFileLaunch.sh'; ...
...%contains command to launch manager file in adeye package
killRosNodes = '/home/adeye/AD-EYE_Core/AD-EYE/ROS_Packages/src/AD-EYE/sh/killRosNodes.sh'; ...
...%contains command to kill all the ros nodes and consecutively rosmaster 
ExeName = 'PreScan.CLI.exe';
max_duration = '120'; %variable in current matlab script

%setting test automation feature tags
clear Results Run; %clear any earlier tags or values

%'fl' and 'fog' are the tags assigned to parameters in PreScan experiment,go to ...
...Experiment > Test Automation Settings > Open Test Automation dialog box  
Run(1).Settings ={
    'fl', '15'; 
    }; %PreScan
Run(1).AdeyeParams = "C:\Users\adeye\AD-EYE_Core\AD-EYE\Experiments\Base_Map\Simulation\TArosparam1.xlsx"; %matlab script for setting up ros parameters
Run(1).ExpDir = "C:\Users\adeye\AD-EYE_Core\AD-EYE\Experiments\Base_Map\Simulation"; %directory containing experiment
Run(1).ExpName = 'Base_Map_S';
Run(1).ExpPexName = 'Base_Map_S.pex'; %PreScan experiment name
Run(1).ExpSlxName = 'Base_Map_S_cs.slx'; %Simulink experiment name
Run(1).SimConstant = "C:\Users\adeye\AD-EYE_Core\AD-EYE\Experiments\Base_Map\Simulation\TAconstant1.xlsx"; %simulink comnstant blocks

Run(2).Settings ={
    'fl', '7.5';
    'fog', 'True';
    }; 
Run(2).AdeyeParams = "C:\Users\adeye\AD-EYE_Core\AD-EYE\Experiments\Base_Map\Simulation\TArosparam2.xlsx";
Run(2).ExpDir = "C:\Users\adeye\AD-EYE_Core\AD-EYE\Experiments\Base_Map\Simulation";
Run(2).ExpName = 'Base_Map_S';
Run(2).ExpPexName = 'Base_Map_S.pex';
Run(2).ExpSlxName = 'Base_Map_S_cs.slx';
Run(2).SimConstant = "C:\Users\adeye\AD-EYE_Core\AD-EYE\Experiments\Base_Map\Simulation\TAconstant1.xlsx";

disp('Setting-up variables...');
NrOfRuns = length(Run); % Number of simulations

%% running the simulation
device = rosdevice(ipaddress,user,password); %setting up the device
device.CatkinWorkspace = catkin_workspace; %setting up the catkin workspace
Results(NrOfRuns).Data = []; % Preallocate results structure.
disp(['Scheduling ' num2str(NrOfRuns) ' simulations...']);
device.ROSFolder = '/opt/ros/kinetic';

for i = 1:NrOfRuns
    runCore(device) %start roscore
    rosinit(hostname) %initialise
    disp('Setting ros parameters from MATLAB Script');
    rosparamScript(Run(i).AdeyeParams); %function (runs a MATLAB script to send all the ros parameters to the linux computer)
    disp('Python node recieving the ros parameters and modifying launch files');
    system(device, launchTemplateModifier); 
    disp('Launching the manager file')
    system(device, managerFileLaunch);

    cd(Run(i).ExpDir);
    MainExperiment = pwd; 
    load_system(Run(i).ExpSlxName);
    simconstantScript(Run(i).SimConstant, Run(i).ExpName);
    ResultsDir = [MainExperiment '\Results\Run_' sprintf('%04.0f%02.0f%02.0f_%02.0f%02.0f%02.0f',clock)]; %save the name of the ...
...experiment folder in the format '\Results\Run_YearMonthDate_HourMinuteSeconds' 
    disp(['Run: ' num2str(i) '/' num2str(NrOfRuns)]);
    RunName = ['Run_' num2str(i, '%01i')]; %name of the experiment(for eg. 'Run_1'); also visible in VisViewer
    RunModel = [RunName '_cs']; %model name (for eg. 'Run_1_cs')
    ResultDir = [ResultsDir '\' RunName]; %creating a folder in ResultsDir named 'Run_1' containing all the files 

    % Create the complete command.
    Settings = cellstr('Altered Settings:'); %takes all the parameter tags and its values from Run.Settings() ...
    ...and save it in cell array named 'Settings'
    Command = ExeName; %all the commands in 'Command' variable are concatenated and executed using a dos function in the end
    CurrentExperiment = Run(i).ExpPexName;
    PathToExperiment = strcat(MainExperiment, '\', CurrentExperiment);
    Command = [Command ' -load ' '"' PathToExperiment '"']; %load the MainExperiment in PreScan
    Command = [Command ' -save ' '"' ResultDir '"']; %save it in ResultDir created    
    
    for j=1:size(Run(i).Settings,1) %size of each cell in Run.Settings() consisting test automation tags and its values
        tag = Run(i).Settings{j,1};
        val = num2str(Run(i).Settings{j,2}, '%50.50g');
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
    system(device,killRosNodes) 
    rosshutdown
end
%% simulations

for i = 1:NrOfRuns
    runResult = Results(i).Data;
    
    % Skip non-existant results.
    if isempty(runResult)
        continue;
    end
end
%% restoring experiment repository
cd(MainExperiment); %MATLAB file path returns back to the last running Experiment directory
Command = ExeName;
Command = [Command ' -load ' '"' PathToExperiment '"' ' -close']; %loads last running experiment again
dos(Command);
%% clean up workspace
clear Command ExeName ExperimentName MainExperiment ResultDir RunModel RunName activeConfig duration endTime startTime ...
    errorCode fileID i j line regenButtonCallbackText regenButtonHandle runResult simout tag val Settings tout;
clear()

function rosparamScript(table)
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
for h = 1: height(rosparamTable)
    ros_param_name = 'adeye/' + rosparamTable.Area(h) + '/' + rosparamTable.Node(h) + '/' + rosparamTable.Variable(h);
    set(ptree, ros_param_name, rosparamTable.Nominal(h))
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
return
%rosshutdown
end

function simconstantScript(table, expname)
%% Setup the Import Options
opts = spreadsheetImportOptions("NumVariables", 2);

% Specify sheet and range
opts.Sheet = "Sheet1";
opts.DataRange = "A2";

% Specify column names and types
opts.VariableNames = ["BlockName", "Value"];
opts.SelectedVariableNames = ["BlockName", "Value"];
opts.VariableTypes = ["string", "double"];
opts = setvaropts(opts, 1, "WhitespaceRule", "preserve");
opts = setvaropts(opts, 1, "EmptyFieldRule", "auto");

% Import the data
simconstantTable = readtable(table, opts, "UseExcel", false);

%% setting constant values
for h = 1:height(simconstantTable)
    constant_block_name = strcat(expname, '_cs', '/', char(simconstantTable.BlockName(h)));
    set_param(constant_block_name, 'Value', num2str(simconstantTable.Value(h)));
end
%% Clear temporary variables
clear opts
return
end

function setupVariables(y)
%% Setup the Import Options
opts = spreadsheetImportOptions("NumVariables", 2);

% Specify sheet and range
opts.Sheet = "Sheet1";
opts.DataRange = "A2";

% Specify column names and types
opts.VariableNames = ["VarName", "VarValue"];
opts.SelectedVariableNames = ["VarName", "VarValue"];
opts.VariableTypes = ["string", "string"];
opts = setvaropts(opts, [1, 2], "WhitespaceRule", "preserve");
opts = setvaropts(opts, [1, 2], "EmptyFieldRule", "auto");

% Import the data
setupVariableTable = readtable(y, opts, "UseExcel", false);

%% setting up values
for h = 1:height(setupVariableTable)
    assignin('base', setupVariableTable.VarName(h), char(setupVariableTable.VarValue(h)));
end

%% Clear temporary variables
clear opts
return
end