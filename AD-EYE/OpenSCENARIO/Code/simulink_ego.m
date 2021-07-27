function simulink_ego(name_simulink,models, name_ego,Struct_pex, Struct_OpenSCENARIO)

    lib_path = "../../lib/";
    openscenario_path = pwd;

    for i = 1:length(models.worldmodel.object  ) %Declare number of objects in xml file %main for loop

        if(convertCharsToStrings(models.worldmodel.object{i, 1}.name  ) == name_ego)
            location = strcat(name_simulink,convertCharsToStrings(models.worldmodel.object{i,1}.name) ,"/");

            %delete Terminators
            f =  Simulink.FindOptions('SearchDepth',1);
            b1 = Simulink.findBlocksOfType(convertStringsToChars(location),'Terminator',f);
            b2 = convertCharsToStrings(getfullname(b1));

            if(isempty(b2) ~= 1)
                for x = 1:length(b2(:,1))
                    S1(x,1)=get_param(b2(x,1),'PortConnectivity');
                    S2 = get_param(S1(x,1).SrcBlock,'name');
                    %location of where the terminators where connected to
                    location1(x,1)= convertCharsToStrings(S2);
                    if(getSimulinkBlockHandle(b2(x,1)) ~= -1)
                        delete_block(b2{x,1})
                    end
                end
                %delete_line
                for p = 1:length(location1)
                    h = get_param(convertStringsToChars(strcat(location,location1(p,1))),'LineHandles');
                    for x = 1:length(h.Outport)
                        if((h.Outport(x)) ~= -1)
                            delete_line(h.Outport(x) )
                        end
                    end
                end

            end

            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Simulink_state_NEW
            location = strcat(name_simulink,convertCharsToStrings(models.worldmodel.object{i,1}.name) ,"/");
            Blockname0 = "Main_block";
            location0 = convertStringsToChars(strcat(location,Blockname0));
            if (getSimulinkBlockHandle(location0) == -1)
                cd(lib_path);
                add_block(strcat("adeye_lib/",Blockname0),location0 );
                cd(openscenario_path);
                %change location
                size_blk = get_param(convertStringsToChars(strcat(location,"SELF_Demux")),'Position');
                X = size_blk(1,1)+600;
                Y = size_blk(1,2)+100;
                Width = 400;
                Height = 2000;
                set_param(location0,'Position',[X Y X+Width Y+Height]);
                set_param(location0,'LinkStatus','inactive');
            end

            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Creating dynamics empty
            Blockname3 = "Dynamics_Empty";
            Blockname4 = convertStringsToChars(strcat("STATE_",convertCharsToStrings(models.worldmodel.object{i,1}.name), "_rc"));
            location3 =convertStringsToChars(strcat(location,Blockname3));
            location4 =convertStringsToChars(strcat(location,Blockname4));
            if (getSimulinkBlockHandle(location3) ~= -1)
                h = get_param(location3,'LineHandles');
                if((h.Outport(1)) ~= -1)
                    delete_line(h.Outport(1) )
                end
                delete_block(location3)
            end

            if (getSimulinkBlockHandle(location3) == -1)
                cd(lib_path);
                add_block(convertStringsToChars(strcat("adeye_lib/",Blockname3)),location3);
                cd(openscenario_path);
                %change location
                size_blk = get_param(location4,'Position');
                X = size_blk(1,1)-550;
                Y = size_blk(1,2)-60;
                Width =120;
                Height =260;
                set_param(location3,'Position',[X Y X+Width Y+Height]);
                set_param(location3,'LinkStatus','inactive')
                
                %if there is an initial_speed
                if(field_exists(Struct_OpenSCENARIO,"Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1,1}.Action{1,1}.Longitudinal.Speed.Initial.Attributes.value"))
                    initial_speed = convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1,1}.Action{1,1}.Longitudinal.Speed.Initial.Attributes.value);
                    step_time = convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1,1}.Action{1,1}.Longitudinal.Speed.Initial.Attributes.time);
                    %add the new block to define the initial speed
                    Blockname6 = "Initial_speed";
                    location6 =convertStringsToChars(strcat(location3,'/',Blockname6));
                    add_block(convertCharsToStrings(strcat("OpenSCENARIO/",Blockname6)), location6);
                    add_condition=1;
                    
                    %delete line which link SELF_Demux to Minimalistic Dynamics block
                    location7 =convertStringsToChars(strcat(location3,'/Subsystem1'));
                    h = get_param(location7,'LineHandles');
                    delete_line(h.Inport(1));
                    
                    %Change the size and the position of the Initial_speed
                    %block
                    size_blk = get_param(location6,'Position');
                    X = size_blk(1,1)-550;
                    Y = size_blk(1,2)+130;
                    Width =80;
                    Height =120;
                    set_param(location6,'Position',[X Y X+Width Y+Height]);
                    
                    %Set the iniatial speed value
                    add_block("simulink/Commonly Used Blocks/Constant", strcat(location3,"/Speed"),"Value", initial_speed);
                    
                    location9 =convertStringsToChars(strcat(location3,'/',"Speed"));
                    size_blk = get_param(location9,'Position');
                    X = size_blk(1,1)-700;
                    Y = size_blk(1,2)+130;
                    set_param(location9,'Position',[X Y X+20 Y+20]);
                    add_line(convertStringsToChars(location3), "Speed/1", "Initial_speed/1");
                    
                    %Set the step time
                    add_block("simulink/Commonly Used Blocks/Constant", strcat(location3,"/Step_time"),"Value", step_time);
                    
                    location10 =convertStringsToChars(strcat(location3,'/',"Step_time"));
                    size_blk = get_param(location10,'Position');
                    X = size_blk(1,1)-700;
                    Y = size_blk(1,2)+290;
                    set_param(location10,'Position',[X Y X+20 Y+20]);
                    add_line(convertStringsToChars(location3), "Step_time/1", "Initial_speed/3");
                    
                    %link the new block with others
                    add_line(convertStringsToChars(location3), "Initial_speed/1", "Subsystem1/1");
                    add_line(convertStringsToChars(location3),"SELF_Demux_10/1","Initial_speed/2");
    
                end
                
                add_line(convertStringsToChars(location), convertStringsToChars(strcat(Blockname3,"/1")),....
                    convertStringsToChars(strcat(Blockname4,"/1" )) ) %connect blocks
            end


            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Connecting lines

            %create variable with all the names of input port of the Main_block and Dynamic_Empty
            h = find_system(convertStringsToChars(strcat(name_simulink,name_ego,"/", Blockname0)),'SearchDepth',1,'BlockType','Inport');
            h1 =convertCharsToStrings(h);
            q = find_system(convertStringsToChars(strcat(name_simulink,name_ego,"/", Blockname3)),'SearchDepth',1,'BlockType','Inport');
            q1 =convertCharsToStrings(q);
            s1 = get_param(convertStringsToChars(strcat(location,Blockname0)),'PortConnectivity');
            s2 = get_param(convertStringsToChars(strcat(location,Blockname3)),'PortConnectivity');
            s = s1;

            x = length(h1);
            for k = 1:length(h1)
                h1(k,1) = strrep(h1(k,1), "//","/");
            end
            for j =1:length(q1)
                x = x+1;
                h1(x,1) = strrep(q1(j,1), "//","/");
                s(x,1) = s2(j,1);
            end

            %Create another varable with all the names of input port of the Main_block for comparision
            %h2 is variable h1 stripped down
            h2 = h1;
            for k = 1:length(h1)
                for p =length(h1):-1:0
                    h2(k,1) = strrep(h2(k,1), strcat("/",Blockname0),"");
                    h2(k,1) = strrep(h2(k,1), strcat("/",Blockname3),"");
                end
                h3 = convertStringsToChars(h2(k,1));
                if (h3(length(h3)-1: end -1) == '_') %check if the end is _x or _xx
                    h2(k,1) = h3(1: end -2);
                    h2(k,1) = convertCharsToStrings(h2(k,1));
                else
                    h2(k,1) = h3(1: end -3);
                    h2(k,1) = convertCharsToStrings(h2(k,1));
                end
            end


            %create variable with all the names of input port of the Main_block
            z=1;
            for k = 1:length(h1)
                existing(k,1) = getSimulinkBlockHandle(convertStringsToChars(h2(k,1)));
                if(existing(k,1) ~=-1)
                    h2(k,1) =  strrep(h2(k,1), strcat(name_simulink,name_ego,"/"),"");
                    h2(k,1) =  strrep(h2(k,1), strcat(name_simulink,name_ego,"/"),"");
                    if (k~=1 && h2(k,1) == h2(k-1,1)) % to know if we are at the first port of the block or at a following one
                        z = z+1;
                    elseif (k~=1)
                        z = 1;
                    end
                    h2(k,1) = strcat(h2(k,1), "/", int2str(z));                           
                    %see if Main_block is already connected
                    if(s(k,1).SrcBlock == -1 && k <= length(s1))
                        add_line(location, h2(k,1),strcat(Blockname0,"/",int2str(k)))
                    elseif(s(k,1).SrcBlock == -1 )
                        add_line(location, h2(k,1),strcat(Blockname3,"/",int2str(k-length(s1))))
                    end
                end
                h2(k,1) =  strrep(h2(k,1), strcat("/", int2str(z)),"");
            end

            %Chaning Rain constant
            Blockname1 = "R";
            location1 = convertStringsToChars(strcat(location,Blockname0,"/",Blockname1));
            if (Struct_pex.Experiment.Attributes.WeatherTypeName == convertStringsToChars("Rain"))
                R = str2double(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Global.SetEnvironment.Environment.Weather.Precipitation.Attributes.intensity);
                set_param(location1,'Value',num2str(R));
            end

            Simulink.BlockDiagram.expandSubsystem(location0,'CreateArea','On')
        end %if statement checking which object in Prescan is the ego vehicle
    end %for loop over all Prescan objects

end %function end
