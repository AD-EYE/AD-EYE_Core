function   trajectory_labels(Velocity_variable,models,name_simulink);
ERROR = 1;

for i = 1:length(Velocity_variable(:,1))
    
    for k = 1:length(models.worldmodel.object)
        if(Velocity_variable(i,1) == convertCharsToStrings(models.worldmodel.object{k, 1}.name))
            
            location = strcat(name_simulink,convertCharsToStrings(models.worldmodel.object{k,1}.name),"/");
            for x = 1:6
                Blockid1 = int2str(x);
                Blockname1 = "Terminator_";
                location1 = convertStringsToChars(strcat(location,Blockname1,Blockid1));
                location2 = convertStringsToChars(strcat(Blockname1,Blockid1,"/1"));
                location3 = convertStringsToChars(strcat("SELF_Demux/",Blockid1));                
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%adding block Goto
                Blockname2 = ["x_","y_","z_","Rotx_","Roty_","Rotz_"];
                Blockid2 = int2str(k);
                location5 =convertStringsToChars(strcat(location,Blockname2(1,x),Blockid2));
                if (getSimulinkBlockHandle(location5) == -1)
                    add_block('simulink/Signal Routing/Goto',location5)
                    %change position of constant block
                    height = 20*x;
                    location4 = convertStringsToChars(strcat(location,"SELF_Demux"));
                    size_blk = get_param(location4,'Position');
                    X = size_blk(1,1)+150;
                    Y = size_blk(1,2)-25+height;
                    Width = 50;
                    Height = 26;
                    set_param(location5,'Position',[X Y X+Width Y+Height]);
                end                
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%delete Terminators
                    f =  Simulink.FindOptions('SearchDepth',1);
                    b1 = Simulink.findBlocksOfType(convertStringsToChars(location),'Terminator',f);
                    b2 = convertCharsToStrings(getfullname(b1));                    
                    if(isempty(b2) ~= 1)
                        for q  = 1:length(b2(:,1))
                            S1=get_param(b2(q,1),'PortConnectivity');
                            S2 = get_param(S1.SrcBlock,'name');
                            %location of where the terminators where connected to
                            location3= convertCharsToStrings(S2);
                            if(getSimulinkBlockHandle(b2(q,1)) ~= -1)
                                delete_block(b2(q,1))
                            end
                        end
                        %delete_line
                        for p = 1:length(location3)
                            h = get_param(convertStringsToChars(strcat(location,location3(p,1))),'LineHandles');
                            for q = 1:length(h.Outport)
                                if((h.Outport(q)) ~= -1)
                                    delete_line(h.Outport(q) )
                                end
                            end
                        end                        
                    end          
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% %adding lines together
                %only add lines if gain does not have a connection
                s= get_param(convertStringsToChars(strcat(location,"SELF_Demux")),'PortConnectivity');                
                if(isempty(s(x+1,1).DstBlock) ==1)
                    add_line(convertStringsToChars(location),convertStringsToChars(strcat("SELF_Demux/",Blockid1))...
                        ,convertStringsToChars(strcat(Blockname2(1,x),Blockid2,"/1")) )
                    ERROR = 0;
                end                
                set_param(convertStringsToChars(strcat(location,Blockname2(1,x),Blockid2)),'Gototag',convertStringsToChars(strcat(Blockname2(1,x),Blockid2)) )
                set_param(convertStringsToChars(strcat(location,Blockname2(1,x),Blockid2)),'TagVisibility','global' )
                
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