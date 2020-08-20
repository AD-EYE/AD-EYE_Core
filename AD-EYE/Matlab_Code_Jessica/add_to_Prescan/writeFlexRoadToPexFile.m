function writeFlexRoadToPexFile(ExperimentPBFile,ExperimentPexFile,RoadPexFile,points)
  
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
nbFlex=1; %counter for number of Bezier road

for i=1:length(allExpRoads)
    
    %we would like modify only road add on pb file and count the number of
    %road and the number of Bezier road on Pex file
    objectTypeName=allExpRoads{i,1}.objectTypeName;
    if  not(strcmp(objectTypeName, 'Road' ))
        if strcmp(objectTypeName,'CubicSplineRoad')
            roadIndex= roadIndex+1;
            nbFlex=nbFlex+1;
        elseif strcmp(objectTypeName,'BezierRoad')
            roadIndex= roadIndex+1;
         elseif strcmp(objectTypeName,'XCrossing')
            roadIndex= roadIndex+1;
        elseif strcmp(objectTypeName,'YCrossing')
            roadIndex= roadIndex+1;
         elseif strcmp(objectTypeName,'Roundabout')
            roadIndex= roadIndex+1;
        end
    else
    
    %Get Road properties from PB file
    currentObjectUniqueID = allExpRoads{i,1}.uniqueID;
    currentObjectNumericalID= allExpRoads{i,1}.numericalID;
    currentOjectTypeId= allExpRoads{i,1}.objectTypeID;
    currentObjectPosition = allExpRoads{i,1}.pose.position;
    currentObjectOrientation = allExpRoads{i,1}.pose.orientation;
    currentObjectOffset = points{1}.Offset;
    
    %Get the correct road template  
    currentRoadStruct=getCorrectRoadStruct('CubicSplineRoad',loadedTemplate);
    
        %Set the correct properties for Bezier road in the STRUCT
        currentRoadStruct.Attributes.id = strcat('FlexRoad_',num2str(nbFlex));
        currentRoadStruct.Attributes.NumericalID = num2str(currentObjectNumericalID);
        currentRoadStruct.Attributes.UniqueId = num2str(currentObjectUniqueID);
        currentRoadStruct.Attributes.ObjectTypeID=num2str(currentOjectTypeId);
        currentRoadStruct.Attributes.RelativeHeading=num2str(points{1}.relativeHeading);
        currentRoadStruct.Attributes.ControlPoint1Distance=num2str(points{1}.EntryTension);
        currentRoadStruct.Attributes.ControlPoint2Distance=num2str(points{1}.ExitTension);
        
        currentRoadStruct.Location.Attributes.X = num2str(currentObjectPosition.x);
        currentRoadStruct.Location.Attributes.Y = num2str(currentObjectPosition.y);
        currentRoadStruct.Location.Attributes.Z = num2str(currentObjectPosition.z);
        
        %currentRoadStruct.Orientation.Attributes.Bank = num2str(rad2deg(currentObjectOrientation.roll));
        currentRoadStruct.Orientation.Attributes.Heading = num2str(currentObjectOrientation.yaw);
        %currentRoadStruct.Orientation.Attributes.Tilt = num2str(rad2deg(currentObjectOrientation.pitch));

        currentRoadStruct.Attributes.Xoffset = num2str(currentObjectOffset.x);
        currentRoadStruct.Attributes.Yoffset = num2str(currentObjectOffset.y);
        currentRoadStruct.Attributes.Zoffset = num2str(currentObjectOffset.z);
        
        currentRoadStruct.CentralLineDefinition.Attributes.UniqueId=num2str(5*roadIndex);
        currentRoadStruct.LaneLineDefinitions.LaneLineDefinition.Attributes.UniqueId=num2str(5*roadIndex+1);
        currentRoadStruct.CurbLineDefinitions.LaneLineDefinition{1,1}.Attributes.UniqueId=num2str(5*roadIndex+2);
        currentRoadStruct.CurbLineDefinitions.LaneLineDefinition{1,2}.Attributes.UniqueId=num2str(5*roadIndex+3);
        currentRoadStruct.CrossSections.RoadCrossSection{1,1}.Attributes.UniqueId=num2str(900+10*nbFlex);
        currentRoadStruct.CrossSections.RoadCrossSection{1,1}.CentralLineDefinition.Attributes.UniqueId=num2str(900+10*nbFlex+1)
        
        for a=2:length(points)
            % define the correct structure
            currentRoadStruct.CrossSections.RoadCrossSection{1,a}=currentRoadStruct.CrossSections.RoadCrossSection{1,2};
            %modify parameters
            currentRoadStruct.CrossSections.RoadCrossSection{1,a}.Attributes.id=strcat('FlexRoad_',num2str(nbFlex),'CubicSplineCrossSection_',num2str(a-2));
            currentRoadStruct.CrossSections.RoadCrossSection{1,a}.Attributes.EntryTension=points{a}.EntryTension;
            currentRoadStruct.CrossSections.RoadCrossSection{1,a}.Attributes.ExitTension=points{a}.ExitTension;
            currentRoadStruct.CrossSections.RoadCrossSection{1,a}.Location.Attributes.X=points{a}.Location.X;
            currentRoadStruct.CrossSections.RoadCrossSection{1,a}.Location.Attributes.Y=points{a}.Location.Y;
            currentRoadStruct.CrossSections.RoadCrossSection{1,a}.Location.Attributes.Z=points{a}.Location.Z;
            currentRoadStruct.CrossSections.RoadCrossSection{1,a}.Orientation.Attributes.Heading=points{a}.Orientation.Heading;
            % change uniqueId 
            currentRoadStruct.CrossSections.RoadCrossSection{1,a}.Attributes.UniqueId=num2str(900+10*nbFlex+a);
        end
        
        currentRoadStruct.CrossSections.RoadCrossSection{1,length(points)+1}=currentRoadStruct.CrossSections.RoadCrossSection{1,1};
        currentRoadStruct.CrossSections.RoadCrossSection{1,length(points)+1}.Attributes.UniqueId=num2str(900+10*nbFlex+length(points)+1);
        currentRoadStruct.CrossSections.RoadCrossSection{1,length(points)+1}.CentralLineDefinition.Attributes.UniqueId=num2str(900+10*nbFlex+length(points)+2)
         
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


for a=1:length(RoadInTemplateList)
    
    try
        templateActorName = RoadInTemplateList{a}.Attributes.xsi_colon_type;
        
    catch
        templateActorName = '';
    end
    
    if strcmp(roadTypeName,templateActorName)
        
        correspondingRoadStruct = RoadInTemplateList{a};
        
    end
    
end

    

end

end