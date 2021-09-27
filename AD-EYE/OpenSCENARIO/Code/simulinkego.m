function simulinkego(nameSimulink,models, nameEgo,StructPex, StructOpenSCENARIO)

    lib_path = "../../lib/";
    openscenario_path = pwd;

    for i = 1:length(models.worldmodel.object  ) %Declare number of objects in xml file %main for loop

        if(convertCharsToStrings(models.worldmodel.object{i, 1}.name  ) == nameEgo)
            locationSimulinkObject = strcat(nameSimulink,convertCharsToStrings(models.worldmodel.object{i,1}.name) ,"/");

            %delete Terminators
            findInteger =  Simulink.FindOptions('SearchDepth',1);
            findBlock = Simulink.findBlocksOfType(convertStringsToChars(locationSimulinkObject),'Terminator',findInteger);
            findBlock = convertCharsToStrings(getfullname(findBlock));

            if(isempty(findBlock) ~= 1)
                for x = 1:length(findBlock(:,1))
                    ports(x,1)=get_param(findBlock(x,1),'PortConnectivity');
                    portName = get_param(ports(x,1).SrcBlock,'name');
                    %location of where the terminators are connected to
                    locationPortName(x,1)= convertCharsToStrings(portName);
                    if(getSimulinkBlockHandle(findBlock(x,1)) ~= -1)
                        delete_block(findBlock{x,1})
                    end
                end
                %delete_line
                for p = 1:length(locationPortName)
                    line = get_param(convertStringsToChars(strcat(locationSimulinkObject,locationPortName(p,1))),'LineHandles');
                    for x = 1:length(line.Outport)
                        if((line.Outport(x)) ~= -1)
                            delete_line(line.Outport(x) )
                        end
                    end
                end

            end

            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Simulink_state_NEW
            locationSimulinkObject = strcat(nameSimulink,convertCharsToStrings(models.worldmodel.object{i,1}.name) ,"/");
            blockMainBlock = "Main_block";
            locationMainBlock = convertStringsToChars(strcat(locationSimulinkObject,blockMainBlock));
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
            locationDynamicsEmpty =convertStringsToChars(strcat(locationSimulinkObject,blockDynamicsEmpty));
            locationObject =convertStringsToChars(strcat(locationSimulinkObject,blockObject));
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
                add_line(convertStringsToChars(locationSimulinkObject), convertStringsToChars(strcat(blockDynamicsEmpty,"/1")),....
                    convertStringsToChars(strcat(blockObject,"/1" )) ) %connect blocks
            end


            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Connecting lines

            %create variable with all the names of input port of the Main_block and Dynamic_Empty
            splittedPathToStepBlock = find_system(convertStringsToChars(strcat(nameSimulink,nameEgo,"/", blockMainBlock)),'SearchDepth',1,'BlockType','Inport');
            splittedPathToStepBlock =convertCharsToStrings(splittedPathToStepBlock);
            inports = find_system(convertStringsToChars(strcat(nameSimulink,nameEgo,"/", blockDynamicsEmpty)),'SearchDepth',1,'BlockType','Inport');
            inportsString =convertCharsToStrings(inports);
            portsMainBlock = get_param(convertStringsToChars(strcat(locationSimulinkObject,blockMainBlock)),'PortConnectivity');
            portsDynamicsEmpty = get_param(convertStringsToChars(strcat(locationSimulinkObject,blockDynamicsEmpty)),'PortConnectivity');
            ports = portsMainBlock;

            x = length(splittedPathToStepBlock);
            for k = 1:length(splittedPathToStepBlock)
                splittedPathToStepBlock(k,1) = strrep(splittedPathToStepBlock(k,1), "//","/");
            end
            for j =1:length(inportsString)
                x = x+1;
                splittedPathToStepBlock(x,1) = strrep(inportsString(j,1), "//","/");
                ports(x,1) = portsDynamicsEmpty(j,1);
            end

            %Create another variable with all the names of input port of the Main_block for comparision
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
                    if (ports(k,1).SrcBlock == -1 && k <= 8)
                        %get Main_block inports name
                        getHandle=get_param(strcat(locationSimulinkObject,blockMainBlock),'Handle');
                        handles=find_system(getHandle, 'LookUnderMasks', 'on', 'FollowLinks', 'on', 'SearchDepth', 1, 'BlockType', 'Inport');
                        portInfo=[get_param(handles,'Name')];
                        inport=portInfo(k);
                        Name=inport{1,1};
                        Name=str2num(Name(12:end));
                        path=splittedPathToStepBlock2(k,1);
                        path=convertStringsToChars(path);
                        splittedPathToStepBlock2(k,1)=path(1:end-2);
                        splittedPathToStepBlock2(k,1) = strcat(splittedPathToStepBlock2(k,1), "/", int2str(Name));
                        add_line(locationSimulinkObject, splittedPathToStepBlock2(k,1),strcat(blockMainBlock,"/",int2str(k)))
                    elseif(ports(k,1).SrcBlock == -1 && k <= length(portsMainBlock) && k>8)
                        add_line(locationSimulinkObject, splittedPathToStepBlock2(k,1),strcat(blockMainBlock,"/",int2str(k)))
                    elseif(ports(k,1).SrcBlock == -1 && k>8 )
                        add_line(locationSimulinkObject, splittedPathToStepBlock2(k,1),strcat(blockDynamicsEmpty,"/",int2str(k-length(portsMainBlock))))
                    end
                end
                splittedPathToStepBlock2(k,1) =  strrep(splittedPathToStepBlock2(k,1), strcat("/", int2str(z)),"");
            end

            %Chaning Rain constant
            blockRain = "fi_lidar_rain_intensity";
            locationBlockRain = convertStringsToChars(strcat(locationSimulinkObject,blockMainBlock,"/",blockRain));
            if (StructPex.Experiment.Attributes.WeatherTypeName == convertStringsToChars("Rain"))
                R = str2double(StructOpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.GlobalAction.EnvironmentAction.Environment.Weather.Precipitation.Attributes.intensity);
                set_param(locationBlockRain,'Value',num2str(R));
            end

            Simulink.BlockDiagram.expandSubsystem(locationMainBlock,'CreateArea','On')
            
            % Send ROS target value of the Ego car
            add_block("simulink/Commonly Used Blocks/Constant", strcat(locationSimulinkObject,"EgoSpeed"),'value', get_field(StructOpenSCENARIO, "StructOpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1,1}.PrivateAction{1,2}.LongitudinalAction.SpeedAction.SpeedActionTarget.AbsoluteTargetSpeed.Attributes.value"));
            add_block("robotlib/Set Parameter", strcat(locationSimulinkObject, "ROS Parameter"));
            add_line(locationSimulinkObject, "EgoSpeed/1", "ROS Parameter/1");
            set_param(strcat(locationSimulinkObject,"ROS Parameter"), "ParameterSource", "specify your own");
            set_param(strcat(locationSimulinkObject,"ROS Parameter"), "ParameterName", "/initial_speed_0");
            
        end %if statement checking which object in Prescan is the ego vehicle
    end %for loop over all Prescan objects

end %function end
