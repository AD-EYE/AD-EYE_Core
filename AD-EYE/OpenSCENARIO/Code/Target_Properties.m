function [Struct_pex] = Target_Properties(Struct_OpenSCENARIO,Struct_pex)

ERROR = 1;


    %%%%%%%%%%SetEnvironment


    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions),'Global') == 1 )  %if Global exists
        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global),'SetEnvironment') == 1 )  %if SetEnvironment exists
            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment),'TargetProperties') == 1 )  %if TargetProperties exists
                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.TargetProperties),'Lidar') == 1 )  %if Lidar exists

                    %%%Reflection
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.TargetProperties.Lidar),'TargetPropertySettings') == 1 )  %if TargetPropertySettings exists
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.TargetProperties.Lidar.Attributes),'ObjectType') == 1  &&...
                                isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.TargetProperties.Lidar.Attributes),'ReflectionPercentage') == 1)  %if ObjectType

                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.TargetProperties.Lidar.Attributes.ObjectType  )) ~= 1 &&...
                                    isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.TargetProperties.Lidar.Attributes.ReflectionPercentage   )) ~= 1)
                                
                                
                                ERROR = 0;
                                
                                if (strcmp(convertCharsToStrings(Struct_pex.Experiment.PrescanObjectTypeSettings.ObjectProperties.item.key.SensorObjectTuple.Attributes.PrescanObjectType)) == convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.TargetProperties.Lidar.Attributes.ObjectType))
                                    Struct_pex.Experiment.PrescanObjectTypeSettings.ObjectProperties.item.value.double = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.TargetProperties.Lidar.Attributes.ReflectionPercentage;
                                end
                                
                                    
                            end %check if ObjectType and ReflectionPercentage has values
                        end %ObjectType field check
                    end %TargetPropertySettings field check

      
                end %Lidar field check
            end%TargetProperties field check
        end%SetEnvironment field check
    end%Global field check




    if(ERROR == 1)
        disp('No target properties (reflexivity) changed');
    else

        disp('Target properties (reflexivity) changed');
    end



    %%%%%%%%%%Infrastructure



    %%%%%%%%%%Traffic
end
