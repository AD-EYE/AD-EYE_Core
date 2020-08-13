%Refreshes the PB file based on the content of PEX file
prescan.experiment.convertPexToDataModels()

%Get exp name and load it for use in DMAPI
xpName = prescan.experiment.getDefaultFilename();
xp = prescan.api.experiment.loadExperimentFromFile(xpName);
% 
%% First create a road
%% First we define the position of the road
x=-25;        %[m]
y=-15;        %[m]
z=0;           %[m]
%we can also define the oriantation
yaw=0;        %[rad]
%%
road_1 = prescan.api.roads.createRoad(xp,x,y,z,yaw);
 
%%
% we indicate option for the road
options.relativeHeading=90; %[degree]
options.deltaX=20; %[meter]
options.deltaY=50; %[meter]
options.deltaZ=0; %[meter]

%%
%Save the xp's changes to the PB file
 xp.saveToFile(xpName);

%Convert the PB to PEX using the writeToPexFile function
pathToTemplatePex = ['C:\Users\adeye\Desktop\real_world_data\TemplatePexFile\TemplatePexFile.pex'];
experimentPexFile = [prescan.experiment.getExperimentName '.pex'];
writeBezierRoadToPexFile(xpName,experimentPexFile,pathToTemplatePex);%,centerlineOffset);

%Run the experiment directly from Matlab
prescan.api.simulink.run(xp,'StopTime','0','Regenerate','on');