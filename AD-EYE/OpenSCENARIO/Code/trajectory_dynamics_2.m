function  trajectory_dynamics_2(name_simulink,models,Struct_OpenSCENARIO,trajectory_variable,Lateral_events,Longitudinal_events,name_ego)


for j = 1:length(models.worldmodel.object)
    
    trajectory_type = ["Longitudinal","Lateral"];
    for z = 1:length(trajectory_type)
        
        p = 0;
        if(isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard,'Story'))
            for q = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story  ) %Number of Stories
                for a= 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act) %Number of acts

                    %check if a trajectory variable exists
                    if( exist('trajectory_variable','var') == 1)
                        %check if an object in trajectory variable exists
                        if(isfield(convertCharsToStrings(trajectory_variable),convertCharsToStrings(models.worldmodel.object{j, 1}.name)) == 1 )
                            %check which story belongs to which car
                            if(convertCharsToStrings(models.worldmodel.object{j, 1}.name)== convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1, q}.Act{1,a}.ManeuverGroup.Actors.EntityRef.Attributes.entityRef))
                                for m = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver)%Number of Maneuvers
                                    for i=1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event)
                                        if(isfield(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name)), convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name))== 1 )
                                            %check if it is a lateral trajectory
                                            if(isfield(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name)),trajectory_type(1,z) ) == 1 )
                                                %check if Object structure exists
                                                if(isfield(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                        .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition),"Objects") == 1 )
                                                    %check if Distance_RelativeObject structure exists
                                                    if(isfield(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition),"Distance_RelativeObject") == 1  || isfield(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition),"TimeHeadWay") == 1 || isfield(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition),"SimulationTimeCondition") == 1  || isfield(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition),"Speed_RelativeObject") == 1)


                                                        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Adding blocks
                                                        %number of events (trajectories)
                                                        p = p+1;
                                                        %%%%%%%%%%%%%%%%%%%%%%%%%%%%Subsystem in Dynamics_Empty
                                                        Blockid = string(1:length(models.worldmodel.object));
                                                        location = strcat(name_simulink,convertCharsToStrings(models.worldmodel.object{j,1}.name),"/Dynamics_Empty/");
                                                        Blockname0 = strcat(trajectory_type(1,z) ,"_Dynamics");
                                                        location0 = convertStringsToChars(strcat(location,Blockname0));
                                                        if (getSimulinkBlockHandle(location0) == -1)
                                                            add_block(convertStringsToChars(strcat("OpenSCENARIO/",Blockname0)),location0 );
                                                            %change location of condition source
                                                            size_blk = get_param(convertStringsToChars(strcat(location,"MuxState")),'Position');
                                                            if(trajectory_type(1,z) =="Lateral")
                                                                X = size_blk(1,1)-250;
                                                                Y = size_blk(1,2)+145;
                                                            elseif(trajectory_type(1,z) =="Longitudinal")
                                                                X = size_blk(1,1)-540;
                                                                Y = size_blk(1,2)+35;
                                                            end
                                                            Width = 200;
                                                            Height = 100;
                                                            set_param(location0,'Position',[X Y X+Width Y+Height]);
                                                            set_param(location0,'LinkStatus','inactive')
                                                        end


                                                        location = strcat(name_simulink,convertCharsToStrings(models.worldmodel.object{j,1}.name),"/Dynamics_Empty/",Blockname0,"/");
                                                        shift1 = -250*(p-1);
                                                        if(trajectory_type(1,z) =="Lateral")
                                                            p_L = Lateral_events;
                                                        elseif(trajectory_type(1,z) =="Longitudinal")
                                                            p_L = Longitudinal_events;
                                                        end

                                                        %change the size of the Add block
                                                        Blockname1 = "Add";
                                                        location1 =convertStringsToChars(strcat(location,Blockname1));
                                                        if(trajectory_type(1,z) =="Lateral")
                                                            set_param(location1,'Inputs',int2str(p_L(1,q)))
                                                        elseif(trajectory_type(1,z) =="Longitudinal")
                                                            set_param(location1,'Inputs',int2str(p_L(1,q)+1))
                                                        end



                                                        %create
                                                        %condition_source_time
                                                        if( isfield(trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                                .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition, 'TimeHeadWayCondition') == 1)
                                                            %add block condition source
                                                            Blockname2 = strcat("Condition_source_time_",trajectory_type(1,z) );
                                                            location2 =convertStringsToChars(strcat(location,Blockname2));
                                                            add_condition = 1;
                                                            %check if Longitudinal_dynamics exisits, otherwise do not create Condition_source
                                                        elseif ( isfield(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition, 'Distance_RelativeObject') == 1 || isfield(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition, 'SimulationTimeCondition') == 1)
                                                            %add block condition source
                                                            Blockname2 = strcat("Condition_source_",trajectory_type(1,z) );
                                                            location2 =convertStringsToChars(strcat(location,Blockname2));
                                                            add_condition = 1;
                                                        else
                                                            Blockname2 = " ";
                                                            location2 =convertStringsToChars(strcat(location,Blockname2));
                                                            add_condition = 0;
                                                        end
                                                        if (getSimulinkBlockHandle(location2) == -1 && add_condition == 1)
                                                            %add condition source
                                                            add_block(convertCharsToStrings(strcat("OpenSCENARIO/",Blockname2)),location2)
                                                            %change location of condition source
                                                            size_blk = get_param(location1,'Position');
                                                            X = size_blk(1,1)+500+shift1;
                                                            Y = size_blk(1,2)-300;
                                                            Width = 70;
                                                            Height =90;
                                                            set_param(location2,'Position',[X Y X+Width Y+Height]);
                                                            %disable link to library
                                                            set_param(location2, 'LinkStatus','inactive');
                                                            set_param(convertStringsToChars(strcat(location,Blockname2,"/Goto4")),'TagVisibility','global');
                                                        end



                                                        %add block for sinusoidal outputs
    %                                                     if ((convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
    %                                                             .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.dynamicsDimension) == "distance" || (isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1, q}.Act{1,a}.ManeuverGroup.Maneuver{1, m}.Event{1, i}.StartTrigger.ConditionGroup.Condition, 'ByEntityCondition')==1 && isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1, q}.Act{1,a}.ManeuverGroup.Maneuver{1, m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.EntityCondition, 'RelativeDistanceCondition')==1)) || (convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
    %                                                             .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.dynamicsDimension) == "time" && isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByValueCondition, 'SimulationTimeCondition')==1))
    %                                                         Blockname3 = "Condition_trajectory";
    %                                                         location3 =convertStringsToChars(strcat(location,Blockname3,Blockid(1,p)));
    %                                                         add_condition = 1;
                                                        if (trajectory_type(1,z) =="Longitudinal" && (isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1, q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Action.PrivateAction.LongitudinalAction), 'LongitudinalDistanceAction')==1 ) && Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}...
                                                            .Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Action.PrivateAction.LongitudinalAction.LongitudinalDistanceAction.Attributes.continuous == "true")
                                                            Blockname3 = "distance";
                                                            Blockname3 = strcat("Trajectory_input_",Blockname3,"_subsystem");
                                                            location3 =convertStringsToChars(strcat(location,Blockname3,Blockid(1,p)));
                                                            add_condition = 1;
                                                        elseif (convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.dynamicsShape) == "sinusoidal" && abs(str2num(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.Target.value)) > 5)
                                                            Blockname3 = "turn";
                                                            Blockname3 = strcat("Trajectory_input_",Blockname3,"_subsystem");
                                                            location3 =convertStringsToChars(strcat(location,Blockname3,Blockid(1,p)));
                                                            add_condition = 1;
                                                        elseif(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.dynamicsShape) == "sinusoidal")
                                                            %add block Trajectory
                                                            Blockname3 = "sinusoidal";
                                                            Blockname3 = strcat("Trajectory_input_",Blockname3,"_subsystem");
                                                            location3 =convertStringsToChars(strcat(location,Blockname3,Blockid(1,p)));
                                                            add_condition = 1;
                                                            %add block for linear outputs
                                                        elseif(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.dynamicsShape) == "linear")
                                                            Blockname3 = "linear";
                                                            Blockname3 = strcat("Trajectory_input_",Blockname3,"_subsystem");
                                                            location3 =convertStringsToChars(strcat(location,Blockname3,Blockid(1,p)));
                                                            add_condition = 1;
                                                            %add block for step outputs
                                                        elseif(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.dynamicsShape) == "step")
                                                            Blockname3 = "step";
                                                            Blockname3 = strcat("Trajectory_input_",Blockname3,"_subsystem");
                                                            location3 =convertStringsToChars(strcat(location,Blockname3,Blockid(1,p)));
                                                            add_condition = 1;
                                                        else
                                                            Blockname3 = "";
                                                            location3 =convertStringsToChars(strcat(location,Blockname3,Blockid(1,p)));
                                                            add_condition = 0;
                                                        end
                                                        if (getSimulinkBlockHandle(location3) == -1 && add_condition == 1)
                                                            add_block(convertCharsToStrings(strcat("OpenSCENARIO/",Blockname3)),location3)
                                                            %change location of Trajectory input
                                                            size_blk = get_param(location1,'Position');
                                                            X = size_blk(1,1)-400;
                                                            Y = size_blk(1,2)+850+shift1;
                                                            Width = 100;
                                                            Height = 150;
                                                            set_param(location3,'Position',[X Y X+Width Y+Height]);
                                                            %disable link to library
                                                            set_param(location3, 'LinkStatus','inactive')

                                                        end
                                                        %add label to condition trajectory
                                                        Blockname4 = "Condition_trajectory";
                                                        if (Blockname4==Blockname3)
                                                            location4 = location3;
                                                        else
                                                            location4 = strcat(location3,"/",Blockname4);
                                                        end
                                                        Blockname5 = "From";
                                                        location5 =convertStringsToChars(strcat(location4,"/",Blockname5));
                                                        if(isfield(trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                                .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition, 'Distance_RelativeObject') == 1 || isfield(trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                                .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition, 'SimulationTimeCondition') == 1 )
                                                            set_param(location5,'Gototag',   convertStringsToChars(strcat("D_",trajectory_type(1,z) ,Blockid(1,j) ) )    )
                                                        end

                                                        if(isfield(trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                                .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition, 'TimeHeadWayCondition') == 1 &&...
                                                                isfield(trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                                .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name), 'StoryboardElementStateCondition') == 0)
                                                            set_param(location5,'Gototag',   convertStringsToChars(strcat("T_",trajectory_type(1,z) ,Blockid(1,j) ) )    )
                                                        end

                                                        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%connecting lines                                                
                                                        if(trajectory_type(1,z) =="Longitudinal")                                                      

                                                            %check if trajectory_output has a connect, otherwise add it
                                                            s3 = get_param(location3, 'PortConnectivity');
                                                            set_param(convertStringsToChars(strcat(location0,"/Goto")),'GotoTag',strcat('V_in_', num2str(a)));

                                                            if(isempty(s3(1,1).DstBlock == 1))
                                                                %add trajectory output to add
                                                                add_line(convertStringsToChars(location0), convertStringsToChars(strcat(Blockname3,Blockid(1,p),"/1"))  ...
                                                                    ,convertStringsToChars(strcat(Blockname1,"/",int2str(p_L(1,q)-p+2))) )
                                                            end

                                                            location = strcat(name_simulink,convertCharsToStrings(models.worldmodel.object{j,1}.name),"/Dynamics_Empty/");
                                                            %Only connect ones
                                                            if(p ==p_L(1,q))
                                                                s5 = get_param(convertStringsToChars(strcat(location,"Gain",int2str(j))), 'PortConnectivity');
                                                                %If initial velocity exists delete line
                                                                if( isempty(s5(2,1).DstBlock) ~= 1)
                                                                    h = get_param(convertStringsToChars(strcat(location,"Gain",int2str(j))),'LineHandles');
                                                                    if((h.Outport(1)) ~= -1)
                                                                        delete_line(h.Outport(1) )
                                                                    end
                                                                end
                                                                %add Longitudinal dynamics to longitudinal
                                                                s6 = get_param(location0, 'PortConnectivity');
                                                                if( s6(1,1).SrcBlock == -1)
                                                                    add_line(location,convertStringsToChars(strcat("Gain",int2str(j),"/1"))...
                                                                        ,convertStringsToChars(strcat(Blockname0,"/1")) )
                                                                end
                                                                s6 = get_param(convertStringsToChars(strcat(location,"MuxState")), 'PortConnectivity');
                                                                if(s6(4,1).SrcBlock == -1)
                                                                    add_line(location, convertStringsToChars(strcat(Blockname0,"/1")),'MuxState/4')
                                                                end
                                                            end

                                                            location10 = convertStringsToChars(strcat(location,"Lateral_Dynamics"));
                                                            if (getSimulinkBlockHandle(location10) == 1)
                                                                s6 = get_param(location3, 'PortConnectivity');
                                                                if(isempty(s6(1,1).DstBlock == 1))
                                                                %add trajectory output to add
                                                                    add_line(convertStringsToChars(location),convertStringsToChars(strcat("Longitudinal_Dynamics","/1"))...
                                                                            ,convertStringsToChars(strcat(Blockname0,"/1")) )
                                                                end
                                                            end
                                                        end


                                                        if(trajectory_type(1,z) =="Lateral")
                                                            %check if trajectory_output has a connect, otherwise add it
                                                            s3 = get_param(location3, 'PortConnectivity');
                                                            if(isempty(s3(1,1).DstBlock == 1))
                                                                %add trajectory output to add
                                                                add_line(convertStringsToChars(location0), convertStringsToChars(strcat(Blockname3,Blockid(1,p),"/1"))  ...
                                                                    ,convertStringsToChars(strcat(Blockname1,"/",int2str(p_L(1,q)-p+1))) )
                                                            end

                                                            if(p ==p_L(1,q))
                                                                location = strcat(name_simulink,convertCharsToStrings(models.worldmodel.object{j,1}.name),"/Dynamics_Empty/");
                                                                s5 = get_param(convertStringsToChars(strcat(location,Blockname0)), 'PortConnectivity');
                                                                %add subsystem to Muxstate
                                                                if( isempty(s5(2,1).DstBlock) == 1)
                                                                    add_line(convertStringsToChars(location),convertStringsToChars(strcat(Blockname0,"/1"))...
                                                                        ,convertStringsToChars(strcat("MuxState","/9")) )
                                                                end
                                                                %add Longitudinal dynamics to lateral
                                                                if(s5(1,1).SrcBlock == -1)
                                                                    if (getSimulinkBlockHandle(convertStringsToChars(strcat(location,"Longitudinal_Dynamics"))) == -1)
                                                                        add_line(convertStringsToChars(location),convertStringsToChars(strcat("Gain",int2str(j),"/1"))...
                                                                            ,convertStringsToChars(strcat(Blockname0,"/1")) )
                                                                    else
                                                                        add_line(convertStringsToChars(location),convertStringsToChars(strcat("Longitudinal_Dynamics","/1"))...
                                                                            ,convertStringsToChars(strcat(Blockname0,"/1")) )
                                                                    end
                                                                end
                                                            end
                                                            if(Blockname3=="Trajectory_input_turn_subsystem")
                                                                set_param(convertStringsToChars(strcat(location,"Lateral_Dynamics","/Trajectory_output","/Switch")),'Threshold', convertStringsToChars(strcat("-",convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                            .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.value))))
                                                                delete_line(strcat(location,"Lateral_Dynamics","/Trajectory_output"),"Asin/1", "Switch/2");
                                                                delete_line(strcat(location,"Lateral_Dynamics","/Trajectory_output"),"Asin/1", "Switch/3");
                                                                add_line(strcat(location,"Lateral_Dynamics","/Trajectory_output"), "From/1", "Switch/2");
                                                                add_line(strcat(location,"Lateral_Dynamics","/Trajectory_output"), "Constant/1", "Switch/3");
                                                                if (str2num(trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                            .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.Target.value) <0)
                                                                    set_param(convertStringsToChars(strcat(location,"Lateral_Dynamics","/Trajectory_output","/Constant")),'value', trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                                .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.value)
                                                                else
                                                                    set_param(convertStringsToChars(strcat(location,"Lateral_Dynamics","/Trajectory_output","/Constant")),'value', strcat("-",trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                                .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.value))
                                                                end
                                                            end

                                                        end




                                                        %%%Adding ROS Send
                                                        %%%Velocity
                                                        if ((z==2 || isfield(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name)),trajectory_type(1,2) ) == 0) && p ==p_L(1,q) && getSimulinkBlockHandle(strcat(location,"ROS Send Velocity")) == -1)
                                                            location = strcat(name_simulink,convertCharsToStrings(models.worldmodel.object{j,1}.name),"/Dynamics_Empty/");
                                                            add_block(strcat("adeye_lib/","ROS Send Velocity"),strcat(location,"ROS Send Velocity") );
                                                            set_param(strcat(location,"ROS Send Velocity"),'LinkStatus', 'inactive') %Unlock links
                                                            set_param(strcat(location,"ROS Send Velocity","/Publish4"),'LinkStatus', 'inactive')
                                                            set_param(strcat(location,"ROS Send Velocity","/Publish4"), "topicSource", "specify your own");
                                                            if (length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act)==1)
                                                                set_param(strcat(location,"ROS Send Velocity","/Publish4"), "topic", "/other_velocity");
                                                            else
                                                                set_param(strcat(location,"ROS Send Velocity","/Publish4"), "topic", strcat("/other_velocity_", num2str(a)));
                                                            end
                                                            if (getSimulinkBlockHandle(strcat(location,"Longitudinal_Dynamics")) ~= -1)
                                                                add_line(strcat(location), 'Longitudinal_Dynamics/1', 'ROS Send Velocity/1');
                                                            else
                                                                add_line(strcat(location), convertStringsToChars(strcat("Gain",int2str(j),"/1")), 'ROS Send Velocity/1');
                                                            end
                                                            add_block("simulink/Commonly Used Blocks/Constant", strcat(location,"EnableSendVelocity"),'value', '1');
                                                            add_line(strcat(location), 'EnableSendVelocity/1', 'ROS Send Velocity/Enable');
                                                            if (getSimulinkBlockHandle(strcat(location,"Lateral_Dynamics")) ~= -1)
                                                                add_line(strcat(location), 'Lateral_Dynamics/1', 'ROS Send Velocity/2');
                                                            else
                                                                add_block("simulink/Commonly Used Blocks/Constant", strcat(location,"constant"), 'value', '0');
                                                                add_line(strcat(location), 'constant/1', 'ROS Send Velocity/2');
                                                            end
                                                            size_blk = get_param(convertStringsToChars(strcat(location,"ROS Send Velocity")),'Position');
                                                            X = size_blk(1,1)+150;
                                                            Y = size_blk(1,2)-1600;
                                                            Width = 200;
                                                            Height = 100;
                                                            set_param(strcat(location,"ROS Send Velocity"),'Position',[X Y X+Width Y+Height]);
                                                        end

                                                        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%changing parameters
                                                        %%%%%%%%%%%%%%%%%%Parameters of Condition source
                                                        if(isfield(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition, 'Distance_RelativeObject') == 1 || isfield(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition, 'SimulationTimeCondition') == 1)
                                                            for h =1: length( models.worldmodel.object)
                                                                if((isfield(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition),"Distance_RelativeObject") == 1 && convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                                        .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Distance_RelativeObject) == ...
                                                                        convertCharsToStrings(models.worldmodel.object{h,1}.name)) ||  (isfield(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition),"SimulationTimeCondition") == 1 && convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                                        .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.SimulationTimeCondition) == ...
                                                                        convertCharsToStrings(models.worldmodel.object{h,1}.name))   &&     convertCharsToStrings(models.worldmodel.object{j,1}.name)  ~= name_ego)
                                                                    convertStringsToChars(strcat(location2,"/From4"))
                                                                    set_param(convertStringsToChars(strcat(location2,"/From4")),'GotoTag',convertStringsToChars(strcat("x_",Blockid(1,h) ) )  )
                                                                    set_param(convertStringsToChars(strcat(location2,"/From1")),'GotoTag',convertStringsToChars(strcat("y_",Blockid(1,h) ) )  )
                                                                    set_param(convertStringsToChars(strcat(location2,"/From3")),'GotoTag',convertStringsToChars(strcat("z_",Blockid(1,h) ) )  )
                                                                end
                                                            end
                                                            convertStringsToChars(strcat(location2,"/From4"))
                                                            set_param(convertStringsToChars(strcat(location2,"/From9")),'GotoTag',convertStringsToChars(strcat("x_",Blockid(1,j) ) )  )
                                                            set_param(convertStringsToChars(strcat(location2,"/From2")),'GotoTag',convertStringsToChars(strcat("y_",Blockid(1,j) ) )  )
                                                            set_param(convertStringsToChars(strcat(location2,"/From5")),'GotoTag',convertStringsToChars(strcat("z_",Blockid(1,j) ) )  )
                                                            if( isfield(trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                                .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition, 'Distance_RelativeObject') == 1)
                                                            set_param(convertStringsToChars(strcat(location2,"/Goto4")),'GotoTag', convertStringsToChars(strcat("D_",trajectory_type(1,z) ,Blockid(1,j) ) )  )

                                                            else
                                                                set_param(convertStringsToChars(strcat(location2,"/Goto4")),'GotoTag', convertStringsToChars(strcat("D_",trajectory_type(1,z) ,Blockid(1,j) ) )  )
                                                            end
                                                        end
                                                        if( isfield(trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                                .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition, 'TimeHeadWayCondition') == 1)
                                                            set_param(convertStringsToChars(strcat(location2,"/Goto4")),'GotoTag', convertStringsToChars(strcat("T_",trajectory_type(1,z) ,Blockid(1,j) ) )  )
                                                        end



        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Parameters of Condition trajetory
                                                        width = abs(str2num(trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                            .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.Target.value));
    %                                                     if (not(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
    %                                                             .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.dynamicsDimension) == "distance" && isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1, q}.Act{1,a}.ManeuverGroup.Maneuver{1, m}.Event{1, i}.StartTrigger.ConditionGroup.Condition, 'ByEntityCondition')==1 && isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1, q}.Act{1,a}.ManeuverGroup.Maneuver{1, m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.EntityCondition, 'RelativeDistanceCondition')==1) || (isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1, q}.Act{1,a}.ManeuverGroup.Maneuver{1, m}.Event{1, i}.StartTrigger.ConditionGroup.Condition, 'ByValueCondition')==1 &&  isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1, q}.Act{1,a}.ManeuverGroup.Maneuver{1, m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByValueCondition, 'SimulationTimeCondition')==0))
    %                                                         if (Blockname3=="Condition_trajectory")
    %                                                             Blockname6 ="";
    %                                                         else
    %                                                             Blockname6="/Condition_trajectory";
    %                                                         end
                                                        Blockname6="/Condition_trajectory";

                                                           if(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule.rule) == "lessThan")
                                                                %%%%%Parameters of Condition_trajectory
                                                                set_param(convertStringsToChars(strcat(location3,Blockname6,"/Gain2")),'Gain','-1')
                                                                set_param(convertStringsToChars(strcat(location3,Blockname6,"/Switch1"))...
                                                                    ,'Criteria','u2 > Threshold')
                                                                set_param(convertStringsToChars(strcat(location3,Blockname6,"/Switch1"))...
                                                                    ,'Threshold',...
                                                                    num2str(-1*str2num(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule.value)) )
                                                            end

                                                            if(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule.rule) == "greaterThan")
                                                                %%%%%Parameters of Condition_trajectory
                                                                set_param(convertStringsToChars(strcat(location3,Blockname6,"/Gain2")),'Gain','1')
                                                                set_param(convertStringsToChars(strcat(location3,Blockname6,"/Switch1"))...
                                                                    ,'Criteria','u2 >= Threshold')
                                                                set_param(convertStringsToChars(strcat(location3,Blockname6,"/Switch1"))...
                                                                    ,'Threshold',...
                                                                    num2str(str2num(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule.value)) )
                                                                %change constant to account for shift if step
                                                            end

                                                            if(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule.rule) == "equalTo")
                                                                %%%%%Parameters of Condition_trajectory
                                                                set_param(convertStringsToChars(strcat(location3,Blockname6,"/Gain2")),'Gain','1')
                                                                set_param(convertStringsToChars(strcat(location3,Blockname6,"/Switch1"))...
                                                                    ,'Criteria','u2 >= Threshold')
                                                                set_param(convertStringsToChars(strcat(location3,Blockname6,"/Switch1"))...
                                                                    ,'Threshold',...
                                                                    num2str(str2num(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule.value)) )
                                                                %change constant to account for shift if step
                                                            end

    %                                                         if (Blockname3=="Trajectory_input_turn_subsystem")
    %                                                             set_param(convertStringsToChars(strcat(location3,Blockname6,"/Switch1"))...
    %                                                                 ,'Criteria','u2 >= Threshold')
    %                                                             set_param(convertStringsToChars(strcat(location3,Blockname6,"/Switch1"))...
    %                                                                 ,'Threshold', '1')
    %                                                             set_param(convertStringsToChars(strcat(location3,Blockname6,"/Gain2")),'Gain','1')
    %                                                             set_param(convertStringsToChars(strcat(location3,Blockname6,"/From")),'GotoTag','V_out' );
    %                                                         end

                                                            if (isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1, q}.Act{1,a}.ManeuverGroup.Maneuver{1, m}.Event{1, i}.StartTrigger.ConditionGroup.Condition, 'ByEntityCondition')==1 && isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1, q}.Act{1,a}.ManeuverGroup.Maneuver{1, m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByEntityCondition.EntityCondition, 'SpeedCondition')==1 )
                                                                if (convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                                        .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Speed_RelativeObject) == "Ego")
                                                                    set_param(convertStringsToChars(strcat(location3,Blockname6,"/Gain2")),'Gain','1')
                                                                    set_param(convertStringsToChars(strcat(location3,Blockname6,"/From")),'GotoTag','velocity' );
                                                                else
                                                                    for h =1: length( models.worldmodel.object)
                                                                        if(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                                            .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Speed_RelativeObject) == ...
                                                                            convertCharsToStrings(models.worldmodel.object{h,1}.name))
                                                                            locat = strcat(name_simulink,convertCharsToStrings(models.worldmodel.object{h,1}.name),"/Dynamics_Empty/");
                                                                            add_block("simulink/Signal Routing/Goto", strcat(locat,"Velocity"),'GotoTag', 'Vel');
                                                                            set_param(strcat(locat,"Velocity"), 'TagVisibility', 'global');
                                                                            if (getSimulinkBlockHandle(strcat(locat,"Longitudinal_Dynamics")) ~= -1)
                                                                                add_line(strcat(locat), 'Longitudinal_Dynamics/1', 'Velocity/1');
                                                                            else
                                                                                add_line(strcat(locat), convertStringsToChars(strcat("Gain",int2str(j),"/1")), 'Velocity/1');
                                                                            end
    %                                                                         set_param(convertStringsToChars(strcat(location3,Blockname6,"/Gain2")),'Gain','1')
                                                                            set_param(convertStringsToChars(strcat(location3,Blockname6,"/From")),'GotoTag','Vel' );
                                                                        end
                                                                    end
                                                                end
                                                            end

                                                            if (isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1, q}.Act{1,a}.ManeuverGroup.Maneuver{1, m}.Event{1, i}.StartTrigger.ConditionGroup.Condition, 'ByValueCondition')==1 &&  isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1, q}.Act{1,a}.ManeuverGroup.Maneuver{1, m}.Event{1, i}.StartTrigger.ConditionGroup.Condition.ByValueCondition, 'SimulationTimeCondition')==1)
                                                                set_param(convertStringsToChars(strcat(location3,Blockname6,"/Gain2")),'Gain','1')
                                                                set_param(convertStringsToChars(strcat(location3,Blockname6,"/Switch1"))...
                                                                    ,'Criteria','u2 >= Threshold')
                                                                set_param(convertStringsToChars(strcat(location3,Blockname6,"/Switch1"))...
                                                                    ,'Threshold', '0.001')    
                                                                set_param(convertStringsToChars(strcat(location3,Blockname6,"/Switch2"))...
                                                                    ,'Criteria','u2 >= Threshold')
                                                                set_param(convertStringsToChars(strcat(location3,Blockname6,"/Switch2"))...
                                                                    ,'Threshold',trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule.value)
                                                                set_param(convertStringsToChars(strcat(location3,Blockname6,"/Constant5")) ,'value', trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule.value) 

                                                            end

                                                            if (Blockname3=="Trajectory_input_distance_subsystem")
                                                                set_param(convertStringsToChars(strcat(location3,Blockname6,"/Switch1"))...
                                                                    ,'Criteria','u2 >= Threshold')
                                                                set_param(convertStringsToChars(strcat(location3,Blockname6,"/Switch1"))...
                                                                    ,'Threshold', '0.001')
                                                                set_param(convertStringsToChars(strcat(location3,Blockname6,"/Gain2")),'Gain','1')
                                                            end

        %%%%%%%%%%%%%%%%%%%%%%% %%%%%Parameters of Trajectory_input
                                                        if (Blockname3=="Trajectory_input_sinusoidal_subsystem" || Blockname3=="Trajectory_input_turn_subsystem")
                                                            Blockname7 = "/Trajectory_input";
                                                            %switch
                                                            set_param(convertStringsToChars(strcat(location3,Blockname7,"/Switch3"))...
                                                            ,'Criteria','u2 >= Threshold')
                                                            set_param(convertStringsToChars(strcat(location3,Blockname7,"/Switch3"))...
                                                            ,'Threshold',...
                                                            convertStringsToChars(strcat("-",convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                            .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.value)))    )
                                                            %function
                                                            set_param(convertStringsToChars(strcat(location3,Blockname7,"/Cos")),'Function','cos')
                                                            %constants and gains
                                                            set_param(convertStringsToChars(strcat(location3,Blockname7,"/Constant3")),'Value',(trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                            .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.Target.value))
                                                            value1 = 4*str2num(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                            .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.value));
                                                            value2 = 2*pi/value1;
                                                            set_param(convertStringsToChars(strcat(location3,Blockname7,"/Gain5")),'Gain',(trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                            .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.Target.value))
                                                            set_param(convertStringsToChars(strcat(location3,Blockname7,"/Gain6")),'Gain',convertStringsToChars(num2str(value2))) 
                                                            set_param(convertStringsToChars(strcat(location3,Blockname7,"/Gain4")),'Gain',strcat("-",convertStringsToChars(num2str(value2)))   )                                                                                            

                                                        elseif (Blockname3=="Trajectory_input_distance_subsystem")
                                                            Blockname7="/Distance_condition";
                                                            set_param(convertStringsToChars(strcat(location3,Blockname7,"/Current_speed")),'GotoTag',strcat('V_in_', num2str(a)) );
                                                            set_param(convertStringsToChars(strcat(location3,Blockname7,"/Distance_wanted")), 'value', trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Condition.Rule.value);
                                                            set_param(convertStringsToChars(strcat(location3,Blockname7,"/Ego_speed")), 'value', trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.Target.value );
                                                            set_param((strcat(location3,Blockname7,"/Current_distance")),'Gototag',   convertStringsToChars(strcat("D_",trajectory_type(1,z) ,Blockid(1,j) ) )    )
                                                            if (i<p_L)
                                                              set_param(convertStringsToChars(strcat(location3,Blockname7,"/Switch7"))...
                                                                    ,'Threshold',...
                                                                    trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i+1}.Attributes.name).Condition.Rule.value)
                                                            else
                                                               h = get_param(convertStringsToChars(strcat(location3,Blockname7,'/Switch7')),'LineHandles');
                                                               delete_line(h.Inport(1));
                                                               add_line(convertStringsToChars(location3), convertStringsToChars(strcat("Switch6","/1")),convertStringsToChars(strcat("Switch7","/1")))
                                                            end

                                                        elseif (Blockname3=="Trajectory_input_step_subsystem")
                                                            Blockname7="/Trajectory_input";
                                                            set_param(convertStringsToChars(strcat(location3,Blockname7,"/speed")), 'value', trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.Target.value )

                                                        elseif (Blockname3=="Trajectory_input_linear_subsystem")
                                                            Blockname7="/Change_speed"; 
                                                            set_param(convertStringsToChars(strcat(location3,Blockname7,"/Desired_speed")), 'value', trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.Target.value );
                                                            set_param(convertStringsToChars(strcat(location3,Blockname7,"/Acceleration")), 'value', trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}...
                                                                    .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.value)
                                                            ini= str2double(trajectory_variable.(models.worldmodel.object{j, 1}.name).init)/3.6;
                                                            set_param(convertStringsToChars(strcat(location3,Blockname7,"/Memory")),'InitialCondition',num2str(ini) );
                                                            set_param(convertStringsToChars(strcat(location3,Blockname7,"/From1")),'GotoTag',strcat('V_in_', num2str(a)) )

                                                        end

                                                            %used in AfterTermination
                                                            b(i,1) = convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name)...
                                                            .(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name).Dynamics.value);


    %                                                             if( isfield(trajectory_variable.(models.worldmodel.object{j, 1}.name)...
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


                                                    %Checking for Aftertermination field
                                                    if(isfield(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,q}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name)),'StoryboardElementStateCondition') == 1)
                                                        set_param(convertStringsToChars(strcat(location3,Blockname6,"/Constant1")),'Value', b(i-1,1));

                                                    end


                                                    end %if statement Distance_RelativeObject check
                                                end %if statement Objects check
                                            end %if statement lateral check
                                        end %for loop number of events (trajectories)
                                    end %if statement which story belongs to which object
                                end %numb er of maneuvers
                            end %if statement which object has trajectories
                        end %Check if object has which event
                    end %if statement to check existence of object in trajectory_variable
                end
            end %if statement to check existence of event in trajectory_variable

        end
    
    end
end% main for loop

disp('LATERAL DYNAMICS ADDED')





end
