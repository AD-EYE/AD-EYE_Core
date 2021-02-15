% DMAPI_NCAP_AEBS_Test_T4_JA_TAP.m % Script to run Euro NCAP test protocol
% for AEB systems: Car-to-Car Junction Assist Turn Across Path: C2C JA TAP
% Last modified: 23/01/2019

% Source: EuroNCAP 2020 proposal Wesley Huslhof

% Acronyms
% AEB: Autonomous Emergency Braking
% Car-to-Car Junction Assist Turn Across Path: C2C JA TAP
% DMAPI: Data Model API
% Euro NCAP: European New Car Assessment Programme
% VUT: Vehicle Under Test
% Target: Target Vehicle

%% Procedure
% Start PreScan Process Manager
% Start GUI using PreScan Process Manager
% File -> Open Experiment
% Start MATLAB using PreScan Process Manager
% Open the specific experiment folder in MATLAB

%% Inputs
speed = (10:5:20).';                                         % Speed, km/h
targetSpeed = [30 45 55].';                                  % km/h

%% Data Model API (DMAPI)
% Read Prescan data model
model = prescan.experiment.readDataModels('NCAP_AEBS_Test_T4_JA_TAP.pb');
scenarioModel = model.scenariomodel;
index_VUT = prescan.worldmodel.objectsFindByName(model.worldmodel, 'Audi_A8_1');
index_GVT = prescan.worldmodel.objectsFindByName(model.worldmodel, 'TargetVehicle'); 
% Trajectory info
% Original pose VUT
cogOffset_VUT_x = model.worldmodel.object{index_VUT}.cogOffset.x;% cog offset in x direction VUT

% Original pose Target
BB_Target_x = model.worldmodel.object{index_GVT}.boundingSize.x;
%% VUT & VRU ImpactPoint 50%                 
S_VUT = [160.4400 160 156.5].' + cogOffset_VUT_x;           % Distance, m
S_Target = [100 102 104].' - (BB_Target_x/2);               % Distance, m

%% Simulink model: NCAP_AEBS_Test_T4_JA_TAP_cs
% Simulink model has two constants
% HostVelocity: change speed of VUT, km/h
% TriggerDelay: delay in triggering the VRU to ensure an impact point of 50%, secs

%% Run all tests
Num_v=length(speed);
for v = 1:length(speed)
    HostVelocity = speed(v);
    velocity_ms = speed(v)/3.6;                            % Velocity from km/h to m/s
    
    % Select the correct Trajectory for VUT
    for t = 1:length(speed)
        model.worldmodel.object{index_VUT}.trajectory{t,1}.isActive = false;
    end
    model.worldmodel.object{index_VUT}.trajectory{v,1}.isActive = true;
    
    Num_vT=length(targetSpeed);
    for vT = 1:length(targetSpeed)
        Target1Velocity = targetSpeed(vT);
        targetSpeed_ms = targetSpeed(vT)/3.6;
        % Trigger the Target based on distance
        TriggerDelay = (S_VUT(v)/velocity_ms) - (S_Target(v)/targetSpeed_ms);
        
        % Validation, writing and running of new model
        vali = prescan.experiment.validate(model);              % Validate model
        if vali == 1
            disp(['Running AEB JA_TAP test ' num2str((v-1)*Num_vT+vT) '/' num2str(Num_v*Num_vT) ': Velocity VUT ' num2str(speed(v)) ' km/h, Velocity Target ' num2str(targetSpeed(vT)) ' km/h']);
            simOut = prescan.experiment.runWithDataModels(model);   % Run model
        else
            disp('Model validation failed');
            return
        end
    end
end
disp('All AEB JA_TAP tests completed')