%% Create parameters configurations for Experiment C as well as the TAOrder file

template_config = "Configurations/SimulinkConfigTemplate.xlsx";
table = readtable(template_config, 'ReadRowNames',true,'ReadVariableNames',false);
TAOrder = readtable("Configurations/TAOrderExperimentC.xlsx", 'ReadRowNames',true,'ReadVariableNames',false);
values = table.Variables;


parameters = cell(2,2);
parameters{1,1} = 19; % reflectivity
parameters{1,2} = 0.05:0.2:1; % reflectivity
parameters{2,1} = 20; % intensity
parameters{2,2} = [0.5 1.5 3.5 7.5 15 40]; % intensity


index = 1;
for reflectivity_index = 1:size(parameters{1,2},2)
    for intensity_index = 1:size(parameters{2,2},2)
        values = table.Variables;
        values{parameters{1,1}, 1} = parameters{1,2}(reflectivity_index);
        values{parameters{2,1}, 1} = parameters{2,2}(intensity_index);
        values{21, 1} = 1;
        values{22, 1} = 1;
        values{23, 1} = 1;
        values{24, 1} = 1;
        table.Variables = values;
        writetable(table, strcat('Configurations/SimulinkConfigExpC_', num2str(index), '.xlsx'), 'WriteRowNames', true, 'WriteVariableNames', false);
        TAOrder{1,index} =  {"W01_Base_World_experimentC"};
        TAOrder{2,index} =  {"W01_Base_World_experimentC"};
        TAOrder{3,index} =  {"BMW_X5_SUV_1"};
        TAOrder{4,index} =  {"AutowareConfigTemplate.xlsx"};
        TAOrder{5,index} =  {strcat('SimulinkConfigExpC_', num2str(index), '.xlsx')};
        TAOrder{6,index} = cell(1);
        TAOrder{7,index} = {"Configurations/SSHConfig.csv"};
        index = index +1;
    end
end

writetable(TAOrder, 'Configurations/TAOrderExperimentC_generated.xlsx', 'WriteRowNames', true, 'WriteVariableNames', false);


%% Run Experiment C
TA('Configurations/TAOrderExperimentC_generated.xlsx',1,index,1);
