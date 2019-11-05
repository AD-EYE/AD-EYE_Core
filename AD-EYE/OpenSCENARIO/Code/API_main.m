function  API_main(name_model,name_ego,name_experiment,name_experiment_template)


clear  trajectory_variable;
close all;
clc;
clear names_trajectories
name_simulink = convertStringsToChars(strcat(name_model,"_cs/")); 

%create new folder for the compilation sheet/simulink file/.pex to be dumped
cd  '..\..\Experiments'
folder_name = strcat(name_experiment_template,"_OpenSCENARIO");
mkdir(convertStringsToChars(folder_name));

%copy files to new folder
cd( convertStringsToChars(strcat(name_experiment)) )
copyfile(  "simulation*", strcat("..\",folder_name) )


%load .pex, .slx, .pb
cd '.\Simulation'
close_system(convertStringsToChars(strcat(name_model,"_cs")),0)
open_system(convertStringsToChars(strcat(name_model,"_cs")))
%Constructing structure from xml file OpenSCENARIO
models = prescan.experiment.readDataModels( convertStringsToChars(strcat(name_model,".pb")) );

%Back to the code folder
cd  '..\..\..\OpenSCENARIO\Code\'


%Go to folder to load xml file
cd( convertStringsToChars(strcat("..\","OpenSCENARIO_experiments\")) )
Struct_OpenSCENARIO = xml2struct(convertStringsToChars(strcat(name_experiment_template,".xosc")));




%%%%%%%%%%%%%%%%%%%%%%%%changing inital conditions
%creating ROS blocks
 simulink_ego(name_simulink,models, name_ego) 
%Changing object dimensions and initial position
[Struct_OpenSCENARIO,models]= initialize_actors(models,Struct_OpenSCENARIO,name_ego);
%Changing environmental variables
[models] = weather_conditions(models,Struct_OpenSCENARIO);


%%%%%%%%%%%%%%%%%%%%%%%%creating variables
%Making Trajectory variable
[trajectory_variable] = trajectory_declaring(models,Struct_OpenSCENARIO);
%creating Velocity_variable
[Velocity_variable] =initial_velocity_declaring(models,Struct_OpenSCENARIO);
%count number of events per story  (story in ech column)
[Lateral_events,Longitudinal_events] = trajectory_counter(models,Struct_OpenSCENARIO,trajectory_variable);



%%%%%%%%%%%%%%%%%%%%Creating Simulink blcks
%creating label to all vehicles as simulink blocks
trajectory_labels(Velocity_variable,models,name_simulink);
%creating initial_velocity simulink blocks
initial_velocity_dynamics(name_simulink,models,Struct_OpenSCENARIO,Velocity_variable);
%Adding block for lonitudinal and lateral dynamics
 trajectory_dynamics(name_simulink,models,Struct_OpenSCENARIO,trajectory_variable,Lateral_events,Longitudinal_events,name_ego)



%direct to folder where to save
cd( convertStringsToChars(strcat("..\..\Experiments\",name_experiment_template,"_OpenSCENARIO\","Simulation")) )

%save everything
name_experiment = save_system(name_simulink,name_simulink);
prescan.experiment.writeDataModels(models,convertStringsToChars(strcat(name_model,".pb")) );
close_system(convertStringsToChars(strcat(name_model,"_cs")),0)

%Go back to code for redo
%call OpenSCENARIO function
cd  '..\..\..\OpenSCENARIO\Code\'

end