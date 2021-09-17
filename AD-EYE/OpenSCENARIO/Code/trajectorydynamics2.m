function  trajectorydynamics2(nameSimulink,models,Struct_OpenSCENARIO,trajectoryVariable,LateralEvents,LongitudinalEvents,nameEgo)

actorsAct=cell(0,1);
for j = 1:length(models.worldmodel.object)
    
    trajectoryType = ["Longitudinal","Lateral"];
    for z = 1:length(trajectoryType)
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        p = 0;
        if(isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard,'Story'))
            for q = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story  ) %Number of Stories
                for a= 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act) %Number of acts

                    % check if a trajectory variable exists
                    if( exist('trajectoryVariable','var') == 1)
                        % check if an object in trajectory variable exists
                        if(isfield(convertCharsToStrings(trajectoryVariable),convertCharsToStrings(models.worldmodel.object{j, 1}.name)) == 1 )
                            % check which story belongs to which car
                            if(convertCharsToStrings(models.worldmodel.object{j, 1}.name)== convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1, q}.Act{1,a}.ManeuverGroup.Actors.EntityRef.Attributes.entityRef))
                                for m = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver)%Number of Maneuvers
                                    for i=1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event)
                                        if(isfield(convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name)), convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name))== 1 )
                                            % check if it is a lateral trajectory
                                            if(isfield(convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name)),trajectoryType(1,z) ) == 1 )
                                                % check if Object structure exists
                                                if(isfield(convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition),"Objects") == 1 )
                                                    % check if a Condition structure exists
                                                    if(isfield(convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition),"Distance_RelativeObject") == 1  || isfield(convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition),"TimeHeadWay") == 1 || isfield(convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition),"SimulationTimeCondition") == 1  || isfield(convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition),"Speed_RelativeObject") == 1)


                                                        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Adding blocks
                                                        % number of events (trajectories)
                                                        p = p+1;
                                                        
                                                        %%%%%%%%%%%%%%%%%%%% Check if another Act was already with this actor
                                                        if isempty(find(ismember(actorsAct, Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Actors.EntityRef.Attributes.entityRef)))
                                                            actorsAct{length(actorsAct)+1,1}=Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Actors.EntityRef.Attributes.entityRef;
                                                            actor=find(ismember(actorsAct, Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Actors.EntityRef.Attributes.entityRef));
                                                        else
                                                            actor=find(ismember(actorsAct, Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Actors.EntityRef.Attributes.entityRef));
                                                            if (a~=actor)
                                                                LateralEvents(a)=LateralEvents(actor)+LateralEvents(a);
                                                                LongitudinalEvents(a)=LongitudinalEvents(actor)+LongitudinalEvents(a);
                                                                if (trajectoryType(1,z) =="Longitudinal")
                                                                    p=LongitudinalEvents(actor)+1;
                                                                else
                                                                    p=LateralEvents(actor)+1;
                                                                end
                                                            end
                                                        end
                                                        %%%%%%%%%%%%%%%%%%%%%%%%%%%%Subsystem in Dynamics_Empty
                                                        blockId = string(1:length(models.worldmodel.object));
                                                        locationDynamicsEmpty = strcat(nameSimulink,convertCharsToStrings(models.worldmodel.object{j,1}.name),"/Dynamics_Empty/");
                                                        blockTrajectoryDynamics = strcat(trajectoryType(1,z) ,"_Dynamics");
                                                        locationBlockTrajectoryDynamics = convertStringsToChars(strcat(locationDynamicsEmpty,blockTrajectoryDynamics));
                                                                                                                
                                                        if(trajectoryType(1,z) =="Lateral")
                                                            nbTrajectoryTypeAction = LateralEvents;
                                                        elseif(trajectoryType(1,z) =="Longitudinal")
                                                            nbTrajectoryTypeAction = LongitudinalEvents;
                                                        end
                                                        
                                                        if (getSimulinkBlockHandle(locationBlockTrajectoryDynamics) == -1)
                                                            add_block(convertStringsToChars(strcat("OpenSCENARIO/",blockTrajectoryDynamics)),locationBlockTrajectoryDynamics );
                                                            % change location of condition source
                                                            size_blk = get_param(convertStringsToChars(strcat(locationDynamicsEmpty,"MuxState")),'Position');
                                                            if(trajectoryType(1,z) =="Lateral")
                                                                X = size_blk(1,1)-270;
                                                                Y = size_blk(1,2)+160;
                                                            elseif(trajectoryType(1,z) =="Longitudinal")
                                                                X = size_blk(1,1)-540;
                                                                Y = size_blk(1,2)+35;
                                                                set_param(convertStringsToChars(strcat(locationBlockTrajectoryDynamics,"/Goto")),'GotoTag',strcat("V0","_",num2str(actor)) );
                                                            end
                                                            WIDTH = 200;
                                                            HEIGHT = 100;
                                                            set_param(locationBlockTrajectoryDynamics,'Position',[X Y X+WIDTH Y+HEIGHT]);
                                                            set_param(locationBlockTrajectoryDynamics,'LinkStatus','inactive')
                                                        end


                                                        locationTrajectoryDynamics = strcat(nameSimulink,convertCharsToStrings(models.worldmodel.object{j,1}.name),"/Dynamics_Empty/",blockTrajectoryDynamics,"/");
                                                        shift1 = -250*(p-1);

                                                        % change the size of the Add block
                                                        blockAdd = "Add";
                                                        locationBlockAdd =convertStringsToChars(strcat(locationTrajectoryDynamics,blockAdd));
                                                        if(trajectoryType(1,z) =="Lateral")
                                                            set_param(locationBlockAdd,'Inputs',int2str(nbTrajectoryTypeAction(1,a)))
                                                        elseif(trajectoryType(1,z) =="Longitudinal")
                                                            set_param(locationBlockAdd,'Inputs',int2str(nbTrajectoryTypeAction(1,a)+1))
                                                        end



                                                        % create condition_source_time
                                                        if( isfield(trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                                .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition, 'TimeHeadWayCondition') == 1)
                                                            %add block condition source
                                                            blockConditionSource = strcat("Condition_source_time_",trajectoryType(1,z) );
                                                            locationBlockConditionSource =convertStringsToChars(strcat(locationTrajectoryDynamics,blockConditionSource));
                                                            add_condition = 1;
                                                            % check if Longitudinal_dynamics exisits, otherwise do not create Condition_source
                                                        elseif ( isfield(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition, 'Distance_RelativeObject') == 1 || isfield(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition, 'SimulationTimeCondition') == 1)
                                                            % add block condition source
                                                            blockConditionSource = strcat("Condition_source_",trajectoryType(1,z) );
                                                            locationBlockConditionSource =convertStringsToChars(strcat(locationTrajectoryDynamics,blockConditionSource));
                                                            add_condition = 1;
                                                        else
                                                            blockConditionSource = " ";
                                                            locationBlockConditionSource =convertStringsToChars(strcat(locationTrajectoryDynamics,blockConditionSource));
                                                            add_condition = 0;
                                                        end
                                                        if (getSimulinkBlockHandle(locationBlockConditionSource) == -1 && add_condition == 1)
                                                            % add condition source
                                                            add_block(convertCharsToStrings(strcat("OpenSCENARIO/",blockConditionSource)),locationBlockConditionSource)
                                                            % change location of condition source
                                                            size_blk = get_param(locationBlockAdd,'Position');
                                                            X = size_blk(1,1)+500+shift1;
                                                            Y = size_blk(1,2)-300;
                                                            WIDTH = 70;
                                                            HEIGHT =90;
                                                            set_param(locationBlockConditionSource,'Position',[X Y X+WIDTH Y+HEIGHT]);
                                                            % disable link to library
                                                            set_param(locationBlockConditionSource, 'LinkStatus','inactive');
                                                            set_param(convertStringsToChars(strcat(locationTrajectoryDynamics,blockConditionSource,"/Goto4")),'TagVisibility','global');
                                                        end


                                                        if (trajectoryType(1,z) =="Longitudinal" && (isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1, q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Action.PrivateAction.LongitudinalAction), 'LongitudinalDistanceAction')==1 ) && Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}...
                                                            .Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Action.PrivateAction.LongitudinalAction.LongitudinalDistanceAction.Attributes.continuous == "true")
                                                            blockTrajectory = "distance";
                                                            blockTrajectory = strcat("Trajectory_input_",blockTrajectory,"_subsystem");
                                                            locationBlockTrajectory =convertStringsToChars(strcat(locationTrajectoryDynamics,blockTrajectory,blockId(1,p)));
                                                            add_condition = 1;
                                                        elseif (convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.dynamicsShape) == "sinusoidal" && abs(str2num(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.Target.value)) > 4)
                                                            blockTrajectory = "turn";
                                                            blockTrajectory = strcat("Trajectory_input_",blockTrajectory,"_subsystem");
                                                            locationBlockTrajectory =convertStringsToChars(strcat(locationTrajectoryDynamics,blockTrajectory,blockId(1,p)));
                                                            add_condition = 1;
                                                        elseif(convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.dynamicsShape) == "sinusoidal")
                                                            % add block Trajectory
                                                            blockTrajectory = "sinusoidal";
                                                            blockTrajectory = strcat("Trajectory_input_",blockTrajectory,"_subsystem");
                                                            locationBlockTrajectory =convertStringsToChars(strcat(locationTrajectoryDynamics,blockTrajectory,blockId(1,p)));
                                                            add_condition = 1;
                                                            % add block for linear outputs
                                                        elseif(convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.dynamicsShape) == "linear")
                                                            blockTrajectory = "linear";
                                                            blockTrajectory = strcat("Trajectory_input_",blockTrajectory,"_subsystem");
                                                            locationBlockTrajectory =convertStringsToChars(strcat(locationTrajectoryDynamics,blockTrajectory,blockId(1,p)));
                                                            add_condition = 1;
                                                            % add block for step outputs
                                                        elseif(convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.dynamicsShape) == "step")
                                                            blockTrajectory = "step";
                                                            blockTrajectory = strcat("Trajectory_input_",blockTrajectory,"_subsystem");
                                                            locationBlockTrajectory =convertStringsToChars(strcat(locationTrajectoryDynamics,blockTrajectory,blockId(1,p)));
                                                            add_condition = 1;
                                                        else
                                                            blockTrajectory = "";
                                                            locationBlockTrajectory =convertStringsToChars(strcat(locationTrajectoryDynamics,blockTrajectory,blockId(1,p)));
                                                            add_condition = 0;
                                                        end
                                                        if (getSimulinkBlockHandle(locationBlockTrajectory) == -1 && add_condition == 1)
                                                            add_block(convertCharsToStrings(strcat("OpenSCENARIO/",blockTrajectory)),locationBlockTrajectory)
                                                            % change location of Trajectory input
                                                            size_blk = get_param(locationBlockAdd,'Position');
                                                            X = size_blk(1,1)-400;
                                                            Y = size_blk(1,2)+850+shift1;
                                                            WIDTH = 100;
                                                            HEIGHT = 150;
                                                            set_param(locationBlockTrajectory,'Position',[X Y X+WIDTH Y+HEIGHT]);
                                                            % disable link to library
                                                            set_param(locationBlockTrajectory, 'LinkStatus','inactive')

                                                        end
                                                        % add label to condition trajectory
                                                        blockConditionTrajectory = "Condition_trajectory";
                                                        if (blockConditionTrajectory==blockTrajectory)
                                                            locationBlockConditionTrajectory = locationBlockTrajectory;
                                                        else
                                                            locationBlockConditionTrajectory = strcat(locationBlockTrajectory,"/",blockConditionTrajectory);
                                                        end
                                                        blockFrom = "From";
                                                        locationBlockFrom =convertStringsToChars(strcat(locationBlockConditionTrajectory,"/",blockFrom));
                                                        if(isfield(trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                                .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition, 'Distance_RelativeObject') == 1 || isfield(trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                                .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition, 'SimulationTimeCondition') == 1 )
                                                            set_param(locationBlockFrom,'Gototag',   convertStringsToChars(strcat("D_",trajectoryType(1,z) ,blockId(1,j) ) )    )
                                                        end

                                                        if(isfield(trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                                .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition, 'TimeHeadWayCondition') == 1 &&...
                                                                isfield(trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                                .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name), 'StoryboardElementStateCondition') == 0)
                                                            set_param(locationBlockFrom,'Gototag',   convertStringsToChars(strcat("T_",trajectoryType(1,z) ,blockId(1,j) ) )    )
                                                        end

                                                        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% connecting lines                                                
                                                        if(trajectoryType(1,z) =="Longitudinal")                                                      

                                                            % check if trajectory_output has a connect, otherwise add it
                                                            s3 = get_param(locationBlockTrajectory, 'PortConnectivity');
                                                            set_param(convertStringsToChars(strcat(locationBlockTrajectoryDynamics,"/Goto")),'GotoTag',strcat("V0","_",num2str(actor)));

                                                            if(isempty(s3(1,1).DstBlock == 1))
                                                                % add trajectory output to add
                                                                add_line(convertStringsToChars(locationBlockTrajectoryDynamics), convertStringsToChars(strcat(blockTrajectory,blockId(1,p),"/1"))  ...
                                                                    ,convertStringsToChars(strcat(blockAdd,"/",int2str(nbTrajectoryTypeAction(1,a)-p+2))) )
                                                            end

                                                            locationDynamicsEmpty = strcat(nameSimulink,convertCharsToStrings(models.worldmodel.object{j,1}.name),"/Dynamics_Empty/");
                                                            % Only connect ones
                                                            if(p ==nbTrajectoryTypeAction(1,a))
                                                                s5 = get_param(convertStringsToChars(strcat(locationDynamicsEmpty,"Gain",int2str(j))), 'PortConnectivity');
                                                                % If initial velocity exists delete line
                                                                if( isempty(s5(2,1).DstBlock) ~= 1)
                                                                    h = get_param(convertStringsToChars(strcat(locationDynamicsEmpty,"Gain",int2str(j))),'LineHandles');
                                                                    if((h.Outport(1)) ~= -1)
                                                                        delete_line(h.Outport(1) )
                                                                    end
                                                                end
                                                                % add Longitudinal dynamics to longitudinal
                                                                s6 = get_param(locationBlockTrajectoryDynamics, 'PortConnectivity');
                                                                if( s6(1,1).SrcBlock == -1)
                                                                    add_line(locationDynamicsEmpty,convertStringsToChars(strcat("Gain",int2str(j),"/1"))...
                                                                        ,convertStringsToChars(strcat(blockTrajectoryDynamics,"/1")) )
                                                                end
                                                                s6 = get_param(convertStringsToChars(strcat(locationDynamicsEmpty,"MuxState")), 'PortConnectivity');
                                                                if(s6(4,1).SrcBlock == -1)
                                                                    add_line(locationDynamicsEmpty, convertStringsToChars(strcat(blockTrajectoryDynamics,"/1")),'MuxState/4')
                                                                end
                                                            end

                                                            locationLateralDynamics = convertStringsToChars(strcat(locationDynamicsEmpty,"Lateral_Dynamics"));
                                                            if (getSimulinkBlockHandle(locationLateralDynamics) == 1)
                                                                s6 = get_param(locationBlockTrajectory, 'PortConnectivity');
                                                                if(isempty(s6(1,1).DstBlock == 1))
                                                                % add trajectory output to add
                                                                    add_line(convertStringsToChars(locationDynamicsEmpty),convertStringsToChars(strcat("Longitudinal_Dynamics","/1"))...
                                                                            ,convertStringsToChars(strcat(blockTrajectoryDynamics,"/1")) )
                                                                end
                                                            end
                                                        end


                                                        if(trajectoryType(1,z) =="Lateral")
                                                            % check if trajectory_output has a connect, otherwise add it
                                                            s3 = get_param(locationBlockTrajectory, 'PortConnectivity');
                                                            if(isempty(s3(1,1).DstBlock == 1))
                                                                % add trajectory output to add
                                                                add_line(convertStringsToChars(locationBlockTrajectoryDynamics), convertStringsToChars(strcat(blockTrajectory,blockId(1,p),"/1"))  ...
                                                                    ,convertStringsToChars(strcat(blockAdd,"/",int2str(nbTrajectoryTypeAction(1,a)-p+1))) )
                                                            end

                                                            if(p ==nbTrajectoryTypeAction(1,a))
                                                                locationDynamicsEmpty = strcat(nameSimulink,convertCharsToStrings(models.worldmodel.object{j,1}.name),"/Dynamics_Empty/");
                                                                s5 = get_param(convertStringsToChars(strcat(locationDynamicsEmpty,blockTrajectoryDynamics)), 'PortConnectivity');
                                                                % add subsystem to Muxstate
                                                                if( isempty(s5(2,1).DstBlock) == 1)
                                                                    add_line(convertStringsToChars(locationDynamicsEmpty),convertStringsToChars(strcat(blockTrajectoryDynamics,"/1"))...
                                                                        ,convertStringsToChars(strcat("MuxState","/9")) )
                                                                end
                                                                % add Longitudinal dynamics to lateral
                                                                if(s5(1,1).SrcBlock == -1)
                                                                    if (getSimulinkBlockHandle(convertStringsToChars(strcat(locationDynamicsEmpty,"Longitudinal_Dynamics"))) == -1)
                                                                        add_line(convertStringsToChars(locationDynamicsEmpty),convertStringsToChars(strcat("Gain",int2str(j),"/1"))...
                                                                            ,convertStringsToChars(strcat(blockTrajectoryDynamics,"/1")) )
                                                                    else
                                                                        add_line(convertStringsToChars(locationDynamicsEmpty),convertStringsToChars(strcat("Longitudinal_Dynamics","/1"))...
                                                                            ,convertStringsToChars(strcat(blockTrajectoryDynamics,"/1")) )
                                                                    end
                                                                end
                                                            end
                                                            
                                                            if(blockTrajectory=="Trajectory_input_turn_subsystem")
                                                                set_param(convertStringsToChars(strcat(locationTrajectoryDynamics,"Trajectory_output","/Switch")),'Threshold', convertStringsToChars(strcat("-",convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                            .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.value))))
                                                                delete_line(strcat(locationTrajectoryDynamics,"Trajectory_output"),"Asin/1", "Switch/2");
                                                                delete_line(strcat(locationTrajectoryDynamics,"Trajectory_output"),"Asin/1", "Switch/3");
                                                                add_line(strcat(locationTrajectoryDynamics,"Trajectory_output"), "From/1", "Switch/2");
                                                                add_line(strcat(locationTrajectoryDynamics,"Trajectory_output"), "Constant/1", "Switch/3");
                                                                if (str2num(trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                            .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.Target.value) <0)
                                                                    set_param(convertStringsToChars(strcat(locationTrajectoryDynamics,"Trajectory_output","/Constant")),'value', trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                                .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.value)
                                                                else
                                                                    set_param(convertStringsToChars(strcat(locationTrajectoryDynamics,"Trajectory_output","/Constant")),'value', strcat("-",trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                                .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.value))
                                                                end
                                                            end

                                                        end




                                                        %%% Adding ROS Velocity
                                                        if ((z==2 || isfield(convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, 1}.Attributes.name)),trajectoryType(1,2) ) == 0) && p ==nbTrajectoryTypeAction(1,a) && getSimulinkBlockHandle(strcat(locationDynamicsEmpty,"ROS Send Velocity")) == -1)
                                                            locationDynamicsEmpty = strcat(nameSimulink,convertCharsToStrings(models.worldmodel.object{j,1}.name),"/Dynamics_Empty/");
                                                            add_block(strcat("adeye_lib/","ROS Send Velocity"),strcat(locationDynamicsEmpty,"ROS Send Velocity") );
                                                            set_param(strcat(locationDynamicsEmpty,"ROS Send Velocity"),'LinkStatus', 'inactive') % Unlock links
                                                            set_param(strcat(locationDynamicsEmpty,"ROS Send Velocity","/Publish4"),'LinkStatus', 'inactive')
                                                            set_param(strcat(locationDynamicsEmpty,"ROS Send Velocity","/Publish4"), "topicSource", "specify your own");
                                                            if (length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act)==1)
                                                                set_param(strcat(locationDynamicsEmpty,"ROS Send Velocity","/Publish4"), "topic", "/other_velocity");
                                                            else
                                                                set_param(strcat(locationDynamicsEmpty,"ROS Send Velocity","/Publish4"), "topic", strcat("/other_velocity_", num2str(actor)));
                                                            end
                                                            if (getSimulinkBlockHandle(strcat(locationDynamicsEmpty,"Longitudinal_Dynamics")) ~= -1)
                                                                add_line(strcat(locationDynamicsEmpty), 'Longitudinal_Dynamics/1', 'ROS Send Velocity/1');
                                                            else
                                                                add_line(strcat(locationDynamicsEmpty), convertStringsToChars(strcat("Gain",int2str(j),"/1")), 'ROS Send Velocity/1');
                                                            end
                                                            add_block("simulink/Commonly Used Blocks/Constant", strcat(locationDynamicsEmpty,"EnableSendVelocity"),'value', '1');
                                                            add_line(strcat(locationDynamicsEmpty), 'EnableSendVelocity/1', 'ROS Send Velocity/Enable');
                                                            % change the size and the position of the added block
                                                            size_blk = get_param(convertStringsToChars(strcat(locationDynamicsEmpty,"EnableSendVelocity")),'Position');
                                                            X = size_blk(1,1)+10;
                                                            Y = size_blk(1,2)-230;
                                                            WIDTH = 20;
                                                            HEIGHT = 20;
                                                            set_param(strcat(locationDynamicsEmpty,"EnableSendVelocity"),'Position',[X Y X+WIDTH Y+HEIGHT]);
                                                            if (getSimulinkBlockHandle(strcat(locationDynamicsEmpty,"Lateral_Dynamics")) ~= -1)
                                                                add_line(strcat(locationDynamicsEmpty), 'Lateral_Dynamics/1', 'ROS Send Velocity/2');
                                                            else
                                                                add_block("simulink/Commonly Used Blocks/Constant", strcat(locationDynamicsEmpty,"constant"), 'value', '0');
                                                                add_line(strcat(locationDynamicsEmpty), 'constant/1', 'ROS Send Velocity/2');
                                                                % change the size and the position of the added block
                                                                size_blk = get_param(convertStringsToChars(strcat(locationDynamicsEmpty,"constant")),'Position');
                                                                X = size_blk(1,1)+10;
                                                                Y = size_blk(1,2)-140;
                                                                WIDTH = 20;
                                                                HEIGHT = 20;
                                                                set_param(strcat(locationDynamicsEmpty,"constant"),'Position',[X Y X+WIDTH Y+HEIGHT]);
                                                            end
                                                            % change the size and the position of the added block Ros send Velocity
                                                            size_blk = get_param(convertStringsToChars(strcat(locationDynamicsEmpty,"ROS Send Velocity")),'Position');
                                                            X = size_blk(1,1)+200;
                                                            Y = size_blk(1,2)-1600;
                                                            WIDTH = 200;
                                                            HEIGHT = 100;
                                                            set_param(strcat(locationDynamicsEmpty,"ROS Send Velocity"),'Position',[X Y X+WIDTH Y+HEIGHT]);
                                                        end

                                                        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% changing parameters
                                                        %%%%%%%%%%%%%%%%%% Parameters of Condition source
                                                        if(isfield(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition, 'Distance_RelativeObject') == 1 || isfield(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition, 'SimulationTimeCondition') == 1)
                                                            for h =1: length( models.worldmodel.object)
                                                                 %%%%%%%%%%% Check if it is a Distance_RelativeObject or a SimulationTimeCondition
                                                                if((isfield(convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition),"Distance_RelativeObject") == 1 && convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                                        .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Distance_RelativeObject) == ...
                                                                        convertCharsToStrings(models.worldmodel.object{h,1}.name)) ||  (isfield(convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition),"SimulationTimeCondition") == 1 && convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                                        .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.SimulationTimeCondition) == ...
                                                                        convertCharsToStrings(models.worldmodel.object{h,1}.name))   &&     convertCharsToStrings(models.worldmodel.object{j,1}.name)  ~= nameEgo)
                                                                    convertStringsToChars(strcat(locationBlockConditionSource,"/From4"))
                                                                    set_param(convertStringsToChars(strcat(locationBlockConditionSource,"/From4")),'GotoTag',convertStringsToChars(strcat("x_",blockId(1,h) ) )  )
                                                                    set_param(convertStringsToChars(strcat(locationBlockConditionSource,"/From1")),'GotoTag',convertStringsToChars(strcat("y_",blockId(1,h) ) )  )
                                                                    set_param(convertStringsToChars(strcat(locationBlockConditionSource,"/From3")),'GotoTag',convertStringsToChars(strcat("z_",blockId(1,h) ) )  )
                                                                end
                                                            end
                                                            convertStringsToChars(strcat(locationBlockConditionSource,"/From4"))
                                                            set_param(convertStringsToChars(strcat(locationBlockConditionSource,"/From9")),'GotoTag',convertStringsToChars(strcat("x_",blockId(1,j) ) )  )
                                                            set_param(convertStringsToChars(strcat(locationBlockConditionSource,"/From2")),'GotoTag',convertStringsToChars(strcat("y_",blockId(1,j) ) )  )
                                                            set_param(convertStringsToChars(strcat(locationBlockConditionSource,"/From5")),'GotoTag',convertStringsToChars(strcat("z_",blockId(1,j) ) )  )
                                                            if( isfield(trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                                .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition, 'Distance_RelativeObject') == 1)
                                                            set_param(convertStringsToChars(strcat(locationBlockConditionSource,"/Goto4")),'GotoTag', convertStringsToChars(strcat("D_",trajectoryType(1,z) ,blockId(1,j) ) )  )

                                                            else
                                                                set_param(convertStringsToChars(strcat(locationBlockConditionSource,"/Goto4")),'GotoTag', convertStringsToChars(strcat("D_",trajectoryType(1,z) ,blockId(1,j) ) )  )
                                                            end
                                                        end
                                                        %%%%%%%%%%%%%%%%%%%% Check if it is a TimeHeadWayCondition
                                                        if( isfield(trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                                .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition, 'TimeHeadWayCondition') == 1)
                                                            set_param(convertStringsToChars(strcat(locationBlockConditionSource,"/Goto4")),'GotoTag', convertStringsToChars(strcat("T_",trajectoryType(1,z) ,blockId(1,j) ) )  )
                                                        end



        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Parameters of Condition trajetory
                                                       % WIDTH = abs(str2num(trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                          %  .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.Target.value));

                                                        blockConditionTrajectory="/Condition_trajectory";

                                                           if(convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule.rule) == "lessThan")
                                                                %%%%% Parameters of Condition_trajectory
                                                                set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockConditionTrajectory,"/Gain2")),'Gain','-1')
                                                                set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockConditionTrajectory,"/Switch1"))...
                                                                    ,'Criteria','u2 > Threshold')
                                                                set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockConditionTrajectory,"/Switch1"))...
                                                                    ,'Threshold',...
                                                                    num2str(-1*str2num(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule.value)) )
                                                            end

                                                            if(convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule.rule) == "greaterThan")
                                                                %%%%% Parameters of Condition_trajectory
                                                                set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockConditionTrajectory,"/Gain2")),'Gain','1')
                                                                set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockConditionTrajectory,"/Switch1"))...
                                                                    ,'Criteria','u2 >= Threshold')
                                                                set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockConditionTrajectory,"/Switch1"))...
                                                                    ,'Threshold',...
                                                                    num2str(str2num(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule.value)) )
                                                                % change constant to account for shift if step
                                                            end

                                                            if(convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule.rule) == "equalTo")
                                                                %%%%% Parameters of Condition_trajectory
                                                                set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockConditionTrajectory,"/Gain2")),'Gain','1')
                                                                set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockConditionTrajectory,"/Switch1"))...
                                                                    ,'Criteria','u2 >= Threshold')
                                                                set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockConditionTrajectory,"/Switch1"))...
                                                                    ,'Threshold',...
                                                                    num2str(str2num(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule.value)) )
                                                                % change constant to account for shift if step
                                                            end
                                                            
                                                            if (isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1, q}.Act{1,a}.ManeuverGroup.Maneuver{1, m}.Event{1, i}.StartTrigger.ConditionGroup.Condition, 'ByEntityCondition')==1 && isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1, q}.Act{1,a}.ManeuverGroup.Maneuver{1, m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.EntityCondition, 'SpeedCondition')==1 )
                                                                if (convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                                        .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Speed_RelativeObject) == "Ego")
                                                                    set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockConditionTrajectory,"/Gain2")),'Gain','1')
                                                                    set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockConditionTrajectory,"/From")),'GotoTag','velocity' );
                                                                else
                                                                    for h =1: length( models.worldmodel.object)
                                                                        if(convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                                            .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Speed_RelativeObject) == ...
                                                                            convertCharsToStrings(models.worldmodel.object{h,1}.name))
                                                                            locationDynanicsEmpty = strcat(nameSimulink,convertCharsToStrings(models.worldmodel.object{h,1}.name),"/Dynamics_Empty/");
                                                                            add_block("simulink/Signal Routing/Goto", strcat(locationDynanicsEmpty,"Velocity"),'GotoTag', 'Vel');
                                                                            % change the size and the position of the added block Velocity
                                                                            size_blk = get_param(convertStringsToChars(strcat(locationDynanicsEmpty,"Velocity")),'Position');
                                                                            X = size_blk(1,1)-120;
                                                                            Y = size_blk(1,2)-300;
                                                                            WIDTH = 50;
                                                                            HEIGHT = 20;
                                                                            set_param(strcat(locationDynanicsEmpty,"Velocity"),'Position',[X Y X+WIDTH Y+HEIGHT]);
                                                                                            set_param(strcat(locationDynanicsEmpty,"Velocity"), 'TagVisibility', 'global');
                                                                            if (getSimulinkBlockHandle(strcat(locationDynanicsEmpty,"Longitudinal_Dynamics")) ~= -1)
                                                                                add_line(strcat(locationDynanicsEmpty), 'Longitudinal_Dynamics/1', 'Velocity/1');
                                                                            else
                                                                                add_line(strcat(locationDynanicsEmpty), convertStringsToChars(strcat("Gain",int2str(j),"/1")), 'Velocity/1');
                                                                            end
    %                                                                         set_param(convertStringsToChars(strcat(location3,Blockname6,"/Gain2")),'Gain','1')
                                                                            set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockConditionTrajectory,"/From")),'GotoTag','Vel' );
                                                                        end
                                                                    end
                                                                end
                                                            end

                                                            if (isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1, q}.Act{1,a}.ManeuverGroup.Maneuver{1, m}.Event{1, i}.StartTrigger.ConditionGroup.Condition, 'ByValueCondition')==1 &&  isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1, q}.Act{1,a}.ManeuverGroup.Maneuver{1, m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByValueCondition, 'SimulationTimeCondition')==1)
                                                                set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockConditionTrajectory,"/Gain2")),'Gain','1')
                                                                set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockConditionTrajectory,"/Switch1"))...
                                                                    ,'Criteria','u2 >= Threshold')
                                                                set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockConditionTrajectory,"/Switch1"))...
                                                                    ,'Threshold', '0.001')    
                                                                set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockConditionTrajectory,"/Switch2"))...
                                                                    ,'Criteria','u2 >= Threshold')
                                                                set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockConditionTrajectory,"/Switch2"))...
                                                                    ,'Threshold',trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule.value)
                                                                set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockConditionTrajectory,"/Constant5")) ,'value', trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule.value) 

                                                            end

%                                                             if (blockTrajectory=="Trajectory_input_distance_subsystem")
%                                                                 set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockConditionTrajectory,"/Switch1"))...
%                                                                     ,'Criteria','u2 >= Threshold')
%                                                                 set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockConditionTrajectory,"/Switch1"))...
%                                                                     ,'Threshold', '0.001')
%                                                                 set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockConditionTrajectory,"/Gain2")),'Gain','1')
%                                                             end

        %%%%%%%%%%%%%%%%%%%%%%% %%%%% Parameters of Trajectory_input
                                                        if (blockTrajectory=="Trajectory_input_sinusoidal_subsystem" || blockTrajectory=="Trajectory_input_turn_subsystem")
                                                            blockTrajectoryInput = "/Trajectory_input";
                                                            % switch
                                                            set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/Switch3"))...
                                                            ,'Criteria','u2 >= Threshold')
                                                            set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/Switch3"))...
                                                            ,'Threshold',...
                                                            convertStringsToChars(strcat("-",convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                            .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.value)))    )
                                                            % function
                                                            set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/Cos")),'Function','cos')
                                                            % constants and gains
                                                            set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/Constant3")),'Value',(trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                            .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.Target.value))
                                                            value1 = 4*str2num(convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                            .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.value));
                                                            value2 = 2*pi/value1;
                                                            set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/Gain5")),'Gain',(trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                            .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.Target.value))
                                                            set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/Gain6")),'Gain',convertStringsToChars(num2str(value2))) 
                                                            set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/Gain4")),'Gain',strcat("-",convertStringsToChars(num2str(value2)))   )                                                                                            

                                                        elseif (blockTrajectory=="Trajectory_input_distance_subsystem")
                                                            blockTrajectoryInput="/Distance_condition";
                                                            set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/From1")),'GotoTag',strcat('V', num2str(p-1), '_',num2str(actor)) );
                                                            %%%%%%%%%%%%%%%% Get the speed value of the entityRef
                                                            if (convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                                    .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).LongitudinalDistanceAction.Attributes.entityRef) == "Ego")
                                                                set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/actorSpeed")),'GotoTag','velocity' );
                                                                set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/actorSpeed2")),'GotoTag','velocity' );
                                                            else
                                                                for h =1: length( models.worldmodel.object)
                                                                    if(convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                                        .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).LongitudinalDistanceAction.Attributes.entityRef) == ...
                                                                        convertCharsToStrings(models.worldmodel.object{h,1}.name))
                                                                        locationDynanicsEmpty = strcat(nameSimulink,convertCharsToStrings(models.worldmodel.object{h,1}.name),"/Dynamics_Empty/");
                                                                        add_block("simulink/Signal Routing/Goto", strcat(locationDynanicsEmpty,"Velocity"),'GotoTag', 'Velo');
                                                                        % change the size and the position of the added block Velocity
                                                                        size_blk = get_param(convertStringsToChars(strcat(locationDynanicsEmpty,"Velocity")),'Position');
                                                                        X = size_blk(1,1)-120;
                                                                        Y = size_blk(1,2)-300;
                                                                        WIDTH = 50;
                                                                        HEIGHT = 20;
                                                                        set_param(strcat(locationDynanicsEmpty,"Velocity"),'Position',[X Y X+WIDTH Y+HEIGHT]);
                                                                        set_param(strcat(locationDynanicsEmpty,"Velocity"), 'TagVisibility', 'global');
                                                                        if (getSimulinkBlockHandle(strcat(locationDynanicsEmpty,"Longitudinal_Dynamics")) ~= -1)
                                                                            add_line(strcat(locationDynanicsEmpty), 'Longitudinal_Dynamics/1', 'Velocity/1');
                                                                        else
                                                                            add_line(strcat(locationDynanicsEmpty), convertStringsToChars(strcat("Gain",int2str(j),"/1")), 'Velocity/1');
                                                                        end
%                                                                         set_param(convertStringsToChars(strcat(location3,Blockname6,"/Gain2")),'Gain','1')
                                                                        set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/actorSpeed")),'GotoTag','Velo' );
                                                                        set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/actorSpeed2")),'GotoTag','Velo' );
                                                                    end
                                                                end
                                                            end
                                                            set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/Distance_wanted")), 'value', trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule.value);
                                                            set_param((strcat(locationBlockTrajectory,blockTrajectoryInput,"/Current_distance")),'Gototag',   convertStringsToChars(strcat("D_",trajectoryType(1,z) ,blockId(1,j) ) )    )
                                                            set_param((strcat(locationBlockTrajectory,blockTrajectoryInput,"/Current_distance1")),'Gototag',   convertStringsToChars(strcat("D_",trajectoryType(1,z) ,blockId(1,j) ) )    )
                                                            set_param((strcat(locationBlockTrajectory,blockTrajectoryInput,"/Current_distance2")),'Gototag',   convertStringsToChars(strcat("D_",trajectoryType(1,z) ,blockId(1,j) ) )    )
                                                                        set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/Distance_wanted")),'value',trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                            .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).LongitudinalDistanceAction.Attributes.distance );
                                                                        set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/Distance_wanted1")),'value',trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                            .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).LongitudinalDistanceAction.Attributes.distance);
                                                                        set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/MaxSpeed")),'value',trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                            .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).LongitudinalDistanceAction.dynamicConstraints.Attributes.maxSpeed );
                                                                        set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/MaxAcceleration")),'value',trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                            .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).LongitudinalDistanceAction.dynamicConstraints.Attributes.maxAcceleration );
                                                                        set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/MaxDeceleration")),'value',trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                            .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).LongitudinalDistanceAction.dynamicConstraints.Attributes.maxDeceleration );
                                                                    
%                                                             if (i<nbTrajectoryTypeAction)
%                                                               set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/Switch7"))...
%                                                                     ,'Threshold',...
%                                                                     trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
%                                                                     .ManeuverGroup.Maneuver{1,m}.Event{1, i+1}.Attributes.name).Condition.Rule.value)
%                                                             else
%                                                                h = get_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,'/Switch7')),'LineHandles');
%                                                                delete_line(h.Inport(1));
%                                                                add_line(convertStringsToChars(locationBlockTrajectory), convertStringsToChars(strcat("Switch6","/1")),convertStringsToChars(strcat("Switch7","/1")))
%                                                             end

                                                        elseif (blockTrajectory=="Trajectory_input_step_subsystem")
                                                            blockTrajectoryInput="/Trajectory_input";
                                                            set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/speed")), 'value', trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.Target.value )
                                                                set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/From")),'GotoTag',strcat("V", num2str(p-1),"_",num2str(actor))); 

                                                        elseif (blockTrajectory=="Trajectory_input_linear_subsystem")
                                                            blockTrajectoryInput="/Change_speed"; 
                                                            set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/Desired_speed")), 'value', trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.Target.value );
                                                                if (strcmp(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.dynamicsDimension, 'time') || strcmp(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.dynamicsDimension, 'distance'))
                                                                    set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/timeDistance")), 'value', trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.value)
                                                                    add_line(strcat(locationBlockTrajectory,blockTrajectoryInput), "Acceleration/1", "Gain/1");
                                                                else
                                                                    set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/Acceleration_rate")), 'value', trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.value)
                                                                    add_line(strcat(locationBlockTrajectory,blockTrajectoryInput), "Acceleration_rate/1", "Gain/1");
                                                                end
                                                            ini= str2double(trajectoryVariable.(models.worldmodel.object{j, 1}.name).init)/3.6;
                                                            set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/Memory")),'InitialCondition',num2str(ini) );
                                                            set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/From1")),'GotoTag',strcat("V", num2str(p-1),"_",num2str(actor)) );
                                                            set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockTrajectoryInput,"/From2")),'GotoTag',strcat("V", num2str(p-1),"_",num2str(actor)) );

                                                        end

                                                            % used in AfterTermination
                                                           % b(i,1) = convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
                                                            %.(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.value);


    %                                                             if( isfield(trajectoryVariable.(models.worldmodel.object{j, 1}.name)...
    %                                                                 .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition, 'TimeHeadWayCondition') == 1)
    %                                                                 set_param(convertStringsToChars(strcat(location3,Blockname6,"/From")),'Gototag',convertStringsToChars(strcat("T_",trajectory_type(1,z) ,Blockid(1,j) )) )
    %                                                             else
    %                                                                 set_param(convertStringsToChars(strcat(location3,Blockname6,"/From")),'Gototag',convertStringsToChars(strcat("D_",trajectory_type(1,z) ,Blockid(1,j) )) )
    %                                                             end
    % 
    %                                                             %change constant to account for shift if step
    %                                                             if(Blockname3 ==  "Trajectory_input_step")
    %                                                                 set_param(convertStringsToChars(strcat(location3,Blockname6,"/Constant1")),'Value', b(i-1,1));
    %                                                             end


                                                    % Checking for Aftertermination field
                                                    if(isfield(convertCharsToStrings(trajectoryVariable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name)),'StoryboardElementStateCondition') == 1)
                                                        set_param(convertStringsToChars(strcat(locationBlockTrajectory,blockConditionTrajectory,"/Constant1")),'Value', b(i-1,1));

                                                    end
                                                    
                                                    %%%%%%%%%%%%%%%%%%%%%%%%% Add goto block for the next Action
                                                    if (trajectoryType(1,z) =="Longitudinal" && p<nbTrajectoryTypeAction(1,a))
                                                        add_block("simulink/Signal Routing/Goto", strcat(locationBlockTrajectory, blockTrajectoryInput, '/oldVelocity'),'GotoTag',strcat("V", num2str(p),"_",num2str(actor)));
                                                        add_line(strcat(locationBlockTrajectory, blockTrajectoryInput), "trueSpeed/1", strcat("oldVelocity", "/1"));                                                        
                                                        set_param(strcat(locationBlockTrajectory, blockTrajectoryInput,"/oldVelocity"), 'TagVisibility', 'global');
                                                    end


                                                    end % if statement Distance_RelativeObject check
                                                end % if statement Objects check
                                            end % if statement lateral check
                                        end % for loop number of events (trajectories)
                                    end % if statement which story belongs to which object
                                end % numb er of maneuvers
                            end % if statement which object has trajectories
                        end % Check if object has which event
                    end % if statement to check existence of object in trajectoryVariable
                end
            end % if statement to check existence of event in trajectoryVariable

        end
    
    end
end% main for loop

disp('LATERAL DYNAMICS ADDED')





end
