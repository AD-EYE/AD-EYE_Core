experimentPexFile = [prescan.experiment.getExperimentName '.pex'];
RoadModify='StraightRoad_1';
modifyRoadLocation(experimentPexFile,RoadModify,10,10,10);

function modifyRoadLocation(ExperimentPexFile,RoadModify,newX,newY,newZ)

%load the file
pexFileName=ExperimentPexFile;

%Make backup of the currnet PEX file
backupFolderPath = [pwd '\BackupPEXFiles'];
if ~exist(backupFolderPath)
    mkdir(backupFolderPath);
end

currentTime = datestr(now,'yy-mm-dd_HH-MM-SS');
%copyfile([pwd '\' pexFileName], [backupFolderPath '\Backup_' currentTime '_' pexFileName]);

%Convert PEX to STRUCT
disp('Loading the experiment and template PEX files...')
loadedPexFile = xml2struct(pexFileName);

%modification Location
currentRoadStruct=getCorrectRoadStruct(RoadModify,loadedPexFile);
currentRoadStruct.Location.Attributes.X=num2str(newX);
currentRoadStruct.Location.Attributes.Y=num2str(newY);
currentRoadStruct.Location.Attributes.Z=num2str(newZ);

%Convert the populated STRUCT to PEX
disp('Overwriting changes to PEX file...')
struct2xml(loadedPexFile,pexFileName)



%Overwriting the current PEX file with the populated one
copyfile([pwd '\' pexFileName '.xml'], [pwd '\' pexFileName]);

disp(['Done...A back up of original PEX file is made at: ' backupFolderPath '\Backup_' currentTime '_' pexFileName]);


    function [CorrespondingRoadStruct]= getCorrectRoadStruct(nameRoad,loadedPexFile)
        
        roadInPexList=loadedPexFile.Experiment.InfraStructure.RoadSegments.RoadSegment;
        CorrespondingRoadStruct='';
        
        for j=1:langht(roadPexList)
            try
                currentRoadName=roadInPexList{j}.Atributes.name;
            catch
                currentRoadName='';
            end
            if strcmp(nameRoad,currentRoadName)
                CorrespondingRoadStruct = roadInPexList{j};
            end
        end
    end
end

