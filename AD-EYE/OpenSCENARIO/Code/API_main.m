function  API_main(nameEgo,nameExperiment,nameExperimentTemplate)

clear  trajectory_variable;
close all;
clc;
clear names_trajectories

% %create new folder for the compilation sheet/simulink file/.pex to be dumped
cd( '..\..\Experiments')
if ~exist(strcat(nameExperiment,'/OpenSCENARIO/Results'), 'dir')
   mkdir(strcat(nameExperiment,'/OpenSCENARIO/Results'))
end
cd(strcat(nameExperiment,'/OpenSCENARIO/Results'))
folderName = strcat(strrep(nameExperimentTemplate,".xosc",""));
nameSimulink = convertStringsToChars(strcat(nameExperiment,"_cs/"));
mkdir(convertStringsToChars(folderName));

%copy files to new folder
cd('..\..')%name_experiment)
mkdir("Results")
mkdir(strcat("Results\",folderName))
copyfile(strcat("OpenSCENARIO\",nameExperiment,"*"), strcat("Results\",folderName,"\OpenSCENARIO"))
if exist('OpenSCENARIO\Resources','dir')
    copyfile("OpenSCENARIO\Resources*", strcat("Results\",folderName,"\OpenSCENARIO"))  
end
movefile("Results\","OpenSCENARIO\")
cd(strcat("OpenSCENARIO/Results/",folderName,"/OpenSCENARIO"))



close_system(convertStringsToChars(nameSimulink), 0)
open_system(convertStringsToChars(nameSimulink))
%Constructing structure from xml file OpenSCENARIO

if ~isfile(convertStringsToChars(strcat(nameExperiment, ".pb")))
    disp("Experiment was not built, it will be built now");
    command = 'PreScan.CLI.exe'; %all the commands in 'Command' variable ...
    ...are concatenated and executed using a dos function in the end
    CurrentExperiment = strcat(pwd, '\', nameExperiment, '.pex');
    command = strcat(command, ' -load ', ' "', CurrentExperiment, '"'); %load the MainExperiment in PreScan
    command = strcat(command, ' -realignPaths'); %unknown use from PreScan
    command = strcat(command, ' -build'); %build the experiment
    command = strcat(command, ' -close');
    errorCode = dos(command); %takes all the above commands in 'Command' variable and execute
    if errorCode ~= 0
        error(['Failed to perform build command: error code' errorCode]);
    end
end
models = prescan.experiment.readDataModels(convertStringsToChars(strcat(nameExperiment, ".pb")));



%Go to folder to load xml file
cd( '..\..\..\..\..\..\OpenSCENARIO\Code\')
%xml2struct("..\..\Experiments\Map_pedestrian_autoware1\Simulation\Map_pedestrian_autoware1.pex")
StructOpenSCENARIO = xml2struct(strcat( "..\OpenSCENARIO_experiments\",nameExperimentTemplate));
StructPex = xml2struct(strcat( "..\..\Experiments\",nameExperiment,"\OpenSCENARIO\Results\",folderName,"\OpenSCENARIO\",nameExperiment,".pex"));

%delete orginal files
delete_files(nameExperiment,folderName)


%%%%%%%%%%%%%%%%%%%%%%%%changing inital conditions
%Changing object dimensions and initial position
 [StructOpenSCENARIO,StructPex]= initializeactors(StructOpenSCENARIO,StructPex,nameEgo);
%Changing environmental variables
 [StructPex] = weatherconditions(StructOpenSCENARIO,StructPex);


%%%%%%%%%%%%%%%%%%%%%%%%creating variables
%Making Trajectory variable
[trajectoryVariable] = trajectorydeclaring(models,StructOpenSCENARIO);
%creating Velocity_variable
[velocityVariable] =initialvelocitydeclaring(models,StructOpenSCENARIO);
%count number of events per story  (story in each column)
[lateralEvents,longitudinalEvents] = trajectorycounter(models,StructOpenSCENARIO,trajectoryVariable);





%%%%%%%%%%%%%%%%%%%%Creating Simulink blocks
%creating ROS blocks
simulinkego(nameSimulink,models, nameEgo, StructPex, StructOpenSCENARIO)
%creating label to all vehicles as simulink blocks
trajectorylabels(velocityVariable,models,nameSimulink);
%creating initial_velocity simulink blocks
initialvelocitydynamics(nameSimulink,models,StructOpenSCENARIO,velocityVariable);
%Adding block for lonitudinal and lateral dynamics
trajectoryDynamics(nameSimulink,models,StructOpenSCENARIO,trajectoryVariable,lateralEvents,longitudinalEvents,nameEgo)



% %direct to folder where to save
cd( strcat("..\..\Experiments\",nameExperiment,"\OpenSCENARIO\Results\",folderName,"\OpenSCENARIO") )
%save .slx
 save_system(nameSimulink,strcat(nameExperiment,"_cs"));
  %save .pb
prescan.experiment.writeDataModels(models,convertStringsToChars(strcat(folderName,".pb")) );
% %Go back to code for redo
 cd ('..\..\..\..\..\..\OpenSCENARIO\Code\')
%save .pex
struct2xml(StructPex,strcat( "..\..\Experiments\",nameExperiment,"\OpenSCENARIO\Results\",folderName,"\OpenSCENARIO\",nameExperiment,".pex"));
%close system
close_system(convertStringsToChars(nameSimulink),0)






 end
