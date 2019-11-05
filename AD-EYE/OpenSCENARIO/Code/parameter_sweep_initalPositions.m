%%%%%%%%%%%%%%%%%%%%Storyboard Init Actions Private
%%%%%%%%%%Private Action
function [models] = parameter_sweep_initalPositions(models,Struct_OpenSCENARIO,j )

for x = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private)
    %checking if initial condition belongs to the same object
    if(convertCharsToStrings(models.worldmodel.object{j, 1}.name) == convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Attributes.object))
        
        for y = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action)
            %check if is it the position field
            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}),'Position') == 1 )                
                
                for z = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}.Position)
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}.Position(1,z)),'World') == 1 )
                        
                        %if x exists
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}.Position(1,z).World.Attributes),'x') == 1 )
                            %Changing x position
                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}.Position(1,z).World.Attributes.x)) ~= 1)
                                models.worldmodel.object{j, 1}.pose.position = prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.pose.position,'x' ,str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}...
                                    .Action{1,y}.Position(1,z).World.Attributes.x) );
                            end
                            
                        end %x field check
                        
                        %if y exists
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}.Position(1,z).World.Attributes),'y') == 1 )
                            %Changing y position
                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}.Position(1,z).World.Attributes.y)) ~= 1)
                                models.worldmodel.object{j, 1}.pose.position = prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.pose.position,'y' ,str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}...
                                    .Action{1,y}.Position(1,z).World.Attributes.y) );
                            end
                            
                        end %y field check
                        
                        %if z exists
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}.Position(1,z).World.Attributes),'z') == 1 )
                            %Changing z position
                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}.Position(1,z).World.Attributes.z)) ~= 1)
                                models.worldmodel.object{j, 1}.pose.position = prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.pose.position,'z' ,str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}...
                                    .Action{1,y}.Position(1,z).World.Attributes.z) );
                            end
                            
                        end %z field check
                        
                        %if r exists
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}.Position(1,z).World.Attributes),'r') == 1 )
                            %Changing roll position %ra?
                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}.Position(1,z).World.Attributes.r)) ~= 1)
                                models.worldmodel.object{j, 1}.pose.orientation = prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.pose.orientation,'roll' ,str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}...
                                    .Action{1,y}.Position(1,z).World.Attributes.r) );
                            end
                            
                        end %r field check
                        
                        %if p exists
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}.Position(1,z).World.Attributes),'p') == 1 )
                            %Changing pitch position %rad
                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}.Position(1,z).World.Attributes.p)) ~= 1)
                                models.worldmodel.object{j, 1}.pose.orientation = prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.pose.orientation,'pitch' ,str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}...
                                    .Action{1,y}.Position(1,z).World.Attributes.p) );
                            end
                        end %p field check
                        
                        %if h exists
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}.Position(1,z).World.Attributes),'h') == 1 )
                            
                            %Changing yaw position %rad
                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}.Position(1,z).World.Attributes.h)) ~= 1)
                                models.worldmodel.object{j, 1}.pose.orientation = prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.pose.orientation,'yaw' ,str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}...
                                    .Action{1,y}.Position(1,z).World .Attributes.h) );
                            end
                        end %h field check
                        
                    end
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}.Position(1,z)),'RelativeLane') == 1 )
                        
                    end
                    
                    
                end
            end
            
            
            %check if is it the Longitudinal field
            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}),'Longitudinal'))
                
                for z = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}.Longitudinal)
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}.Longitudinal(1,z)),'World') == 1 )
                        
                        
                    end
                    
                end
                
            end
            
            
            
            %check if is it the Lateral field
            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}),'Lateral'))
                
                for z = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}.Lateral)
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}.Lateral(1,z)),'World') == 1 )
                        
                        
                    end
                    
                end
                
            end
            
            
            
        end
    end
end