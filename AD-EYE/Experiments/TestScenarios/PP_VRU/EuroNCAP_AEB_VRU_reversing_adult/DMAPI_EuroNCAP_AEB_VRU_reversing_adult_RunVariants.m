% DMAPI_NCAP_AEB_VRU_reversing_adult_RunVariants.m % Script to run Euro NCAP VRU test protocol
% for AEB systems: Car-to-Pedestrian Reversing Adult 50% % (CPRA-50)
% Last modified: 28/01/2019

% Source: EuroNCAP 2020 Wesley Hulshof

% Acronyms
% AEB: Autonomous Emergency Braking
% Car-to-Pedestrian Reversing Adult 50%: CPRA-50
% DMAPI: Data Model API
% Euro NCAP: European New Car Assessment Programme
% VUT: Vehicle Under Test
% VRU: Vulnerable Road Users

% Limitations
% -------------------------------------------------------------------------
% Script can only handle a scenario with vehicles located on a straight
% road in x-direction, e.g., yaw rotations of the road are not possible

%% Procedure
% Start PreScan Process Manager
% Start GUI using PreScan Process Manager
% File -> Open Experiment
% Start MATLAB using PreScan Process Manager
% Open the specific experiment folder in MATLAB

%% Inputs
speed = [4 8].';                    % Speed, km/h
overlap = 50;                       % Lateral overlap 50%
pedSpeed = 5;                       % Speed, km/h

%% Data Model API (DMAPI)
% Read Prescan data model
model = prescan.experiment.readDataModels('EuroNCAP_AEB_VRU_reversing_adult.pb');

%% Simulink model: EuroNCAP_AEB_VRU_reversing_adult_cs
% Simulink model has three constants
% HostVelocity: change speed of VUT, km/h
% Target1Velocity: change speed of VRU, km/h
% ImpactOffset: ImpactOffset is the distance from the center of the VRU.
%

%% Run all tests Moving
Target1Velocity = pedSpeed;
pedSpeed_ms = pedSpeed/3.6;
ImpactOffset = 0;                   % 50% overlap

Num_v=length(speed);
for v = 1:length(speed)
    HostVelocity = speed(v);
    % Validation, writing and running of new model
    vali = prescan.experiment.validate(model);                                      % Validate model
    if vali == 1
        disp(['Running AEB VRU reversing adult test ' num2str(v) '/' num2str(Num_v) ': Velocity ' num2str(speed(v)) ' km/h']);
        simOut = prescan.experiment.runWithDataModels(model, 'Regenerate', 'off');   % Run model
    else
        disp('Model validation failed');
        return
    end
end
disp('All AEB VRU reversing adult tests completed')