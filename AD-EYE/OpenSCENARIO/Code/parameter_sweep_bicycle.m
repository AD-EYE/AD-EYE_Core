%%%%%%%%%%%%%%%%%%%%Entities Object
%%%%%%%%%%Vehicle
function [models] = parameter_sweep_bicycle(array, i,models,Struct_OpenSCENARIO,Struct_pex,k )
for j =array %second for loop
    
    if(isfield(convertCharsToStrings(Struct_pex.Experiment.Actors.Actor{1,j}.Attributes)  ,'ObjectTypeID') == 1 )    %if objectTypeID exists
        
        %Check if j is a car in .pex file
        if (str2double(Struct_pex.Experiment.Actors.Actor{1, j}.Attributes.ObjectTypeID  ) == k)
            for x = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private)
                %Check if j is a car in .pex file
                if ( convertCharsToStrings(Struct_pex.Experiment.Actors.Actor{1, j}.Attributes.id    ) == convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x}.Attributes.object))
                    z = j
                    %{
            %changing name
            models.worldmodel.object{j, 1}= prescan.experiment.setFieldValue(...
                models.worldmodel.object{j, 1},'name', Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Attributes.name );
            j
            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}),'Vehicle') == 1 )  %if Vehicle exists
                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle),'BoundingBox') == 1 )  %if BoundingBox exists
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox),'Center') == 1 )  %if Center exists
                        
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Center.Attributes),'x') == 1 )  %if x exists
                            %Changing center of mass position
                            if (isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Center.Attributes.x)) ~= 1)
                                models.worldmodel.object{j, 1}.cogOffset =prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.cogOffset ,'x' ,str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Center.Attributes.x  ) );
                            end
                        end%x field check
                        
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Center.Attributes),'y') == 1 )  %if y exists
                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Center.Attributes.y)) ~= 1)
                                models.worldmodel.object{j, 1}.cogOffset =prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.cogOffset ,'y' ,str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Center.Attributes.y  ) );
                            end
                        end%y field check
                        
                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Center.Attributes),'z') == 1 )  %if z exists
                            if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Center.Attributes.z)) ~= 1)
                                models.worldmodel.object{j, 1}.cogOffset =prescan.experiment.setFieldValue(...
                                    models.worldmodel.object{j, 1}.cogOffset ,'z' ,str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.BoundingBox.Center.Attributes.z  ) );
                            end
                        end%z field check
                        
                    end%Center field check
                    
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
                end%BoundingBox field check
                
                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle),'Performance') == 1 )  %if Performance exists
                    %Changing maxwalking speed
                    
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.Performance.Attributes),'maxSpeed') == 1 )  %if maxSpeed exists
                        if(isnan(str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.Performance.Attributes.maxSpeed)) ~= 1)
                            models.worldmodel.object{j, 1}.human   =prescan.experiment.setFieldValue(...
                                models.worldmodel.object{j, 1}.human,'maxWalkingSpeed' ,str2num(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Vehicle.Performance.Attributes.maxSpeed) );
                        end
                    end %maxSpeed field check
                end %Performance field check
                
                
            end %vehicle field check
                    %}
                end
            end
        end %check if it is the object, CyclingCyclist2
    end%check if it has a objectTypeID
end %Main for loop
end %end of function