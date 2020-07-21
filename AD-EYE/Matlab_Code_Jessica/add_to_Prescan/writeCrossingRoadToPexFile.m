function writeCrossingRoadToPexFile(ExperimentPBFile,ExperimentPexFile,RoadPexFile,type)
  
%load all files
pexFileName=ExperimentPexFile;
pbFileName=ExperimentPBFile;
RoadTemplate=RoadPexFile;
    
%Make backup of the currnet PEX file
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

%get all roads on the pb file 
myExp = prescan.experiment.readDataModels(pbFileName);
allExpRoads = myExp.worldmodel.object;
roadIndex = 1;
nbCross=1;

for i=1:length(allExpRoads)
    
    objectTypeName=allExpRoads{i,1}.objectTypeName;
    if  not(strcmp(objectTypeName, 'Road' ))
        if strcmp(objectTypeName,'BezierRoad')
            roadIndex= roadIndex+1;
        elseif strcmp(objectTypeName,'XCrossing')
            roadIndex= roadIndex+1;
            if strcmp(type,'X')
                nbCross=nbCross+1;
            end
        elseif strcmp(objectTypeName,'YCrossing')
            roadIndex= roadIndex+1;
            if strcmp(type,'Y')
                nbCross=nbCross+1;
            end
         elseif strcmp(objectTypeName,'roundabout')
            roadIndex= roadIndex+1;
        end
    else
    
    %Get Road properties from PB fil
    currentObjectUniqueID = allExpRoads{i,1}.uniqueID;
    currentObjectNumericalID= allExpRoads{i,1}.numericalID;
    currentObjectPosition = allExpRoads{i,1}.pose.position;
    currentObjectOrientation = allExpRoads{i,1}.pose.orientation;
    
    %Get the correct road template  
    currentRoadStruct=getCorrectRoadStruct(loadedTemplate,strcat(type,'Crossing'));
    
        %Set the correct properties for each road in the STRUCT
        currentRoadStruct.Attributes.xsi_colon_type=strcat(type,'Crossing');
        currentRoadStruct.Attributes.id = strcat(type,'Crossing_',num2str(nbCross));
        currentRoadStruct.Attributes.NumericalID = num2str(currentObjectNumericalID);
        currentRoadStruct.Attributes.UniqueId = num2str(currentObjectUniqueID);
        
        currentRoadStruct.Location.Attributes.X = num2str(currentObjectPosition.x);
        currentRoadStruct.Location.Attributes.Y = num2str(currentObjectPosition.y);
        currentRoadStruct.Location.Attributes.Z = num2str(currentObjectPosition.z);
        
%         currentRoadStruct.Orientation.Attributes.Bank = num2str(rad2deg(currentObjectOrientation.roll));
%         currentRoadStruct.Orientation.Attributes.Heading = num2str(rad2deg(currentObjectOrientation.yaw));
%         currentRoadStruct.Orientation.Attributes.Tilt = num2str(rad2deg(currentObjectOrientation.pitch));
        
        loadedPexFile.Experiment.InfraStructure.RoadSegments.RoadSegment{1,roadIndex} = currentRoadStruct;
        
        roadIndex = roadIndex + 1;
    end   
 end
        


%Convert the populated STRUCT to PEX
disp('Overwriting changes to PEX file...')
struct2xml(loadedPexFile,pexFileName)



%Overwriting the current PEX file with the populated one
copyfile([pwd '\' pexFileName '.xml'], [pwd '\' pexFileName]);

disp(['Done...A back up of original PEX file is made at: ' backupFolderPath '\Backup_' currentTime '_' pexFileName]);


%Function to get the correct template for each road
function [correspondingRoadStruct] = getCorrectRoadStruct(loadedTemplate,nameCross)


RoadInTemplateList = loadedTemplate.Experiment.InfraStructure.RoadSegments.RoadSegment;
correspondingRoadStruct = '';


for j=1:length(RoadInTemplateList)
    
    try
        templateActorName = RoadInTemplateList{j}.Attributes.xsi_colon_type;
        
    catch
        templateActorName = '';
    end
    
    if strcmp(nameCross,templateActorName)
        
        correspondingRoadStruct = RoadInTemplateList{j};
        
    end
    
end

    

end
end