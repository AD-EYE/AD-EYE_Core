% DMAPI_NCAP_AEB_VRU_longitudinal_adult_RunVariants.m % Script to run Euro NCAP VRU test protocol
% for AEB systems: Car-to-Pedestrian Longitudinal Adult% (CPLA-25, CPLA-50)
% Last modified: 08/01/2019

% Source: Euro NCAP AEB C2C Test Protocol v2.0.1 From January 2018
% https://cdn.euroncap.com/media/26997/euro-ncap-aeb-vru-test-protocol-v20.pdf

% Acronyms
% AEB: Autonomous Emergency Braking
% Car-to-Pedestrian Longitudinal Adult 25%: CPLA-25
% Car-to-Pedestrian Longitudinal Adult 50%: CPLA-50
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
% The specification of the test is given in section 7.2.4
speed = (20:5:80).';                % Speed, km/h
overlap = [25 50].';                % Lateral overlap
pedSpeed = 5;                       % km/h

TTC = 4.5;                          % T0 = TTC 4s defined in section 7.4.2
Smin = 10;                          % VRU 28m from Impact Point -- defined in section 7.4.2

%% Data Model API (DMAPI)
% Read Prescan data model
model = prescan.experiment.readDataModels('EuroNCAP_AEB_VRU_longitudinal_adult.pb');

% Trajectory info
% Trajectory's start location, x coordinate, m
tra_dis_x0 = model.scenariomodel.catalogs.trajectoryCatalog.trajectory{1, 1}.vertex{1, 1}.position.world.pose.position.x;

% VUT distance trajectory's start location in x direction, m
tra_dis_x0_VUT = model.scenariomodel.catalogs.maneuverCatalog.maneuver{1, 1}.event{1, 1}.startConditions{1, 1}.condition{1,1}.byEntity.traveledDistance;

% Original pose VUT
index_VUT = prescan.worldmodel.objectsFindByName(model.worldmodel, 'VUT');
index_Target = prescan.worldmodel.objectsFindByName(model.worldmodel, 'HumanTextured_1'); 
x0_VUT = model.worldmodel.object{index_VUT}.pose.position.x;         % Original x-coordinate, m
y0_VUT = model.worldmodel.object{index_VUT}.pose.position.y;         % Original y-coordinate, m
yaw_VUT = model.worldmodel.object{index_VUT}.pose.orientation.yaw;   % Heading of VUT, rad
cogOffset_VUT_x = model.worldmodel.object{index_VUT}.cogOffset.x;    % cog offset in x direction VUT
cogOffset_VUT_y = model.worldmodel.object{index_VUT}.cogOffset.y;    % cog offset in y direction VUT
cobbOffset_VUT_x = model.worldmodel.object{index_VUT}.cobbOffset.x;  % cobb offset in x direction VUT, m

%Lengths of Vehicles
length_VUT = model.worldmodel.object{index_VUT}.boundingSize.x;      % Length of VUT, m
length_VRU = model.worldmodel.object{index_Target}.boundingSize.x;      % Length of VRU, m

% Widths of vehicles
width_VUT = model.worldmodel.object{index_VUT}.boundingSize.y;       % Width of VUT, m
width_VRU = model.worldmodel.object{index_Target}.boundingSize.y;    % Width of Target, m

% Front location VUT x direction, m
front_VUT_x = x0_VUT - cobbOffset_VUT_x + length_VUT;

%% Simulink model: EuroNCAP_AEB_VRU_longitudinal_adult_cs
% Simulink model has two constants
% Offset: change offset of VUT: ActorOffset_Left(+) / Right(-), m
% HostVelocity: change speed of VUT, m/s

%% Run all tests
Num_c=length(overlap);
for c = 1:length(overlap)
    % Set overlap
    if overlap(c) == 25
        Offset = 0.25 * width_VUT;  
    elseif overlap(c) == 50	
        Offset = 0;		%center-line aligned    
    end

    % apply offset by moving Target CoG
    model.worldmodel.object{index_Target}.cogOffset.y=Offset;
    
    Num_v=length(speed);
    for v = 1:length(speed)
        HostVelocity = speed(v)/3.6;                                % Velocity from km/h to m/s
        
        % Position the VRU based on headway
        deltaV = HostVelocity - (pedSpeed/3.6);
        S_TTC = deltaV*TTC;
        headway = max(Smin,S_TTC);                              % Headway, m
        loc_VRU = front_VUT_x + headway + length_VRU/2;         % Assume location of VRU is at midlength
        % Set new location of VRU, m
        model.scenariomodel.catalogs.maneuverCatalog.maneuver{2, 1}.event{1, 1}.startConditions{1, 1}.condition{1,1}.byEntity.traveledDistance = loc_VRU;
        
        % Validation, writing and running of new model
        vali = prescan.experiment.validate(model);              % Validate model
        if vali == 1
            disp(['Running AEB VRU longitudinal adult test ' num2str((c-1)*Num_v+v) '/' num2str(Num_c*Num_v) ': Overlap ' num2str(overlap(c)) '%, Velocity ' num2str(speed(v)) ' km/h']);
            simOut = prescan.experiment.runWithDataModels(model, 'Regenerate', 'off');   % Run model
        else
            disp('Model validation failed');
            return
        end
    end
end
disp('All AEB VRU longitudinal adult tests completed')