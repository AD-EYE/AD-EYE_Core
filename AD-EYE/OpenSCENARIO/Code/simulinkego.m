function simulinkego(nameSimulink,models, nameEgo,StructPex, StructOpenSCENARIO)

    lib_path = "../../lib/";
    openscenario_path = pwd;

    for i = 1:length(models.worldmodel.object  ) %Declare number of objects in xml file %main for loop

        if(convertCharsToStrings(models.worldmodel.object{i, 1}.name  ) == nameEgo)
            locationSimulinkObject = strcat(nameSimulink,convertCharsToStrings(models.worldmodel.object{i,1}.name) ,"/");

            %delete Terminators
            f =  Simulink.FindOptions('SearchDepth',1);
            b1 = Simulink.findBlocksOfType(convertStringsToChars(locationSimulinkObject),'Terminator',f);
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
                    h = get_param(convertStringsToChars(strcat(locationSimulinkObject,location1(p,1))),'LineHandles');
                    for x = 1:length(h.Outport)
                        if((h.Outport(x)) ~= -1)
                            delete_line(h.Outport(x) )
                        end
                    end
                end

            end

            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Simulink_state_NEW
            locationSimulinkObject = strcat(nameSimulink,convertCharsToStrings(models.worldmodel.object{i,1}.name) ,"/");
            blockMainBlock = "Main_block";
            locationMainBlock = convertStringsToChars(strcat(location,blockMainBlock));
            if (getSimulinkBlockHandle(locationMainBlock) == -1)
                cd(lib_path);
                add_block(strcat("adeye_lib/",blockMainBlock),locationMainBlock );
                cd(openscenario_path);
                %change location
                size_blk = get_param(convertStringsToChars(strcat(locationSimulinkObject,"SELF_Demux")),'Position');
                X = size_blk(1,1)+600;
                Y = size_blk(1,2)+100;
                Width = 400;
                Height = 2000;
                set_param(locationMainBlock,'Position',[X Y X+Width Y+Height]);
                set_param(locationMainBlock,'LinkStatus','inactive');
            end

            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Creating dynamics empty
            blockDynamicsEmpty = "Dynamics_Empty";
            blockObject = convertStringsToChars(strcat("STATE_",convertCharsToStrings(models.worldmodel.object{i,1}.name), "_rc"));
            locationDynamicsEmpty =convertStringsToChars(strcat(location,blockDynamicsEmpty));
            locationObject =convertStringsToChars(strcat(location,blockObject));
            if (getSimulinkBlockHandle(locationDynamicsEmpty) ~= -1)
                h = get_param(locationDynamicsEmpty,'LineHandles');
                if((h.Outport(1)) ~= -1)
                    delete_line(h.Outport(1) )
                end
                delete_block(locationDynamicsEmpty)
            end

            if (getSimulinkBlockHandle(locationDynamicsEmpty) == -1)
                cd(lib_path);
                add_block(convertStringsToChars(strcat("adeye_lib/",blockDynamicsEmpty)),locationDynamicsEmpty);
                cd(openscenario_path);
                %change location
                size_blk = get_param(locationObject,'Position');
                X = size_blk(1,1)-550;
                Y = size_blk(1,2)-60;
                Width =120;
                Height =260;
                set_param(locationDynamicsEmpty,'Position',[X Y X+Width Y+Height]);
                set_param(locationDynamicsEmpty,'LinkStatus','inactive')
                add_line(convertStringsToChars(location), convertStringsToChars(strcat(blockDynamicsEmpty,"/1")),....
                    convertStringsToChars(strcat(Blockname4,"/1" )) ) %connect blocks
            end


            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Connecting lines

            %create variable with all the names of input port of the Main_block and Dynamic_Empty
            splittedPathToStepBlock = find_system(convertStringsToChars(strcat(nameSimulink,nameEgo,"/", blockMainBlock)),'SearchDepth',1,'BlockType','Inport');
            splittedPathToStepBlock =convertCharsToStrings(splittedPathToStepBlock);
            q = find_system(convertStringsToChars(strcat(nameSimulink,nameEgo,"/", blockDynamicsEmpty)),'SearchDepth',1,'BlockType','Inport');
            q1 =convertCharsToStrings(q);
            s1 = get_param(convertStringsToChars(strcat(locationSimulinkObject,blockMainBlock)),'PortConnectivity');
            s2 = get_param(convertStringsToChars(strcat(locationSimulinkObject,blockDynamicsEmpty)),'PortConnectivity');
            s = s1;

            x = length(splittedPathToStepBlock);
            for k = 1:length(splittedPathToStepBlock1)
                splittedPathToStepBlock(k,1) = strrep(splittedPathToStepBlock(k,1), "//","/");
            end
            for j =1:length(q1)
                x = x+1;
                splittedPathToStepBlock(x,1) = strrep(q1(j,1), "//","/");
                s(x,1) = s2(j,1);
            end

            %Create another varable with all the names of input port of the Main_block for comparision
            %h2 is variable h1 stripped down
            splittedPathToStepBlock2 = splittedPathToStepBlock;
            for k = 1:length(splittedPathToStepBlock)
                for p =length(splittedPathToStepBlock):-1:0
                    splittedPathToStepBlock2(k,1) = strrep(splittedPathToStepBlock2(k,1), strcat("/",blockMainBlock),"");
                    splittedPathToStepBlock2(k,1) = strrep(splittedPathToStepBlock2(k,1), strcat("/",blockDynamicsEmpty),"");
                end
                splittedPathToStepBlock3 = convertStringsToChars(splittedPathToStepBlock2(k,1));
                if (splittedPathToStepBlock3(length(splittedPathToStepBlock3)-1: end -1) == '_') %check if the end is _x or _xx
                    splittedPathToStepBlock2(k,1) = splittedPathToStepBlock3(1: end -2);
                    splittedPathToStepBlock2(k,1) = convertCharsToStrings(splittedPathToStepBlock2(k,1));
                else
                    splittedPathToStepBlock2(k,1) = splittedPathToStepBlock3(1: end -3);
                    splittedPathToStepBlock2(k,1) = convertCharsToStrings(splittedPathToStepBlock2(k,1));
                end
            end


            %create variable with all the names of input port of the Main_block
            z=1;
            for k = 1:length(splittedPathToStepBlock)
                existing(k,1) = getSimulinkBlockHandle(convertStringsToChars(splittedPathToStepBlock2(k,1)));
                if(existing(k,1) ~=-1)
                    splittedPathToStepBlock2(k,1) =  strrep(splittedPathToStepBlock2(k,1), strcat(nameSimulink,nameEgo,"/"),"");
                    splittedPathToStepBlock2(k,1) =  strrep(splittedPathToStepBlock2(k,1), strcat(nameSimulink,nameEgo,"/"),"");
                    if (k~=1 && splittedPathToStepBlock2(k,1) == splittedPathToStepBlock2(k-1,1)) % to know if we are at the first port of the block or at a following one
                        z = z+1;
                    elseif (k~=1)
                        z = 1;
                    end
                    splittedPathToStepBlock2(k,1) = strcat(splittedPathToStepBlock2(k,1), "/", int2str(z)); 
                    %see if Main_block is already connected
                    if (s(k,1).SrcBlock == -1 && k <= 8)
                        %get Main_block inports name
                        sim=get_param(strcat(locationSimulinkObject,blockMainBlock),'Handle');
                        handles=find_system(sim, 'LookUnderMasks', 'on', 'FollowLinks', 'on', 'SearchDepth', 1, 'BlockType', 'Inport');
                        portInfo=[get_param(handles,'Name')];
                        inport=portInfo(k);
                        Name=inport{1,1};
                        Name=str2num(Name(12:end));
                        a=splittedPathToStepBlock2(k,1);
                        a=convertStringsToChars(a);
                        splittedPathToStepBlock2(k,1)=a(1:end-2);
                        splittedPathToStepBlock2(k,1) = strcat(splittedPathToStepBlock2(k,1), "/", int2str(Name));
                        add_line(location, splittedPathToStepBlock2(k,1),strcat(blockMainBlock,"/",int2str(k)))
                    elseif(s(k,1).SrcBlock == -1 && k <= length(s1) && k>8)
                        add_line(location, splittedPathToStepBlock2(k,1),strcat(blockMainBlock,"/",int2str(k)))
                    elseif(s(k,1).SrcBlock == -1 && k>8 )
                        add_line(location, splittedPathToStepBlock2(k,1),strcat(blockDynamicsEmpty,"/",int2str(k-length(s1))))
                    end
                end
                splittedPathToStepBlock2(k,1) =  strrep(splittedPathToStepBlock2(k,1), strcat("/", int2str(z)),"");
            end

            %Chaning Rain constant
            blockRain = "R";
            locationBlockRain = convertStringsToChars(strcat(locationSimulinkObject,blockMainBlock,"/",blockRain));
            if (StructPex.Experiment.Attributes.WeatherTypeName == convertStringsToChars("Rain"))
                R = str2double(StructOpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.GlobalAction.EnvironmentAction.Environment.Weather.Precipitation.Attributes.intensity);
                set_param(locationBlockRain,'Value',num2str(R));
            end

            Simulink.BlockDiagram.expandSubsystem(locationMainBlock,'CreateArea','On')
        end %if statement checking which object in Prescan is the ego vehicle
    end %for loop over all Prescan objects

end %function end
