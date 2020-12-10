function TA(TAOrderFile,firstcolumn,lastcolumn)
    switch nargin
      case 0
        error('The TA order files must be passed as an argument')
      case 1
        firstcolumn = 1;
        TAOrder = readtable(TAOrderFile, 'ReadRowNames',true,'ReadVariableNames',false);
        lastcolumn = width(TAOrder);
      case 2
          TAOrder = readtable(TAOrderFile, 'ReadRowNames',true,'ReadVariableNames',false);
        lastcolumn = width(TAOrder);
      case 3
          TAOrder = readtable(TAOrderFile, 'ReadRowNames',true,'ReadVariableNames',false);
      otherwise
        error('3 inputs are accepted.')
    end
    
    
    
    
    %setting up experiments
    BasePath = pwd;
    rosshutdown;
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

    shFolderPath = '/home/adeye/AD-EYE_Core/AD-EYE/ROS_Packages/src/AD-EYE/sh';
    launchTemplateModifier = strcat(shFolderPath, '/' , 'launchTemplateModifier.sh'); ...
        ...%contains command to run the python node which receives ros parameters and modifies launch files 
    managerFileLaunch = strcat(shFolderPath, '/', 'managerFileLaunch.sh'); ...
    ...%contains command to launch manager file in adeye package

    killRosNodes = strcat(shFolderPath, '/', 'killRosNodes.sh'); ...
    ...%contains command to kill all the ros nodes and consecutively rosmaster 
    ExeName = 'PreScan.CLI.exe';
    max_duration = 200; %variable in current matlab script
    % goal = '/move_base_simple/goal';
    % poseStamped = 'geometry_msgs/PoseStamped';

    %setting test automation feature tags
    clear Results Run; %clear any earlier tags or values

    %'fl', 'fog', etc. are the tags assigned to parameters in PreScan experiment,go to ...
    ...Experiment > Test Automation Settings > Open Test Automation dialog box  

    

    if(firstcolumn<1)
        error("first column index must be strictly greater than zero");
    end
    if(firstcolumn>lastcolumn)
        error("first column index must lesser than the last column index");
    end

    for c = firstcolumn:min(lastcolumn,width(TAOrder))
        Run(c).FolderExpName = TAOrder{'FolderExpName',c}{1};
        Run(c).PrescanExpName = TAOrder{'PrescanExpName',c}{1};
        Run(c).EgoName = TAOrder{'EgoName',c}{1};
        Run(c).AutowareConfig = TAOrder{'AutowareConfig',c}{1};
        Run(c).SimulinkConfig = [BasePath,'/Configurations/', TAOrder{'SimulinkConfig',c}{1}];
    %     Run(c).GoalConfig = TAOrder{'GoalConfig',c}{1};
        Run(c).TagsConfig = TAOrder{'TagsConfig',c}{1};
    end



    disp('Setting-up variables...');
    NrOfRuns = length(Run); % Number of simulations

    %% running the simulation
    device = rosdevice(ipaddress,user,password); %setting up the device
    device.CatkinWorkspace = catkin_workspace; %setting up the catkin workspace
    device.ROSFolder = ROS_folder; %setting up the ROS folder
    Results(NrOfRuns).Data = []; % Preallocate results structure.
    disp(['Scheduling ' num2str(NrOfRuns) ' simulations...']);

    runtimes = zeros(1,NrOfRuns);

    % Store information about this TA session
    fileID = fopen('C:\Users\adeye\Documents\TA_status.txt','a');
    fprintf(fileID,num2str(run, '\n'));
    fprintf(fileID,num2str(run, '\n'));
    fprintf(fileID,num2str(run, '\n'));
    c = clock;
    fprintf(fileID,num2str(strcat("TA start time: ",num2str(fix(c(4))),"_",num2str(fix(c(5))),"_",num2str(fix(1000*c(6))),".pcd")));
    fprintf(fileID,num2str(run, '\n'));
    fprintf(fileID,num2str(run, '\n'));
    fclose(fileID);
    
    failed_runs = [];
    for run = firstcolumn:min(lastcolumn,width(TAOrder))
        tic
        runCore(device) %start roscore
        rosinit(hostname) %initialise

        ptree = rosparam;
        cd ('..\OpenSCENARIO\Code')
        
        
        splitted_string = split(Run(run).FolderExpName,"/");
        experiment_name = splitted_string(length(splitted_string)-1);
        clear splitted_string;
        experiment_name = experiment_name{1};
        if isfile(strcat("../../Experiments/",Run(run).FolderExpName,"/",experiment_name,".xosc"))
            Struct_OpenSCENARIO = xml2struct(strcat("../../Experiments/",Run(run).FolderExpName,"/",experiment_name,".xosc"));
            if(field_exists(Struct_OpenSCENARIO,"Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story.Act.Sequence.Maneuver.Event{1,1}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.Distance.Attributes.value"))
                set(ptree,'/simulink/trigger_distance',str2double(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story.Act.Sequence.Maneuver.Event{1,1}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.Distance.Attributes.value));
                disp('Setting ros parameters from TArosparam Table');
            end
        end
        
%         rosparamTable = readROSConfigTable(strcat("../../TA/Configurations/",Run(run).AutowareConfig));
%         [index,] = intersect(find(rosparamTable{:,2}=="op_common_params"),find(rosparamTable{:,3}=="maxVelocity"));
%         if ~isempty(index)
%             set(ptree,'/simulink/trigger_distance',str2double(rosparamTable{index,7}));
% 
%             disp('Setting ros parameters from TArosparam Table');
%         end
        cd('..\..\TA\Configurations');




        rosparamScript(Run(run).AutowareConfig, Run(run).PrescanExpName); %function (runs a MATLAB script...
        ...to send all the ros parameters to the linux computer)
        cd('..');
    %     disp('Setting up goal for actor in simulation');
    %     [pub, msg] = rospublisher(goal ,poseStamped);
    %     goalpoints(pub, msg, Run(run).GoalConfig);
        disp('Python node recieving the ros parameters and modifying launch files');
        system(device, launchTemplateModifier); 
        disp('Launching the manager file')
        system(device, managerFileLaunch);


        %cd(['.././Experiments/',Run(run).ExpName,'/Simulation']);
        cd(BasePath)
        cd(['../Experiments/',Run(run).FolderExpName]);
        MainExperiment = pwd;
        
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
        CurrentExperiment = strcat(MainExperiment, '/', Run(run).PrescanExpName, '.pex');
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


        % Put the configuration files with the experiment
        copyfile(Run(run).SimulinkConfig,ResultDir)
        copyfile(strcat(BasePath,"/Configurations/",Run(run).AutowareConfig),ResultDir)

        % Navigate to new experiment.
        cd(ResultDir);
        %Update the Simulink model
        load_system([RunModel,'.slx']);
        disp('Setting up constant blocks in Simulink model');
        simconstantSet(Run(run).SimulinkConfig, RunName, Run(run).EgoName);
        save_system([RunModel,'.slx']);
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
        
        
        simulation_ran = 0;
        run_counter = 0;
        while simulation_ran==0 && run_counter<5
            try
                run_counter = run_counter + 1;
                sim(RunModel, [startTime endTime]); %running the simulation
                simulation_ran = 1;
            catch ME
                switch ME.identifier
                    case 'SL_SERVICES:utils:CNTRL_C_INTERRUPTION' % if the user interruped the code
                        rethrow(ME)
                    case 'Simulink:SFunctions:SFcnErrorStatus' % most likely a PreScan federate issue, in that case we will kill all federates and try to run again
                        warning("Failed to start experiment. Other attemps will be made until success.")
                        fileID = fopen('C:\Users\adeye\Documents\TA_status.txt','a');
                        fprintf(fileID,strcat(RunModel,"\n"));
                        fprintf(fileID,ME.message);
                        c = clock;
                        fprintf(fileID,num2str(strcat("time: ",num2str(fix(c(4))),"_",num2str(fix(c(5))),"_",num2str(fix(1000*c(6))))));
                        fprintf(fileID,"\n");
                        fprintf(fileID,"\n");
                        fclose(fileID);
                        dir = pwd;
                        cd(BasePath);
                        !KillAllFederates.bat
                        cd(dir);
                        clear dir;
                    otherwise % if there was a PreScan issue such as missing federates then we can try to run again
                        disp(ME.identifier)
                        rethrow(ME)
                end
            end
        end
        if simulation_ran==0
            failed_runs = [failed_runs, num2str(run, '%01i')];
        end
        

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
        !KillAllFederates.bat
        runtimes(run) = toc;
        writetable(array2table(runtimes),"runtimes.xlsx")
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
    %% function
    %[pnames,pvalues]=search(ptree, paramname)
    isaninteger = @(p)isfinite(p) & p==floor(p);
    
    rosparamTable = readROSConfigTable(table);

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

%% kill the ssh sever, rosmaster and ros shutdown the process in case of error
function killall()
    rosshutdown;
    device = evalin('base', 'device');
    killAllScript = '/home/adeye/AD-EYE_Core/AD-EYE/ROS_Packages/src/AD-EYE/sh/killall.sh';
    system(device, killAllScript);
    %evalin('base', 'clear');
end