function  API_main(name_ego,name_experiment,name_experiment_template)

clear  trajectory_variable;
close all;
clc;
clear names_trajectories

% %create new folder for the compilation sheet/simulink file/.pex to be dumped
cd( '..\..\Experiments')
if ~exist(strcat(name_experiment,'/OpenSCENARIO/Results'), 'dir')
   mkdir(strcat(name_experiment,'/OpenSCENARIO/Results'))
end
cd(strcat(name_experiment,'/OpenSCENARIO/Results'))
folder_name = strcat(strrep(name_experiment_template,".xosc",""));
name_simulink = convertStringsToChars(strcat(name_experiment,"_cs/"));
mkdir(convertStringsToChars(folder_name));

%copy files to new folder
cd('..\..')%name_experiment)
mkdir("Results")
mkdir(strcat("Results\",folder_name))
copyfile(strcat("OpenSCENARIO\",name_experiment,"*"), strcat("Results\",folder_name,"\OpenSCENARIO"))
if exist('OpenSCENARIO\Resources','dir')
    copyfile("OpenSCENARIO\Resources*", strcat("Results\",folder_name,"\OpenSCENARIO"))  
end
movefile("Results\","OpenSCENARIO\")
cd(strcat("OpenSCENARIO/Results/",folder_name,"/OpenSCENARIO"))



close_system(convertStringsToChars(name_simulink), 0)
open_system(convertStringsToChars(name_simulink))
%Constructing structure from xml file OpenSCENARIO

if ~isfile(convertStringsToChars(strcat(name_experiment, ".pb")))
    disp("Experiment was not built, it will be built now");
    command = 'PreScan.CLI.exe'; %all the commands in 'Command' variable ...
    ...are concatenated and executed using a dos function in the end
    CurrentExperiment = strcat(pwd, '\', name_experiment, '.pex');
    command = strcat(command, ' -load ', ' "', CurrentExperiment, '"'); %load the MainExperiment in PreScan
    command = strcat(command, ' -realignPaths'); %unknown use from PreScan
    command = strcat(command, ' -build'); %build the experiment
    command = strcat(command, ' -close');
    errorCode = dos(command); %takes all the above commands in 'Command' variable and execute
    if errorCode ~= 0
        error(['Failed to perform build command: error code' errorCode]);
    end
end
models = prescan.experiment.readDataModels(convertStringsToChars(strcat(name_experiment, ".pb")));



%Go to folder to load xml file
cd( '..\..\..\..\..\..\OpenSCENARIO\Code\')
%xml2struct("..\..\Experiments\Map_pedestrian_autoware1\Simulation\Map_pedestrian_autoware1.pex")
Struct_OpenSCENARIO = xml2struct(strcat( "..\OpenSCENARIO_experiments\",name_experiment_template));
Struct_pex = xml2struct(strcat( "..\..\Experiments\",name_experiment,"\OpenSCENARIO\Results\",folder_name,"\OpenSCENARIO\",name_experiment,".pex"));

%delete orginal files
delete_files(name_experiment,folder_name)


%%%%%%%%%%%%%%%%%%%%%%%%changing inital conditions
%Changing object dimensions and initial position
 [Struct_OpenSCENARIO,Struct_pex]= initializeactors(Struct_OpenSCENARIO,Struct_pex,name_ego);
%Changing environmental variables
 [Struct_pex] = weatherconditions(Struct_OpenSCENARIO,Struct_pex);


%%%%%%%%%%%%%%%%%%%%%%%%creating variables
%Making Trajectory variable
[trajectoryVariable] = trajectorydeclaring(models,Struct_OpenSCENARIO);
%creating Velocity_variable
[velocityVariable] =initialvelocitydeclaring(models,Struct_OpenSCENARIO);
%count number of events per story  (story in ech column)
[lateralEvents,longitudinalEvents] = trajectorycounter(models,Struct_OpenSCENARIO,trajectoryVariable);





%%%%%%%%%%%%%%%%%%%%Creating Simulink blocks
%creating ROS blocks
simulinkego(name_simulink,models, name_ego, Struct_pex, Struct_OpenSCENARIO)
%creating label to all vehicles as simulink blocks
trajectorylabels(velocityVariable,models,name_simulink);
%creating initial_velocity simulink blocks
initialvelocitydynamics(name_simulink,models,Struct_OpenSCENARIO,velocityVariable);
%Adding block for lonitudinal and lateral dynamics
trajectorydynamics2(name_simulink,models,Struct_OpenSCENARIO,trajectoryVariable,lateralEvents,longitudinalEvents,name_ego)



% %direct to folder where to save
cd( strcat("..\..\Experiments\",name_experiment,"\OpenSCENARIO\Results\",folder_name,"\OpenSCENARIO") )
%save .slx
 save_system(name_simulink,strcat(name_experiment,"_cs"));
  %save .pb
prescan.experiment.writeDataModels(models,convertStringsToChars(strcat(folder_name,".pb")) );
% %Go back to code for redo
 cd ('..\..\..\..\..\..\OpenSCENARIO\Code\')
%save .pex
struct2xml(Struct_pex,strcat( "..\..\Experiments\",name_experiment,"\OpenSCENARIO\Results\",folder_name,"\OpenSCENARIO\",name_experiment,".pex"));
%close system
close_system(convertStringsToChars(name_simulink),0)






 end
