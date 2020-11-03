% input:
%   roads_to_add: cell with:
%       roads_to_add{i}.position:structure: position.x position.y position.z [meter]
%        roads_to_add{i}.orientation: integer [radian]
%        roads_to_add{i}.type: string ('X' or 'Y')
%        roads_to_add{i}.heading: vector length 4 [radian]

function add_roundabout(roads_to_add)
    %Refreshes the PB file based on the content of PEX file
    prescan.experiment.convertPexToDataModels()

    %Get exp name and load it for use in DMAPI
    xpName = prescan.experiment.getDefaultFilename();
    xp = prescan.api.experiment.loadExperimentFromFile(xpName);

    %% First create roads
    nbRoads=length(roads_to_add);
    
    for i=1:nbRoads
        %first define position
        x=roads_to_add{i}.position.x;   %[meter]
        y=roads_to_add{i}.position.y;   %[meter]
        z=roads_to_add{i}.position.z;   %[meter]
        % second define orientation
        yaw=roads_to_add{i}.orientation;    %[radian]
        % now add the road
        prescan.api.roads.createRoad(xp,x,y,z,yaw);
        
      % define position of branches
    %correspond to the angle between the x axis of the crossing and the branch
        roads_to_add{i}.headings=rad2deg(roads_to_add{i}.headings);  %[degree]
    end
    
%%

    %Convert the PB to PEX using the writeRoundaboutToPexFile function
    pathToTemplatePex = ['C:\Users\adeye\Desktop\real_world_data\TemplatePexFile\TemplatePexFile.pex'];
    experimentPexFile = [prescan.experiment.getExperimentName '.pex'];
    writeRoundaboutToPexFile(xpName,experimentPexFile,pathToTemplatePex,roads_to_add);
    
end
