 name_model = "Map_pedestrian_autoware";
name_ego = "Mazda_RX8_Coupe_1"; 
name_experiment = "Map_pedestrian_autoware";

ExpNameArray = ["Map_pedestrian_autoware1" "Map_pedestrian_autoware2"];
AutowareExpNameArray = ["Map_pedestrian_autoware" ];
AutowareConfigArray = ["AutowareConfig.xlsx" ];
GoalConfigArray = ["GoalConfig.xlsx" ];
SimulinkConfigArray = ["SimulinkConfig.xlsx"];
TagsConfigArray = ["TagsConfig" ];
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

%TACombinations(ExpNameArray, AutowareExpNameArray, AutowareConfigArray, GoalConfigArray, SimulinkConfigArray, TagsConfigArray, SHHConfig)
% 
% cd '..\..\TA'
% rosshutdown
%   TA('TAOrder.csv')  