ta_openscenario_progress_bar = waitbar(0,'Starting TA OpenSCENARIO interface','Name','TA_OpenSCENARIO progress');
% cleanup = onCleanup( @()(delete(ta_openscenario_progress_bar)));


%% Parameter onfigurations

global EgoNameArray
global PrescanExpNameArray
global AutowareConfigArray
global SimulinkConfigArray
global TagsConfigArray
EgoNameArray = ["BMW_X5_SUV_1"];
adeye_base = "C:\Users\adeye\AD-EYE_Core\AD-EYE\";

%% Experiment A
% ScenarioExpNameArray = ["Experiment_A"];
% FolderExpNameArray = ["Experiment_A"];
% PrescanExpNameArray = ["KTH_pedestrian_autoware_light"];
% AutowareConfigArray = ["AutowareConfigTemplate.xlsx"];
% SimulinkConfigArray = ["SimulinkConfig.xlsx"];

%% Scenario 1
% ScenarioExpNameArray = ["Decelerating"];
% FolderExpNameArray = ["Decelerating"];
% PrescanExpNameArray = ["W01_Base_Map"];
% AutowareConfigArray = ["AutowareConfigTemplate.xlsx"];
% SimulinkConfigArray = ["SimulinkConfigExpBmap1goal1.xlsx", "SimulinkConfigExpBmap1goal2.xlsx", "SimulinkConfigExpBmap1goal3.xlsx"];

%% Experiment B Map 1
ScenarioExpNameArray = ["Experiment_B"];
FolderExpNameArray = ["Experiment_B"];
PrescanExpNameArray = ["W01_Base_Map"];
AutowareConfigArray = ["AutowareConfigTemplate.xlsx"];
SimulinkConfigArray = ["SimulinkConfigExpBmap1goal1.xlsx", "SimulinkConfigExpBmap1goal2.xlsx", "SimulinkConfigExpBmap1goal3.xlsx"];

%% Experiment B Map 2
% ScenarioExpNameArray = ["Experiment_B"];
% FolderExpNameArray = ["Experiment_B"];
% PrescanExpNameArray = ["W03_Forest"];
% AutowareConfigArray = ["AutowareConfigTemplate.xlsx"];
% SimulinkConfigArray = ["SimulinkConfigExpBmap2goal1.xlsx", "SimulinkConfigExpBmap2goal2.xlsx", "SimulinkConfigExpBmap2goal3.xlsx"];

%% Experiment B Map 3
% ScenarioExpNameArray = ["Experiment_B"];
% FolderExpNameArray = ["Experiment_B"];
% PrescanExpNameArray = ["W07_Neighborhood"];
% AutowareConfigArray = ["AutowareConfigTemplate.xlsx"];
% SimulinkConfigArray = ["SimulinkConfigExpBmap3goal1.xlsx", "SimulinkConfigExpBmap3goal2.xlsx", "SimulinkConfigExpBmap3goal3.xlsx"];




TagsConfigArray = [""];
SSHConfig = "Configurations/SSHConfig.csv";



%% Extract TA specific configurations (AutowareConfig or SimulinkConfig)
waitbar(.13,ta_openscenario_progress_bar,'Extract TA specific configurations from xosc scenarios');
convertStringsToChars(strcat('..\OpenSCENARIO_experiments\',ScenarioExpNameArray(1)));
cd(adeye_base + "OpenSCENARIO\Code")
Struct_OpenSCENARIO = xml2struct([convertStringsToChars(strcat('..\OpenSCENARIO_experiments\',ScenarioExpNameArray(1))), '.xosc']);
%Struct_OpenSCENARIO = xml2struct(['..\OpenSCENARIO_experiments\KTH_pedestrian_autowareRain', '.xosc']);
cd(adeye_base + "TA\Configurations")


addpath(adeye_base+"OpenSCENARIO\Code")

for x = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private)
    if(convertCharsToStrings(get_field(Struct_OpenSCENARIO,strcat("Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, ",num2str(x),"}.Attributes.entityRef"))) == "Ego")
        speed_ego = get_field(Struct_OpenSCENARIO, strcat("Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1,",num2str(x),"}.PrivateAction{1,1}.LongitudinalAction.SpeedAction.SpeedActionTarget.AbsoluteTargetSpeed.Attributes.value"));
        %Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.PrivateAction{1,1}.LongitudinalAction.SpeedAction.SpeedActionTarget.AbsoluteTargetSpeed.Attributes.value
        if(contains(speed_ego, '{'))
            findOpen = strfind(speed_ego, ',');
                start_val = extractBetween(speed_ego, 2, findOpen(1)-1);
                step = extractBetween(speed_ego, findOpen(1)+1, findOpen(2)-1);
                end_val = extractBetween(speed_ego, findOpen(2)+1, strlength(speed_ego)-1);
                setSpeedEgo(str2double(start_val), str2double(step), str2double(end_val))
        end
    end
end

if(field_exists(Struct_OpenSCENARIO,"Struct_OpenSCENARIO.OpenSCENARIO.GlobalAction.EnvironmentAction.Environment.Weather.Precipitation.Attributes.intensity"))
    rain_intensity= convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes.intensity)
    findOpen = strfind(rain_intensity, ';');
    values = [];
    for i= 1:length(findOpen)+1
        if i==1
            values = [values,str2double(extractBetween(rain_intensity, 2, findOpen(i)-1))];
        end
        if i>1 && i<length(findOpen)+1
            values = [values,str2double(extractBetween(rain_intensity, findOpen(i-1)+1, findOpen(i)-1))];
        end
        if i== length(findOpen)+1
            values = [values,str2double(extractBetween(rain_intensity, findOpen(i-1)+1, strlength(rain_intensity)-1))];
        end
    end
    setRainIntensity(values)
end

if(field_exists(Struct_OpenSCENARIO,"Struct_OpenSCENARIO.OpenSCENARIO.GlobalAction.EnvironmentAction.TargetProperties.Lidar.TargetPropertySettings.Attributes.ReflectionPercentage"))
    reflectivity = convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Global.SetEnvironment.TargetProperties.Lidar.TargetPropertySettings.Attributes.ReflectionPercentage)
    if(contains(reflectivity, '{'))
        findOpen = strfind(reflectivity, ',');
            start_val = extractBetween(reflectivity, 2, findOpen(1)-1);
            step = extractBetween(reflectivity, findOpen(1)+1, findOpen(2)-1);
            end_val = extractBetween(reflectivity, findOpen(2)+1, strlength(reflectivity)-1);
            setReflectivity(str2double(start_val), str2double(step), str2double(end_val))
    end
end




%%  Create OpenSCENARIO files
waitbar(.23,ta_openscenario_progress_bar,'Creating OpenSCENARIO experiments');
cd(adeye_base + "OpenSCENARIO\Code")

name_ego = EgoNameArray(1);
name_prescan_experiment = PrescanExpNameArray(1);

%Creating multiple .xosc and experiment files
listOfNames = OpenScenarioMod(convertStringsToChars(ScenarioExpNameArray(1)));

for i = 1:length(listOfNames)
    waitbar(.23+(i-1)*0.5/length(listOfNames),ta_openscenario_progress_bar,'Creating OpenSCENARIO experiments');
    listOfNames(i)
    API_main(name_ego,name_prescan_experiment,listOfNames(i))
end

%% Configure OpenSCENARIO experiments
waitbar(.73,ta_openscenario_progress_bar,'Configuring OpenSCENARIO experiments');

ScenarioExpNameArray = listOfNames;
PrescanExpName = PrescanExpNameArray(1);
% remove .xosc file extension
for i=1:length(listOfNames)
    ScenarioExpNameArray(i) = erase(ScenarioExpNameArray(i),".xosc");
    FolderExpNameArray(i) = strcat(PrescanExpName,"/OpenSCENARIO/Results/",ScenarioExpNameArray(i),"/OpenSCENARIO");
    copyfile(strcat("../OpenSCENARIO_experiments/",ScenarioExpNameArray(i),".xosc"),strcat("../../Experiments/",FolderExpNameArray(i)))
end
duplicateEgoNames(length(listOfNames));
duplicatePrescanExp(length(listOfNames));



%% Create Experiments and run
waitbar(.83,ta_openscenario_progress_bar,'Generating TAOrder file');

cd(adeye_base + "TA")
TACombinations(FolderExpNameArray, PrescanExpNameArray, EgoNameArray, AutowareConfigArray, SimulinkConfigArray, TagsConfigArray, SSHConfig)




waitbar(.93,ta_openscenario_progress_bar,'Starting TA');
rosshutdown
close(ta_openscenario_progress_bar)
% TA('Configurations/TAOrder.xlsx', 150, 2000, 1)
%TA('Configurations/TAOrder.xlsx', 1, 2)
TA('Configurations/TAOrder.xlsx', 1, 500)






%% Functions
% duplicates the current configurations of experiemnts nb_duplications
% times
function duplicateAutowareConfigs(nb_duplications)
    global AutowareConfigArray
    AutowareConfigArray = repelem(AutowareConfigArray,nb_duplications);
end

function duplicateSimulinkConfigs(nb_duplications)
    global SimulinkConfigArray
    SimulinkConfigArray = repelem(SimulinkConfigArray,nb_duplications);
end

function duplicateEgoNames(nb_duplications)
    global EgoNameArray
    EgoNameArray = repelem(EgoNameArray,nb_duplications);
end

function duplicatePrescanExp(nb_duplications)
    global PrescanExpNameArray
    PrescanExpNameArray = repelem(PrescanExpNameArray,nb_duplications);
end

% sets the reflectivity in SimulinkConfigs and updates the list
function setReflectivity(start_val, step, end_val)
    global SimulinkConfigArray
    old_nb_experiments = length(SimulinkConfigArray);
    nb_steps = fix((end_val - start_val) / step) +1;
    duplicateSimulinkConfigs(nb_steps);
    %duplicateConfigs(nb_steps);
    for i = 1:nb_steps
        for j=1:old_nb_experiments
            table = readtable(SimulinkConfigArray(i+(j-1)*nb_steps));
            row = find(strcmp('percent_reflecting_sfc',table{:,1}));
            table{row,2} = start_val+(i-1)*step;
            insertBefore(SimulinkConfigArray(i),'.xlsx',strcat('_',num2str(i)));
            writetable(table,insertBefore(SimulinkConfigArray(i+(j-1)*nb_steps),'.xlsx',strcat('_',num2str(i))));
            SimulinkConfigArray(i+(j-1)*nb_steps)=insertBefore(SimulinkConfigArray(i+(j-1)*nb_steps),'.xlsx',strcat('_',num2str(i)));
        end
    end
end


% sets the Rain Intensity in SimulinkConfigs and updates the list
function setRainIntensity(values)
    global SimulinkConfigArray
    old_nb_experiments = length(SimulinkConfigArray);
    nb_steps = length(values);
    duplicateSimulinkConfigs(nb_steps);
    %duplicateConfigs(nb_steps);
    for i = 1:nb_steps
        for j=1:old_nb_experiments
            table = readtable(SimulinkConfigArray(i+(j-1)*nb_steps));
            row = find(strcmp('R',table{:,1}));
            table{row,2} = values(i);
            insertBefore(SimulinkConfigArray(i),'.xlsx',strcat('_',num2str(i)));
            writetable(table,insertBefore(SimulinkConfigArray(i+(j-1)*nb_steps),'.xlsx',strcat('_',num2str(i))));
            SimulinkConfigArray(i+(j-1)*nb_steps)=insertBefore(SimulinkConfigArray(i+(j-1)*nb_steps),'.xlsx',strcat('_',num2str(i)));
        end
    end
end


% sets the Rain Intensity in AutowareConfigs and updates the list
function setSpeedEgo(start_val, step, end_val)
    global AutowareConfigArray
    old_nb_experiments = length(AutowareConfigArray);
    nb_steps = fix((end_val - start_val) / step) +1;
    duplicateAutowareConfigs(nb_steps);
    %duplicateConfigs(nb_steps);
    for i = 1:nb_steps
        for j=1:old_nb_experiments
            table = readtable(AutowareConfigArray(i+(j-1)*nb_steps));
            row = find(strcmp('maxVelocity',table{:,3}));
            table{row,7} = {num2str(start_val+(i-1)*step)};
            insertBefore(AutowareConfigArray(i),'.xlsx',strcat('_',num2str(i)));
            writetable(table,insertBefore(AutowareConfigArray(i+(j-1)*nb_steps),'.xlsx',strcat('_',num2str(i))));
            AutowareConfigArray(i+(j-1)*nb_steps)=insertBefore(AutowareConfigArray(i+(j-1)*nb_steps),'.xlsx',strcat('_',num2str(i)));
        end
    end
end
