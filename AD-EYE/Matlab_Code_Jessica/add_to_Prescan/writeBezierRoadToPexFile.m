function writeBezierRoadToPexFile(ExperimentPBFile,ExperimentPexFile,RoadPexFile,options)
  
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

%get all objects on the pb file
myExp = prescan.experiment.readDataModels(pbFileName);
allExpRoads = myExp.worldmodel.object;
roadIndex = 1; %counter for number of roads
nbBezier=1; %counter for number of Bezier road

for i=1:length(allExpRoads)
    
    %we would like modify only road add on pb file and count the number of
    %road and the number of Bezier road on Pex file
    objectTypeName=allExpRoads{i,1}.objectTypeName;
    if  not(strcmp(objectTypeName, 'Road' ))
        if strcmp(objectTypeName,'BezierRoad')
            roadIndex= roadIndex+1;
            nbBezier=nbBezier+1;
         elseif strcmp(objectTypeName,'XCrossing')
            roadIndex= roadIndex+1;
        elseif strcmp(objectTypeName,'YCrossing')
            roadIndex= roadIndex+1;
         elseif strcmp(objectTypeName,'Roundabout')
            roadIndex= roadIndex+1;
         elseif strcmp(objectTypeName,'CubicSplineRoad')
            roadIndex= roadIndex+1;
        end
    else
    
    %Get Road properties from PB file
    currentObjectUniqueID = allExpRoads{i,1}.uniqueID;
    currentObjectNumericalID= allExpRoads{i,1}.numericalID;
    currentOjectTypeId= allExpRoads{i,1}.objectTypeID;
    currentObjectPosition = allExpRoads{i,1}.pose.position;
    currentObjectOrientation = allExpRoads{i,1}.pose.orientation;
    
    %Get the correct road template  
    currentRoadStruct=getCorrectRoadStruct('BezierRoad',loadedTemplate);
    
        %Set the correct properties for Bezier road in the STRUCT
        currentRoadStruct.Attributes.id = strcat('CurvedRoad_',num2str(nbBezier));
        currentRoadStruct.Attributes.NumericalID = num2str(currentObjectNumericalID);
        currentRoadStruct.Attributes.UniqueId = num2str(currentObjectUniqueID);
        currentRoadStruct.Attributes.ObjectTypeID=num2str(currentOjectTypeId);
        currentRoadStruct.Attributes.RelativeHeading=num2str(options.relativeHeading);
        currentRoadStruct.Attributes.Xoffset=num2str(options.deltaX);
        currentRoadStruct.Attributes.Yoffset=num2str(options.deltaY);
        currentRoadStruct.Attributes.Zoffset=num2str(options.deltaZ);
        
        currentRoadStruct.Location.Attributes.X = num2str(currentObjectPosition.x);
        currentRoadStruct.Location.Attributes.Y = num2str(currentObjectPosition.y);
        currentRoadStruct.Location.Attributes.Z = num2str(currentObjectPosition.z);
        
        %currentRoadStruct.Orientation.Attributes.Bank = num2str(rad2deg(currentObjectOrientation.roll));
        currentRoadStruct.Orientation.Attributes.Heading = num2str(currentObjectOrientation.yaw);
        %currentRoadStruct.Orientation.Attributes.Tilt = num2str(rad2deg(currentObjectOrientation.pitch));
        
        
        currentRoadStruct.CentralLineDefinition.Attributes.UniqueId=num2str(5*roadIndex);
        currentRoadStruct.LaneLineDefinitions.LaneLineDefinition.Attributes.UniqueId=num2str(5*roadIndex+1);
        currentRoadStruct.CurbLineDefinitions.LaneLineDefinition{1,1}.Attributes.UniqueId=num2str(5*roadIndex+2);
        currentRoadStruct.CurbLineDefinitions.LaneLineDefinition{1,2}.Attributes.UniqueId=num2str(5*roadIndex+3);
        
        %add properties to the pex file convert into structure
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
function [correspondingRoadStruct] = getCorrectRoadStruct(roadTypeName,loadedTemplate)


RoadInTemplateList = loadedTemplate.Experiment.InfraStructure.RoadSegments.RoadSegment;
correspondingRoadStruct = '';


for j=1:length(RoadInTemplateList)
    
    try
        templateActorName = RoadInTemplateList{j}.Attributes.xsi_colon_type;
        
    catch
        templateActorName = '';
    end
    
    if strcmp(roadTypeName,templateActorName)
        
        correspondingRoadStruct = RoadInTemplateList{j};
        
    end
    
end

    

end

end