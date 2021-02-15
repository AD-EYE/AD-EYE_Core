% DMAPI_NCAP_AEB_VRU_turning_adult_RunVariants.m % Script to run Euro NCAP VRU test protocol
% for AEB systems: Car-to-Pedestrian Turning Adult% (CPTA)
% Last modified: 23/01/2019

% Source: EuroNCAP 2020 proposal Wesley Huslhof

% Acronyms
% AEB: Autonomous Emergency Braking
% Car-to-Pedestrian Turning Adult 50%: CPTA
% DMAPI: Data Model API
% Euro NCAP: European New Car Assessment Programme
% VUT: Vehicle Under Test
% VRU: Vulnerable Road Users

%% Procedure
% Start PreScan Process Manager
% Start GUI using PreScan Process Manager
% File -> Open Experiment
% Start MATLAB using PreScan Process Manager
% Open the specific experiment folder in MATLAB

%% Inputs
speed = [10 15 20 10].';            % Speed, km/h
overlap = [50].';                   % Lateral overlap
pedSpeed = 5;                       % km/h

%% Data Model API (DMAPI)
% Read Prescan data model
model = prescan.experiment.readDataModels('EuroNCAP_AEB_VRU_turning_adult.pb');
scenarioModel = model.scenariomodel;

% Trajectory info
% Original pose VUT
cogOffset_VUT_x = model.worldmodel.object{1, 1}.cogOffset.x;        % cog offset in x direction VUT

%% VUT & VRU ImpactPoint 50%
S_VUT = [68.5 69 68 61.5].' - cogOffset_VUT_x;                      % Distance, m
S_VRU = [5.2 5.65 5.74 9.45].';                                     % Distance, m

pedTraj = [2 2 2 1].';                                              % 2 = Left Turn, 1 = RightTurn
%% Simulink model: EuroNCAP_AEB_VRU_truning_adult_cs
% Simulink model has two constants
% HostVelocity: change speed of VUT, km/h
% TriggerDelay: delay in triggering the VRU to ensure an impact point of 50%, secs

%% Run all tests
Num_v=length(speed);
for v = 1:length(speed)
    HostVelocity = speed(v);
    speed_ms = speed(v)/3.6;                                        % Velocity from km/h to m/s
    Target1Velocity = pedSpeed;
    pedSpeed_ms = 5/3.6;  
    
    % Select the correct Trajectory for VUT
    for t = 1:length(speed)
        model.worldmodel.object{1,1}.trajectory{t,1}.isActive = false;
    end
    model.worldmodel.object{1,1}.trajectory{v,1}.isActive = true;
  
    % Select the correct Trajectory for VRU
    model.worldmodel.object{3,1}.trajectory{pedTraj(v),1}.isActive = true;
    
    % Trigger the VRU based on distance 
    TriggerDelay = (S_VUT(v)/speed_ms) - (S_VRU(v)/pedSpeed_ms);
    
    % Validation, writing and running of new model
    vali = prescan.experiment.validate(model);                      % Validate model
    if vali == 1
        disp(['Running AEB VRU turning adult test ' num2str(v) '/' num2str(Num_v) ': Velocity ' num2str(speed(v)) ' km/h']);
        simOut = prescan.experiment.runWithDataModels(model);       % Run model
    else
        disp('Model validation failed');
        return
    end
end
disp('All AEB VRU turning adult tests completed')