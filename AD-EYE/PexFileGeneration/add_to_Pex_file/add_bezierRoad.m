% input:
%   roads_to_add: cell with: 
%           raods_to_add{i}.position: position.x position.y position.z [meter]
%            raods_to_add{i}.orientation [radian]
%            raods{i}_to_add.heading [radian]
%            raods{i}_to_add.delta: delta.x delta.y delta.z [meter]
%            raods{i}_to_add.tension: tension.entry tension.exit [meter]

function add_bezierRoad(roads_to_add)
    %Refreshes the PB file based on the content of PEX file
    prescan.experiment.convertPexToDataModels()

    %Get exp name and load it for use in DMAPI
    xpName = prescan.experiment.getDefaultFilename();
    xp = prescan.api.experiment.loadExperimentFromFile(xpName);
    % 
    %% First create a road
    %%
    nbRoads=length(roads_to_add);
    if nbRoads<2
        disp('Warning:if there are no roads on the experiment now, the function will work but if you use it again it will not work. If there is one road on the experiment now, the function will not work.');
    end
    %%
    for i=1:nbRoads
        
        %firstly we define position of the road
        x=roads_to_add{i}.position.x;      %[m]
        y=roads_to_add{i}.position.y;      %[m]
        z=roads_to_add{i}.position.z;      %[m]
        % secondly we define orientation of the road
        yaw=roads_to_add{i}.orientation; %[rad]
        % now we add the road
        prescan.api.roads.createRoad(xp,x,y,z,yaw);
        
        % now we define options of the road
        options{i}.relativeHeading=rad2deg(roads_to_add{i}.heading); %[degree]
        options{i}.deltaX=roads_to_add{i}.delta.x; %[meter]
         options{i}.deltaY=roads_to_add{i}.delta.y; %[meter]
        options{i}.deltaZ=roads_to_add{i}.delta.z; %[meter]
        options{i}.EntryTension=roads_to_add{i}.tension.entry;  %[meter]
        options{i}.ExitTension=roads_to_add{i}.tension.exit;    %[meter]
        
    end
    
    %%
    %Save the xp's changes to the PB file
     xp.saveToFile(xpName);

    %Convert the PB to PEX using the writeToPexFile function
    pathToTemplatePex = ['C:\Users\adeye\Desktop\real_world_data\TemplatePexFile\TemplatePexFile.pex'];
    experimentPexFile = [prescan.experiment.getExperimentName '.pex'];
    writeBezierRoadToPexFile(xpName,experimentPexFile,pathToTemplatePex,options);%,centerlineOffset);

    %Run the experiment directly from Matlab
%     prescan.api.simulink.run(xp,'StopTime','0','Regenerate','on');
end
