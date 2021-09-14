function   trajectorylabels(velocityVariable,models,name_simulink)
ERROR = 1;

for i = 1:length(velocityVariable(:,1))
    
    for k = 1:length(models.worldmodel.object)
        if(velocityVariable(i,1) == convertCharsToStrings(models.worldmodel.object{k, 1}.name))
            
            locationSimulinkObject = strcat(name_simulink,convertCharsToStrings(models.worldmodel.object{k,1}.name),"/");
            for x = 1:6
                blockId1 = int2str(x);
                blockTerminator = "Terminator_";
                locationBlockTerminator = convertStringsToChars(strcat(locationSimulinkObject,blockTerminator,blockId1));
                locationPortTerminator = convertStringsToChars(strcat(blockTerminator,blockId1,"/1"));
                locationBlockSelfDemux = convertStringsToChars(strcat("SELF_Demux/",blockId1));                
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%adding block Goto
                blockPosition = ["x_","y_","z_","Rotx_","Roty_","Rotz_"];
                blockId2 = int2str(k);
                locationBlockPosition =convertStringsToChars(strcat(locationSimulinkObject,blockPosition(1,x),blockId2));
                if (getSimulinkBlockHandle(locationBlockPosition) == -1)
                    add_block('simulink/Signal Routing/Goto',locationBlockPosition)
                    %change position of constant block
                    height = 20*x;
                    locationSelfDemux = convertStringsToChars(strcat(locationSimulinkObject,"SELF_Demux"));
                    sizeBlock = get_param(locationSelfDemux,'Position');
                    X = sizeBlock(1,1)+150;
                    Y = sizeBlock(1,2)-25+height;
                    WIDTH = 50;
                    HEIGHT = 26;
                    set_param(locationBlockPosition,'Position',[X Y X+WIDTH Y+HEIGHT]);
                end                
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%delete Terminators
                properties =  Simulink.FindOptions('SearchDepth',1);
                findTerminators = Simulink.findBlocksOfType(convertStringsToChars(locationSimulinkObject),'Terminator',properties);
                findTerminatorNames = convertCharsToStrings(getfullname(findTerminators));                    
                if(isempty(findTerminatorNames) ~= 1)
                    for q  = 1:length(findTerminatorNames(:,1))
                        S1=get_param(findTerminatorNames(q,1),'PortConnectivity');
                        S2 = get_param(S1.SrcBlock,'name');
                        %location of where the terminators where connected to
                        locationBlockSelfDemux= convertCharsToStrings(S2);
                        if(getSimulinkBlockHandle(findTerminatorNames(q,1)) ~= -1)
                            delete_block(findTerminatorNames(q,1))
                        end
                    end
                    %delete_line
                    for p = 1:length(locationBlockSelfDemux)
                        h = get_param(convertStringsToChars(strcat(locationSimulinkObject,locationBlockSelfDemux(p,1))),'LineHandles');
                        for q = 1:length(h.Outport)
                            if((h.Outport(q)) ~= -1)
                                delete_line(h.Outport(q) )
                            end
                        end
                    end                        
                end          
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% %adding lines together
                %only add lines if gain does not have a connection
                s= get_param(convertStringsToChars(strcat(locationSimulinkObject,"SELF_Demux")),'PortConnectivity');                
                if(isempty(s(x+1,1).DstBlock) ==1)
                    add_line(convertStringsToChars(locationSimulinkObject),convertStringsToChars(strcat("SELF_Demux/",blockId1))...
                        ,convertStringsToChars(strcat(blockPosition(1,x),blockId2,"/1")) )
                    ERROR = 0;
                end                
                set_param(convertStringsToChars(strcat(locationSimulinkObject,blockPosition(1,x),blockId2)),'Gototag',convertStringsToChars(strcat(blockPosition(1,x),blockId2)) )
                set_param(convertStringsToChars(strcat(locationSimulinkObject,blockPosition(1,x),blockId2)),'TagVisibility','global' )
                
            end %of for loop
        end
    end 
end
   
    if(ERROR == 1)
        disp('Labels not added/not connected');
    else
        
        disp('Labels added/connected');
    end
    
end