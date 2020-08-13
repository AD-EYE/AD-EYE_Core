function  API_main(name_ego,name_experiment,name_experiment_template)

clear  trajectory_variable;
close all;
clc;
clear names_trajectories

% %create new folder for the compilation sheet/simulink file/.pex to be dumped
cd( '..\..\Experiments')
folder_name = strcat(strrep(name_experiment_template,".xosc",""));
name_simulink = convertStringsToChars(strcat(name_experiment,"_cs/"));
mkdir(convertStringsToChars(folder_name));


%copy files to new folder
cd(name_experiment )
copyfile(  "simulation*", strcat("..\",folder_name) )
cd(strcat("..\..\Experiments\",folder_name,"\Simulation\"))



close_system(convertStringsToChars(name_simulink),0)
open_system(convertStringsToChars(name_simulink))
%Constructing structure from xml file OpenSCENARIO
models = prescan.experiment.readDataModels( convertStringsToChars(strcat(name_experiment,".pb")) );



%Go to folder to load xml file
cd( '..\..\..\OpenSCENARIO\Code\')
%xml2struct("..\..\Experiments\Open_scen_lucie_test1\Simulation\Open_scen_lucie_test1.pex")
Struct_OpenSCENARIO = xml2struct(strcat( "..\OpenSCENARIO_experiments\",name_experiment_template));
Struct_pex = xml2struct(strcat( "..\..\Experiments\",folder_name,"\Simulation\",name_experiment,".pex"));

%delete orginal files
delete_files(name_experiment,folder_name)


%%%%%%%%%%%%%%%%%%%%%%%%changing inital conditions
%Changing object dimensions and initial position
 [Struct_OpenSCENARIO,Struct_pex]= initialize_actors(Struct_OpenSCENARIO,Struct_pex,name_ego);
%Changing environmental variables
 [Struct_pex] = weather_conditions(Struct_OpenSCENARIO,Struct_pex);


%%%%%%%%%%%%%%%%%%%%%%%%creating variables
%Making Trajectory variable
[trajectory_variable] = trajectory_declaring(models,Struct_OpenSCENARIO);
%creating Velocity_variable
[Velocity_variable] =initial_velocity_declaring(models,Struct_OpenSCENARIO);
%count number of events per story  (story in ech column)
[Lateral_events,Longitudinal_events] = trajectory_counter(models,Struct_OpenSCENARIO,trajectory_variable);





%%%%%%%%%%%%%%%%%%%%Creating Simulink blcks
%creating ROS blocks
simulink_ego(name_simulink,models, name_ego, Struct_pex, Struct_OpenSCENARIO)
%creating label to all vehicles as simulink blocks
trajectory_labels(Velocity_variable,models,name_simulink);
%creating initial_velocity simulink blocks
initial_velocity_dynamics(name_simulink,models,Struct_OpenSCENARIO,Velocity_variable);
%Adding block for lonitudinal and lateral dynamics
 trajectory_dynamics(name_simulink,models,Struct_OpenSCENARIO,trajectory_variable,Lateral_events,Longitudinal_events,name_ego)



% %direct to folder where to save
cd( strcat("..\..\Experiments\",folder_name,"\Simulation\") )
%save .slx
 save_system(name_simulink,strcat(folder_name,"_cs"));
  %save .pb
prescan.experiment.writeDataModels(models,convertStringsToChars(strcat(folder_name,".pb")) );
% %Go back to code for redo
 cd ('..\..\..\OpenSCENARIO\Code\')
%save .pex
struct2xml(Struct_pex,strcat( "..\..\Experiments\",folder_name,"\Simulation\",folder_name,".pex"));
%close system
close_system(convertStringsToChars(strcat(folder_name,"_cs")),0)






 end
