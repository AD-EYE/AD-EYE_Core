%%
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
%%

function writeConnectionToPexFile(connections,ExperimentPexFile,RoadPexFile)

%load all files
pexFileName=ExperimentPexFile;
RoadTemplate=RoadPexFile;
    
%Make backup of the current PEX file
backupFolderPath = [pwd '\BackupPEXFiles'];
if ~exist(backupFolderPath)
    mkdir(backupFolderPath);
end

currentTime = datestr(now,'yy-mm-dd_HH-MM-SS');
copyfile([pwd '\' pexFileName], [backupFolderPath '\Backup_' currentTime '_' pexFileName]);


%Convert PEX to STRUCT
disp('Loading the experiment and template PEX files...') %message for the commande
loadedPexFile = xml2struct(pexFileName); 
loadedTemplate = xml2struct(RoadTemplate);

%get the connection template
currentStruct=loadedTemplate.Experiment.InfraStructure.RoadSegmentConnections.Connection{1,1};

try 
    indexConnection=length(loadedPexFile.Experiment.InfraStructure.RoadSegmentConnections.Connection)+1;
catch
    indexConnection=1;
end

len=length(connections);
for i=1:len
    currentStruct.Attributes.id = strcat('RoadJointConnection_',num2str(indexConnection));
    currentStruct.Attributes.Road_A_UniqueId = connections{i}.RoadA_Id;
    currentStruct.Attributes.Road_B_UniqueId = connections{i}.RoadB_Id;
    currentStruct.Attributes.Joint_A_Id= num2str(connections{i}.JointaId);
    currentStruct.Attributes.Joint_B_Id= num2str(connections{i}.JointbId);
    currentStruct.Attributes.UniqueId=num2str(100*i*5);
    
    if i==1 & indexConnection==2 %this test is true when there already is one connection on the Pex file
        ConnectionOnPexFile=loadedPexFile.Experiment.InfraStructure.RoadSegmentConnections.Connection; %we save informations of the connection
        loadedPexFile.Experiment.InfraStructure.RoadSegmentConnections.Connection={}; % We supress informations to have an array
        loadedPexFile.Experiment.InfraStructure.RoadSegmentConnections.Connection{1,1}=ConnectionOnPexFile; %we add on the first position of the array informations of the connection
    end
    
    loadedPexFile.Experiment.InfraStructure.RoadSegmentConnections.Connection{1,indexConnection}=currentStruct;
    indexConnection=indexConnection+1;
    
end

 %Convert the populated STRUCT to PEX
disp('Overwriting changes to PEX file...')
struct2xml(loadedPexFile,pexFileName)



%Overwriting the current PEX file with the populated one
copyfile([pwd '\' pexFileName '.xml'], [pwd '\' pexFileName]);

disp(['Done...A back up of original PEX file is made at: ' backupFolderPath '\Backup_' currentTime '_' pexFileName]);

end

