%Refreshes the PB file based on the content of PEX file
prescan.experiment.convertPexToDataModels()

%Get exp name and load it for use in DMAPI
xpName = prescan.experiment.getDefaultFilename();
xp = prescan.api.experiment.loadExperimentFromFile(xpName);
% 
%% First create a road
%% First we define the position of the road
x=0;        %[m]
y=-100;        %[m]
z=0;           %[m]
%we can also define the oriantation
yaw=0;        %[rad]
%%
road_1 = prescan.api.roads.createRoad(xp,x,y,z,yaw);
%% Parameters of the road
% for each part of bezier road you would you need to have all of this
% parametters
%first general for the start and the end of the road
points{1}.relativeHeading=30; %[degree]
points{1}.Offset.x=70; %[meter]
points{1}.Offset.y=40; %[meter]
points{1}.Offset.z=0; %[meter]
points{1}.EntryTension=9; %[meter]
points{1}.ExitTension=20; %[meter]

%second for point in the middle of the road (if just 3 turns)
points{2}.EntryTension=12.08;
points{2}.ExitTension=9.68;
points{2}.Location.X=30.9;
points{2}.Location.Y=0.64;
points{2}.Location.Z=0;
points{2}.Orientation.Heading=67.87; %[degree]

% for exemple we add an other turn
points{3}.EntryTension=16.5;
points{3}.ExitTension=19.7;
points{3}.Location.X=23.46;
points{3}.Location.Y=43.05;
points{3}.Location.Z=0;
points{3}.Orientation.Heading=45; %[degree]

% for exemple we add an other turn
points{4}.EntryTension=13.33;
points{4}.ExitTension=4.6;
points{4}.Location.X=51.39;
points{4}.Location.Y=33.93;
points{4}.Location.Z=0;
points{4}.Orientation.Heading=349.2; %[degree]
%%
%Save the xp's changes to the PB file
 xp.saveToFile(xpName);

%Convert the PB to PEX using the writeToPexFile function
pathToTemplatePex = ['C:\Users\adeye\Desktop\real_world_data\TemplatePexFile\TemplatePexFile.pex'];
experimentPexFile = [prescan.experiment.getExperimentName '.pex'];
writeFlexRoadToPexFile(xpName,experimentPexFile,pathToTemplatePex,points);%,centerlineOffset);

%Run the experiment directly from Matlab
%prescan.api.simulink.run(xp,'StopTime','0','Regenerate','on');