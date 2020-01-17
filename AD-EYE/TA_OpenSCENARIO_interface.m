adeye_base = "C:\Users\adeye\Documents\AD-EYE_Core\AD-EYE\";

%%  Create openscenario files

cd(adeye_base + "OpenSCENARIO\Code")

name_model = "KTH_car_osc";
name_ego = "BMW_X5_SUV_1";
name_experiment = "KTH_car_osc";

%Creating multiple .xosc and experiment files
listOfNames = OpenScenarioMod(convertStringsToChars(name_experiment));

for i = 1:length(listOfNames)
    listOfNames(i)
    API_main(name_ego,name_experiment,listOfNames(i))
end

%% Configure

EgoNameArray = ["BMW_X5_SUV_1" "BMW_X5_SUV_1" "BMW_X5_SUV_1" "BMW_X5_SUV_1"];
ExpNameArray = ["KTH_car_osc1" "KTH_car_osc2" "KTH_car_osc3" "KTH_car_osc4" "KTH_car_osc5"];
AutowareExpNameArray = ["KTH_car_osc" "KTH_car_osc" "KTH_car_osc" "KTH_car_osc" "KTH_car_osc"];
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
