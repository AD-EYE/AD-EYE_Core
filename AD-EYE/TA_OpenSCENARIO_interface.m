name_model = "KTH_pedestrian_autoware";
name_ego = "BMW_X5_SUV_1"; 
name_experiment = "KTH_pedestrian_autoware";

EgoNameArray = ["BMW_X5_SUV_1" "BMW_X5_SUV_1"];
ExpNameArray = ["KTH_pedestrian_autoware1" "KTH_pedestrian_autoware2"];
AutowareExpNameArray = ["KTH_pedestrian_autoware" "KTH_pedestrian_autoware" ];
AutowareConfigArray = ["AutowareConfig.xlsx" ];
GoalConfigArray = ["GoalConfig.xlsx" ];
SimulinkConfigArray = ["SimulinkConfig.xlsx"];
TagsConfigArray = [""];
SHHConfig = "ssh";

% ExpNameArray = ["e1" "e2"];
% AutowareExpNameArray = ["a1" "a2"];
% AutowareConfigArray = ["ac1" "ac2" "ac3"];
% GoalConfigArray = ["g1" "g2"];
% SimulinkConfigArray = ["sc1" "sc2"];
% TagsConfigArray = ["t1" "t2"];
% SHHConfig = "ssh";

%Creating multiple .xosc
listOfNames = OpenScenarioMod(convertStringsToChars(name_experiment));

for i = 1:length(listOfNames)
    listOfNames(i)
API_main(name_ego,name_experiment,listOfNames(i))
end
%     %cd '..\..\TA'
%     TACombinations(ExpNameArray, AutowareExpNameArray, EgoNameArray, AutowareConfigArray, GoalConfigArray, SimulinkConfigArray, TagsConfigArray, SHHConfig)
%  
%     rosshutdown
%       TA('TAOrder.csv')  