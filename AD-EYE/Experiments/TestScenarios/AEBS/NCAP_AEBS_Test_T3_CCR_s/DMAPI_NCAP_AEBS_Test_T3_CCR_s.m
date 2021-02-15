% DMAPI_NCAP_AEBS_Test_T3_CCR_s.m Function to run Euro NCAP test protocol
% for AEB systems: CCRs scenario

% Source: Euro NCAP AEB C2C Test Protocol v2.0.1 From January 2018
% https://cdn.euroncap.com/media/32278/euro-ncap-aeb-c2c-test-protocol-v201.pdf

% Acronyms
% AEB: Autonomous Emergency Braking
% C2C: Car-to-Car
% CCRs: Car-to-Car Rear stationary
% DMAPI: Data Model API
% Euro NCAP: European New Car Assessment Programme
% GVT: Global Vehicle Target
% VUT: Vehicle Under Test

%% Procedure
% Start PreScan Process Manager
% Start GUI using PreScan Process Manager
% File -> Open Experiment
% Start MATLAB using PreScan Process Manager
% Open the specific experiment folder in MATLAB

%% Inputs
speed = (10:5:80).';                % Speed, km/h (Sec. 8.2.3)
overlap = [-50 -75 100 75 50].';    % Lateral overlap, % (Fig. 3)

%% Data Model API (DMAPI)
% Read Prescan data model
model = prescan.experiment.readDataModels('NCAP_AEBS_Test_T3_CCR_s.pb');
index_VUT = prescan.worldmodel.objectsFindByName(model.worldmodel, 'Audi_A8_1');
index_GVT = prescan.worldmodel.objectsFindByName(model.worldmodel, 'GuidedSoftTarget_1');
% Widths of vehicles
width_VUT = model.worldmodel.object{index_VUT}.boundingSize.y;   % Width of VUT, m
width_GVT = model.worldmodel.object{index_GVT}.boundingSize.y;   % Width of GVT, m

% Original pose VUT
x0_VUT = model.worldmodel.object{index_VUT}.pose.position.x;             % Original x-coordinate, m
y0_VUT = model.worldmodel.object{index_VUT}.pose.position.y;             % Original y-coordinate, m
yaw_VUT = model.worldmodel.object{index_VUT}.pose.orientation.yaw;   % Heading of VUT, rad
cogOffset_VUT_x = model.worldmodel.object{index_VUT}.cogOffset.x;    % cog offset in x direction VUT
cogOffset_VUT_y = model.worldmodel.object{index_VUT}.cogOffset.y;    % cog offset in y direction VUT

%% Simulink model: NCAP_AEBS_Test_T3_CCR_s_cs
% Simulink model has two constants
% offset: change offset of GVT: ActorOffset_Left(+) / Right(-), m
% velocity: change speed of GVT, m/s

%% Run all tests
Num_c=length(overlap);
for c = 1:length(overlap)
    % Set overlap
    if overlap(c) == -50
      offset = width_GVT/2;
    elseif overlap(c) == -75
      offset = width_GVT/2 - 0.25 * width_VUT;
    elseif overlap(c) == 100
      offset = 0;
    elseif overlap(c) == 50
      offset = -(width_GVT/2);
    elseif overlap(c) == 75
      offset = -(width_GVT/2 - 0.25 * width_VUT);
    end

    % apply offset by moving GVT CoG
    model.worldmodel.object{index_GVT}.cogOffset.y=offset;

    Num_v=length(speed);
    for v = 1:length(speed)
        velocity = speed(v)/3.6;                    % Velocity from km/h to m/s

        % Validation, writing and running of new model
        vali = prescan.experiment.validate(model);  % Validate model
        if vali == 1
            disp(['Running AEB CCR_s test ' num2str((c-1)*Num_v+v) '/' num2str(Num_c*Num_v) ': Overlap ' num2str(overlap(c)) '%, Velocity ' num2str(speed(v)) ' km/h']);
            simOut = prescan.experiment.runWithDataModels(model, 'Regenerate', 'off');   % Run model
        else
            disp('Model validation failed');
            return
        end
    end
end
disp('All AEB CCR_s tests completed')