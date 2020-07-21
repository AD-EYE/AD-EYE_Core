%Refreshes the PB file based on the content of PEX file
prescan.experiment.convertPexToDataModels()

%Get exp name and load it for use in DMAPI
xpName = prescan.experiment.getDefaultFilename();
xp = prescan.api.experiment.loadExperimentFromFile(xpName);
% 
%define road id and joint id
RoadA_Id='CurvedRoad_3';
RoadB_Id='CurvedRoad_4';
JointaId=1;
JointbId=0;


pathToTemplatePex = ['C:\Users\adeye\Desktop\real_world_data\TemplatePexFile\TemplatePexFile.pex'];
ExperimentPexFile = [prescan.experiment.getExperimentName '.pex'];

%add connection to the pex file
addLinkBetweenRoads(RoadA_Id,RoadB_Id,JointaId,JointbId,ExperimentPexFile,pathToTemplatePex)

%Run the experiment directly from Matlab
prescan.api.simulink.run(xp,'StopTime','0','Regenerate','on');