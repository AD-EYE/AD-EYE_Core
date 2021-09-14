function addcollectdatablock(Struct_OpenSCENARIO,nameEgo,name_experiment,name_experiment_template)

folder_name = strcat(strrep(name_experiment_template,".xosc",""));
nameSimulink = convertStringsToChars(strcat(name_experiment,"_cs/"));

cd( '..\..\Experiments')
cd(strcat(name_experiment,'/OpenSCENARIO/Results'))
cd('..\..')
cd(strcat("OpenSCENARIO/Results/",folder_name,"/OpenSCENARIO"))
open_system(convertStringsToChars(nameSimulink))
addpath('..\..\..\..\..\..\OpenSCENARIO\Code\')
models = prescan.experiment.readDataModels(convertStringsToChars(strcat(folder_name, ".pb")));

cd( '..\..\..\..\..\..\OpenSCENARIO\Code\')
Struct_pex = xml2struct(strcat( "..\..\Experiments\",name_experiment,"\OpenSCENARIO\Results\",folder_name,"\OpenSCENARIO\",name_experiment,".pex"));

%Changing object dimensions and initial position
[Struct_OpenSCENARIO,Struct_pex]= initialize_actors(Struct_OpenSCENARIO,Struct_pex,nameEgo);
%Making Trajectory variable
[trajectory_variable] = trajectory_declaring(models,Struct_OpenSCENARIO);
%count number of events per story  (story in ech column)
[Lateral_events,Longitudinal_events] = trajectory_counter(models,Struct_OpenSCENARIO,trajectory_variable);


    numberOfSimout = 0;
    for j = 1:length(models.worldmodel.object) %Declare number of objects in xml file %main for loop

        if(convertCharsToStrings(models.worldmodel.object{j, 1}.name  ) == nameEgo)
            locationSimulinkObject = strcat(nameSimulink,convertCharsToStrings(models.worldmodel.object{j,1}.name) ,"/");
            blockMainBlock = "Main_block";
            locationMainBlock = convertStringsToChars(strcat(locationSimulinkObject,blockMainBlock));
            
            add_block("simulink/Sinks/To Workspace", strcat(locationSimulinkObject, "Workspace"));
            add_line(locationSimulinkObject, "from_velocity/1", "Workspace/1");
            set_param(strcat(locationSimulinkObject, "Workspace"),'Saveformat','Structure With Time');
            set_param(strcat(locationSimulinkObject, "Workspace"),'Variablename','simout_0_1');
        end
        
        trajectory_type = ["Longitudinal","Lateral"];
        for z = 1:length(trajectory_type)
            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            p = 0;
            if(isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard,'Story'))
                for q = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story  ) %Number of Stories
                    for a= 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act) %Number of acts

                        %check if a trajectory variable exists
                        if( exist('trajectory_variable','var') == 1)
                            %check if an object in trajectory variable exists
                            if(isfield(convertCharsToStrings(trajectory_variable),convertCharsToStrings(models.worldmodel.object{j, 1}.name)) == 1 )
                                %check which story belongs to which car
                                if(convertCharsToStrings(models.worldmodel.object{j, 1}.name)== convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1, q}.Act{1,a}.ManeuverGroup.Actors.EntityRef.Attributes.entityRef))
                                    for m = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver)%Number of Maneuvers
                                        for i=1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event)
                                            if(isfield(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name)), convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name))== 1 )
                                                    %check if it is a lateral trajectory
                                                if(isfield(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name)),trajectory_type(1,z) ) == 1 )
                                                    %check if Object structure exists
                                                    if(isfield(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition),"Objects") == 1 )
                                                        %check if a Condition structure exists
                                                        if(isfield(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition),"Distance_RelativeObject") == 1  || isfield(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition),"TimeHeadWay") == 1 || isfield(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition),"SimulationTimeCondition") == 1  || isfield(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition),"Speed_RelativeObject") == 1)
                                                            
                                                            %number of events (trajectories)
                                                            p = p+1;
                                                            
                                                            locationDynamicsEmpty = strcat(nameSimulink,convertCharsToStrings(models.worldmodel.object{j,1}.name),"/Dynamics_Empty/");
                                                            if(trajectory_type(1,z) =="Lateral")
                                                                p_L = Lateral_events;
                                                            elseif(trajectory_type(1,z) =="Longitudinal")
                                                                p_L = Longitudinal_events;
                                                            end
                                                            
                                                            if ( p ==p_L(1,q))
                                                                numberOfSimout = numberOfSimout +1;
                                                                add_block("simulink/Sinks/To Workspace", strcat(locationDynamicsEmpty, "Workspace_", num2str(numberOfSimout), "_", num2str(z)));
                                                                add_line(locationDynamicsEmpty, strcat(trajectory_type(1,z),"_Dynamics/1"), strcat("Workspace_", num2str(numberOfSimout), "_", num2str(z),"/1"));
                                                                set_param(strcat(locationDynamicsEmpty, "Workspace_", num2str(numberOfSimout), "_", num2str(z)),'Saveformat','Structure With Time');
                                                                set_param(strcat(locationDynamicsEmpty, "Workspace_", num2str(numberOfSimout), "_", num2str(z)),'Variablename',strcat('simout_', num2str(numberOfSimout), '_',num2str(z)));
                                                            end
                                                            
                                                        end %if statement lateral check
                                                    end %for loop number of events (trajectories)
                                                end
                                            end %if statement which story belongs to which object
                                        end %numb er of maneuvers
                                    end %if statement which object has trajectories
                                end %Check if object has which event
                            end %if statement to check existence of object in trajectory_variable
                        end %if trajectory variable exists
                    end %if statement to check existence of event in trajectory_variable

                end %Number of Stories

            end %if Story 
        end %for in trajectory_type
    end% main for loop
    
% %direct to folder where to save
cd( strcat("..\..\Experiments\",name_experiment,"\OpenSCENARIO\Results\",folder_name,"\OpenSCENARIO") )
%save .slx
save_system(nameSimulink,strcat(name_experiment,"_cs"));
%save .pb
prescan.experiment.writeDataModels(models,convertStringsToChars(strcat(folder_name,".pb")) );
% %Go back to code for redo
 cd ('..\..\..\..\..\..\OpenSCENARIO\Code\')
%close system
close_system(convertStringsToChars(nameSimulink),0)

end