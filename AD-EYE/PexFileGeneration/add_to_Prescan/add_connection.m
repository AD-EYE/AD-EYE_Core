% THis function is to link two raods. 
% It is important to notice that if roads are not side by side the function
% add a link. So it is your responsability to be sure that the id of roads
% and joints are good
% input:
%       connections: array with:
%               connections{i}.roadA_Id
%               connections{i}.roadB_Id
%               connections{i}.JointaId
%               connections{i}.JointbId
%
%RoadA_Id is the id of the first road like 'CurvedRoad_1' and RoadB_Id is
%the id of the second road. JointaId indicated if the connection is with
%the beginning of the road (0) or the end of the road (1). If it is
%Xcrossing or roundabout, JointId=0,1,2 ou 3. If it is Ycrossing,
%JointId=0,1 ou 2. 

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
