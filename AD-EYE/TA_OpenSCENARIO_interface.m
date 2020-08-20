adeye_base = "C:\Users\adeye\AD-EYE_Core\AD-EYE\";

%% Parameter onfigurations

global EgoNameArray
global ExpNameArray
global PrescanExpNameArray
global AutowareConfigArray
global GoalConfigArray
global SimulinkConfigArray
global TagsConfigArray
EgoNameArray = ["BMW_X5_SUV_1"];
ExpNameArray = ["KTH_pedestrian_autowareRain"]; %to fill in based on the length of OpenScenarioMod
PrescanExpNameArray = ["KTH_pedestrian_autoware"];
AutowareConfigArray = ["AutowareConfigTemplate.xlsx"];
GoalConfigArray = ["GoalConfig.xlsx"];
SimulinkConfigArray = ["SimulinkConfig.xlsx"];
TagsConfigArray = [""];
SHHConfig = "ssh";

%% Extract TA specific configurations (AutowareConfig or SimulinkConfig)
strcat('..\OpenSCENARIO_experiments',ExpNameArray(1))
cd(adeye_base + "OpenSCENARIO\Code")
Struct_OpenSCENARIO = xml2struct([convertStringsToChars(strcat('..\OpenSCENARIO_experiments\',ExpNameArray(1))), '.xosc']);
%Struct_OpenSCENARIO = xml2struct(['..\OpenSCENARIO_experiments\KTH_pedestrian_autowareRain', '.xosc']);
cd(adeye_base + "TA\Configurations")

for x = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private)
    if('Ego' == convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Attributes.object))
        speed_ego = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,1}.Longitudinal.Speed.Target.Absolute.Attributes.value
        if(length(strfind(speed_ego, '{')) > 0)
            findOpen = strfind(speed_ego, ';');
                start_val = extractBetween(speed_ego, 2, findOpen(1)-1);
                step = extractBetween(speed_ego, findOpen(1)+1, findOpen(2)-1);
                end_val = extractBetween(speed_ego, findOpen(2)+1, strlength(speed_ego)-1);
                setSpeedEgo(str2double(start_val), str2double(step), str2double(end_val))
        end

    end
end

if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions),'Global') == 1 ) 
    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global),'SetEnvironment') == 1 )  %if SetEnvironment exists
        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment),'Environment') == 1 )  %if Environment exists
            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment),'Weather') == 1 )  %if Weather exist
                if(convertCharsToStrings( Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes.type) == "typeRain")
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes),'intensity') == 1 ) 
                        rain_intensity= convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes.intensity)
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
                end
            end
        end
    end
end

if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions),'Global') == 1 ) 
    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global),'SetEnvironment') == 1 )  %if SetEnvironment exists
        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment),'Environment') == 1 )  %if Environment exists
            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment),'TargetProperties') == 1)
                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.TargetProperties),'Lidar') == 1)
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.TargetProperties.Lidar),'TargetPropertySettings') == 1)
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.TargetProperties.Lidar.TargetPropertySettings),'Attributes') == 1)
                            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.TargetProperties.Lidar.TargetPropertySettings.Attributes),'ReflectionPercentage') == 1)
                                
                                
                                reflectivity = convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.TargetProperties.Lidar.TargetPropertySettings.Attributes.ReflectionPercentage)
                                if(length(strfind(reflectivity, '{')) > 0)
                                    findOpen = strfind(reflectivity, ';');
                                        start_val = extractBetween(reflectivity, 2, findOpen(1)-1);
                                        step = extractBetween(reflectivity, findOpen(1)+1, findOpen(2)-1);
                                        end_val = extractBetween(reflectivity, findOpen(2)+1, strlength(reflectivity)-1);
                                        setReflectivity(str2double(start_val), str2double(step), str2double(end_val))
                                end
                            end
                        end
                    end
                end
            end
        end
    end
end



%%  Create openscenario files

cd(adeye_base + "OpenSCENARIO\Code")

name_ego = EgoNameArray(1);
name_prescan_experiment = PrescanExpNameArray(1);

%Creating multiple .xosc and experiment files
listOfNames = OpenScenarioMod(convertStringsToChars(ExpNameArray(1)));

for i = 1:length(listOfNames)
    listOfNames(i)
    API_main(name_ego,name_prescan_experiment,listOfNames(i))
end

%% Configure OpenScenario experiments

% duplicateConfigs(length(listOfNames));
% for i = 1:length(ExpNameArray)/length(listOfNames)
%     ExpNameArray((i-1)*length(listOfNames)+1:i*length(listOfNames)) = listOfNames;
% end
ExpNameArray = listOfNames;
% remove .xosc file extension
for i=1:length(listOfNames)
    ExpNameArray(i) = erase(ExpNameArray(i),".xosc");
end
duplicateEgoNames(length(listOfNames));
duplicatePrescanExp(length(listOfNames));



%% Create Experiments and run

cd(adeye_base + "TA")
TACombinations(ExpNameArray, PrescanExpNameArray, EgoNameArray, AutowareConfigArray, GoalConfigArray, SimulinkConfigArray, TagsConfigArray, SHHConfig)

rosshutdown

TA('TAOrder.csv')






%% Functions
% duplicates the current configurations of experiemnts nb_duplications
% times
function duplicateConfigs(nb_duplications)
    global EgoNameArray
    global ExpNameArray
    global PrescanExpNameArray
    global AutowareConfigArray
    global GoalConfigArray
    global SimulinkConfigArray
    global TagsConfigArray
    EgoNameArray = repelem(EgoNameArray,nb_duplications);
    ExpNameArray = repelem(ExpNameArray,nb_duplications);
    PrescanExpNameArray = repelem(PrescanExpNameArray,nb_duplications);
    AutowareConfigArray = repelem(AutowareConfigArray,nb_duplications);
    GoalConfigArray = repelem(GoalConfigArray,nb_duplications);
    SimulinkConfigArray = repelem(SimulinkConfigArray,nb_duplications);
    TagsConfigArray = repelem(TagsConfigArray,nb_duplications);
end

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
