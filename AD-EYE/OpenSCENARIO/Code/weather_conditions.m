function [Struct_pex] = weather_conditions(Struct_OpenSCENARIO,Struct_pex)

ERROR = 1;


    %%%%%%%%%%SetEnvironment


    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions),'Global') == 1 )  %if Global exists
        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global),'SetEnvironment') == 1 )  %if SetEnvironment exists
            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment),'Environment') == 1 )  %if Environment exists
                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment),'Weather') == 1 )  %if Weather exists

                    %%%weather fog
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather),'Fog') == 1 )  %if Weather exists
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Fog.Attributes),'boundingBox') == 1  &&...
                                isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Fog.Attributes),'visualRange') == 1)  %if boundingBox exists

                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Fog.Attributes.boundingBox  )) ~= 1 &&...
                                    isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Fog.Attributes.visualRange   )) ~= 1)
                                if( str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Fog.Attributes.boundingBox) ~=0 )

                                Struct_pex.Experiment.WeatherFogSettings.Attributes.Enabled = convertStringsToChars("true");
                                 Struct_pex.Experiment.WeatherFogSettings.CurrentFogConfiguration.Attributes.Density  = str2double(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Fog.Attributes.boundingBox) ;
                                 Struct_pex.Experiment.WeatherFogSettings.CurrentFogConfiguration.Attributes.End= str2double(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Fog.Attributes.visualRange );
                                ERROR = 0;

                                end%if bondingbox is not 0, turn fog on
                            end %check if boundingbox and visualrange has values
                        end%boundingBox and visualrange field check
                    end%Fog field check



                    %%%weather precipitation
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather),'Precipitation') == 1 )  %if Precipitation exists
                        %type is a string so different check if it is empty
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes),'type') == 1 )  %if type exists
                            if(strcmp(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes.type )," ")== 0 &&...
                                    convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes.type ) ~= 'typeNone')

                                if(convertCharsToStrings( Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes.type) == "typeRain")

                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes),'intensity') == 1 )  %if intensity exists
                                        if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes.intensity )) ~= 1)

                                            Struct_pex.Experiment.Attributes.WeatherTypeName =convertStringsToChars("Rain");
                                            % Calculating rain density according to the Prescan Manual (p.497 ?Rain density)
                                            R  = str2double(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes.intensity);
                                            % Values other than rho comes from moderate frain from the Prescan Manual
% Causing Prescan to crash
%                                             vp = 4.20;
%                                             Dp = 1.06 * 10^-3;
%                                             rho = (6*R) / (vp * pi() * (Dp^3));
%                                             %       These values can also be set according the Table 3 depending on R
%                                             % Assigning values
%                                             Struct_pex.Experiment.WeatherRainSettings.CurrentRainConfiguration.Direction.Attributes.Z = vp;
%                                             Struct_pex.Experiment.WeatherRainSettings.CurrentRainConfiguration.Attributes.PSize = Dp*10^3;
%                                             Struct_pex.Experiment.WeatherRainSettings.CurrentRainConfiguration.Attributes.Density = rho;
                                            ERROR = 0;
                                        end
                                    end %intensity field check

                                elseif(convertCharsToStrings( Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes.type) == "typeSnow")

                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes),'intensity') == 1 )  %if intensity exists
                                        if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes.intensity )) ~= 1)

                                            Struct_pex.Experiment.Attributes.WeatherTypeName =convertStringsToChars("Snow");
                                           Struct_pex.Experiment.WeatherSnowSettings.CurrentSnowConfiguration.Attributes.Density  = str2double(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes.intensity);
                                            ERROR = 0;
                                        end
                                    end %intensity field check



                                end %type field check
                            end%type field check
                        end%Precipitation field check

                            %}
                    end%Weather field check
                end%Environment field check
            end%SetEnvironment field check
        end%Global field check




    if(ERROR == 1)
        disp('No weather conditions changed');
    else

        disp('Weather conditions changed');
    end



    %%%%%%%%%%Infrastructure



    %%%%%%%%%%Traffic
end
