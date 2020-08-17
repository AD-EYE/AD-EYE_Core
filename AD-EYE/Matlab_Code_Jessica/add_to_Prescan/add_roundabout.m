% input:
%   position:structure: position.x position.y position.z [meter]
%   orientation: integer [radian]
%   type: string ('X' or 'Y')
%   heading: vector length 4 [radian]

function add_roundabout(position,orientation,headings)
    %Refreshes the PB file based on the content of PEX file
    prescan.experiment.convertPexToDataModels()

    %Get exp name and load it for use in DMAPI
    xpName = prescan.experiment.getDefaultFilename();
    xp = prescan.api.experiment.loadExperimentFromFile(xpName);

    %% First create a road
    %% First we define the position of the road
    x=position.x;        %[m]
    y=position.y;        %[m]
    z=position.z;           %[m]
    %we can also define the oriantation
    yaw=orientation;        %[rad]
    %%
    %add a road in pb file
    prescan.api.roads.createRoad(xp,x,y,z,yaw);
    %%
    % definition of position of branches
    % we indicate the angle between the y axis of the roundabout and the branch
    headings=rad2deg(headings); %[degree]

    %Save the xp's changes to the PB file
     xp.saveToFile(xpName);

    %Convert the PB to PEX using the writeRoundaboutToPexFile function
    pathToTemplatePex = ['C:\Users\adeye\Desktop\real_world_data\TemplatePexFile\TemplatePexFile.pex'];
    experimentPexFile = [prescan.experiment.getExperimentName '.pex'];
    writeRoundaboutToPexFile(xpName,experimentPexFile,pathToTemplatePex);%,centerlineOffset);
end
