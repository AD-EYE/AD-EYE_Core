TAOpensScenarioProgressBar = waitbar(0,'Starting TA OpenSCENARIO interface','Name','TA_OpenSCENARIO progress');
% cleanup = onCleanup( @()(delete(TAOpensScenarioProgressBar)));


%% Parameter onfigurations

global egoNameArray
global prescanExperimentTemplates
global TARosParametersTemplates
global TASimulinkParametersTemplates
global tagsConfigs
egoNameArray = ["BMW_X5_SUV_1"];
adeye_base = "C:\Users\adeye\AD-EYE_Core\AD-EYE\";

%% Experiment A
xoscFinaleNames = ["Experiment_A"];
folderNames = ["Experiment_A"];
prescanExperimentTemplates = ["KTH_pedestrian_autoware_light"];
TARosParametersTemplates = ["AutowareConfigTemplate.xlsx"];
TASimulinkParametersTemplates = ["SimulinkConfig.xlsx"];

%% Scenario 1
% xoscFinaleNames = ["Turn_right_Signal"];
% folderNames = ["Turn_right_Signal"];
% prescanExperimentTemplates = ["W01_Base_Map"];
% TARosParametersTemplates = ["AutowareConfigTemplate.xlsx"];
% TASimulinkParametersTemplates = ["SimulinkConfigExpBmap1goal1.xlsx", "SimulinkConfigExpBmap1goal2.xlsx", "SimulinkConfigExpBmap1goal3.xlsx"];

%% Experiment B Map 1
% xoscFinaleNames = ["Experiment_B"];
% folderNames = ["Experiment_B"];
% prescanExperimentTemplates = ["W01_Base_Map"];
% TARosParametersTemplates = ["AutowareConfigTemplate.xlsx"];
% TASimulinkParametersTemplates = ["SimulinkConfigExpBmap1goal1.xlsx", "SimulinkConfigExpBmap1goal2.xlsx", "SimulinkConfigExpBmap1goal3.xlsx"];

%% Experiment B Map 2
% xoscFinaleNames = ["Experiment_B"];
% folderNames = ["Experiment_B"];
% prescanExperimentTemplates = ["W03_Forest"];
% TARosParametersTemplates = ["AutowareConfigTemplate.xlsx"];
% TASimulinkParametersTemplates = ["SimulinkConfigExpBmap2goal1.xlsx", "SimulinkConfigExpBmap2goal2.xlsx", "SimulinkConfigExpBmap2goal3.xlsx"];

%% Experiment B Map 3
% xoscFinaleNames = ["Experiment_B"];
% folderNames = ["Experiment_B"];
% prescanExperimentTemplates = ["W07_Neighborhood"];
% TARosParametersTemplates = ["AutowareConfigTemplate.xlsx"];
% TASimulinkParametersTemplates = ["SimulinkConfigExpBmap3goal1.xlsx", "SimulinkConfigExpBmap3goal2.xlsx", "SimulinkConfigExpBmap3goal3.xlsx"];




tagsConfigs = [""];
SSHConfig = "Configurations/SSHConfig.csv";

%% Create OpenSCENARIO files
waitbar(.23,TAOpensScenarioProgressBar,'Creating OpenSCENARIO experiments');

%Creating multiple .xosc and experiment files
cd(adeye_base + "OpenSCENARIO\Code")
listOfNames = openscenariomod(convertStringsToChars(xoscFinaleNames(1)));

listOfNames_2=[];
for s= 1:length(listOfNames)
    d=convertStringsToChars(strcat('..\OpenSCENARIO_experiments\',listOfNames(s)));
    cd(adeye_base + "OpenSCENARIO\Code")
    Struct_OpenSCENARIO = xml2struct([d(1:end-5), '.xosc']);
    d=convertStringsToChars(listOfNames(s));
    listOfNames_2=[listOfNames_2,openscenariomod2(d(1:end-5))];
end

%% Configure OpenSCENARIO experiments
name_ego = egoNameArray(1);
name_prescan_experiment = prescanExperimentTemplates(1);

for i = 1:length(listOfNames_2)
    waitbar(.23+(i-1)*0.5/length(listOfNames_2),TAOpensScenarioProgressBar,'Creating OpenSCENARIO experiments');
    listOfNames_2(i)
    API_main(name_ego,name_prescan_experiment,listOfNames_2(i))
end

waitbar(.73,TAOpensScenarioProgressBar,'Configuring OpenSCENARIO experiments');

xoscFinaleNames = listOfNames_2;
PrescanExpName = prescanExperimentTemplates(1);
% remove .xosc file extension
for i=1:length(listOfNames_2)
    xoscFinaleNames(i) = erase(xoscFinaleNames(i),".xosc");
    folderNames(i) = strcat(PrescanExpName,"/OpenSCENARIO/Results/",xoscFinaleNames(i),"/OpenSCENARIO");
    copyfile(strcat("../OpenSCENARIO_experiments/",xoscFinaleNames(i),".xosc"),strcat("../../Experiments/",folderNames(i)))
end
duplicateEgoNames(length(listOfNames_2));
duplicatePrescanExp(length(listOfNames_2));




%% Extract TA specific configurations (AutowareConfig or SimulinkConfig)
waitbar(.13,TAOpensScenarioProgressBar,'Extract TA specific configurations from xosc scenarios');

duplicateAutowareConfigs(length(listOfNames_2));
duplicateSimulinkConfigs(length(listOfNames_2));
for s= 1:length(listOfNames_2)
    d=convertStringsToChars(strcat('..\OpenSCENARIO_experiments\',listOfNames_2(s)));
    cd(adeye_base + "OpenSCENARIO\Code")
    Struct_OpenSCENARIO = xml2struct([d(1:end-5), '.xosc']);
    cd(adeye_base + "TA\Configurations")
    addpath(adeye_base+"OpenSCENARIO\Code")
    for x = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private)
        if(convertCharsToStrings(get_field(Struct_OpenSCENARIO,strcat("Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, ",num2str(x),"}.Attributes.entityRef"))) == "Ego")
            speed_ego = get_field(Struct_OpenSCENARIO, strcat("Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1,",num2str(x),"}.PrivateAction{1,1}.LongitudinalAction.SpeedAction.SpeedActionTarget.AbsoluteTargetSpeed.Attributes.value"));
            setSpeedEgo(speed_ego,s)
        end
    end

    if(field_exists(Struct_OpenSCENARIO,"Struct_OpenSCENARIO.OpenSCENARIO.GlobalAction.EnvironmentAction.Environment.Weather.Precipitation.Attributes.intensity"))
        rain_intensity= convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.GlobalAction.EnvironmentAction.Environment.Weather.Precipitation.Attributes.intensity);
        setRainIntensity(rain_intensity,s)
    end

    if(field_exists(Struct_OpenSCENARIO,"Struct_OpenSCENARIO.OpenSCENARIO.GlobalAction.EnvironmentAction.TargetProperties.Lidar.TargetPropertySettings.Attributes.ReflectionPercentage"))
        reflectivity = convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.GlobalAction.EnvironmentAction.TargetProperties.Lidar.TargetPropertySettings.Attributes.ReflectionPercentage);
        setReflectivity(reflectivity,s)
    end
end


%% Create Experiments and run
waitbar(.83,TAOpensScenarioProgressBar,'Generating TAOrder file');

cd(adeye_base + "TA")
TACombinations(folderNames, prescanExperimentTemplates, egoNameArray, TARosParametersTemplates, TASimulinkParametersTemplates, tagsConfigs, SSHConfig)




waitbar(.93,TAOpensScenarioProgressBar,'Starting TA');
rosshutdown
close(TAOpensScenarioProgressBar)
% TA('Configurations/TAOrder.xlsx', 150, 2000, 1)
%TA('Configurations/TAOrder.xlsx', 1, 2)
TA('Configurations/TAOrder.xlsx', 1, 500)






%% Functions
% duplicates the current configurations of experiemnts nb_duplications
% times
function duplicateAutowareConfigs(nb_duplications)
    global TARosParametersTemplates
    TARosParametersTemplates = repelem(TARosParametersTemplates,nb_duplications);
end

function duplicateSimulinkConfigs(nb_duplications)
    global TASimulinkParametersTemplates
    TASimulinkParametersTemplates = repelem(TASimulinkParametersTemplates,nb_duplications);
end

function duplicateEgoNames(nb_duplications)
    global egoNameArray
    egoNameArray = repelem(egoNameArray,nb_duplications);
end

function duplicatePrescanExp(nb_duplications)
    global prescanExperimentTemplates
    prescanExperimentTemplates = repelem(prescanExperimentTemplates,nb_duplications);
end

% sets the reflectivity in SimulinkConfigs and updates the list
function setReflectivity(reflectivity,i)
    global TASimulinkParametersTemplates
    table = readtable(TASimulinkParametersTemplates(i));
    row = find(strcmp('percent_reflecting_sfc',table{:,1}));
    table{row,2} = reflectivity;
    TASimulinkParametersTemplates(i)=insertBefore(TASimulinkParametersTemplates(i),'.xlsx',strcat('_',num2str(i)));
    insertBefore(TASimulinkParametersTemplates(i),'.xlsx',strcat('_',num2str(i)));
    writetable(table,TASimulinkParametersTemplates(i));
end


% sets the Rain Intensity in SimulinkConfigs and updates the list
function setRainIntensity(rain_intensity,i)
    global TASimulinkParametersTemplates
    table = readtable(TASimulinkParametersTemplates(i));
    TASimulinkParametersTemplates(i)=insertBefore(TASimulinkParametersTemplates(i),'.xlsx',strcat('_',num2str(i)));
    row = find(strcmp('R',table{:,1}));
    table{row,2} = rain_intensity;
    writetable(table,TASimulinkParametersTemplates(i));
end


% sets the Rain Intensity in AutowareConfigs and updates the list
function setSpeedEgo(speed_ego,i)
    global TARosParametersTemplates
    table = readtable(TARosParametersTemplates(i));
    TARosParametersTemplates(i)=insertBefore(TARosParametersTemplates(i),'.xlsx',strcat('_',num2str(i)));
    row = find(strcmp('maxVelocity',table{:,3}));
    table{row,7} = {speed_ego};
    writetable(table,TARosParametersTemplates(i));    
end

