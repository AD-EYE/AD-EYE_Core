adeye_base = "C:\Users\adeye\AD-EYE_Core\AD-EYE\";

%%  Create openscenario files

cd(adeye_base + "OpenSCENARIO\Code")

name_model = "Open_scen_lucie_test";
name_ego = "BMW_X5_SUV_1";
name_experiment = "Open_scen_lucie_test";

%Creating multiple .xosc and experiment files
listOfNames = OpenScenarioMod(convertStringsToChars(name_experiment));

for i = 1:length(listOfNames)
    listOfNames(i)
    API_main(name_ego,name_experiment,listOfNames(i))
end

%% Configure

EgoNameArray = ["BMW_X5_SUV_1" "BMW_X5_SUV_1" "BMW_X5_SUV_1" "BMW_X5_SUV_1"];
ExpNameArray = ["Open_scen_lucie_test1" "Open_scen_lucie_test2" "Open_scen_lucie_test3" "Open_scen_lucie_test4"];
AutowareExpNameArray = ["Open_scen_lucie_test" "Open_scen_lucie_test" "Open_scen_lucie_test" "Open_scen_lucie_test" ];
AutowareConfigArray = ["AutowareConfig1.xlsx" "AutowareConfig2.xlsx" "AutowareConfig3.xlsx" "AutowareConfig4.xlsx"];
GoalConfigArray = ["GoalConfig.xlsx" ];
SimulinkConfigArray = ["SimulinkConfig.xlsx"];
TagsConfigArray = [""];
SHHConfig = "ssh";

%% Create Experiments and run

cd(adeye_base + "TA")
TACombinations(ExpNameArray, AutowareExpNameArray, EgoNameArray, AutowareConfigArray, GoalConfigArray, SimulinkConfigArray, TagsConfigArray, SHHConfig)

rosshutdown

TA('TAOrder.csv')

