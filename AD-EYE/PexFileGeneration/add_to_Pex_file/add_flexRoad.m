% input
%   roads: struct with:
%           roads{i}.position: position.x position.y position.z [meter]
%           roads{i}.orientation [radian]
%           roads{i}.points: structure (see exemple to now what they are on points)

% exemple for points:
%first general for the start and the end of the road
% points{1}.relativeHeading=30; %[degree]
% points{1}.Offset.x=70; %[meter]
% points{1}.Offset.y=40; %[meter]
% points{1}.Offset.z=0; %[meter]
% points{1}.EntryTension=9; %[meter]
% points{1}.ExitTension=20; %[meter]
% 
% %second for point in the middle of the road (if just 3 turns: begin, end and middle points)
% points{2}.EntryTension=12.08;
% points{2}.ExitTension=9.68;
% points{2}.Location.X=30.9;
% points{2}.Location.Y=0.64;
% points{2}.Location.Z=0;
% points{2}.Orientation.Heading=67.87; %[radian]

function add_flexRoad(roads)%position,orientation, points)
    %Refreshes the PB file based on the content of PEX file
    prescan.experiment.convertPexToDataModels()

    %Get exp name and load it for use in DMAPI
    xpName = prescan.experiment.getDefaultFilename();
    xp = prescan.api.experiment.loadExperimentFromFile(xpName);
    % 
    %% First create a road
    nbroads=length(roads);
    
    for j=1:nbroads
        
        %first we define the position of the road
        x=roads{j}.position.x;  %[meter]
        y=roads{j}.position.y %[meter]
        z=roads{j}.position.z;  %[meter]
        % secondly we define the orientation of the road
        yaw=roads{j}.orientation;   %[radian]
        % now we add the road
        prescan.api.roads.createRoad(xp,x,y,z,yaw);
    
    % finally we difine parameters of the road

        len=length(roads{j}.points);
        for i=2:len
            roads{j}.points{i}.Orientation.Heading=rad2deg(roads{j}.points{i}.Orientation.Heading);
        end
    end
    

    %%
    %Save the xp's changes to the PB file
     xp.saveToFile(xpName);

    %Convert the PB to PEX using the writeToPexFile function
    pathToTemplatePex = ['C:\Users\adeye\Desktop\real_world_data\TemplatePexFile\TemplatePexFile.pex'];
    experimentPexFile = [prescan.experiment.getExperimentName '.pex'];
    writeFlexRoadToPexFile(xpName,experimentPexFile,pathToTemplatePex,roads);

end
