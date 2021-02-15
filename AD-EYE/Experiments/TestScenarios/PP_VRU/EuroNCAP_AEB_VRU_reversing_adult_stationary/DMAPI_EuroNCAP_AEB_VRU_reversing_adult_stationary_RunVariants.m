% DMAPI_NCAP_AEB_VRU_reversing_adult_stationary_RunVariants.m % Script to run Euro NCAP VRU test protocol
% for AEB systems: Car-to-Pedestrain Reversing Adult Stationary% (CPRA-s)
% Last modified: 28/01/2019

% Source: EuroNCAP 2020 Wesley Hulshof

% Acronyms
% AEB: Autonomous Emergency Braking
% Car-to-Pedestrian Reversing Adult Stationary: CPRC-s
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
overlap = [25 50 75].';             % Lateral overlap
pedSpeed = 0;                       % Speed, km/h

%% Data Model API (DMAPI)
% Read Prescan data model
model = prescan.experiment.readDataModels('EuroNCAP_AEB_VRU_reversing_adult_stationary.pb');

% Original pose VRU
x0_VRU = model.worldmodel.object{2, 1}.pose.position.x;             % Original x-coordinate, m
y0_VRU = model.worldmodel.object{2, 1}.pose.position.y;             % Original y-coordinate, m
cogOffset_VRU_x = model.worldmodel.object{2, 1}.cogOffset.x;        % cog offset in x direction VUT
cogOffset_VRU_y = model.worldmodel.object{2, 1}.cogOffset.y;        % cog offset in y direction VUT

% Widths of vehicles
width_VUT = model.worldmodel.object{1, 1}.boundingSize.y;           % Width of VUT, m

%% Simulink model: EuroNCAP_AEB_VRU_reversing_adult_stationary_cs
% Simulink model has one constant
% HostVelocity: change speed of VUT, km/h

%% Run all tests
Num_c=length(overlap);
for c = 1:length(overlap)
    % Set overlap
    if overlap(c) == 25
        Offset = (-0.25) * width_VUT;
    elseif overlap(c) == 50
        Offset = 0;		%center-line aligned
    elseif overlap(c) == 75 
        Offset = 0.25 * width_VUT;
    end
    
    % Set overlap
    model.worldmodel.object{2, 1}.pose.position.y = (y0_VRU + cogOffset_VRU_y) + Offset;
    
    Num_v=length(speed);
    for v = 1:length(speed)
        HostVelocity = speed(v);
       
        % Validation, writing and running of new model
        vali = prescan.experiment.validate(model);                  % Validate model
        if vali == 1
            disp(['Running AEB VRU reversing adult stationary test ' num2str((c-1)*Num_v+v) '/' num2str(Num_c*Num_v) ': Overlap ' num2str(overlap(c)) '%, Velocity ' num2str(speed(v)) ' km/h']);
            simOut = prescan.experiment.runWithDataModels(model, 'Regenerate', 'off');   % Run model
        else
            disp('Model validation failed');
            return
        end
    end
end
disp('All AEB VRU reversing adult stationary tests completed')