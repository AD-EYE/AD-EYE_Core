% THis function is to link two raods. 
% It is important to notice that if road are not side by side the function
% add a link. So it is your responsability to be sure that the id of road
% and joint are good
% input:
% RoadAid for exemple'Roundabout_1';
% RoadBid for exemple'YCrossing_2';
% Jointaid for exemple 3;
% Jointbid for exemple 1;

function add_connection(connections) %RoadAid,RoadBid,JointAid, JointBid)

%Refreshes the PB file based on the content of PEX file
prescan.experiment.convertPexToDataModels()

if length(connections)<2
    disp('Warning:if there are no connections on the experiment now, the function will work but if you use it again it will not work. If there is only one connection on the experiment now, the function will not work.');
end

%define template pex file and experiment pex file
pathToTemplatePex = ['C:\Users\adeye\Desktop\real_world_data\TemplatePexFile\TemplatePexFile.pex'];
ExperimentPexFile = [prescan.experiment.getExperimentName '.pex'];

%add connection to the pex file
writeConnectionToPexFile(connections,ExperimentPexFile,pathToTemplatePex); %RoadA_Id,RoadB_Id,JointaId,JointbId,ExperimentPexFile,pathToTemplatePex)
end
%Run the experiment directly from Matlab
%prescan.api.simulink.run(xp,'StopTime','0','Regenerate','on');