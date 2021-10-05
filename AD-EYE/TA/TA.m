function TA(TAOrderFile, firstcolumn, lastcolumn, clearFiles, collectOutputs)
    global collectdata
    ta_progress_bar = waitbar(0,'Initializing test automation','Name','TA progress');
    cleanup = onCleanup(@()(delete(ta_progress_bar)));
    
    switch nargin
      case 1 % Only the TAOrder was passed, run all the experiments.
          firstcolumn = 1;
          TAOrder = readtable(TAOrderFile, 'ReadRowNames',true,'ReadVariableNames',false);
          lastcolumn = width(TAOrder);
          clearFiles = 0;
          collectOutputs = false;
      case 2 % the TAorder and one index were passed, run only this one.
          TAOrder = readtable(TAOrderFile, 'ReadRowNames',true,'ReadVariableNames',false);
          lastcolumn = firstcolumn;
          clearFiles = 0;
          collectOutputs = false;
      case 3 % the TAOrder was passed with a start and an end. The interval [firstcolumn,lastcolumn] will be ran.
          TAOrder = readtable(TAOrderFile, 'ReadRowNames',true,'ReadVariableNames',false);
          lastcolumn = min(lastcolumn, width(TAOrder));
          clearFiles = 0;
          collectOutputs = false;
      case 4 % the TAOrder was passed with a start and an end. The interval [firstcolumn,lastcolumn] will be ran. If clearFiles is 1 then the generated files and folders will be removed.
          TAOrder = readtable(TAOrderFile, 'ReadRowNames',true,'ReadVariableNames',false);
          lastcolumn = min(lastcolumn, width(TAOrder));
          collectOutputs = false;
      case 5 % the TAOrder was passed with a start and an end. The interval [firstcolumn,lastcolumn] will be ran. If clearFiles is 1 then the generated files and folders will be removed.
          TAOrder = readtable(TAOrderFile, 'ReadRowNames',true,'ReadVariableNames',false);
          lastcolumn = min(lastcolumn, width(TAOrder));
      otherwise
          error('MATLAB:notEnoughInputs', 'Usage is as follow:\n   TA(TAOrderFile)                                      run the full TAorder\n   TA(TAOrderFile,run_index)                            run the run_index experiment of TAorder\n   TA(TAOrderFile,firstcolumn,lastcolumn)               run TAOrder between firstcolumn and lastcolumn included\n   TA(TAOrderFile,firstcolumn,lastcolumn,clearFiles)   run TAOrder between firstcolumn and lastcolumn included and clears the generated files if clear_file is set to 1\n')
    end
    
    collectdata = [num2str(collectOutputs)];
    
    if(firstcolumn<1)
        error("first column index must be strictly greater than zero");
    end
    if(firstcolumn>lastcolumn)
        error("first column index must lesser than the last column index");
    end
    if(lastcolumn>width(TAOrder))
        error("last column index must lesser than the number of column in the TAOrder file");
    end
    
    
    
    ta_path = pwd;
    rosshutdown;
    
    [device, hostname] = getSSHDevice(TAOrder); % Cofiguration of the Ubuntu computer
    
    max_duration = 200;
    % goal = '/move_base_simple/goal';
    % poseStamped = 'geometry_msgs/PoseStamped';
 

    for c = firstcolumn:min(lastcolumn,width(TAOrder))
        runs(c).folderName = TAOrder{'folderExperiment',c}{1};
        runs(c).prescanExperiment = TAOrder{'prescanExperiment',c}{1};
        runs(c).EgoName = TAOrder{'EgoName',c}{1};
        runs(c).TARosParameters = TAOrder{'TARosParameters',c}{1};
        runs(c).TASimulinkParameters = [ta_path,'/Configurations/', TAOrder{'TASimulinkParameters',c}{1}];
  %     runs(c).GoalConfig = TAOrder{'GoalConfig',c}{1};
    end
    
    for c = firstcolumn:min(lastcolumn,width(TAOrder))
         %'fl', 'fog', etc. are the tags assigned to parameters in PreScan experiment,go to Experiment > Test Automation Settings > Open Test Automation dialog box
        runs(c).TagsConfig = split(split(TAOrder{'TagsConfig',c}{1},"/"),"=",1); % Split the string to a have a cell of parameters
    end

    
    disp(['Scheduling ' num2str(length(runs)-firstcolumn+1) ' simulations...']);

    runtimes = zeros(1,length(runs));


    logInit()
    failed_experiments = [];
    
    for run_index = firstcolumn:min(lastcolumn,width(TAOrder))
        waitbar((run_index-firstcolumn+1) / (length(runs)-firstcolumn+1), ta_progress_bar,['Run index ' num2str(run_index) '    ' num2str(run_index-firstcolumn+1) '/' num2str(length(runs)-firstcolumn+1)]);
        [simulation_ran, runtimes] = doARun(runs, run_index, device, hostname, ta_path, max_duration, runtimes, firstcolumn, clearFiles, collectOutputs);
        if simulation_ran == 0
            failed_experiments = [failed_experiments,run_index];
        end
        if mod(run_index,fix((lastcolumn-firstcolumn+1)/10)) == 0 % Regularly try to rerun the failed experiments
            disp("Retrying the experiments that failed to run so far")
            failed_experiments_copy = failed_experiments;
            for i = length(failed_experiments_copy):-1:1 % Loop in reverse order so that we can remove elements without changing the indexes of the upcoming i
                [simulation_ran, runtimes] = doARun(runs, run_index, device, hostname, ta_path, max_duration, runtimes, firstcolumn, clearFiles);
                if simulation_ran == 1% If this run suceeded then we can remove it from the failed experiments
                    failed_experiments(i) = [];
                end
            end
        end
    end

    
    cd(ta_path);
    clear()
end

function [simulation_ran, runtimes] = doARun(runs, run_index, device, hostname, ta_path, max_duration, runtimes, firstcolumn, clearFiles, collectOutputs)
    tic
    runCore(device) % Start roscore
    rosinit(hostname) % Start Matlab node

    setROSParamFromOpenSCENARIO(runs, run_index);

    setROSParamAndLaunch(runs, run_index, device); % set ROS params from the TARosParameters and starts the ADI

    cd(ta_path)
    cd(['../Experiments/',runs(run_index).folderName]);
    MainExperiment = pwd;

    % creating experiment names and folders
    run_directory = [MainExperiment '\Results\Run_' sprintf('%04.0f%02.0f%02.0f_%02.0f%02.0f%02.0f',clock)]; %save the name of the experiment folder in the format '\Results\Run_YearMonthDate_HourMinuteSeconds' 
    disp(['Run index ' num2str(run_index) '    ' num2str(run_index-firstcolumn+1) '/' num2str(length(runs)-firstcolumn+1)]);
    run_name = ['Run_' num2str(run_index, '%01i')]; %name of the experiment(for eg. 'Run_1'); also visible in VisViewer
    simulink_name = [run_name '_cs']; %model name (for eg. 'Run_1_cs')
    folder_to_delete = run_directory;
    run_directory = [run_directory '\' run_name]; %creating a folder in ResultsDir named 'Run_1' containing all the files 

    settings = duplicateTemplatePrescanExperiment(MainExperiment, runs, run_index, run_directory); % Use PreScan CLI to duplicate the template

    storeConfiguration(runs, run_index, ta_path, run_directory, settings); % Saves the TA config files in the run folder

    cd(run_directory); % Navigate to new experiment
    scenarioFile = dir(fullfile(run_directory, '*.xosc')); % We search the name of the xosc file
    scenarioName = scenarioFile.name;
    scenarioNameWithoutExtension = scenarioName(1:end-5);
    % The number of xosc files generated from the xosc OpenScenario file
    % will give the number of TA simulation
    numberOfTAScenario = length(dir(fullfile("C:\Users\adeye\AD-EYE_Core\AD-EYE\OpenSCENARIO\OpenSCENARIO_experiments/", strcat(scenarioNameWithoutExtension,'*')))) -1;
    if not(numberOfTAScenario ==0) % If there is no TA parameters
        index= mod(run_index, numberOfTAScenario); % Look for the right final xosc generated
        if (index ==0)
            index=numberOfTAScenario;
        end
        scenarioFinalName = strrep(scenarioName, '.xosc', strcat(num2str(index), '.xosc')); % xosc file following ASAM convention, and scenario which is running
        copyfile(strcat("C:\Users\adeye\AD-EYE_Core\AD-EYE\OpenSCENARIO\OpenSCENARIO_experiments/",scenarioFinalName),run_directory); % put the xosc file corresponding to the running simulation inside the run folder
        delete(scenarioName); % delete the variant xosc file
    end
    % Update the Simulink model
    load_system([simulink_name,'.slx']);
    simconstantSet(runs(run_index).TASimulinkParameters, run_name, runs(run_index).EgoName);
    save_system([simulink_name,'.slx']);

    open_system(simulink_name); % Opens the simulink model for the next two function calls
    regenerateCompilationSheet(simulink_name);
    [startTime, endTime] = checkSimulationTimes(simulink_name, max_duration); % Determine simulation start and end times and saturate the total length (avoid infinite durations).

    simulation_ran = 0;
    run_counter = 0;
    while simulation_ran==0 && run_counter<5
        try
            run_counter = run_counter + 1;
            sim(simulink_name, [startTime endTime]); %running the simulation
            simulation_ran = 1;
        catch ME
            switch ME.identifier
                case 'SL_SERVICES:utils:CNTRL_C_INTERRUPTION' % if the user interruped the code
                    rethrow(ME) % we throw the Matlab Exception
                case 'Simulink:SFunctions:SFcnErrorStatus' % most likely a PreScan federate issue, in that case we will kill all federates, log and try to run again
                    warning("Failed to start experiment. Other attemps will be made until success.")
                    storeFailedExperimentLog(run_index, ME);
                    killPrescanFederates(ta_path)
                otherwise % if there was a PreScan issue such as missing federates then we can try to run again
                    disp(ME.identifier)
                    rethrow(ME)
            end
        end
    end

    %Close the experiment
    save_system(simulink_name);
    if (collectOutputs)
        i=0;
        outputsLength = 0;
        outputs=struct([]);
        while (exist(strcat('simout_', num2str(i), '_1')) || exist(strcat('simout_', num2str(i), '_2')))
            if (exist(strcat('simout_', num2str(i), '_1')))
                outputsLength = outputsLength +1;
                outputs{outputsLength, 1} = eval(strcat('simout_', num2str(i), '_1'));
                i= i+1;
            end
            if (exist(strcat('simout_', num2str(i), '_2')))
                outputsLength = outputsLength +1;
                outputs{outputsLength, 1} = eval(strcat('simout_', num2str(i), '_2'));
                i=i+1;
            end
        end
        adeye_base = "C:\Users\adeye\AD-EYE_Core\AD-EYE\";
        addpath(adeye_base+"OpenSCENARIO\Code");
        compareinitialfinalvalues(outputs);
    end
    close_system(simulink_name);

    disp('Killing all the ros nodes');

    %contains command to kill all the ros nodes and consecutively rosmaster 
    system(device,'/home/adeye/AD-EYE_Core/AD-EYE/ROS_Packages/src/AD-EYE/sh/killRosNodes.sh'); 
    rosshutdown;

    cd(ta_path);
    killPrescanFederates(ta_path)

    if clearFiles
        rmdir(folder_to_delete,'s') % cleanup the experiment folder
    end
    
    runtimes(run_index) = toc;
    writetable(array2table(runtimes),"runtimes.xlsx")
end

function setROSParamAndLaunch(runs, run_index, device)
    sh_folder_path = '/home/adeye/AD-EYE_Core/AD-EYE/ROS_Packages/src/AD-EYE/sh';
    launch_template_modifier = strcat(sh_folder_path, '/' , 'launchTemplateModifier.sh'); % Script to run the node modifies the launch files 
    manager_file_launch = strcat(sh_folder_path, '/', 'managerFileLaunch.sh'); %contains command to launch manager file in adeye package
    rosparamScript(runs(run_index).TARosParameters, runs(run_index).prescanExperiment); % Send all the ros parameters to the linux computer
    cd('..');
    disp('Python node recieving the ros parameters and modifying launch files');
    system(device, launch_template_modifier); 
    disp('Launching the manager file')
    system(device, manager_file_launch);
end

function storeFailedExperimentLog(run_index, ME)
    fileID = fopen('C:\Users\adeye\Documents\TA_status.txt','a');
    fprintf(fileID,strcat(num2str(run_index),"\n"));
    fprintf(fileID,ME.message);
    c = clock;
    fprintf(fileID,num2str(strcat("time: ",num2str(fix(c(4))),"_",num2str(fix(c(5))),"_",num2str(fix(1000*c(6))))));
    fprintf(fileID,"\n");
    fprintf(fileID,"\n");
    fclose(fileID);
end

function [device, hostname] = getSSHDevice(TAOrder)
    SSHConfigFile = TAOrder{'SHHConfig',1}{1};
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

function setROSParamFromOpenSCENARIO(runs, run_index)
    ptree = rosparam;
    cd ('..\OpenSCENARIO\Code')

    splitted_string = split(runs(run_index).folderName,"/");
    experiment_name = splitted_string(end);
    clear splitted_string;
    experiment_name = experiment_name{1};
    if isfile(strcat("../../Experiments/",runs(run_index).folderName,"/",experiment_name,".xosc"))
        Struct_OpenSCENARIO = xml2struct(strcat("../../Experiments/",runs(run_index).folderName,"/",experiment_name,".xosc"));
        if(field_exists(Struct_OpenSCENARIO,"Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story.Act.Sequence.Maneuver.Event{1,1}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.Distance.Attributes.value"))
            set(ptree,'/simulink/trigger_distance',str2double(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story.Act.Sequence.Maneuver.Event{1,1}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.Distance.Attributes.value));
            disp('Setting ros parameters from OpenSCENARIO file');
        end
    end

%         rosparamTable = readROSConfigTable(strcat("../../TA/Configurations/",Run(run).TARosParameters));
%         [index,] = intersect(find(rosparamTable{:,2}=="op_common_params"),find(rosparamTable{:,3}=="maxVelocity"));
%         if ~isempty(index)
%             set(ptree,'/simulink/trigger_distance',str2double(rosparamTable{index,7}));
% 
%             disp('Setting ros parameters from TArosparam Table');
%         end
    cd('..\..\TA\Configurations');
end

function [startTime, endTime] = checkSimulationTimes(simulink_name, max_duration)
    % Determine simulation start and end times (avoid infinite durations).
    activeConfig = getActiveConfigSet(simulink_name);
    startTime = str2double(get_param(activeConfig, 'StartTime')); %'StartTime' always set to 0
    endTime = str2double(get_param(activeConfig, 'StopTime'));
    duration = endTime - startTime;
    if (duration >= max_duration)
        endTime = startTime + max_duration;
    end
end

function storeConfiguration(runs, run_index, ta_path, run_directory, settings)
    % Put the configuration files with the experiment
    copyfile(runs(run_index).TASimulinkParameters,run_directory)
    copyfile(strcat(ta_path,"/Configurations/",runs(run_index).TARosParameters),run_directory)
    % Store current settings to file.
    fileID = fopen([run_directory '\settings.txt'],'wt');
    for line=1:length(settings)
        fprintf(fileID, '%s\n',char(settings(line)));
    end
    fclose(fileID);
end

function killPrescanFederates(ta_path)
    dir = pwd;
    cd(ta_path);
    !KillAllFederates.bat
    cd(dir);
    clear dir;
end

function logInit()
    % Store information about this TA session
    fileID = fopen('C:\Users\adeye\Documents\TA_status.txt','a');
    fprintf(fileID,'\n');
    fprintf(fileID,'\n');
    fprintf(fileID,'\n');
    c = clock;
    fprintf(fileID,num2str(strcat("TA start time: ",num2str(fix(c(4))),"_",num2str(fix(c(5))),"_",num2str(fix(1000*c(6))),".pcd")));
    fprintf(fileID,'\n');
    fprintf(fileID,'\n');
    fclose(fileID);
end

function settings = duplicateTemplatePrescanExperiment(MainExperiment, runs, run_index, run_directory)
    % Create the complete command.
    settings = cellstr('Altered Settings:'); %takes all the parameter tags and its values from Run.TagsConfig() ...
    ...and save it in cell array named 'Settings'
    command = 'PreScan.CLI.exe'; %all the commands in 'Command' variable ...
    ...are concatenated and executed using a dos function in the end
    CurrentExperiment = strcat(MainExperiment, '\', runs(run_index).prescanExperiment, '.pex');
    command = [command ' -load ' '"' CurrentExperiment '"']; %load the MainExperiment in PreScan
    command = [command ' -save ' '"' run_directory '"']; %save it in ResultDir created    
    for setting=1:size(runs(run_index).TagsConfig,2) %size of each cell in ...
        ...Run.TagsConfig() consisting test automation tags and its values
        if size(runs(run_index).TagsConfig,2)>=2
            tag = runs(run_index).TagsConfig{1,setting};
            val = num2str(runs(run_index).TagsConfig{2,setting}, '%50.50g');
            command = [command ' -set ' tag '=' val];
            settings(end+1) = cellstr([tag ' = ' val]);
        end
    end
    command = [command ' -realignPaths']; %unknown use from PreScan
    command = [command ' -build']; %build the experiment    
    command = [command ' -close'];
    errorCode = dos(command); %takes all the above commands in 'Command' variable and execute
    if errorCode ~= 0
        error(['Failed to perform command: ' command]);
    end
end

function regenerateCompilationSheet(simulink_name)
    regenButtonHandle = find_system(simulink_name, 'FindAll', 'on', 'type', 'annotation','text','Regenerate'); % find the 'regenerate' block in simulink model
    regenButtonCallbackText = get_param(regenButtonHandle,'ClickFcn'); % get the command from the block
    eval(regenButtonCallbackText); %  the command
end

%% function rosparamTable
function rosparamTable = readROSConfigTable(table)
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
end

%% function rosparam script
function rosparamScript(table, worldName)
    isaninteger = @(p)isfinite(p) & p==floor(p);
    
    rosparamTable = readROSConfigTable(table);

    % set parameters and evaluate the table for range
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
    % Clear temporary variables
    clear opts
end

%% function simconstantset
function simconstantSet(table, expname, EgoName)
    disp('Setting up constant blocks in Simulink model');
    simconstantTable = readtable(table,'ReadRowNames',false);
    for h = 1:height(simconstantTable)
        constant_block_name = strcat(expname, '_cs', '/', EgoName, '/', char(simconstantTable.BlockName(h)));
        set_param(constant_block_name, 'Value', string(simconstantTable.Value(h)));
    end
end

%% function goalpoints
function goalpoints(pub, msg, table)
    TAgoal = readtable(strcat('Configurations/',table),'ReadRowNames',true);
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
end
