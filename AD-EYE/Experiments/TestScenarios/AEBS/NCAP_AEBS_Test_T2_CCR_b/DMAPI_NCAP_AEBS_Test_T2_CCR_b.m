% DMAPI_NCAP_AEBS_Test_T2_CCR_b.m Function to run Euro NCAP test protocol
% for AEB systems: CCRb scenario
% Last modified: 09/10/2018

% Source: Euro NCAP AEB C2C Test Protocol v2.0.1 From January 2018
% https://cdn.euroncap.com/media/32278/euro-ncap-aeb-c2c-test-protocol-v201.pdf
% -------------------------------------------------------------------------

% Acronyms
% -------------------------------------------------------------------------
% AEB: Autonomous Emergency Braking
% C2C: Car-to-Car
% CCRb: Car-to-Car Rear Braking
% DMAPI: Data Model API
% Euro NCAP: European New Car Assessment Programme
% GVT: Global Vehicle Target
% VUT: Vehicle Under Test

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
deceleration = [-2 -6].';           % Deceleration, m/s^2 (Sec. 8.2.3)
headway = [12 40].';                % Headway, m (Sec. 8.2.3)
overlap = [-50 -75 100 75 50].';    % Lateral overlap, % (Fig. 3; Sec. 8.2.3)
velocity=50/3.6; % fixed velocity
%% Data Model API (DMAPI)
% Read Prescan data model
model = prescan.experiment.readDataModels('NCAP_AEBS_Test_T2_CCR_b.pb');

%% Retrieve data
% Trajectory info
% Trajectory's start location, x coordinate, m
tra_dis_x0 = model.scenariomodel.catalogs.trajectoryCatalog.trajectory{1, 1}.vertex{1, 1}.position.world.pose.position.x;

% VUT distance trajectory's start location in x direction, m
tra_dis_x0_VUT = model.scenariomodel.catalogs.maneuverCatalog.maneuver{2, 1}.event{1, 1}.startCondition{1, 1}.byEntity.traveledDistance;

% VUT parameters
index_VUT = prescan.worldmodel.objectsFindByName(model.worldmodel, 'Audi_A8_1');
index_GVT = prescan.worldmodel.objectsFindByName(model.worldmodel, 'GuidedSoftTarget_1');
x0_VUT = model.worldmodel.object{index_VUT}.pose.position.x;         % x-coordinate VUT location on trajectory, m
y0_VUT = model.worldmodel.object{index_VUT}.pose.position.y;         % Original y-coordinate, m
yaw_VUT = model.worldmodel.object{index_VUT}.pose.orientation.yaw;   % Heading of VUT, rad
cogOffset_VUT_x = model.worldmodel.object{index_VUT}.cogOffset.x;    % cog offset in x direction VUT
cogOffset_VUT_y = model.worldmodel.object{index_VUT}.cogOffset.y;    % cog offset in y direction VUT
cobbOffset_VUT_x = model.worldmodel.object{index_VUT}.cobbOffset.x;  % cobb offset in x direction VUT, m
length_VUT = model.worldmodel.object{index_VUT}.boundingSize.x;      % Length of VUT, m

% GVT parameters
length_GVT = model.worldmodel.object{index_GVT}.boundingSize.x;          % Length of GVT, m
cogOffset_x0_GVT = model.worldmodel.object{index_GVT}.cogOffset.x;        % Offset CoG from x0, m

% Widths of vehicles
width_VUT = model.worldmodel.object{index_VUT}.boundingSize.y;   % Width of VUT, m
width_GVT = model.worldmodel.object{index_GVT}.boundingSize.y;   % Width of GVT, m

%% Run all tests

% Front location VUT x direction, m
front_VUT_x = x0_VUT - cobbOffset_VUT_x + length_VUT;

Num_h=length(headway);
for h = 1:length(headway)
    % Calculate new trajectory location of GVT, m
    loc_GVT = front_VUT_x ...
        + headway(h) ...
        + length_GVT/2 ...  % Assume location of GVT is at midlength
        + cogOffset_x0_GVT;

    % Traveled distance GVT, m
    dis_GVT = loc_GVT - tra_dis_x0;

    % Set new location of GVT, m
    model.scenariomodel.catalogs.maneuverCatalog.maneuver{1, 1}.event{1, 1}.startCondition{1, 1}.byEntity.traveledDistance = dis_GVT;

    Num_v=length(deceleration);
    for v = 1:length(deceleration)

        % Set decelaration
        model.scenariomodel.catalogs.maneuverCatalog.maneuver{1, 1}.event{1, 1}.action{1, 1}.privateAction.longitudinal.speed.dynamics.rate = deceleration(v);

        % Set overlap
        Num_c=length(overlap);
        for c = 1:length(overlap)
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

            % Validation and running of new model
            vali = prescan.experiment.validate(model);  % Validate model
            if vali == 1
                disp(['Running AEB CCR_b test ' num2str((h-1)*Num_v*Num_c+(v-1)*Num_c+c) '/' num2str(Num_h*Num_v*Num_c) ': Distance ' num2str(headway(h)) ' m, Deceleration ' num2str(deceleration(v)) ' m/s^2, Overlap ' num2str(overlap(c)) '%']);
                simOut = prescan.experiment.runWithDataModels(model, 'Regenerate', 'off');   % Run model
            else
                disp('Model validation failed');
                return
            end

        end
    end
end
disp('All AEB CCR_b tests completed')