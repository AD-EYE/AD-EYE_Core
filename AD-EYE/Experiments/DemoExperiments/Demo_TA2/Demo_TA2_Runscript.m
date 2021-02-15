%% Demo_TA2_Runscript
% =========================================================================
% Runscript for demonstration of the possibilities for Test Automation that
% requires the PreScan Experiment Editor to rebuild a scenario.
%
% Author:   D. Terra
% Company:  TNO Automotive Safety Solutions, Rijswijk, the Netherlands.
% Date:     December 2010 - January 2011
%
% This demo runscript is based on the simulation Demo_TA2.
%
% =========================================================================

% Test Automation 2 stores the results of consecutive simulations and
% displays them when finished.

%% Set-up of variables
% Make sure previous settings are ignored.
clear Results Run;

% Format: {Tag, Value}
% Tags are already defined by a user in the PreScan Experiment Editor.
% Non-specifed tags remain unchanged.
Run(1).Settings ={ };

Run(2).Settings ={
    'LaneCountNorth', 3;
    'LaneCountSouth', 3;
    'Traject', 'Trajectory_2';
    };

Run(3).Settings ={
    'LaneCountNorth', 3;
    'LaneCountSouth', 3;
    };

Run(4).Settings ={
    'Traject', 'Trajectory_2';
    };


disp('Setting-up variables...');
disp('------------------------');
ExeName = 'PreScan.CLI.exe';
ExperimentName = 'Demo_TA2';
MainExperiment = pwd;
ExperimentDir = [pwd '\..'];
ResultsDir = [MainExperiment '\Results\TA_' sprintf('%04.0f%02.0f%02.0f_%02.0f%02.0f%02.0f',clock)];

% Number of simulations.
NrOfRuns = length(Run);
% Number of beams on the TIS sensor (as defined in the Experiment Editor).
NumBeams = 3;

%% The simulations
Results(NrOfRuns).Data = []; % Preallocate results structure.

disp(['Scheduling ' num2str(NrOfRuns) ' simulations...']);
disp('-------------------------');

for i = 1:NrOfRuns
    disp(['Run: ' num2str(i) '/' num2str(NrOfRuns)]);
    
    RunName = ['Run_' num2str(i, '%03i')];
    RunModel = [RunName '_cs'];
    ResultDir = [ResultsDir '\' RunName];

    % Create the complete command
    Settings = cellstr('Altered Settings:');
    Command = ExeName;
    Command = [Command ' -load ' '"' MainExperiment '"'];
    Command = [Command ' -save ' '"' ResultDir '"'];    
    for j=1:size(Run(i).Settings,1)
        tag = Run(i).Settings{j,1};
        val = num2str(Run(i).Settings{j,2}, '%50.50g');
        Command = [Command ' -set ' tag '=' val];
        Settings(end+1) = cellstr([tag ' = ' val]);
    end
    Command = [Command ' -realignPaths'];
    Command = [Command ' -build'];    
    Command = [Command ' -close'];
    
    % Execute the command (creates altered PreScan experiment).
    errorCode = dos(Command);
    if errorCode ~= 0
        disp(['Failed to perform command: ' Command]);
        continue;
    end

    % Navigate to new experiment.
    cd(ResultDir);
    open_system(RunModel);
    
    % Regenerate compilation sheet.
    regenButtonHandle = find_system(RunModel, 'FindAll', 'on', 'type', 'annotation','text','Regenerate');
    regenButtonCallbackText = get_param(regenButtonHandle,'ClickFcn');
    eval(regenButtonCallbackText);
    
    % Determine simulation start and end times (avoid infinite durations).
    activeConfig = getActiveConfigSet(RunModel);
    startTime = str2double(get_param(activeConfig, 'StartTime'));
    endTime = str2double(get_param(activeConfig, 'StopTime'));
    duration = endTime - startTime;
    if (duration == Inf)
        endTime = startTime + 10;
    end
    
    % Simulate the new model.
    sim(RunModel, [startTime endTime]);
    Results(i).Data = simout;
    
    % Store current settings to file.
    fileID = fopen([ResultDir '\settings.txt'],'wt');
    for line=1:length(Settings)
        fprintf(fileID, '%s\n',char(Settings(line)));
    end
    fclose(fileID);
    
    % Store results to file.
    ResultFileDir = [ResultDir '\Results\'];
    [mkDirStatus,mkDirMessage,mkDirMessageid] = mkdir(ResultFileDir);
    resultFileName = [ResultFileDir 'simout.mat'];
    save(resultFileName,'simout');
    
    %Close the experiment
    save_system(RunModel);
    close_system(RunModel);
end

%% Create figure to plot results in.
figWidth = 0.8;
figHeight = 0.5;
figX = 0.05;
figY = 1.0-figHeight-0.1;
resultImg=figure(...
    'Visible', 'off',...
    'Units','normalized',...
    'Position',[figX figY figWidth figHeight],...
    ...%'Menubar', 'none',...
    'Name', 'TIS Beam hitcounts',...
    'NumberTitle', 'off'...
);

for i = 1:NrOfRuns
    runResult = Results(i).Data;
    
    % Skip non-existant results.
    if isempty(runResult)
        continue;
    end
    
    % Add results to the figure.
    detectedRows = find(runResult(:,2));        
    subplot(1, NrOfRuns, i);
    hist(runResult(detectedRows,1), 1:1:NumBeams);
    set(findobj(gca,'Type','patch'),'FaceColor','r');
    histTitle = ['Run ' num2str(i, '%03i')];
    title(histTitle,'FontName','FixedWidth');
    xlabel('Beam ID');
    ylabel('');
end

% Show the figure
set(resultImg, 'Visible', 'on');

%% Load main experiment to restore experiment repository
cd(MainExperiment);
Command = ExeName;
Command = [Command ' -load ' '"' MainExperiment '"' ' -close'];
dos(Command);

%% Clean up workspace
clear Command ExeName ExperimentDir ExperimentName MainExperiment NumBeams ResultDir ResultFileDir RunModel RunName activeConfig detectedRows duration endTime startTime errorCode figHeight figWidth figX figY fileID i j line regenButtonCallbackText regenButtonHandle resultFileName runResult simout tag val Settings tout;
