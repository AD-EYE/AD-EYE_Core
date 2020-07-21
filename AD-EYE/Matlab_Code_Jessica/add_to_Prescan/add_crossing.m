%Refreshes the PB file based on the content of PEX file
prescan.experiment.convertPexToDataModels()

%Get exp name and load it for use in DMAPI
xpName = prescan.experiment.getDefaultFilename();
xp = prescan.api.experiment.loadExperimentFromFile(xpName);

%% First create a road
%% First we define the position of the road
x=50;        %[m]
y=-30;        %[m]
z=0;           %[m]
%we can also define the oriantation
yaw=0;        %[rad]
%%
road_1 = prescan.api.roads.createRoad(xp,x,y,z,yaw);
type='Y';
%%
%Save the xp's changes to the PB file
 xp.saveToFile(xpName);

%Convert the PB to PEX using the writeToPexFile function
pathToTemplatePex = ['C:\Users\adeye\Desktop\real_world_data\TemplatePexFile\TemplatePexFile.pex'];
experimentPexFile = [prescan.experiment.getExperimentName '.pex'];
writeCrossingRoadToPexFile(xpName,experimentPexFile,pathToTemplatePex,type);%,centerlineOffset);

%Run the experiment directly from Matlab
%prescan.api.simulink.run(xp,'StopTime','0','Regenerate','on');