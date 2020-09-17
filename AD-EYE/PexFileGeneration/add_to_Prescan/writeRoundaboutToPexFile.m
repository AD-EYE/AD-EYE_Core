function writeRoundaboutToPexFile(ExperimentPBFile,ExperimentPexFile,RoadPexFile,roads_to_add)
  
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
allExpObjects = myExp.worldmodel.object; %On this varaible we have all objects on the pb file (roads, trees, cars ...)
roadIndex = 1;
nbRoundabout=1;
indexRoadsAdd=1;

for i=1:length(allExpObjects)
    
    %we would like modify only road add on pb file and count the number of
    %road and the number of Bezier road on Pex file
    objectTypeName=allExpObjects{i,1}.objectTypeName;
    if  not(strcmp(objectTypeName, 'Road' ))
        if strcmp(objectTypeName,'BezierRoad')
            roadIndex= roadIndex+1;
        elseif strcmp(objectTypeName,'CubicSplineRoad')
            roadIndex= roadIndex+1;
        elseif strcmp(objectTypeName,'XCrossing')
            roadIndex= roadIndex+1;
        elseif strcmp(objectTypeName,'YCrossing')
            roadIndex= roadIndex+1;
         elseif strcmp(objectTypeName,'Roundabout')
            roadIndex= roadIndex+1;
            nbRoundabout= nbRoundabout+1;
        elseif strcmp(objectTypeName,'StraightRoad')
            roadIndex=roadIndex+1;
        end
    else
    
    %Get Road properties from PB file
    currentObjectCoGOffset =allExpObjects{i,1}.cogOffset;
    currentObjectUniqueID = allExpObjects{i,1}.uniqueID;
    currentObjectNumericalID= allExpObjects{i,1}.numericalID;
    currentObjectPosition = allExpObjects{i,1}.pose.position;
    currentObjectOrientation = allExpObjects{i,1}.pose.orientation;
    
    %Get the correct road template  
    currentRoadStruct=getCorrectRoadStruct(loadedTemplate,'Roundabout');
    
        %Set the correct properties for each road in the STRUCT
        currentRoadStruct.Attributes.xsi_colon_type='Roundabout';
        currentRoadStruct.Attributes.id = strcat('Roundabout_',num2str(nbRoundabout));
        currentRoadStruct.Attributes.NumericalID = num2str(currentObjectNumericalID);
        currentRoadStruct.Attributes.UniqueId = num2str(currentObjectUniqueID);
        
        currentRoadStruct.Location.Attributes.X = num2str(currentObjectPosition.x);
        currentRoadStruct.Location.Attributes.Y = num2str(currentObjectPosition.y);
        currentRoadStruct.Location.Attributes.Z = num2str(currentObjectPosition.z);
        
        currentRoadStruct.Orientation.Attributes.Heading = num2str(currentObjectOrientation.yaw);
        
        currentRoadStruct.CoGOffset.Attributes.X = num2str(currentObjectCoGOffset.x);
        currentRoadStruct.CoGOffset.Attributes.Y = num2str(currentObjectCoGOffset.y);
        currentRoadStruct.CoGOffset.Attributes.Z = num2str(currentObjectCoGOffset.z);
        
        %definition of position of branches
        for k=1:4
            currentRoadStruct.CrossSections.RoadCrossSection{1,k}.Attributes.Heading=num2str(roads_to_add{indexRoadsAdd}.headings{k});
        end
        
        %add properties to the pex file convert into structure
        loadedPexFile.Experiment.InfraStructure.RoadSegments.RoadSegment{1,roadIndex} = currentRoadStruct;
        
        roadIndex = roadIndex + 1;
        indexRoadsAdd=indexRoadsAdd+1;
        
    end   
 end
        


%Convert the populated STRUCT to PEX
disp('Overwriting changes to PEX file...')
struct2xml(loadedPexFile,pexFileName)



%Overwriting the current PEX file with the populated one
copyfile([pwd '\' pexFileName '.xml'], [pwd '\' pexFileName]);

disp(['Done...A back up of original PEX file is made at: ' backupFolderPath '\Backup_' currentTime '_' pexFileName]);

end