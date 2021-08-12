function [trajectory_variable] = trajectory_declaring(models,Struct_OpenSCENARIO)

trajectory_variable = [];

if(isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard,'Story'))
    for k = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story  ) %Number of Stories

        %check if Entity field exists
        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Actors),'EntityRef') == 1 )
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
                                    
                                    for l = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private) %for each private
                                        if strcmp((models.worldmodel.object{j, 1}.name),Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, l}.Attributes.entityRef)
                                            for p = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.PrivateAction) %for each Action
                                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, l}.PrivateAction{1,p}),'LongitudinalAction') == 1)
                                                    trajectory_variable.(models.worldmodel.object{j, 1}.name).init = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, l}.PrivateAction{1,p}.LongitudinalAction.SpeedAction.SpeedActionTarget.AbsoluteTargetSpeed.Attributes.value;
                                                elseif (isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, l}.PrivateAction{1,p}),'LateralAction') == 1 )
                                                    trajectory_variable.(models.worldmodel.object{j, 1}.name).init = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, l}.PrivateAction{1,p}.LateralAction.SpeedAction.SpeedActionTarget.AbsoluteTargetSpeed.Attributes.value;
                                                end
                                            end
                                        end
                                    end
                                    

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
%                                                     
%                                                      d=1;
%                                                     %acceleration = get_field(Struct_OpenSCENARIO, strcat("Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,",num2str(k),"}.Act.ManeuverGroup.Maneuver{1,",num2str(m),"}.Event{1,",num2str(i),"}.Action.PrivateAction.LongitudinalAction.SpeedAction.SpeedActionDynamics.Attributes.value"));
%                                                         %Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.PrivateAction{1,1}.LongitudinalAction.SpeedAction.SpeedActionTarget.AbsoluteTargetSpeed.Attributes.value
%                                                         acceleration=Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Action.PrivateAction.LongitudinalAction.SpeedAction.SpeedActionDynamics.Attributes.value;
%                                                         if(contains(acceleration, '{'))
%                                                             findOpen = strfind(acceleration, ',');
%                                                             start_val = extractBetween(acceleration, 2, findOpen(1)-1);
%                                                             step = extractBetween(acceleration, findOpen(1)+1, findOpen(2)-1);
%                                                             end_val = extractBetween(acceleration, findOpen(2)+1, strlength(acceleration)-1);
%                                                             trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
%                                                             .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.value = cell(1,((str2num(end_val{1,1})-str2num(start_val{1,1}))/str2num(step{1,1}))+1);
%                                                             for b=str2num(start_val{1,1}):str2num(step{1,1}):str2num(end_val{1,1})
%                                                                 trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
%                                                                 .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.value{1, d} = b;
%                                                                 d=d+1;
%                                                             end
%                                                         end

                                                    %Check if in Target field
                                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                            .Action.PrivateAction.LongitudinalAction.SpeedAction),'SpeedActionTarget') == 1 )
                                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                                .Action.PrivateAction.LongitudinalAction.SpeedAction.SpeedActionTarget),'RelativeTargetSpeed') == 1 )

                                                            trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.Target = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                                .Action.PrivateAction.LongitudinalAction.SpeedAction.SpeedActionTarget.RelativeTargetSpeed.Attributes;


                                                        end %Relative field check
                                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                                .Action.PrivateAction.LongitudinalAction.SpeedAction.SpeedActionTarget),'AbsoluteTargetSpeed') == 1 )

                                                            trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.Target = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i }...
                                                                .Action.PrivateAction.LongitudinalAction.SpeedAction.SpeedActionTarget.AbsoluteTargetSpeed.Attributes;
                                                        end %Absolute field check
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
                                                                .Action.PrivateAction.LateralAction.LaneChangeAction.LaneChangeTarget),'AbsoluteTargetLane') == 1 )

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
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.TriggeringEntities.Attributes.triggeringEntitiesRule;

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
                                                             %if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                    % .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.EntityCondition.RelativeDistanceCondition.Position), "RelativeObjectPosition") == 1)

                                                                %add Relative distance to Trajectory_variable
                                                                trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Distance_RelativeObject = (Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.EntityCondition.RelativeDistanceCondition.Attributes.entityRef);


                                                           %end %RelativeObject field check

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
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition), "ByValueCondition") == 1)
                                                    %Check AfterTermination field
                                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByValueCondition), "StoryboardElementStateCondition") == 1)
                                                        %Check type,name,rule field
                                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByValueCondition.StoryboardElementStateCondition.Attributes), "storyboardElementType") == 1 &&...
                                                                isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByValueCondition.StoryboardElementStateCondition.Attributes), "storyboardElementRef") == 1 &&...
                                                                isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByValueCondition.StoryboardElementStateCondition.Attributes), "state") == 1 )

                                                            for p = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event)

                                                                %Check what StoryboardElementStateCondition says
                                                                if(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByValueCondition.StoryboardElementStateCondition.Attributes.storyboardElementRef) == convertCharsToStrings( trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                                        .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i-1}.Attributes.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,m}.Event{1, i-1 }...
                                                                        .Action.Attributes.name)))

                                                                    trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition = trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, p}.Attributes.name).Condition;

                                                                    trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Aftertermination = ' ';

                                                                end
                                                            end


                                                        end %Check type,name,rule field check

                                                    end %Afterterminaison field check
                                                    
                                                    %Check
                                                    %SimulationTimeCondition
                                                    %field
                                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByValueCondition), "SimulationTimeCondition") == 1)
                                                        
                                                        trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Objects = trajectory_variable.(models.worldmodel.object{j, 1}.name);
                                                        
                                                        %Check rule, value
                                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByValueCondition.SimulationTimeCondition.Attributes), "rule") == 1 &&...
                                                                isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByValueCondition.SimulationTimeCondition.Attributes), "value") == 1)

                                                            trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule = Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByValueCondition.SimulationTimeCondition.Attributes;
                                                            
                                                            trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.SimulationTimeCondition = ' ';
                                                                   

                                                        end %%Check rule,value

                                                    end %SimulationTimeCondition field check



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







