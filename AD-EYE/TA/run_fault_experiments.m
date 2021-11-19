% nb_runs = 240;
nb_runs = 20;

folderNames = ["W15_Road_Side_Parking\W15_Road_Side_Parking_low_res"];
prescanExperimentTemplates = ["W15_Road_Side_Parking"];
TARosParametersTemplates = ["AutowareConfigTemplate.xlsx"];
TASimulinkParametersTemplates = ["SimulinkEmptyConfig.xlsx"];
TASimulinkParametersTemplates = repelem(TASimulinkParametersTemplates, nb_runs);

egoNameArray = ["BMW_X5_SUV_1"];
tagsConfigs = [""];
SSHConfig = "Configurations/SSHConfig.csv";

TACombinations(folderNames, prescanExperimentTemplates, egoNameArray, TARosParametersTemplates, TASimulinkParametersTemplates, tagsConfigs, SSHConfig)



TA('Configurations/TAOrder.xlsx', 1, 500, 1, false)