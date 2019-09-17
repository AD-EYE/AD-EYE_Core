%% Refresh Mapping of all experiments

% Global Parameters

%Mapping

pointCloudMapping = true;
vectorMapping = true;
override = false; %Run mapping even if files already exists

%Paths

%Constructing AD-EYE_Core path
AD_EYEpath = extractBefore(pwd, "AD-EYE\"); % <AD-EYE_Core>

BasePath = AD_EYEpath + "AD-EYE\Experiments\"; % <AD-EYE_Core>/AD-EYE/Experiments

logFile = AD_EYEpath + "AD-EYE\TA\GrandUnifiedMapping.log";

pointCloudMapDir = "Pointcloud_Files\";
vectorMapDir = "Vector_Map_Files\";

pex2csvDir = AD_EYEpath + "Pex_Data_Extraction\pex2csv_exe\";
pex2csvExe = "pex2csv";
pex2csvVersion = fileread(pex2csvDir + "version.txt");

log("Grand Unified Mapping :\n");
log("\n\tpex2csv : " + pex2csvVersion + "\n\n");
log("  Point Cloud\t: " + pointCloudMapping + "\n");
log("  Vector Map \t: " + vectorMapping + "\n");
log("  Overriding \t: " + override + "\n\n\n");

% List of experiments
ExpList = parseExp(BasePath, pointCloudMapDir, vectorMapDir);

nbExp = length(ExpList);

max_duration = 100;

%% Running mappings
for i = 1:nbExp	
    % Name and Dirs
  	ExpName = ExpList(i);
	RunModel = ExpName + "_cs";
	mapExpDir = BasePath + ExpName + "\Mapping\";
    simExpDir = BasePath + ExpName + "\Simulation\";
	ExpPexName = ExpName + ".pex";
	
    log("\nMapping   - " + ExpName + " -\n\n");
	
%	command = ExeName;
%	command = command + " -load " + '"' + mapExpDir;
%	command = command + " -realignPaths";
%	command = command + " -build";
%	command = command + " -close";
    if(pointCloudMapping == true)
        pointCloudMap(mapExpDir, RunModel, max_duration, pointCloudMapDir, override);
    end
    if(vectorMapping == true)
        vectorMap(simExpDir, ExpPexName, pex2csvDir, pex2csvExe, vectorMapDir, override, pex2csvVersion);
    end
end

%Log every messages in the log file
fileID = fopen(logFile, "wt");
fprintf(fileID, log());
fclose(fileID);

cd(BasePath);
%% Clean up workspace
clear pointCloudMapping vectorMapping override AD_EYEpath BasePath logFile pointCloudMapDir vectorMapDir pex2csvDir pex2csvExe pex2csvVersion ExpList nbExp max_duration i ExpName RunModel mapExpDir simExpDir ExpPexName fileID;
%% Functions

function pointCloudMap(ExpDir, RunModel, max_duration, pointCloudMapDir, override)
    alreadyMapped = checkMapping(ExpDir + "..\" + pointCloudMapDir);
    if(alreadyMapped == true && override == false)
        log("\tINFO : Point cloud mapping already done.\n");
        return
    elseif(alreadyMapped == true)
        log("\tINFO : Overriding previous point cloud mapping.\n");
        delete(ExpDir + "..\" + pointCloudMapDir + "\*.pcd");
    end
    log("\tRunning the point cloud mapping\n");
    % Navigate to a new experiment
	cd(ExpDir);
	open_system(RunModel);
	
	% Regenerate compilation sheet
	%	find the "regenerate" command block in simulink model
    regenButtonHandle = find_system(RunModel, "FindAll", 'on', "type", "annotation","text","Regenerate");
    regenButtonCallbackText = get_param(regenButtonHandle,'ClickFcn'); %execute the command
    eval(regenButtonCallbackText); %regenerates the compilation sheet
    
    % Determine simulation start and end times (avoid infinite durations).
    activeConfig = getActiveConfigSet(RunModel);
    startTime = str2double(get_param(activeConfig, 'StartTime')); %'StartTime'always set to 0
    endTime = str2double(get_param(activeConfig, 'StopTime'));
    duration = endTime - startTime;
    if (duration >= max_duration) %Limit the duration
        log("\tWARN : duration > max_duration = " + max_duration + "\n\t (duration = " + duration + ")\n");
        endTime = startTime + max_duration;
    end
	
	% Running the point cloud Mapping
    log("\tRunning the simulation  ");
    sim(RunModel, [startTime endTime]);
    % Close the experiment
	close_system(RunModel);
    log("-  Done\n");
end

function vectorMap(ExpDir, ExpPexName, pex2csvDir, pex2csvExe, vectorMapDir, override, pex2csvVersion)
    vectorMapFolder = ExpDir + "..\" + vectorMapDir;
    alreadyMapped = checkMapping(vectorMapFolder);
    if(alreadyMapped == true && override == false)
        log("\tINFO : Vector mapping already done.\n");
        return
    elseif(alreadyMapped == true)
        log("\tINFO : Overriding previous vector mapping.\n");
        delete(vectorMapFolder + "\*.csv");
        delete(vectorMapFolder + "\pex2csv.log");
    end
    log("\tRunning the vector mapping  ");
    arguments =  ExpDir + ExpPexName; %Input file
    arguments = arguments + " " + vectorMapFolder;
    [status, output] = system(pex2csvDir + pex2csvExe + " " + arguments);
    % Handle errors
    if status ~= 0
    	disp("Error during vector mapping :");
    	disp(output);
    else
        % Logging the version of pex2csv
        fileID = fopen(vectorMapFolder + "\pex2csv.log", "w");
        fprintf(fileID, pex2csvVersion);
        fclose(fileID);
    end
    log("-  Done\n");
end

%Checks if the mapping is already done
% (In fact just check if there is at least 1 file in the given folder)
function mappingAlreadyDone = checkMapping(mapFolder)
    mappingAlreadyDone = false;
    x = size(ls(mapFolder));
    if(x(1) > 2) % An empty folder contains ['.' '..']
        mappingAlreadyDone = true;
    end
end

function logMsg = log(msg)
    persistent logStr
    if(isempty(logStr))
        logStr = "";
    end
    if(nargin == 1)
        fprintf(msg);
        logStr = append(logStr, msg);
    end
    logMsg = logStr;
end

%Used to create the experiment list
% Checks the Experiment folder and looks if 
% the needed subfolders are inside.
% Otherwise, it ignores the folder
function ExpList = parseExp(ExpFolder, pointCloudMapDir, vectorMapDir)
    log("Searching for experiments in folder  '" + strrep(ExpFolder, "\", "\\") + "' : \n");
    ExpList = string(ls(ExpFolder));
    ExpList = strtrim(ExpList); % Removing extra whitespaces
    ExpList(2) = []; %Removing firsts elements ( '.' ; '..' )
    ExpList(1) = [];
    exp = 1;
    %Checking if folders represents valid experiments
    while(exp <= length(ExpList))
        keep = true;
        mapPexFile = ExpFolder + ExpList(exp) + "\Mapping\" + ExpList(exp) + ".pex";
        simPexFile = ExpFolder + ExpList(exp) + "\Simulation\" + ExpList(exp) + ".pex";
        pointCloudFolder = ExpFolder + ExpList(exp) + "\" + pointCloudMapDir;
        vecFolder = ExpFolder + ExpList(exp) + "\" + vectorMapDir;
        if(isfile(ExpList(exp))) %If it is a file
            keep = false;
            log(ExpList(exp) + " : ignored\n\tNot an experiment folder\n");
        elseif(~exist(mapPexFile, "file")) % "Mapping/<ExpName>.pex not found"
            keep = false;
            log(ExpList(exp) + " : ignored\n\t'Mapping\\" + ExpList(exp) + ".pex' not found\n");
        elseif(~exist(simPexFile, "file")) % "Simulation/<ExpName>.pex not found"
            keep = false;
            log(ExpList(exp) + " : ignored\n\t'Simulation\\" + ExpList(exp) + ".pex' not found\n");
        elseif(~exist(pointCloudFolder, "dir")) % Pointcloud map folder is absent
            mkdir(pointCloudFolder);
            log("INFO : " + ExpList(exp) + " : Created folder " + pointCloudMapDir + "\n");
        elseif(~exist(vecFolder, "dir")) % Vector map folder is absent
            mkdir(vecFolder);
            log("INFO : " + ExpList(exp) + " : Created folder " + vectorMapDir + "\n");
        end
        
        if(keep)
            exp = exp + 1; % Go next
        else
            ExpList(exp) = []; % Remove folder
        end
    end
    log("\nExperiments found :\n");
    log("\t" + strjoin(ExpList, "\n\t") + "\n");
end
