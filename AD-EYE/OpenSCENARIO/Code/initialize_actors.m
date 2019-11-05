function [Struct_OpenSCENARIO,models]= initialize_actors(models,Struct_OpenSCENARIO,name_ego)



%%%%%%%%%%Vehicle/Pedestrians

array = 1:length(models.worldmodel.object); %Declare number of objects in .pex file
%Creating initial position/dimensions of objects
for i = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object) %Declare number of objects in xml file %main for loop
    
    %checking if field is a Vehicle otherwise a Pedestian
    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}),'Vehicle') == 1 )
        
        if(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Attributes.name) == "Ego" && Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Attributes.object == "Ego" )
            %change name of ego car
            x {1,1} = Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Attributes.name;
            x {1,2} = i;
            Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Attributes.name = convertStringsToChars(name_ego);
            Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Attributes.object = convertStringsToChars(name_ego);
            
            %checking type of vehicle car
            if(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}...
                    .Vehicle.Attributes.category) == "car" )
                
                k = 1;
                [array,models,j] = parameter_sweep_vehicle(array, i, models,Struct_OpenSCENARIO,k ); %changing object parameters
                [models] = parameter_sweep_initalPositions(models,Struct_OpenSCENARIO,j );                   %changing initial conditions
                
                %checking type of vehicle truck
            elseif(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}...
                    .Vehicle.Attributes.category) == "truck")
                k =3;
                [array,models,j] = parameter_sweep_vehicle(array, i, models,Struct_OpenSCENARIO,k );  %changing object parameters
                [models] = parameter_sweep_initalPositions(models,Struct_OpenSCENARIO,j );                    %changing initial conditions
                
                %checking type of vehicle motorbike
            elseif(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}...
                    .Vehicle.Attributes.category) == "motorbike")
                k = 2;
                [array,models,j] = parameter_sweep_vehicle(array, i, models,Struct_OpenSCENARIO,k );  %changing object parameters
                [models] = parameter_sweep_initalPositions(models,Struct_OpenSCENARIO,j );                    %changing initial conditions
                
                %checking type of vehicle bicycle
            elseif(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}...
                    .Vehicle.Attributes.category) == "bicycle")
                k = 4;
                [array,models,j] = parameter_sweep_bicycle(array, i, models,Struct_OpenSCENARIO,k );    %changing object parameters
                [models] = parameter_sweep_initalPositions(models,Struct_OpenSCENARIO,j );                      %changing initial conditions
                
            end
            
        elseif(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}),'Pedestrian') == 1 ) %Check pedestrain field
            
            k = 4;
            [array,models,j] = parameter_sweep_pedestrian(array, i, models,Struct_OpenSCENARIO,k );  %changing object parameter
            [models] = parameter_sweep_initalPositions(models,Struct_OpenSCENARIO,j );    %changing initial conditions
            
        end %ego car check        
    end %first main if statement  
    
    
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%checking if field is in VehicleCatalog
    if(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.CatalogReference.Attributes.catalogName) == "VechicleCatalog")
        if(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Attributes.name) == "Ego" && Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Attributes.object == "Ego" )
            %change name of ego car
            x{1,1} = Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Attributes.name;
            x {1,2} = i;
            Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Attributes.name = convertStringsToChars(name_ego);
            Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Attributes.object = convertStringsToChars(name_ego);
        end %check ego
        
        %disp('In VechicleCatalog')
        k = 1;  % Car
        [array,models,j] = parameter_sweep_vehicle(array, i, models,Struct_OpenSCENARIO,k ); %changing object parameters
        [models] = parameter_sweep_initalPositions(models,Struct_OpenSCENARIO,j );  %changing initial condition
    end %check VechicleCatalog
    
    %checking if field is in TruckCatalog
    if(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.CatalogReference.Attributes.catalogName) == "TruckCatalog")
        if(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Attributes.name) == "Ego" && Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Attributes.object == "Ego" )
            %change name of ego car
            x {1,1} = Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Attributes.name;
            x {1,2} = i;
            Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Attributes.name = convertStringsToChars(name_ego);
            Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Attributes.object = convertStringsToChars(name_ego);
        end %check ego
        
        %disp('In TruckCatalog')
        k = 3;  % Truck
        [array,models,j] = parameter_sweep_vehicle(array, i, models,Struct_OpenSCENARIO,k ); %changing object parameters
        [models] = parameter_sweep_initalPositions(models,Struct_OpenSCENARIO,j );  %changing initial condition
    end %check TruckCatalog
    
    %checking if field is in MotorbikeCatalog
    if(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.CatalogReference.Attributes.catalogName) == "MotorbikeCatalog")
        if(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Attributes.name) == "Ego" && Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Attributes.object == "Ego" )
            %change name of ego car
            x {1,1} = Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Attributes.name;
            x {1,2} = i;
            Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Attributes.name = convertStringsToChars(name_ego);
            Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Attributes.object = convertStringsToChars(name_ego);
        end %check ego
        
        %disp('In MotorbikeCatalog')
        k = 2;  % Motorbike
        [array,models,j] = parameter_sweep_vehicle(array, i, models,Struct_OpenSCENARIO,k ); %changing object parameters
        [models] = parameter_sweep_initalPositions(models,Struct_OpenSCENARIO,j );  %changing initial condition
    end %check MotorbikeCatalog
    
    %checking if field is in PedestrianCatalog
    if(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.CatalogReference.Attributes.catalogName) == "PedestrianCatalog")
        if(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Attributes.name) == "Ego" && Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Attributes.object == "Ego" )
            %change name of ego car
            x {1,1} = Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Attributes.name;
            x {1,2} = i;
            Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, i}.Attributes.name = convertStringsToChars(name_ego);
            Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, i}.Attributes.object = convertStringsToChars(name_ego);
        end %check ego
        
        %disp('In PedestrianCatalog')
        k = 4;
        [array,models,j] = parameter_sweep_pedestrian(array, i, models,Struct_OpenSCENARIO,k );  %changing object parameter
        [models] = parameter_sweep_initalPositions(models,Struct_OpenSCENARIO,j );                       %changing initial conditions
        
    end   %check PedestrianCatalog
    
    
end %main for loop

%change ego name back
Struct_OpenSCENARIO.OpenSCENARIO.Entities.Object{1, x {1,2}}.Attributes.name = x {1,1};
Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, x {1,2}}.Attributes.object = x {1,1};





%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%create cells to allow 
%for multiple stories, maneuvers and events

%make cell of Story to allow for multiple stories
if(length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story) == 1)
    Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story=  {Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story};
end

for k = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story)
    
    %make cell of Maneuvers to allow for multiple Maneuvers
    if(length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver) == 1)
        Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver=  {Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver};
    end
    
    for i = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver)
        %make cell of Events to allow for multiple Events
        if(length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,i}.Event) == 1)
            Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,i}.Event=  {Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,i}.Event};
        end
        
    end
end

disp('Initial positions and dimensions changed')
end