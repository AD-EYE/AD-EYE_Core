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
 
%% After creating a road we need to add sections to it
% sectionLength = 200;     %[m]
% road_1.addStraightSection(sectionLength);
% sectionLength = 50;
% startCurvature = 0.025;
% endCurvature = 0.1;
% road_1.addSpiralSection(sectionLength, startCurvature, endCurvature);
sectionLength = 10;     %[m]
startCurvature = 0.025; %[1/m]
endCurvature = 0.1;     %[1/m]
road_1.addSpiralSection(sectionLength, startCurvature, endCurvature);
centerlineOffset.x=10;
centerlineOffset.y=20;
centerlineOffset.z=0;
%% Once the sections have been added, we add lanes to the road

lane1 = road_1.addLeftLane(3.2);
marker = lane1.getLaneMarker('Outer');
marker.type = 'Broken';
lane2 = road_1.addLeftLane(3.2);
marker = lane2.getLaneMarker('Outer');
marker.type = 'Solid';
lane3 = road_1.addRightLane(3.2);
marker = lane3.getLaneMarker('Outer');
marker.type = 'Broken';
lane4 = road_1.addRightLane(3.2);
marker = lane4.getLaneMarker('Outer');
marker.type = 'Solid';

centerOfLane1 = - 3.2/2; % 2 lanes to the right, just in the middle of one
centerOfLane2 = -3.2 - 3.2/2; % 2 lanes to the right, just in the middle of one
edgeOfRoadLeft = -15; 
edgeOfRoadRight = 15; 

%Save the xp's changes to the PB file
 xp.saveToFile(xpName);

%Convert the PB to PEX using the writeToPexFile function
pathToTemplatePex = ['C:\Users\adeye\Desktop\real_world_data\TemplatePexFile\TemplatePexFile.pex'];
experimentPexFile = [prescan.experiment.getExperimentName '.pex'];
writeBezierRoadToPexFile(xpName,experimentPexFile,pathToTemplatePex);%,centerlineOffset);

%Run the experiment directly from Matlab
prescan.api.simulink.run(xp,'StopTime','0','Regenerate','on');