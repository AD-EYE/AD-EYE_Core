% input:
%   position: position.x position.y position.z [meter]
%   orientation [radian]
%   heading [radian]
%   delta: delta.x delta.y delta.z [meter]
%   tension: tension.entry tension.exit [meter]

function add_bezierRoad(position,orientation,heading,delta,tension)
    %Refreshes the PB file based on the content of PEX file
    prescan.experiment.convertPexToDataModels()

    %Get exp name and load it for use in DMAPI
    xpName = prescan.experiment.getDefaultFilename();
    xp = prescan.api.experiment.loadExperimentFromFile(xpName);
    % 
    %% First create a road
    %% First we define the position of the road
    x=position.x;        %[m]
    y=position.y;        %[m]
    z=position.z;           %[m]
    %we can also define the orientation
    yaw=orientation;        %[rad]
    %%
    road_1 = prescan.api.roads.createRoad(xp,x,y,z,yaw);

    %%
    % we indicate option for the road
    options.relativeHeading=rad2deg(heading); %[degree]
    options.deltaX=delta.x; %[meter]
    options.deltaY=delta.y; %[meter]
    options.deltaZ=delta.z; %[meter]
    options.EntryTension=tension.entry;
    options.ExitTension=tension.exit;
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
