function [velocityVariable] =initialvelocitydeclaring(models,Struct_OpenSCENARIO)


for j =1:length(models.worldmodel.object) %main for loop
    
            if(field_exists(Struct_OpenSCENARIO, "Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private"))  %if Private exists               
                
                for k = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private) %for each private
                    if("Ego" ~= convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Attributes.entityRef))
                        velocityVariable(k,1) = convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Attributes.entityRef);                    
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}),'PrivateAction') == 1 )  %if Action exists                        
                            for p = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.PrivateAction) %for each Action

                                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Longitudinal

                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.PrivateAction{1,p}),'LongitudinalAction') == 1 )  %if Speed exists
                                    velocityVariable(k,2) = "Longitudinal";
                                    if(field_exists(Struct_OpenSCENARIO, "Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.PrivateAction{1,p}.LongitudinalAction.SpeedAction.SpeedActionDynamics.Attributes.dynamicsShape"))
                                        
                                        velocityVariable(k,3) = convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.PrivateAction{1,p}.LongitudinalAction.SpeedAction.SpeedActionDynamics.Attributes.dynamicsShape);

                                    end%check shape

                                    if(field_exists(Struct_OpenSCENARIO,"Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.PrivateAction{1,p}.LongitudinalAction.SpeedAction.SpeedActionTarget.AbsoluteTargetSpeed"))

                                            velocityVariable(k,4) = str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.PrivateAction{1,p}.LongitudinalAction.SpeedAction.SpeedActionTarget.AbsoluteTargetSpeed.Attributes.value);
                                            velocityVariable(k,5) = "Absolute";

                                     end %check Absolute

                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.PrivateAction{1,p}.LongitudinalAction.SpeedAction.SpeedActionTarget),'RelativeTargetSpeed') == 1 )  %if Absolute exists

                                        velocityVariable(k,4) = str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.PrivateAction{1,p}.LongitudinalAction.SpeedAction.SpeedActionTarget.RelativeTargetSpeed.Attributes.value);
                                        velocityVariable(k,5) = "Relative";

                                    end %check Relative
                                end %check Longitudinal


                            end %end third for loop

                        end %check Action
                        
                     
                    end %end if not ego
                end %end second for loop, private
                
                
            end %check Private
    
end %main for loop, number of objects in Prescan

end%end of function
