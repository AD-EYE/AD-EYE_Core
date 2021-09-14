%%%%%%%%%%%%%%%%%%%%Creating initial speed
%Creating simulink block for initial velocity
function initialvelocitydynamics(name,models,Struct_OpenSCENARIO,velocityVariable)


for j =1:length(models.worldmodel.object) %main for loop
    
    for x = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private)
        
        %checking if initial condition belongs to the same object
        if(convertCharsToStrings(models.worldmodel.object{j, 1}.name) == convertCharsToStrings(velocityVariable(x,1)) && convertCharsToStrings(velocityVariable(x,1)) ~= "Ego")
            
            for y = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.PrivateAction)
                %check if is it the position field
                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.PrivateAction{1,y}),'LongitudinalAction') == 1 )
                    
                    locationDynamicsEmpty = strcat(name,convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO...
                        .Storyboard.Init.Actions.Private{1, x}.Attributes.entityRef),"/Dynamics_Empty/");
                    blockId = string(1:length(models.worldmodel.object));
                    %setting position mode to off
                    set_param(convertStringsToChars(strcat(locationDynamicsEmpty,"MuxState")) ,'PositioningMode','off');
                    
 %%%%%%%%%%%%%%%%%%%%%% Adding block                    
                    %adding block Constant
                    blockConstant = "Constant";
                    locationblockConstant =convertStringsToChars(strcat(locationDynamicsEmpty,blockConstant,blockId(1,j)));
                    if (getSimulinkBlockHandle(locationblockConstant) == -1)
                        add_block('simulink/Sources/Constant',locationblockConstant);
                        %change location of constant block
                        locationBlockMuxState =convertStringsToChars(strcat(locationDynamicsEmpty,"MuxState"));
                        sizeBlock = get_param(locationBlockMuxState,'Position');
                        X = sizeBlock(1,1)-750;
                        Y = sizeBlock(1,2)+60;
                        WIDTH = sizeBlock(1,3)*0.1;
                        HEIGHT = sizeBlock(1,4)*0.2;
                        set_param(locationblockConstant,'Position',[X Y X+WIDTH Y+HEIGHT]);
                    end
                    
                    %adding block Gain
                    blockGain = "Gain";
                    locationBlockGain =convertStringsToChars(strcat(locationDynamicsEmpty,blockGain,blockId(1,j)));
                    if (getSimulinkBlockHandle(locationBlockGain) == -1)
                        add_block('simulink/Commonly Used Blocks/Gain',locationBlockGain);
                        %change position of gain block
                        sizeBlock = get_param(locationBlockMuxState,'Position');
                        X = sizeBlock(1,1)-650;
                        Y = sizeBlock(1,2)+60;
                        WIDTH = sizeBlock(1,3)*0.1;
                        HEIGHT = sizeBlock(1,4)*0.2;
                        set_param(locationBlockGain,'Position',[X Y X+WIDTH Y+HEIGHT]);
                    end
                    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%delete Terminators
                    properties =  Simulink.FindOptions('SearchDepth',1);
                    findBlocksGround = Simulink.findBlocksOfType(convertStringsToChars(locationDynamicsEmpty),'Ground',properties);
                    findBlocksGroundNames = convertCharsToStrings(getfullname(findBlocksGround));
                    
                    if(isempty(findBlocksGroundNames) ~= 1)
                        for q  = 1:length(findBlocksGroundNames(:,1))
                            S1=get_param(findBlocksGroundNames(q,1),'PortConnectivity');
                            S2 = get_param(S1.DstBlock,'name');
                            %location of where the terminators where connected to
                            locationBlockGround= convertCharsToStrings(S2);
                            if(getSimulinkBlockHandle(findBlocksGroundNames(q,1)) ~= -1)
                                delete_block(findBlocksGroundNames(q,1))
                            end
                        end
                        %delete_line
                        for p = 1:length(locationBlockGround)
                            h = get_param(convertStringsToChars(strcat(locationDynamicsEmpty,locationBlockGround(p,1))),'LineHandles');
                            for q = 1:length(h.Inport)
                                if((h.Inport(q)) ~= -1)
                                    delete_line(h.Inport(q) )
                                end
                            end
                        end                        
                    end              

                    %%%%%%%%%%%%%%%%%%%%%%%%%%%Connecting everything
                    %only add lines if gain does not have a connection
                    
                    s2 = get_param(convertStringsToChars(strcat(locationDynamicsEmpty,"MuxState")), 'PortConnectivity');
                    if(s2(4,1).SrcBlock == -1)
                        add_line(convertStringsToChars(locationDynamicsEmpty), convertStringsToChars(strcat(blockGain,blockId(1,j), "/1"))...
                            ,'MuxState/4');
                    end
                     s= get_param(locationBlockGain,'PortConnectivity');
                    if((s(1,1).SrcBlock) == -1)
                        add_line(convertStringsToChars(locationDynamicsEmpty), convertStringsToChars(strcat(blockConstant,blockId(1,j),"/1")) ...
                            ,convertStringsToChars(strcat(blockGain,blockId(1,j), "/1")));
                    end
                    
                    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%set parameters
                    
                    %if value field exists in Dynamics
                    if(field_exists(Struct_OpenSCENARIO, strcat("Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1,",num2str(x),"}.PrivateAction{1,",num2str(y),"}.LongitudinalAction.SpeedAction.SpeedActionDynamics.value")))
                        set_param(locationblockConstant,'Value',Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}...
                                    .PrivareAction{1,y}.LongitudinalAction.SpeedAction.SpeedActionDynamics.Attributes.value); 
                    end
                        
                        
                    %if value field exists in Target
                    if(field_exists(Struct_OpenSCENARIO, strcat("Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, ",num2str(x),"}.PrivateAction{1,",num2str(y),"}.LongitudinalAction.SpeedAction.SpeedActionTarget.AbsoluteTargetSpeed")))
                        set_param(locationblockConstant,'Value',Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}...
                                .PrivateAction{1,y}.LongitudinalAction.SpeedAction.SpeedActionTarget.AbsoluteTargetSpeed.Attributes.value);
                    end %check Target field
                        
                        
                    set_param(locationBlockGain,'Gain','1/3.6') ;
                    break;
                    
                end%Longitudinal check
                
            end %third for loop, number of Action
        end %if car is not ego
        
    end %second for loop, number of Private
end %main for loop, number of Prescan objects

end %end function
