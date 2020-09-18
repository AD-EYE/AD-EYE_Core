function writeCrossingRoadToPexFile(ExperimentPBFile,ExperimentPexFile,RoadPexFile,roads_to_add)
  
%load all files
pexFileName=ExperimentPexFile;
pbFileName=ExperimentPBFile;
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

%get all roads on the pb file 
myExp = prescan.experiment.readDataModels(pbFileName);
allExpObjects = myExp.worldmodel.object; %On this varaible we have all objects on the pb file (roads, trees, cars ...)
roadIndex = 1;
nbCross=1;
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
            if strcmp(type,'X')
                nbCross=nbCross+1;
            end
        elseif strcmp(objectTypeName,'YCrossing')
            roadIndex= roadIndex+1;
            if strcmp(type,'Y')
                nbCross=nbCross+1;
            end
         elseif strcmp(objectTypeName,'Roundabout')
            roadIndex= roadIndex+1;
        elseif strcmp(objectTypeName,'StraightRoad')
            roadIndex=roadIndex+1;
        end
    else
    
    %Get Road properties from PB fil
    currentObjectUniqueID = allExpObjects{i,1}.uniqueID;
    currentObjectNumericalID= allExpObjects{i,1}.numericalID;
    currentObjectPosition = allExpObjects{i,1}.pose.position;
    currentObjectOrientation = allExpObjects{i,1}.pose.orientation;
    currentObjectCoGOffset =allExpObjects{i,1}.cogOffset;
    
    %Get the correct road template  
    currentRoadStruct=getCorrectRoadStruct(loadedTemplate,strcat(type,'Crossing'));
    
        %Set the correct properties for each road in the STRUCT
        currentRoadStruct.Attributes.xsi_colon_type=strcat(roads_to_add{indexRoadsAdd}.type,'Crossing');
        currentRoadStruct.Attributes.id = strcat(type,'Crossing_',num2str(nbCross));
        currentRoadStruct.Attributes.NumericalID = num2str(currentObjectNumericalID);
        currentRoadStruct.Attributes.UniqueId = num2str(currentObjectUniqueID);
        
        currentRoadStruct.Location.Attributes.X = num2str(currentObjectPosition.x);
        currentRoadStruct.Location.Attributes.Y = num2str(currentObjectPosition.y);
        currentRoadStruct.Location.Attributes.Z = num2str(currentObjectPosition.z);
        
        currentRoadStruct.CoGOffset.Attributes.X = num2str(currentObjectCoGOffset.x);
        currentRoadStruct.CoGOffset.Attributes.Y = num2str(currentObjectCoGOffset.y);
        currentRoadStruct.CoGOffset.Attributes.Z = num2str(currentObjectCoGOffset.z);

        currentRoadStruct.Orientation.Attributes.Heading = num2str(currentObjectOrientation.yaw);
        
        %we will define position of branchs
        if roads_to_add{indexRoadsAdd}.type=='Y' 
            nbBranch=3;
        else
            nbBranch=4;
        end
        for k=1:nbBranch
            currentRoadStruct.CrossSections.RoadCrossSection{1,k}.Attributes.Heading=num2str(roads_to_add{indexRoadsAdd}.headingskj});
        end
        
        %add properties to the pex file convert into structure
        if i==1 & roadIndex==2 %this test is true when there already is one road on the Pex file
            RoadInformations= loadedPexFile.Experiment.InfraStructure.RoadSegments.RoadSegment; %we save informations of the road
            loadedPexFile.Experiment.InfraStructure.RoadSegments.RoadSegment={}; % We supress informations to have an array
            loadedPexFile.Experiment.InfraStructure.RoadSegments.RoadSegment{1,1}=RoadInformations; %we add on the first position of the array informations of the road
        end
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