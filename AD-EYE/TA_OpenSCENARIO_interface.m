 name_model = "Simulation";
name_ego = "Mazda_RX8_Coupe_1"; 
name_experiment_template = "Map_pedestrian_autoware";
name_experiment = name_experiment_template;

L = xosc_generation(name_experiment_template,models);

for i = 1:L
    name_experiment_template = strcat("Map_pedestrian_autoware",int2str(i));
API_main(name_model,name_ego,name_experiment,name_experiment_template)
end



    