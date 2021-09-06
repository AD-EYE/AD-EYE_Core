%%%%%%%%%%%%%%%%%%%%Storyboard Init Actions Private
%%%%%%%%%%Private Action
function [Struct_pex] = parametersweepinitialpositions(Struct_OpenSCENARIO,Struct_pex,k,i)


for j = 1:length(Struct_pex.Experiment.Actors.Actor ) %Declare number of objects in .pei file
    for x = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private )
        
        if(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.ScenarioObject{1, i}.Attributes.name) == convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Attributes.entityRef))
            %Check if j is a car in .pei file
            if ( convertCharsToStrings(Struct_pex.Experiment.Actors.Actor{1, j}.Attributes.id    ) == convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Attributes.entityRef))

                if(isfield(convertCharsToStrings(Struct_pex.Experiment.Actors.Actor{1,j}.Attributes)  ,'ObjectTypeID') == 1 )    %if objectTypeID exists
    
                    %Check if j is a car in .pei file
                    if (str2double(Struct_pex.Experiment.Actors.Actor{1, j}.Attributes.ObjectTypeID  ) == k)
                        Struct_pex.Experiment.Actors.Actor{1, j}.Attributes.id
                        %             Struct_pex.Experiment.Actors.Actor{1, j}.Attributes.ObjectTypeID
                        for y = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.PrivateAction)
                            
                            
                            %check if is it the position field
                            if(field_exists(Struct_OpenSCENARIO,strcat("Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, ",num2str(x),"}.PrivateAction{1,",num2str(y),"}.TeleportAction.Position")))
                                for z = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.PrivateAction{1,y}.TeleportAction.Position)
                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.PrivateAction{1,y}.TeleportAction.Position(1,z)),'WorldPosition') == 1 )
                                        
                                        %if i exists
                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.PrivateAction{1,y}.TeleportAction.Position(1,z).WorldPosition.Attributes),'x') == 1 )
                                            %Changing i position
                                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.PrivateAction{1,y}.TeleportAction.Position(1,z).WorldPosition.Attributes.x)) ~= 1)
                                                
                                                Struct_pex.Experiment.Actors.Actor{1, j}.Location.Attributes.X = str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}...
                                                    .PrivateAction{1,y}.TeleportAction.Position(1,z).WorldPosition.Attributes.x);
                                                                                   
                                            end
                                            
                                        end %i field check
                                        
                                        %if y exists
                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.PrivateAction{1,y}.TeleportAction.Position(1,z).WorldPosition.Attributes),'y') == 1 )
                                            %Changing y position
                                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.PrivateAction{1,y}.TeleportAction.Position(1,z).WorldPosition.Attributes.y)) ~= 1)
                                                
                                                Struct_pex.Experiment.Actors.Actor{1, j}.Location.Attributes.Y = str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}...
                                                    .PrivateAction{1,y}.TeleportAction.Position(1,z).WorldPosition.Attributes.y);
                                                                                           
                                                
                                            end
                                            
                                        end %y field check
                                        
                                        %if z exists
                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.PrivateAction{1,y}.TeleportAction.Position(1,z).WorldPosition.Attributes),'z') == 1 )
                                            %Changing z position
                                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.PrivateAction{1,y}.TeleportAction.Position(1,z).WorldPosition.Attributes.z)) ~= 1)
                                                
                                                Struct_pex.Experiment.Actors.Actor{1, j}.Location.Attributes.Z = str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}...
                                                    .PrivateAction{1,y}.TeleportAction.Position(1,z).WorldPosition.Attributes.z);
                                                                                              
                                            end
                                            
                                        end %z field check
                                        
                                        %if r exists
                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.PrivateAction{1,y}.TeleportAction.Position(1,z).WorldPosition.Attributes),'r') == 1 )
                                            %Changing roll position %ra?
                                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.PrivateAction{1,y}.TeleportAction.Position(1,z).WorldPosition.Attributes.r)) ~= 1)
                                                
                                                Struct_pex.Experiment.Actors.Actor{1, j}.Orientation.Attributes.Bank=  (180/pi)*str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}...
                                                    .PrivateAction{1,y}.TeleportAction.Position(1,z).WorldPosition.Attributes.r);
                                            end
                                            
                                        end %r field check
                                        
                                        %if p exists
                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.PrivateAction{1,y}.TeleportAction.Position(1,z).WorldPosition.Attributes),'p') == 1 )
                                            %Changing pitch position %rad
                                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.PrivateAction{1,y}.TeleportAction.Position(1,z).WorldPosition.Attributes.p)) ~= 1)
                                                
                                                Struct_pex.Experiment.Actors.Actor{1, j}.Orientation.Attributes.Tilt  = (180/pi)*str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}...
                                                    .PrivateAction{1,y}.TeleportAction.Position(1,z).WorldPosition.Attributes.p) ;
                                            end
                                        end %p field check
                                        
                                        %if h exists
                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.PrivateAction{1,y}.TeleportAction.Position(1,z).WorldPosition.Attributes),'h') == 1 )
                                            
                                            %Changing yaw position %rad
                                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.PrivateAction{1,y}.TeleportAction.Position(1,z).WorldPosition.Attributes.h)) ~= 1)
                                                
                                                Struct_pex.Experiment.Actors.Actor{1, j}.Orientation.Attributes.Heading  =(180/pi)*str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}...
                                                    .PrivateAction{1,y}.TeleportAction.Position(1,z).WorldPosition .Attributes.h);
                                            end
                                        end %h field check
                                        
                                    end
                                    
                                    
                                end %main for loop
                            end   %position field check
                        end
                    end
                end
            end
        end
    end
end
end %main function