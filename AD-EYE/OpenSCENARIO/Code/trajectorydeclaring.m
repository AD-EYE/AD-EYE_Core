function [trajectoryVariable] = trajectorydeclaring(models,Struct_OpenSCENARIO)

trajectoryVariable = [];

if(isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard,'Story'))
    for k = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story  ) %Number of Stories
        for a= 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act) %Number of Acts

            %check if Entity field exists
            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Actors),'EntityRef') == 1 )
                %check if Maneuver field exists
                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup),'Maneuver') == 1 )

                    for m = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Maneuver)%Number of Maneuvers

                        %check if Event field exists
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Maneuver{1,m}),'Event') == 1 )

                            for j =1:length(models.worldmodel.object) %Third for loop
                                if(convertCharsToStrings(models.worldmodel.object{j, 1}.name) == convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Actors.EntityRef.Attributes.entityRef))

                                    trajectoryVariable.(models.worldmodel.object{j, 1}.name).j = j; %declare structure
                                    trajectoryVariable.(models.worldmodel.object{j, 1}.name).yaw =  models.worldmodel.object{j, 1}.pose.orientation.yaw;

                                    for i = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event  ) %Number of Events

                                        trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name) = (Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name);

                                        for l = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private) %for each Private
                                            if strcmp((models.worldmodel.object{j, 1}.name),Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, l}.Attributes.entityRef)
                                                for p = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.PrivateAction) %for each Action
                                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, l}.PrivateAction{1,p}),'LongitudinalAction') == 1)
                                                        trajectoryVariable.(models.worldmodel.object{j, 1}.name).init = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, l}.PrivateAction{1,p}.LongitudinalAction.SpeedAction.SpeedActionTarget.AbsoluteTargetSpeed.Attributes.value;
                                                    elseif (isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, l}.PrivateAction{1,p}),'LateralAction') == 1 )
                                                        trajectoryVariable.(models.worldmodel.object{j, 1}.name).init = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, l}.PrivateAction{1,p}.LateralAction.SpeedAction.SpeedActionTarget.AbsoluteTargetSpeed.Attributes.value;
                                                    end
                                                end
                                            end
                                        end


                                        %OSCPrivateAction
                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i }.Action), "PrivateAction" )== 1)
                                            %Check if in Longitudinal field
                                            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                    .Action.PrivateAction),'LongitudinalAction') == 1 )

                                                trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name) = struct('Longitudinal',' ');

                                                %Check if in
                                                %LongitudinalDistanceAction
                                                %field
                                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                        .Action.PrivateAction.LongitudinalAction),'LongitudinalDistanceAction') == 1 )

                                                        trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name) = struct('Distance',(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}...
                                                            .Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Action.PrivateAction.LongitudinalAction.LongitudinalDistanceAction.Attributes.continuous));
                                                end

                                                %Check if in Dynamics field
                                                if(field_exists(Struct_OpenSCENARIO, "Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Action.PrivateAction.LongitudinalAction.SpeedAction.SpeedActionDynamics" ))
                                                    trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name) = struct('Dynamics',(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}...
                                                            .Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Action.PrivateAction.LongitudinalAction.SpeedAction.SpeedActionDynamics.Attributes),'Condition',' ','Longitudinal',' ');

                                                    %Check if in Relative field
                                                    if(field_exists(Struct_OpenSCENARIO, "Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Action.PrivateAction.LongitudinalAction.SpeedAction.SpeedActionTarget.RelativeTargetSpeed"))
                                                        trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.Target = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                                .Action.PrivateAction.LongitudinalAction.SpeedAction.SpeedActionTarget.RelativeTargetSpeed.Attributes;


                                                    end %Relative field check
                                                    %Check if in Absolute field        
                                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                                    .Action.PrivateAction.LongitudinalAction.SpeedAction.SpeedActionTarget),'AbsoluteTargetSpeed') == 1 )

                                                        trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.Target = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                            .Action.PrivateAction.LongitudinalAction.SpeedAction.SpeedActionTarget.AbsoluteTargetSpeed.Attributes;
                                                    end %Absolute field check

                                                end %Dynamics field check
                                            end %Longitudinal field check


                                            %Check if in LaneChangeActionDynamics field
                                            if(field_exists(Struct_OpenSCENARIO, strcat("Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1," , num2str(k), "}.Act{1," , num2str(a), "}.ManeuverGroup.Maneuver{1," , num2str(m), "}.Event{1, " , num2str(i), "}.Action.PrivateAction.LateralAction.LaneChangeAction.LaneChangeActionDynamics")))
                                                
                                                trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name) = struct('Dynamics',(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}...
                                                            .Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Action.PrivateAction.LateralAction.LaneChangeAction.LaneChangeActionDynamics.Attributes),'Condition',' ','Lateral',' ' );

                                                %Check if in AbsoluteTarget field
                                                if(field_exists(Struct_OpenSCENARIO, "Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Action.PrivateAction.LateralAction.LaneChangeAction.LaneChangeTarget.AbsoluteTargetLane"))
                                                    trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.Target = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                            .Action.PrivateAction.LateralAction.LaneChangeAction.LaneChangeTarget.AbsoluteTargetLane.Attributes;

                                                end %Target AbsoluteTarget check
                                            end %LaneChangeActionDynamics field check

                                            trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                .Action.Attributes.name) = convertStringsToChars(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i }.Action.Attributes.name);
                                            %Adding action structure to compare in Aftertermination

                                        end%Private field check






                                        %Check StartTrigger field
                                        if(field_exists(Struct_OpenSCENARIO, "Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition"))
                                            %Check Attributes field
                                            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition), "Attributes") == 1)

                                                trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition = struct('Attributes',(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.Attributes),'Rule', ' ', 'Attributes_rule',' ','Object',' ' );

                                            end  %Attributes field check

                                                    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%ByEntity
                                            %Check ByEntity field
                                            if(field_exists(Struct_OpenSCENARIO, "Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.TriggeringEntities"))
                                                trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Attributes_rule = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.TriggeringEntities.Attributes.triggeringEntitiesRule;

                                                trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Objects = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.TriggeringEntities.EntityRef.Attributes.entityRef;

                                                %Check EntityCondition and RelativeDistanceAction field
                                                if(field_exists(Struct_OpenSCENARIO, "Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.EntityCondition.RelativeDistanceCondition"))

                                                    %add Condition Rule to trajectoryVariable
                                                    trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.EntityCondition.RelativeDistanceCondition.Attributes;

                                                        %Check RelativeObject field
                                                         %if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                                % .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.EntityCondition.RelativeDistanceCondition.Position), "RelativeObjectPosition") == 1)

                                                    %add Relative distance to trajectoryVariable
                                                    trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Distance_RelativeObject = (Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.EntityCondition.RelativeDistanceCondition.Attributes.entityRef);


                                                       %end %RelativeObject field check

                                                end %RelativeDistanceAction field check

                                                if (isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.EntityCondition), "SpeedCondition") == 1)

                                                    trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.EntityCondition.SpeedCondition.Attributes;

                                                    %add Relative distance to trajectoryVariable
                                                    trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                           .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Speed_RelativeObject = (Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                           .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.TriggeringEntities.EntityRef.Attributes.entityRef);
                                                end

                                                    %Check TimeHeadWay field
                                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.EntityCondition), "TimeHeadWayCondition") == 1)

                                                    %add TimeHeadWay to trajectoryVariable
                                                    trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.EntityCondition.TimeHeadWayCondition.Attributes;

                                                    trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.TimeHeadWayCondition = ' ';


                                                end %TimeHeadWay field check

                                            end %ByEntity field  check

                                                    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%ByState
                                            %Check ByState and
                                            %AfterTerminaison fields
                                            if(field_exists(Struct_OpenSCENARIO, "Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByValueCondition.StoryboardElementStateCondition"))
                                                %Check type,name,rule field
                                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByValueCondition.StoryboardElementStateCondition.Attributes), "storyboardElementType") == 1 &&...
                                                    isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByValueCondition.StoryboardElementStateCondition.Attributes), "storyboardElementRef") == 1 &&...
                                                    isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByValueCondition.StoryboardElementStateCondition.Attributes), "state") == 1 )

                                                    for p = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event)

                                                        %Check what StoryboardElementStateCondition says
                                                        if(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByValueCondition.StoryboardElementStateCondition.Attributes.storyboardElementRef) == convertCharsToStrings( trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                                .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i-1}.Attributes.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i-1 }...
                                                                .Action.Attributes.name)))

                                                            trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition = trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, p}.Attributes.name).Condition;

                                                            trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Aftertermination = ' ';

                                                        end
                                                    end


                                                end %Check type,name,rule field check

                                                %Check
                                                %SimulationTimeCondition
                                                %field
                                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByValueCondition), "SimulationTimeCondition") == 1)

                                                    trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Objects = trajectoryVariable.(models.worldmodel.object{j, 1}.name);

                                                    %Check rule, value
                                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByValueCondition.SimulationTimeCondition.Attributes), "rule") == 1 &&...
                                                            isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByValueCondition.SimulationTimeCondition.Attributes), "value") == 1)

                                                        trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByValueCondition.SimulationTimeCondition.Attributes;

                                                        trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.SimulationTimeCondition = ' ';


                                                    end %%Check rule,value

                                                end %SimulationTimeCondition field check



                                            end %ByState field  check
                                        end %Startcondition field  check
                                    end% end fourth  for loop
                                end %check object between OpenSCENARIO and Prescan
                            end %end Thrid for loop
                        end %Entity field check
                    end%second for loop maneuvers
                end %Maneuver field check
            end %Event field check
        end %Act loop
    end%end main for loop
end



end %Main function







