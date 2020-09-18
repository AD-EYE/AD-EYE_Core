%This function writes PB content into Experiment's PEX file so that the experiment can
%be modified from the GUI. This function ONLY add objects that are under
%actor category in the GUI (e.g cars, buildings, pedesterian etc) and not
%objects like roads and trajectories
%
%Inputs:
%      1-Experiment PB File 
%      2-Experiment PEX File that is to be written
%      3-Template PEX file containing relevant XML data
%
%
%Outpus:
%      None - This function creates & overwrites the experiment PEX file
%      A backup of the current PEX file will be made with the timestamp
%      Simply replace the PEX file with its backup to revent changes
%
%Example:
%        FcnCreateCS('Experiment.pb','Experiment.pex','TemplateExperiment.pex')
%
%Limitations:
%   1.For function to work, the PBCamera plugin must be disabled from the
%   experiment to skip certain checks regarding car's light IDs (fixed in
%   2020.2?)
%




function writeActorToPexFile(ExperimentPBFile,ExperimentPexFile,TemplatePexFile)


%Load All Files
pexFileName = ExperimentPexFile;
actorsTemplate = TemplatePexFile;
pbFileName = ExperimentPBFile;

%Make backup of the current PEX file
backupFolderPath = [pwd '\BackupPEXFiles'];
if ~exist(backupFolderPath)
    mkdir(backupFolderPath);
end

currentTime = datestr(now,'yy-mm-dd_HH-MM-SS');
copyfile([pwd '\' pexFileName], [backupFolderPath '\Backup_' currentTime '_' pexFileName]);

%Convert PEX to STRUCT
disp('Loading the experiment and template PEX files...')
loadedPexFile = xml2struct(pexFileName);
loadedTemplate = xml2struct(actorsTemplate);

myExp = prescan.experiment.readDataModels(pbFileName);
allExpObjects = myExp.worldmodel.object;

actorIndex = 1;
for i=1:length(allExpObjects)
    
    %Get Actor properties from PB file
    currentObjectCategoryName = allExpObjects{i,1}.objectTypeName;
    currentObjectName = allExpObjects{i,1}.name;
    currentObjectUniqueID = allExpObjects{i,1}.uniqueID;
    currentObjectNumericalID = allExpObjects{i,1}.numericalID;
    currentObjectPosition = allExpObjects{i,1}.pose.position;
    currenctObjectOrientation = allExpObjects{i,1}.pose.orientation;
 
    %Get the correct actor template depending on the Actor property
    currentActorStruct = getCorrectActorStruct(currentObjectCategoryName,loadedTemplate);

    
    if ~isempty(currentActorStruct) 
        
        %If you don't want any specific item to show up in the CS, filter
        %them here!!!
%         if ~contains(lower(currentObjectCategoryName),'house')
%             %Show everything in CS except houses
%             currentActorStruct.ObjectSimulatorInfo.Attributes.AlwaysOnCompilationSheet = 'true';
%         end
        
        
        %Set the correct properties for each Actor in the STRUCT
        currentActorStruct.Attributes.ActorKind = currentObjectCategoryName;
        currentActorStruct.Attributes.NumericalID = num2str(currentObjectNumericalID);
        currentActorStruct.Attributes.UniqueId = num2str(currentObjectUniqueID);
        currentActorStruct.Attributes.id = currentObjectName;
        
        currentActorStruct.Location.Attributes.X = num2str(currentObjectPosition.x);
        currentActorStruct.Location.Attributes.Y = num2str(currentObjectPosition.y);
        currentActorStruct.Location.Attributes.Z = num2str(currentObjectPosition.z);
        
        currentActorStruct.Orientation.Attributes.Bank = num2str(rad2deg(currenctObjectOrientation.roll));
        currentActorStruct.Orientation.Attributes.Heading = num2str(rad2deg(currenctObjectOrientation.yaw));
        currentActorStruct.Orientation.Attributes.Tilt = num2str(rad2deg(currenctObjectOrientation.pitch));
        
            
        %Set attachement point ID of pedesterians to -1 (Prescan should dynamically assign some
        %uniqueID to it
        %Check if object has attachment ID
        attachementIDFieldName = fieldnames(currentActorStruct.AttachmentPointIds);
        if attachementIDFieldName(1) == "item"
            currentActorStruct.AttachmentPointIds.item.value.int.Text = num2str(-1);
        end
        
        loadedPexFile.Experiment.Actors.Actor{1,actorIndex} = currentActorStruct;
         loadedPexFile.Experiment.Actors
        actorIndex = actorIndex + 1;

            
        
        
    end
        
end

%Convert the populated STRUCT to PEX
disp('Overwriting changes to PEX file...')
struct2xml(loadedPexFile,pexFileName)



%Overwriting the current PEX file with the populated one
copyfile([pwd '\' pexFileName '.xml'], [pwd '\' pexFileName]);

disp(['Done...A back up of original PEX file is made at: ' backupFolderPath '\Backup_' currentTime '_' pexFileName]);

%Function to get the correct template for each Actor
function [correspondingActorStruct] = getCorrectActorStruct(actorCategoryName,loadedTemplate)


actorsInTemplateList = loadedTemplate.Experiment.Actors.Actor;
correspondingActorStruct = '';


for j=1:length(actorsInTemplateList)
    
    try
        templateActorName = actorsInTemplateList{j}.Attributes.ActorKind;
        
    catch
        templateActorName = '';
    end
    
    if strcmp(actorCategoryName,templateActorName)
        
        correspondingActorStruct = actorsInTemplateList{j};
        
    end
    
end

    

end
end