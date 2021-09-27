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
% xoscFinaleNames = ["Experiment_A"];
% folderNames = ["Experiment_A"];
% prescanExperimentTemplates = ["KTH_pedestrian_autoware_light"];
% TARosParametersTemplates = ["AutowareConfigTemplate.xlsx"];
% TASimulinkParametersTemplates = ["SimulinkConfig.xlsx"];

%% Scenario 1
xoscFinaleNames = ["Pedestrian_Action"];
folderNames = ["Pedestrian_Action"];
prescanExperimentTemplates = ["W01_Base_Map"];
TARosParametersTemplates = ["AutowareConfigTemplate.xlsx"];
TASimulinkParametersTemplates = ["SimulinkConfigExpBmap1goal1.xlsx"];

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
listOfNames = OpenScenarioMod(convertStringsToChars(xoscFinaleNames(1)));

name_ego = egoNameArray(1);
name_prescan_experiment = prescanExperimentTemplates(1);

for i = 1:length(listOfNames)
    waitbar(.23+(i-1)*0.5/length(listOfNames),TAOpensScenarioProgressBar,'Creating OpenSCENARIO experiments');
    listOfNames(i)
    API_main(name_ego,name_prescan_experiment,listOfNames(i))
end


%% Extract TA specific configurations (AutowareConfig or SimulinkConfig)
waitbar(.13,TAOpensScenarioProgressBar,'Extract TA specific configurations from xosc scenarios');

addpath(adeye_base+"OpenSCENARIO\Code")
d=convertStringsToChars(strcat('..\OpenSCENARIO_experiments\',listOfNames(s)));
cd(adeye_base + "OpenSCENARIO\Code")
Struct_OpenSCENARIO = xml2struct([d(1:end-5), '.xosc']);
cd(adeye_base + "TA\Configurations")
addpath(adeye_base+"OpenSCENARIO\Code")
for x = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private)
    if(convertCharsToStrings(get_field(Struct_OpenSCENARIO,strcat("Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, ",num2str(x),"}.Attributes.entityRef"))) == "Ego")
        speedEgo = get_field(Struct_OpenSCENARIO, strcat("Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1,",num2str(x),"}.PrivateAction{1,2}.LongitudinalAction.SpeedAction.SpeedActionTarget.AbsoluteTargetSpeed.Attributes.value"));
        %Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.PrivateAction{1,1}.LongitudinalAction.SpeedAction.SpeedActionTarget.AbsoluteTargetSpeed.Attributes.value
        if(contains(speedEgo, '{'))
            findOpen = strfind(speedEgo, ',');
                startVal = extractBetween(speedEgo, 2, findOpen(1)-1);
                step = extractBetween(speedEgo, findOpen(1)+1, findOpen(2)-1);
                endVal = extractBetween(speedEgo, findOpen(2)+1, strlength(speedEgo)-1);
                setSpeedEgo(str2double(startVal), str2double(step), str2double(endVal))
        end
    end
end

if(fieldexists(Struct_OpenSCENARIO,"Struct_OpenSCENARIO.OpenSCENARIO.GlobalAction.EnvironmentAction.Environment.Weather.Precipitation.Attributes.intensity"))
    rainIntensity= convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.GlobalAction.EnvironmentAction.Environment.Weather.Precipitation.Attributes.intensity)
    findOpen = strfind(rainIntensity, ';');
    values = [];
    for i= 1:length(findOpen)+1
        if i==1
            values = [values,str2double(extractBetween(rainIntensity, 2, findOpen(i)-1))];
        end
        if i>1 && i<length(findOpen)+1
            values = [values,str2double(extractBetween(rainIntensity, findOpen(i-1)+1, findOpen(i)-1))];
        end
        if i== length(findOpen)+1
            values = [values,str2double(extractBetween(rainIntensity, findOpen(i-1)+1, strlength(rainIntensity)-1))];
        end
    end
    setRainIntensity(values)
end

if(fieldexists(Struct_OpenSCENARIO,"Struct_OpenSCENARIO.OpenSCENARIO.GlobalAction.EnvironmentAction.TargetProperties.Lidar.TargetPropertySettings.Attributes.ReflectionPercentage"))
    reflectivity = convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.GlobalAction.EnvironmentAction.TargetProperties.Lidar.TargetPropertySettings.Attributes.ReflectionPercentage)
    if(contains(reflectivity, '{'))
        findOpen = strfind(reflectivity, ',');
            start_val = extractBetween(reflectivity, 2, findOpen(1)-1);
            step = extractBetween(reflectivity, findOpen(1)+1, findOpen(2)-1);
            end_val = extractBetween(reflectivity, findOpen(2)+1, strlength(reflectivity)-1);
            setReflectivity(str2double(start_val), str2double(step), str2double(end_val))
    end
end

cd(adeye_base + "OpenSCENARIO\Code")
listOfNames2=[];
for s= 1:length(listOfNames)
    d=convertStringsToChars(strcat('..\OpenSCENARIO_experiments\',listOfNames(s)));
    cd(adeye_base + "OpenSCENARIO\Code")
    Struct_OpenSCENARIO = xml2struct([d(1:end-5), '.xosc']);
    d=convertStringsToChars(listOfNames(s));
    listOfNames2=[listOfNames2,OpenScenarioMod2(d(1:end-5))];
end

%% Configure OpenSCENARIO experiments

waitbar(.73,TAOpensScenarioProgressBar,'Configuring OpenSCENARIO experiments');
cd(adeye_base + "OpenSCENARIO\Code")

xoscFinaleNames = listOfNames;
PrescanExpName = prescanExperimentTemplates(1);
% remove .xosc file extension
for i=1:length(listOfNames)
    xoscFinaleNames(i) = erase(xoscFinaleNames(i),".xosc");
    folderNames(i) = strcat(PrescanExpName,"/OpenSCENARIO/Results/",xoscFinaleNames(i),"/OpenSCENARIO");
    copyfile(strcat("../OpenSCENARIO_experiments/",xoscFinaleNames(i),".xosc"),strcat("../../Experiments/",folderNames(i)))
end
duplicateEgoNames(length(listOfNames));
duplicatePrescanExp(length(listOfNames));



%% Create Experiments and run
waitbar(.83,TAOpensScenarioProgressBar,'Generating TAOrder file');

cd(adeye_base + "TA")
TACombinations(folderNames, prescanExperimentTemplates, egoNameArray, TARosParametersTemplates, TASimulinkParametersTemplates, tagsConfigs, SSHConfig)




waitbar(.93,TAOpensScenarioProgressBar,'Starting TA');
rosshutdown
close(TAOpensScenarioProgressBar)
% TA('Configurations/TAOrder.xlsx', 150, 2000, 1)
%TA('Configurations/TAOrder.xlsx', 1, 2)
TA('Configurations/TAOrder.xlsx', 1, 500, 0, false)






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
function setRainIntensity(rainIntensity)
    global TASimulinkParametersTemplates
    old_nb_experiments = length(TASimulinkParametersTemplates);
    nb_steps = length(values);
    duplicateSimulinkConfigs(nb_steps);
    %duplicateConfigs(nb_steps);
    for i = 1:nb_steps
        for j=1:old_nb_experiments
            table = readtable(TASimulinkParametersTemplates(i+(j-1)*nb_steps));
            row = find(strcmp('fi_lidar_rain_intensity',table{:,1}));
            table{row,2} = rainIntensity;
            row = find(strcmp('FaultInjectionLidar1',table{:,1}));
            table{row,2} = 2;
            row = find(strcmp('FaultInjectionLidar2',table{:,1}));
            table{row,2} = 2;
            row = find(strcmp('FaultInjectionLidar3',table{:,1}));
            table{row,2} = 2;
            row = find(strcmp('FaultInjectionLidar4',table{:,1}));
            table{row,2} = 2;
            insertBefore(TASimulinkParametersTemplates(i),'.xlsx',strcat('_',num2str(i)));
            writetable(table,insertBefore(TASimulinkParametersTemplates(i+(j-1)*nb_steps),'.xlsx',strcat('_',num2str(i))));
            TASimulinkParametersTemplates(i+(j-1)*nb_steps)=insertBefore(TASimulinkParametersTemplates(i+(j-1)*nb_steps),'.xlsx',strcat('_',num2str(i)));
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
