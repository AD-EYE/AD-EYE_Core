%%%%%%%%%%%%%%%%%%%%Creating initial speed
%Creating simulink block for initial velocity
function initial_velocity_dynamics(name,models,Struct_OpenSCENARIO,Velocity_variable)


for j =1:length(models.worldmodel.object) %main for loop
    
    for x = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private)
        
        %checking if initial condition belongs to the same object
        if(convertCharsToStrings(models.worldmodel.object{j, 1}.name) == convertCharsToStrings(Velocity_variable(x,1)) && convertCharsToStrings(Velocity_variable(x,1)) ~= "Ego")
            
            for y = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action)
                %check if is it the position field
                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Action{1,y}),'Longitudinal') == 1 )
                    
                    location = strcat(name,convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO...
                        .Storyboard.Init.Actions.Private{1, x}.Attributes.object),"/Dynamics_Empty/");
                    Blockid = string(1:length(models.worldmodel.object));
                    %setting position mode to off
                    set_param(convertStringsToChars(strcat(location,"MuxState")) ,'PositioningMode','off');
                    
 %%%%%%%%%%%%%%%%%%%%%% Adding block                    
                    %adding block Constant
                    Blockname1 = "Constant";
                    location1 =convertStringsToChars(strcat(location,Blockname1,Blockid(1,j)));
                    if (getSimulinkBlockHandle(location1) == -1)
                        add_block('simulink/Sources/Constant',location1);
                        %change location of constant block
                        location4 =convertStringsToChars(strcat(location,"MuxState"));
                        size_blk = get_param(location4,'Position');
                        X = size_blk(1,1)-750;
                        Y = size_blk(1,2)+60;
                        Width = size_blk(1,3)*0.1;
                        Height = size_blk(1,4)*0.2;
                        set_param(location1,'Position',[X Y X+Width Y+Height]);
                    end
                    
                    %adding block Gain
                    Blockname2 = "Gain";
                    location2 =convertStringsToChars(strcat(location,Blockname2,Blockid(1,j)));
                    if (getSimulinkBlockHandle(location2) == -1)
                        add_block('simulink/Commonly Used Blocks/Gain',location2);
                        %change position of gain block
                        size_blk = get_param(location4,'Position');
                        X = size_blk(1,1)-650;
                        Y = size_blk(1,2)+60;
                        Width = size_blk(1,3)*0.1;
                        Height = size_blk(1,4)*0.2;
                        set_param(location2,'Position',[X Y X+Width Y+Height]);
                    end
                    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%delete Terminators
                    f =  Simulink.FindOptions('SearchDepth',1);
                    b1 = Simulink.findBlocksOfType(convertStringsToChars(location),'Ground',f);
                    b2 = convertCharsToStrings(getfullname(b1));
                    
                    if(isempty(b2) ~= 1)
                        for q  = 1:length(b2(:,1))
                            S1=get_param(b2(q,1),'PortConnectivity');
                            S2 = get_param(S1.DstBlock,'name');
                            %location of where the terminators where connected to
                            location3= convertCharsToStrings(S2);
                            if(getSimulinkBlockHandle(b2(q,1)) ~= -1)
                                delete_block(b2(q,1))
                            end
                        end
                        %delete_line
                        for p = 1:length(location3)
                            h = get_param(convertStringsToChars(strcat(location,location3(p,1))),'LineHandles');
                            for q = 1:length(h.Inport)
                                if((h.Inport(q)) ~= -1)
                                    delete_line(h.Inport(q) )
                                end
                            end
                        end                        
                    end              

                    %%%%%%%%%%%%%%%%%%%%%%%%%%%Connecting everything
                    %only add lines if gain does not have a connection
                    
                    s2 = get_param(convertStringsToChars(strcat(location,"MuxState")), 'PortConnectivity');
                    if(s2(4,1).SrcBlock == -1)
                        add_line(convertStringsToChars(location), convertStringsToChars(strcat(Blockname2,Blockid(1,j), "/1"))...
                            ,'MuxState/4');
                    end
                     s= get_param(location2,'PortConnectivity');
                    if((s(1,1).SrcBlock) == -1)
                        add_line(convertStringsToChars(location), convertStringsToChars(strcat(Blockname1,Blockid(1,j),"/1")) ...
                            ,convertStringsToChars(strcat(Blockname2,Blockid(1,j), "/1")));
                    end
                    
                    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%set parameters
                    
                    %if rate field exists
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}...
                            .Action{1,y}.Longitudinal),'Speed') == 1 )
                        %Check if Dynamics exists
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}...
                                .Action{1,y}.Longitudinal.Speed),'Dynamics') == 1 )
                            %Check if rate exists
                            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}...
                                    .Action{1,y}.Longitudinal.Speed.Dynamics),'rate') == 1 )                                
                                set_param(location1,'Value',Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}...
                                    .Action{1,y}.Longitudinal.Speed.Dynamics.Attributes.rate);                                
                            end %rate field check
                        end %Dynamics field check
                        
                        
                        %if rate field exists
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}...
                                .Action{1,y}.Longitudinal.Speed),'Target') == 1 )
                            %if Absolute exists
                            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}...
                                    .Action{1,y}.Longitudinal.Speed.Target),'Absolute') == 1 )                                
                                set_param(location1,'Value',Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}...
                                    .Action{1,y}.Longitudinal.Speed.Target.Absolute.Attributes.value);                                
                            end %check Absolute field
                        end %check Target field
                        
                        
                        set_param(location2,'Gain','1/3.6') ;
                        break;
                        
                        
                    end%Speed field check
                    
                end%Longitudinal check
                
            end %third for loop, number of Action
        end %if car is not ego
        
    end %second for loop, number of Private
end %main for loop, number of Prescan objects

end %end function
