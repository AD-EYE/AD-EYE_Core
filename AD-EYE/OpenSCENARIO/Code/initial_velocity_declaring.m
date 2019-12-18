function [Velocity_variable] =initial_velocity_declaring(models,Struct_OpenSCENARIO)


for j =1:length(models.worldmodel.object) %main for loop
    
    
    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard),'Init') == 1 )  %if Init exists
        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init),'Actions') == 1 )  %if Actions exists
            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions),'Private') == 1 )  %if Private exists               
                
                for k = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private) %for each private
                    Velocity_variable(k,1) = convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Attributes.object);                    
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}),'Action') == 1 )  %if Action exists                        
                        for p = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Action) %for each Action
                            
                            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Longitudinal
                            
                            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Action{1,p}),'Longitudinal') == 1 )  %if Speed exists
                                Velocity_variable(k,2) = "Longitudinal";
                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Action{1,p}.Longitudinal),'Speed') == 1 )  %if Longitudinal exists
                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Action{1,p}.Longitudinal.Speed),'Dynamics') == 1 )  %if Longitudinal exists
                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Action{1,p}.Longitudinal.Speed.Dynamics.Attributes),'shape') == 1 )  %if Longitudinal exists
                                            
                                            Velocity_variable(k,3) = convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Action{1,p}.Longitudinal.Speed.Dynamics.Attributes.shape);
                                            
                                        end%check snape
                                    end %check Dynamics
                                    
                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Action{1,p}.Longitudinal.Speed),'Target') == 1 )  %if Longitudinal exists
                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Action{1,p}.Longitudinal.Speed.Target),'Absolute') == 1 )  %if Absolute exists
                                            
                                            Velocity_variable(k,4) = str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Action{1,p}.Longitudinal.Speed.Target.Absolute.Attributes.value);
                                            Velocity_variable(k,5) = "Absolute";
                                            
                                        end %check Absolute
                                        
                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Action{1,p}.Longitudinal.Speed.Target),'Relative') == 1 )  %if Absolute exists
                                            
                                            Velocity_variable(k,4) = str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Action{1,p}.Longitudinal.Speed.Target.Relative.Attributes.value);
                                            Velocity_variable(k,5) = "Relative";
                                            
                                        end %check Relative
                                    end %check Target
                                    
                                end %check Speed
                            end %check Longitudinal
                            
                            
                        end %end third for loop
                        
                    end %check Action
                end %end second for loop, private
                
                
            end %check Private
        end %check Actions
    end %check Init
    
end %main for loop, number of objects in Prescan

end%end of function
