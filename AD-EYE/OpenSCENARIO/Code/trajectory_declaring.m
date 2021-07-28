function [trajectory_variable] = trajectory_declaring(models,Struct_OpenSCENARIO)

trajectory_variable = [];

if(isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard,'Story'))
    for k = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story  ) %Number of Stories

        %check if Entity field exists
        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Actors),'Entity') == 1 )
            %check if Maneuver field exists
            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup),'Maneuver') == 1 )

                for m = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver)%Number of Maneuvers

                    %check if Event field exists
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}),'Event') == 1 )

                        for j =1:length(models.worldmodel.object) %Thrid for loop
                            if(convertCharsToStrings(models.worldmodel.object{j, 1}.name) == convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Actors.EntityRef.Attributes.entityRef))

                                trajectory_variable.(models.worldmodel.object{j, 1}.name).j = j; %declare structure
                                trajectory_variable.(models.worldmodel.object{j, 1}.name).yaw =  models.worldmodel.object{j, 1}.pose.orientation.yaw;

                                for i = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event  ) %Number of events

                                    trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name) = (Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name);



                                    %OSCPrivateAction
                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i }.Action), "PrivateAction" )== 1)
                                        %Check if in Longitudinal field
                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                .Action.PrivateAction),'LongitudinalAction') == 1 )

                                            trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name) = struct('Longitudinal',' ');

                                            %Check if in Speed field
                                            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                    .Action.PrivateAction.LongitudinalAction),'SpeedAction') == 1 )
                                                %Check if in Dynamics field
                                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                        .Action.PrivateAction.LongitudinalAction.SpeedAction),'SpeedActionDynamics') == 1 )

                                                    trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name) = struct('Dynamics',(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}...
                                                        .Act.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Action.PrivateAction.LongitudinalAction.SpeedAction.SpeedActionDynamics.Attributes),'Condition',' ','Longitudinal',' ');

                                                    %Check if in Target field
                                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                            .Action.PrivateAction.LongitudinalAction.SpeedAction),'SpeedActionTarget') == 1 )
                                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                                .Action.Private.Longitudinal.Speed.Target),'AbsoluteTargetSpeed') == 1 )

                                                            trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.Target = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                                .Action.PrivateAction.LongitudinalAction.SpeedAction.SpeedActionTarget.AbsoluteTargetSpeed.Attributes;


                                                        end %Relative field check
                                                    end %Target field check
                                                end  %Dynamics field check

                                            end %Speed field check
                                        end %Longitudinal field check


                                        %Check if in Lateral field
                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                .Action.PrivateAction),'LateralAction') == 1 )
                                            %Check if in LaneChange field
                                            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                    .Action.PrivateAction.LateralAction),'LaneChangeAction') == 1 )
                                                %Check if in Dynamics field
                                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                        .Action.PrivateAction.LateralAction.LaneChangeAction),'LaneChangeActionDynamics') == 1 )

                                                    trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name) = struct('Dynamics',(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}...
                                                        .Act.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Action.PrivateAction.LateralAction.LaneChangeAction.LaneChangeActionDynamics.Attributes),'Condition',' ','Lateral',' ' );

                                                    %Check if in Target field
                                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                            .Action.PrivateAction.LateralAction.LaneChangeAction),'LaneChangeTarget') == 1 )
                                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                                .Action.PrivateAction.Lateralv.LaneChangeAction.LaneChangeTarget),'AbsoluteTargetLane') == 1 )

                                                            trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.Target = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                                .Action.PrivateAction.LateralAction.LaneChangeAction.LaneChangeTarget.AbsoluteTargetLane.Attributes;


                                                        end %Relative field check
                                                    end %Target field check
                                                end %Dynamics field check

                                            end %LaneChange field check
                                        end %Lateral field check

                                        trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                            .Action.Attributes.name) = convertStringsToChars(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i }.Action.Attributes.name);
                                        %adding action structure to compare in Aftertermination

                                    end%Private field check






                                    %Check StartTrigger field
                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}), "StartTrigger") == 1)
                                        %Check ConditionGroup field
                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger), "ConditionGroup") == 1)
                                            %Check Condition field
                                            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup), "Condition") == 1)
                                                %Check Attributes field
                                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition), "Attributes") == 1)

                                                    trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition = struct('Attributes',(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.Attributes),'Rule', ' ', 'Attributes_rule',' ','Object',' ' );

                                                end  %Attributes field check

                                                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%ByEntity
                                                %Check ByEntity field
                                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition), "ByEntityCondition") == 1)
                                                    %%Check TriggeringEntities field
                                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition), "TriggeringEntities") == 1)

                                                        trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Attributes_rule = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.TriggeringEntities.Attributes.TriggeringEntitiesrule;

                                                        trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Objects = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.TriggeringEntities.EntityRef.Attributes.entityRef;

                                                    end %TriggeringEntities field check

                                                    %Check EntityCondition field
                                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition), "EntityCondition") == 1)
                                                        %Check Distance field
                                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.EntityCondition), "RelativeDistanceCondition") == 1)

                                                            %add Condition Rule to Trajectory_variable
                                                            trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.EntityCondition.RelativeDistanceCondition.Attributes;

                                                            %Check RelativeObject field
%                                                             if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
%                                                                     .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.EntityCondition.RelativeDistanceCondition.Position), "RelativeObject") == 1)

                                                                %add Relative distance to Trajectory_variable
                                                                trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Distance_RelativeObject = (Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.EntityCondition.RelativeDistanceCondition.entityRef.Attributes);


                                                            end %RelativeObject field check

                                                        end %Distance field check

                                                        %Check TimeHeadWay field
                                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.EntityCondition), "TimeHeadWayCondition") == 1)

                                                            %add TimeHeadWay to Trajectory_variable
                                                            trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.EntityCondition.TimeHeadWayCondition.Attributes;

                                                            trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.TimeHeadWayCondition = ' ';


                                                        end %TimeHeadWay field check

                                                    end % EntityCondition field check

                                                end %ByEntity field  check

                                                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%ByState
                                                %Check ByState field
                                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition), "ByStateCondition") == 1)
                                                    %Check AfterTermination field
                                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByStateCondition), "StoryboardElementStateCondition") == 1)
                                                        %Check type,name,rule field
                                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByStateCondition.StoryboardElementStateCondition.Attributes), "storyboardElementType") == 1 &&...
                                                                isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByStateCondition.StoryboardElementStateCondition.Attributes), "storyboardElementRef") == 1 &&...
                                                                isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByStateCondition.StoryboardElementStateCondition.Attributes), "state") == 1 )

                                                            for p = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event)

                                                                %Check what StoryboardElementStateCondition says
                                                                if(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByStateCondition.StoryboardElementStateCondition.Attributes.storyboardElementRef) == convertCharsToStrings( trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                                        .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i-1}.Attributes.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i-1 }...
                                                                        .Action.Attributes.name)))

                                                                    trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition = trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, p}.Attributes.name).Condition;

                                                                    trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Aftertermination = ' ';

                                                                end
                                                            end


                                                        end %%Check type,name,rule field check

                                                    end %AfterTermination field check

                                                end %ByState field  check









                                            end %Condition field check
                                        end %ConditionGroup field check
                                    end %Startcondition field  check




                                end% end fourth  for loop
                            end %check object between OpenSCENARIO and Prescan
                        end %end Thrid for loop
                    end %Entity field check
                end%second for loop maneuvers
            end %Maneuver field check
        end %Event field check
    end%end main for loop
end




end %Main function







