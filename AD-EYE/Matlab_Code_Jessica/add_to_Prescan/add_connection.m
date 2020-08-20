% THis function is to link two raods. 
% It is important to notice that if road are not side by side the function
% add a link. So it is your responsability to be sure that the id of road
% and joint are good
% input:
% RoadAid for exemple'Roundabout_1';
% RoadBid for exemple'YCrossing_2';
% Jointaid for exemple 3;
% Jointbid for exemple 1;

function add_connection(RoadAid,RoadBid,JointAid, JointBid)
%Refreshes the PB file based on the content of PEX file
prescan.experiment.convertPexToDataModels()

%Get exp name and load it for use in DMAPI
xpName = prescan.experiment.getDefaultFilename();
xp = prescan.api.experiment.loadExperimentFromFile(xpName);
% 
%define road id and joint id
RoadA_Id=RoadAid;
RoadB_Id=RoadBid;
JointaId=JointAid;
JointbId=JointBid;

%define template pex file and experiment pex file
pathToTemplatePex = ['C:\Users\adeye\Desktop\real_world_data\TemplatePexFile\TemplatePexFile.pex'];
ExperimentPexFile = [prescan.experiment.getExperimentName '.pex'];

%add connection to the pex file
writeConnectionToPexFile(RoadA_Id,RoadB_Id,JointaId,JointbId,ExperimentPexFile,pathToTemplatePex)
end
%Run the experiment directly from Matlab
%prescan.api.simulink.run(xp,'StopTime','0','Regenerate','on');