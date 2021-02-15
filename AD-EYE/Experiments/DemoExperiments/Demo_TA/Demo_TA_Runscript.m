%% Demo_TA_Runscript
% =========================================================================
% Runscript for demonstration of Test Automation in PreScan
%
% Author:   Floris Leneman
% Company:  TNO Automotive, Helmond, the Netherlands.
% Date:     22 April 2008
%
%
% This demo runscript is based on the simulation Demo_TA_cs.mdl
% of TNO Automotive.
%
% =========================================================================

% Test Automation is divided in three steps:
% - Set-up of variables 
% - Schedule runs 
% - Compare results 

%% Set-up of variables
disp('Setting-up variables...');
disp('------------------------');
ModelName = 'Demo_TA_cs';
open_system(ModelName);
StopTime  = 5;
Counter  =  0;
clear Results Run;

% Run settings
% (To set TA variables in the Const blocks in the Compilation Sheet)
% Format: {System, TA Variable, Value}
% Note: all Values should be numerical
Run(1).Settings ={'Mazda_RX8_1', 'TIS_1_NoiseAzimuthIllumination' , 5;
    'Mazda_RX8_1', 'TIS_1_NoiseAzimuthReflection'   , 0;
    'Mazda_RX8_1', 'TIS_1_DriftAzimuthGaussianSigma', 0;
    'Mazda_RX8_1', 'TIS_1_NoiseRangeType'           , 'uint32(0)';
    'Mazda_RX8_1', 'TIS_1_NoiseRange'               , 0};

Run(2).Settings ={'Mazda_RX8_1', 'TIS_1_NoiseAzimuthIllumination' , 0;
    'Mazda_RX8_1', 'TIS_1_NoiseAzimuthReflection'   , 5;
    'Mazda_RX8_1', 'TIS_1_DriftAzimuthGaussianSigma', 0;
    'Mazda_RX8_1', 'TIS_1_NoiseRangeType'           , 'uint32(0)';
    'Mazda_RX8_1', 'TIS_1_NoiseRange'               , 0};

Run(3).Settings ={'Mazda_RX8_1', 'TIS_1_NoiseAzimuthIllumination' , 0;
    'Mazda_RX8_1', 'TIS_1_NoiseAzimuthReflection'   , 0;
    'Mazda_RX8_1', 'TIS_1_DriftAzimuthGaussianSigma', 5;
    'Mazda_RX8_1', 'TIS_1_NoiseRangeType'           , 'uint32(0)';
    'Mazda_RX8_1', 'TIS_1_NoiseRange'               , 0};

Run(4).Settings ={'Mazda_RX8_1', 'TIS_1_NoiseAzimuthIllumination' , 0;
    'Mazda_RX8_1', 'TIS_1_NoiseAzimuthReflection'   , 0;
    'Mazda_RX8_1', 'TIS_1_DriftAzimuthGaussianSigma', 0;
    'Mazda_RX8_1', 'TIS_1_NoiseRangeType'           , 'uint32(0)';
    'Mazda_RX8_1', 'TIS_1_NoiseRange'               , 2};

Run(5).Settings ={'Mazda_RX8_1', 'TIS_1_NoiseAzimuthIllumination' , 0;
    'Mazda_RX8_1', 'TIS_1_NoiseAzimuthReflection'   , 0;
    'Mazda_RX8_1', 'TIS_1_DriftAzimuthGaussianSigma', 0;
    'Mazda_RX8_1', 'TIS_1_NoiseRangeType'           , 'uint32(1)';
    'Mazda_RX8_1', 'TIS_1_NoiseRange'               , 2};


%% Schedule simulations
% Three steps
% - Set variables
% - Run simulation
% - Save results
disp('Scheduling simulations...');
disp('-------------------------');
% Create Output dir
dirout = sprintf('Results/Results_%04.0f%02.0f%02.0f_%02.0f%02.0f%02.0f',clock);
mkdir(dirout);

NrOfRuns = length(Run);
for i = 1:NrOfRuns
    Counter =  Counter + 1;
    disp(['Run: ' num2str(Counter) '/' num2str(NrOfRuns)])

    % Set TA Variables
    % Sets TA variables in the Const blocks in the Compilation Sheet, in
    % the correct subsystem
    for j=1:size(Run(i).Settings,1)
        set_param([ModelName '/' Run(i).Settings{j,1} '/' Run(i).Settings{j,2}],'Value',num2str(Run(i).Settings{j,3}));
    end

    % Set adequate stop time
    % The stop time will be used by PreScan to check if the simulation
    % reached the end time
    set_param(ModelName,'StopTime',num2str(StopTime));

    % Run simulation
    sim(ModelName);

    % Collect & save results
    % Results are gathered in the variable simout ('To_Workspace' block)
    filename = sprintf('%s/simout_%05.0f.mat',dirout,i);
    simout=simout';
    save(filename,'simout');

    % Save log file (TA_Log.txt) to check later on if simulation was 
    % successfull
    % The simulation is successfull when
    % - no errors during simulation
    % - end-time of the simulation is reached
    TALogName = sprintf('TA_Logs/TA_Log_Run%05.0f.txt',i);
    %movefile('TA_Logs/TA_Log.txt',TALogName);
end %for i

%% Compare results
disp('Analysing results...');
disp('------------------------');
for i=1:NrOfRuns
    disp(['Run: ' num2str(i) '/' num2str(NrOfRuns)])

    % Check if simulation was successfull 
    successfull = true;%successfull = false;
    %TALogName = sprintf('TA_Logs/TA_Log_Run%05.0f.txt',i);
    %fid = fopen(TALogName);
    %while 1
    %    tline = fgetl(fid);
    %    if ~ischar(tline),   break,   end
    %    if strcmp(tline,'Simulation ended successfully')
    %        successfull = true;
    %    end
    %end
    %fclose(fid);
    
    if successfull
        % Load results
        filename = sprintf('%s/simout_%05.0f.mat',dirout,i);
        load(filename);%simout

        % Create & save plot
        % 'PlotHistogram_TA' is the same function as used in
        % Demo_TISDriftAndNoise, adapted to save results for TA
        PlotHistogram_TA(simout,i,dirout);
    else
        disp('Simulation was not successfull.')
    end
end
