%%%%%%%%%%%%%%%%%%%%Entities Object
%%%%%%%%%%Pedestrians
function [array,models,j] = parameter_sweep_pedestrian(array, i,models,Struct_OpenSCENARIO,k )
for j =array
    
    if(isfield(convertCharsToStrings(models.worldmodel.object{j, 1}),'objectTypeID') == 1 )  %if objectTypeID exists        
        if (models.worldmodel.object{j, 1}.objectTypeID == k)
            %Changing center of mass position
            
            models.worldmodel.object{j, 1}= prescan.experiment.setFieldValue(...
                models.worldmodel.object{j, 1},'name', Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Attributes.name );            
            
            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}),'Pedestrian') == 1 )  %if Pedestrian exists             
                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Pedestrian),'BoundingBox') == 1 )  %if BoundingBox exists
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Pedestrian.BoundingBox),'Center') == 1 )  %if Center exists
                        
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Pedestrian.BoundingBox.Center.Attributes),'x') == 1 )  %if x exists
                            %Changing center of mass of pedestrian
                            if (isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Pedestrian.BoundingBox.Center.Attributes.x)) ~= 1)
                                models.worldmodel.object{j, 1}.cogOffset =prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.cogOffset ,'x' ,str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Pedestrian.BoundingBox.Center.Attributes.x  ) );
                            end
                            
                        end %x field check
                        
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Pedestrian.BoundingBox.Center.Attributes),'y') == 1 )  %if y exists
                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Pedestrian.BoundingBox.Center.Attributes.y)) ~= 1)
                                models.worldmodel.object{j, 1}.cogOffset =prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.cogOffset ,'y' ,str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Pedestrian.BoundingBox.Center.Attributes.y  ) );
                            end
                        end %y field check
                        
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Pedestrian.BoundingBox.Center.Attributes),'z') == 1 )  %if z exists
                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Pedestrian.BoundingBox.Center.Attributes.z)) ~= 1)
                                models.worldmodel.object{j, 1}.cogOffset =prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.cogOffset ,'z' ,str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Pedestrian.BoundingBox.Center.Attributes.z  ) );
                            end
                        end %z field check
                        
                        
                    end %Center field check
                    
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Pedestrian.BoundingBox),'Dimensions') == 1 )  %if Dimensions exists
                        %Changing pedestrian dimensions
                        
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Pedestrian.BoundingBox.Dimension.Attributes),'length') == 1 )  %if length exists
                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Pedestrian.BoundingBox.Dimension.Attributes.length)) ~= 1)
                                models.worldmodel.object{j, 1}.boundingSize =prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.boundingSize ,'x' ,str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Pedestrian.BoundingBox.Dimension.Attributes.length  ) );
                            end
                        end %length field check
                        
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Pedestrian.BoundingBox.Dimension.Attributes),'width') == 1 )  %if width exists
                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Pedestrian.BoundingBox.Dimension.Attributes.width)) ~= 1)
                                models.worldmodel.object{j, 1}.boundingSize =prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.boundingSize ,'y' ,str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Pedestrian.BoundingBox.Dimension.Attributes.width  ) );
                            end
                            
                        end %width field check
                        
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Pedestrian.BoundingBox.Dimension.Attributes),'height') == 1 )  %if height exists
                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Pedestrian.BoundingBox.Dimension.Attributes.height)) ~= 1)
                                models.worldmodel.object{j, 1}.boundingSize =prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.boundingSize ,'z' ,str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Pedestrian.BoundingBox.Dimension.Attributes.height  ) );
                            end
                            
                        end %height field check
                        
                    end %Dimensions field check
                end %BoundingBox field check
            end %Pedestrian field check
            
            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Attributes),'mass') == 1 )  %if height exists
                
                if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Attributes.mass )) ~= 1)
                    models.worldmodel.object{j, 1}.genericModel.contents.genericModelDynamics.parameters2dDynamics.physicsParameters  =prescan.experiment.setFieldValue(...
                        models.worldmodel.object{j, 1}.genericModel.contents.genericModelDynamics.parameters2dDynamics.physicsParameters...
                        ,'mass' ,single(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Attributes.mass)) );
                end
                
            end
            
            array(array == j) = [];
            break;
        end %check if it has a objectTypeID
    end
end

