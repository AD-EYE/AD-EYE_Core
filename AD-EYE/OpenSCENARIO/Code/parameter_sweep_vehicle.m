%%%%%%%%%%%%%%%%%%%%Entities Object
%%%%%%%%%%Vehicle
function [array,models,j] = parameter_sweep_vehicle(array, i,models,Struct_OpenSCENARIO,k )
for j =array %second for loop
    
    if(isfield(convertCharsToStrings(models.worldmodel.object{j, 1}),'objectTypeID') == 1 )  %if objectTypeID exists       
        
        %Check if j is a car in .pex file
        if (models.worldmodel.object{j, 1}.objectTypeID == k)
            
            %changing name
            models.worldmodel.object{j, 1}= prescan.experiment.setFieldValue(...
                models.worldmodel.object{j, 1},'name', Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Attributes.name );
            
            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}),'Vehicle') == 1 )  %if Vehicle exists             
                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle),'BoundingBox') == 1 )  %if BoundingBox exists
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox),'Center') == 1 )  %if Center exists
                        
                        
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Center.Attributes),'x') == 1 )  %if x exists
                            %Changing center of mass position
                            if (isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Center.Attributes.x)) ~= 1)
                                models.worldmodel.object{j, 1}.cogOffset =prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.cogOffset ,'x' ,str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Center.Attributes.x  ) );
                            end                            
                        end %x field check
                        
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Center.Attributes),'y') == 1 )  %if y exists
                            
                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Center.Attributes.y)) ~= 1)
                                models.worldmodel.object{j, 1}.cogOffset =prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.cogOffset ,'y' ,str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Center.Attributes.y  ) );
                            end
                        end  %y field check
                        
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Center.Attributes),'z') == 1 )  %if z exists
                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Center.Attributes.z)) ~= 1)
                                models.worldmodel.object{j, 1}.cogOffset =prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.cogOffset ,'z' ,str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Center.Attributes.z  ) );
                            end
                        end  %z field check
                        
                    end %Center field check
                    
                    
                    
                    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Dimensions                    
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox),'Dimensions') == 1 )  %if Dimensions exists
                        %Changing car dimensions
                        
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Dimension.Attributes),'length') == 1 )  %if length exists
                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Dimension.Attributes.length)) ~= 1)
                                models.worldmodel.object{j, 1}.boundingSize =prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.boundingSize ,'x' ,str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Dimension.Attributes.length  ) );
                            end
                            
                        end %length field check
                        
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Dimension.Attributes),'width') == 1 )  %if width exists
                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Dimension.Attributes.width)) ~= 1)
                                models.worldmodel.object{j, 1}.boundingSize =prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.boundingSize ,'y' ,str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Dimension.Attributes.width  ) );
                            end
                            
                        end %width field check
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Dimension.Attributes),'height') == 1 )  %if height exists
                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Dimension.Attributes.height)) ~= 1)
                                models.worldmodel.object{j, 1}.boundingSize =prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.boundingSize ,'z' ,str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Dimension.Attributes.height  ) );
                            end
                        end %height field check
                        
                    end %Dimensions field check
                end %BoundingBox field check
                
                
                
                    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Performance                                    
                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle),'Performance') == 1 )  %if Performance exists
                    
                    %Changing car perfomance
                    
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.Performance.Attributes),'mass') == 1 )  %if mass exists
                        
                        if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.Performance.Attributes.mass)) ~= 1)
                            models.worldmodel.object{j, 1}.genericModel.contents.genericModelDynamics.parameters2dDynamics.physicsParameters =prescan.experiment.setFieldValue(...
                                models.worldmodel.object{j, 1}.genericModel.contents.genericModelDynamics.parameters2dDynamics.physicsParameters...
                                ,'mass' ,single(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.Performance.Attributes.mass ) ));
                        end
                    end %Mass field check
                    
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.Performance.Attributes),'maxDeceleration') == 1 )  %if maxDeceleration exists
                        
                        if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.Performance.Attributes.maxDeceleration)) ~= 1)
                            models.worldmodel.object{j, 1}.genericModel.contents.genericModelDynamics.parameters2dDynamics.physicsParameters =prescan.experiment.setFieldValue(...
                                models.worldmodel.object{j, 1}.genericModel.contents.genericModelDynamics.parameters2dDynamics.physicsParameters...
                                ,'maxDeceleration' ,single(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.Performance.Attributes.maxDeceleration )) );
                        end
                        
                    end %maxDeceleration field check
                    
                end %Performance field check
                
                
                         %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Axles                
                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle),'Axles') == 1 )  %if Axles exists
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.Axles),'Front') == 1 )  %if Axles exists                        
                        
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.Axles.Front.Attributes),'maxSteering') == 1 )  %if maxSteering exists
                            %Changing car axles
                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.Axles.Front.Attributes.maxSteering)) ~= 1)
                                models.worldmodel.object{j, 1}.genericModel.contents.genericModelDynamics.parameters2dDynamics.steeringParameters =prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.genericModel.contents.genericModelDynamics.parameters2dDynamics.steeringParameters...
                                    ,'maximumSteeringWheelAngle' ,single(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.Axles.Front.Attributes.maxSteering )*1000) );
                            end
                        end %maxSteering field check
                        
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.Axles.Front.Attributes),'wheelDiameter') == 1 )  %if wheelDiameter exists
                            
                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.Axles.Front.Attributes.wheelDiameter)) ~= 1)
                                models.worldmodel.object{j, 1}.genericModel.contents.genericModelDynamics.parameters2dDynamics.dynamicsParameters   =prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.genericModel.contents.genericModelDynamics.parameters2dDynamics.dynamicsParameters...
                                    ,'tireRadius' ,single(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.Axles.Front.Attributes.wheelDiameter)*0.5) );
                            end
                        end %wheelDiameter field check
                        
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.Axles.Front.Attributes),'trackWidth') == 1 )  %if trackWidth exists
                            
                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.Axles.Front.Attributes.trackWidth)) ~= 1)
                                models.worldmodel.object{j, 1}.genericModel.contents.genericModelDynamics.parameters2dDynamics.dynamicsParameters   =prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.genericModel.contents.genericModelDynamics.parameters2dDynamics.dynamicsParameters...
                                    ,'trackWidth' ,single(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.Axles.Front.Attributes.trackWidth)) );
                            end
                        end  %trackWidth field check                        
                        
                    end%Axles field check
                end  %Front field check
                
            end %vehicle field check
            
            
            
            array(array == j) = []; %do not use this vehicle again in the main loop
            break;                  %break for second loop
        end %check if it has a objectTypeID
    end
end
