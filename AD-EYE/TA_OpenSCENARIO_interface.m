name_model = "KTH_pedestrian_autoware";
name_ego = "BMW_X5_SUV_1";
name_experiment = "KTH_pedestrian_autoware";

%Creating multiple .xosc and experiment files
listOfNames = OpenScenarioMod(convertStringsToChars(name_experiment));

for i = 1:length(listOfNames)
    listOfNames(i)
API_main(name_ego,name_experiment,listOfNames(i))
end




EgoNameArray = ["BMW_X5_SUV_1" "BMW_X5_SUV_1" "BMW_X5_SUV_1" "BMW_X5_SUV_1"];
ExpNameArray = ["KTH_pedestrian_autoware1" "KTH_pedestrian_autoware2" "KTH_pedestrian_autoware3" "KTH_pedestrian_autoware4"];
AutowareExpNameArray = ["KTH_pedestrian_autoware" "KTH_pedestrian_autoware" "KTH_pedestrian_autoware" "KTH_pedestrian_autoware" ];
AutowareConfigArray = ["AutowareConfig1.xlsx" "AutowareConfig2.xlsx" "AutowareConfig3.xlsx" "AutowareConfig4.xlsx"];
GoalConfigArray = ["GoalConfig.xlsx" ];
SimulinkConfigArray = ["SimulinkConfig.xlsx"];
TagsConfigArray = [""];
SHHConfig = "ssh";



%cd '..\..\TA'
% TACombinations(ExpNameArray, AutowareExpNameArray, EgoNameArray, AutowareConfigArray, GoalConfigArray, SimulinkConfigArray, TagsConfigArray, SHHConfig)
% 
% rosshutdown
% 
% TA('TAOrder.csv')