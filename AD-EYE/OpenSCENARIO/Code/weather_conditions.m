function [models] = weather_conditions(models,Struct_OpenSCENARIO)

ERROR = 1;

if(isfield(models.worldmodel.weather,'fog') ==1 ||isfield(models.worldmodel.weather,'precipitation') ==1 )
%%%%%%%%%%SetEnvironment
%%%Time of day

 if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions),'Global') == 1 )  %if Global exists 
    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global),'SetEnvironment') == 1 )  %if SetEnvironment exists 
        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment),'Environment') == 1 )  %if Environment exists     
            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment),'Weather') == 1 )  %if Weather exists     
    
                %%%weather fog
                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather),'Fog') == 1 )  %if Weather exists    
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Fog.Attributes),'boundingBox') == 1 )  %if boundingBox exists 
        
                        if(isnan(str2double(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Fog.Attributes.boundingBox  )) ~= 1 &&...
                        str2double(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Fog.Attributes.boundingBox) ~=0) 
                    
                        models.worldmodel.weather.fog = prescan.experiment.setFieldValue(...
                        models.worldmodel.weather.fog, 'density', str2double(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Fog.Attributes.boundingBox)  );
                     ERROR = 0;
                        end

                        end%boundingBox field check
                        
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Fog.Attributes),'visualRange') == 1 )  %if visualRange exists                            
                            if(isnan(str2double(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Fog.Attributes.visualRange   )) ~= 1)
                               
                                models.worldmodel.weather.fog = prescan.experiment.setFieldValue(...
                                    models.worldmodel.weather.fog, 'visibility', str2double(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Fog.Attributes.visualRange )  );
                                ERROR = 0;
                            elseif(isnan(str2double(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Fog.Attributes.visualRange   )) ~= 1 &&...
                                    str2double(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Fog.Attributes.visualRange) == 0)
                                
                                models.worldmodel.weather= rmfield(models.worldmodel.weather, 'fog');
                                
                            end                          
                            
                        end%visualRange field check
                end%Fog field check

 
                
                %%%weather sun
                
                %%%weather precipitation
                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather),'Precipitation') == 1 )  %if Precipitation exists
                    
                    %type is a string so different check if it is empty
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes),'type') == 1 )  %if type exists
                        if(strcmp(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes.type )," ")== 0 &&...
                                convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes.type ) ~= 'typeNone')
                            
                            models.worldmodel.weather.precipitation= prescan.experiment.setFieldValue(...
                                models.worldmodel.weather.precipitation, 'subType', Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes.type  );
                             ERROR = 0;
                        end %type field check
                        
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes),'intensity') == 1 )  %if intensity exists                            
                            if(isnan(str2double(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes.intensity )) ~= 1)
                                
                                models.worldmodel.weather.precipitation= prescan.experiment.setFieldValue(...
                                    models.worldmodel.weather.precipitation, 'density', int32(str2double(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes.intensity))  );
                                 ERROR = 0;
                            elseif(isnan(str2double(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes.intensity )) ~= 1 &&...
                                    str2double(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes.intensity) == 0)
                                models.worldmodel.weather= rmfield(models.worldmodel.weather, 'precipitation');
                            end
                            
                        end %intensity field check
                    end%type field check
                    
                    
                end%Precipitation field check
            end%Weather field check
        end%Environment field check
    end%SetEnvironment field check
 end%Global field check
 
end%check if field exists in Prescan
   
    
    
    if(ERROR == 1)
        disp('No weather conditions changed');
    else
        
        disp('Weather conditions changed');
    end
    


%%%%%%%%%%Infrastructure



%%%%%%%%%%Traffic
end