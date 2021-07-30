function [Struct_OpenSCENARIO,Struct_pex]= initialize_actors(Struct_OpenSCENARIO,Struct_pex,name_ego)

%%%%%%%%%%Vehicle/Pedestrians

%Creating initial position/dimensions of ScenarioObjects
for i = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Entities.ScenarioObject) %Declare number of ScenarioObjects in xml file %main for loop
    
    
    %checking if field is a Vehicle otherwise a Pedestian
    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.ScenarioObject{1, i}),'Vehicle') == 1 )
        
        if(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.ScenarioObject{1, i}.Attributes.name) == "Ego" && convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Attributes.entityRef) == "Ego" )
            %change name of ego car
            x {1,1} = Struct_OpenSCENARIO.OpenSCENARIO.Entities.ScenarioObject{1, i}.Attributes.name;
            x {1,2} = i;
            Struct_OpenSCENARIO.OpenSCENARIO.Entities.ScenarioObject{1, i}.Attributes.name = convertStringsToChars(name_ego);
            Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Attributes.entityRef = convertStringsToChars(name_ego);
        end %ego car check
        
        %checking type of vehicle car
        if(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.ScenarioObject{1, i}...
                .Vehicle.Attributes.category) == "car" )
            k = 1;
            
            %checking type of vehicle truck
        elseif(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.ScenarioObject{1, i}...
                .Vehicle.Attributes.category) == "truck")
            k =3;
            
            %checking type of vehicle motorbike
        elseif(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.ScenarioObject{1, i}...
                .Vehicle.Attributes.category) == "motorbike")
            k = 2;
            
            %checking type of vehicle bicycle
        elseif(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.ScenarioObject{1, i}...
                .Vehicle.Attributes.category) == "bicycle")
            k = 4;
        end

        %[models] = parameter_sweep_bicycle(array, i, models,Struct_OpenSCENARIO,Struct_pex,k );    %changing ScenarioObject parameters
        [Struct_pex] = parameter_sweep_initalPositions(Struct_OpenSCENARIO,Struct_pex,k,i); %changing initial conditions
    end %first main if statement
    
    %checking type of pedestrian
    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.ScenarioObject{1, i}),'Pedestrian') == 1 && convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.ScenarioObject{1, i}...
            .Pedestrian.Attributes.category) == "pedestrian" ) %Check pedestrain field
        k = 4;
        %[models] = parameter_sweep_pedestrian(array, i, models,Struct_OpenSCENARIO,Struct_pex,k );  %changing ScenarioObject parameter
        [Struct_pex] = parameter_sweep_initalPositions(Struct_OpenSCENARIO,Struct_pex,k,i); %changing initial conditions
    end
    
    
    
    
    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.ScenarioObject{1, i}), 'CatalogReference') ==1)
        
        if(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.ScenarioObject{1, i}.Attributes.name) == "Ego" && Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Attributes.entityRef == "Ego" )
            %change name of ego car
            x {1,1} = Struct_OpenSCENARIO.OpenSCENARIO.Entities.ScenarioObject{1, i}.Attributes.name;
            x {1,2} = i;
            Struct_OpenSCENARIO.OpenSCENARIO.Entities.ScenarioObject{1, i}.Attributes.name = convertStringsToChars(name_ego);
            Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Attributes.entityRef = convertStringsToChars(name_ego);
        end %check ego
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%checking if field is in VehicleCatalog
        if(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.ScenarioObject{1, i}.CatalogReference.Attributes.catalogName) == "VechicleCatalog" )
            disp('In VechicleCatalog')
            k = 1;  % Car
        end
        
        %checking if field is in TruckCatalog
        if(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.ScenarioObject{1, i}.CatalogReference.Attributes.catalogName) == "TruckCatalog")
            disp('In TruckCatalog')
            k = 3;  % Truck
        end
        
        %checking if field is in MotorbikeCatalog
        if(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.ScenarioObject{1, i}.CatalogReference.Attributes.catalogName) == "MotorbikeCatalog")
            disp('In MotorbikeCatalog')
            k = 2;  % Motorbike
        end
        
        %checking if field is in PedestrianCatalog
        if(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.ScenarioObject{1, i}.CatalogReference.Attributes.catalogName) == "PedestrianCatalog")
            disp('In PedestrianCatalog')
            k = 4;
            disp('miep')
        end
        
        %[models] = parameter_sweep_vehicle(array, i, models,Struct_OpenSCENARIO,Struct_pex,k ); %changing ScenarioObject parameters
        [Struct_pex] = parameter_sweep_initalPositions(Struct_OpenSCENARIO,Struct_pex,k,i); %changing initial condition
    end
    
end %main for loop

%change ego name back
Struct_OpenSCENARIO.OpenSCENARIO.Entities.ScenarioObject{1, x {1,2}}.Attributes.name = x {1,1};
Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x {1,2}}.Attributes.entityRef = x {1,1};



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%create cells to allow
%for multiple stories, maneuvers and events

%make cell of Story to allow for multiple stories
if(isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard,'Story'))
    if(length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story) == 1)
        Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story=  {Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story};
    end

    for k = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story)

        if(isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k},'Act') == 1)
            if(isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act,'ManeuverGroup') == 1)

                %make cell of Maneuvers to allow for multiple Maneuvers
                if(length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver) == 1)
                    Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver=  {Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver};
                end

                for i = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver)
                    %make cell of Events to allow for multiple Events
                    if(length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,i}.Event) == 1)
                        Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,i}.Event=  {Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.ManeuverGroup.Maneuver{1,i}.Event};
                    end

                end
            end
        end
    end
end

disp('Initial positions and dimensions changed')
end