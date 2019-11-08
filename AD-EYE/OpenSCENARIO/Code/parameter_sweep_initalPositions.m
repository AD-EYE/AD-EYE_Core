%%%%%%%%%%%%%%%%%%%%Storyboard Init Actions Private
%%%%%%%%%%Private Action
function [Struct_pex] = parameter_sweep_initalPositions(Struct_OpenSCENARIO,Struct_pex,k,i)


for j = 1:length(Struct_pex.Experiment.Actors.Actor ) %Declare number of objects in .pei file
    
    
    %Check if j is a car in .pei file
    if ( convertCharsToStrings(Struct_pex.Experiment.Actors.Actor{1, j}.Attributes.id    ) == convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Attributes.object))
        
        if(isfield(convertCharsToStrings(Struct_pex.Experiment.Actors.Actor{1,j}.Attributes)  ,'ObjectTypeID') == 1 )    %if objectTypeID eiists
            
            %Check if j is a car in .pei file
            if (str2double(Struct_pex.Experiment.Actors.Actor{1, j}.Attributes.ObjectTypeID  ) == k)
                
                for y = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Action)
                    
                    
                    %check if is it the position field
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Action{1,y}),'Position') == 1 )
                        
                        for z = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Action{1,y}.Position)
                            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Action{1,y}.Position(1,z)),'World') == 1 )
                                
                                %if i eiists
                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Action{1,y}.Position(1,z).World.Attributes),'x') == 1 )
                                    %Changing i position
                                    if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Action{1,y}.Position(1,z).World.Attributes.x)) ~= 1)
                                        
                                        Struct_pex.Experiment.Actors.Actor{1, j}.Location.Attributes.X = str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}...
                                            .Action{1,y}.Position(1,z).World.Attributes.x);
                                    end
                                    
                                end %i field check
                                
                                %if y eiists
                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Action{1,y}.Position(1,z).World.Attributes),'y') == 1 )
                                    %Changing y position
                                    if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Action{1,y}.Position(1,z).World.Attributes.y)) ~= 1)
                                        
                                        Struct_pex.Experiment.Actors.Actor{1, j}.Location.Attributes.Y = str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}...
                                            .Action{1,y}.Position(1,z).World.Attributes.y);
                                        
                                    end
                                    
                                end %y field check
                                
                                %if z eiistsd
                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Action{1,y}.Position(1,z).World.Attributes),'z') == 1 )
                                    %Changing z position
                                    if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Action{1,y}.Position(1,z).World.Attributes.z)) ~= 1)
                                        
                                        Struct_pex.Experiment.Actors.Actor{1, j}.Location.Attributes.Z = str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}...
                                            .Action{1,y}.Position(1,z).World.Attributes.z);
                                    end
                                    
                                end %z field check
                                
                                %if r eiists
                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Action{1,y}.Position(1,z).World.Attributes),'r') == 1 )
                                    %Changing roll position %ra?
                                    if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Action{1,y}.Position(1,z).World.Attributes.r)) ~= 1)
                                        
                                        Struct_pex.Experiment.Actors.Actor{1, j}.Orientation.Attributes.Bank=  (180/pi)*str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}...
                                            .Action{1,y}.Position(1,z).World.Attributes.r);
                                    end
                                    
                                end %r field check
                                
                                %if p eiists
                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Action{1,y}.Position(1,z).World.Attributes),'p') == 1 )
                                    %Changing pitch position %rad
                                    if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Action{1,y}.Position(1,z).World.Attributes.p)) ~= 1)
                                        
                                        Struct_pex.Experiment.Actors.Actor{1, j}.Orientation.Attributes.Tilt  = (180/pi)*str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}...
                                            .Action{1,y}.Position(1,z).World.Attributes.p) ;
                                    end
                                end %p field check
                                
                                %if h eiists
                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Action{1,y}.Position(1,z).World.Attributes),'h') == 1 )
                                    
                                    %Changing yaw position %rad
                                    if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Action{1,y}.Position(1,z).World.Attributes.h)) ~= 1)
                                        
                                        Struct_pex.Experiment.Actors.Actor{1, j}.Orientation.Attributes.Heading  =(180/pi)*str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}...
                                            .Action{1,y}.Position(1,z).World .Attributes.h);
                                    end
                                end %h field check
                                
                            end
                            
                            
                        end %main forloop
                    end   %position field check
                end
            end
        end
    end
end
end %main function