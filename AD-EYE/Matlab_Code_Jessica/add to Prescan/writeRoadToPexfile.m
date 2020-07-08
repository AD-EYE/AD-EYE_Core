ExperimentPBFile='C:\Users\adeye\Desktop\real_world_data\Experiment\Experiment.pb';
EperimentPexFile='C:\Users\adeye\Desktop\real_world_data\Experiment\Experiment.pex';
TemplatePexFile='';
function writeRoadToPexFile(ExperimentPBFile,ExperimentPexFile,TemplatePexFile)
    
    %Load All Files
    pexFileName = ExperimentPexFile;
    actorsTemplate = TemplatePexFile;
    pbFileName = ExperimentPBFile;
    
    %Make backup of the currnet PEX file
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
    
    roadIndex = 1; %first modification for road
    for i=1:length(allExpObjects)

        %Get Road properties from PB file
        currentObjectCategoryName = allExpObjects{i,1}.objectTypeName;
        currentObjectName = allExpObjects{i,1}.name;
        currentObjectUniqueID = allExpObjects{i,1}.uniqueID;
        currentObjectNumericalID = allExpObjects{i,1}.numericalID;
        currentObjectPosition = allExpObjects{i,1}.pose.position;
        currenctObjectOrientation = allExpObjects{i,1}.pose.orientation;
        currentObjectNumberofLanes=allExpObjects{i,l}.NumberofLanes;
        (currentObjectRoadLength=allExpObjects{i,l}.RoadLength

        %Get the correct actor template depending on the Actor property
        currentRoadStruct = getCorrectActorStruct(currentObjectCategoryName,loadedTemplate);


        if ~isempty(currentRoadStruct) 

            %If you don't want any specific item to show up in the CS, filter
            %them here!!!
            if ~contains(lower(currentObjectCategoryName),'house')
                %Show everything in CS except houses
                currentRoadStruct.ObjectSimulatorInfo.Attributes.AlwaysOnCompilationSheet = 'true';
            end


            %Set the correct properties for each Actor in the STRUCT
            %need to modify this for add road
            currentRoadStruct.Attributes.type = currentObjectCategoryName;
            currentRoadStruct.Attributes.NumericalID = num2str(currentObjectNumericalID);
            currentRoadStruct.Attributes.UniqueId = num2str(currentObjectUniqueID);
            currentRoadStruct.Attributes.id = currentObjectName;
            currentRoadStruct.Attributes.MasSpeed="50";
            currentRoadStruct.Attributes.NumberofLanes = num2str(currentObjectNumberofLanes);
            currentRoadStruct.Attributes.RoadLength= num2str(currentObjectRoadLength);
            
            currentRoadStruct.Location.Attributes.X = num2str(currentObjectPosition.x);
            currentRoadStruct.Location.Attributes.Y = num2str(currentObjectPosition.y);
            currentRoadStruct.Location.Attributes.Z = num2str(currentObjectPosition.z);

            currentRoadStruct.Orientation.Attributes.Bank = num2str(rad2deg(currenctObjectOrientation.roll));
            currentRoadStruct.Orientation.Attributes.Heading = num2str(rad2deg(currenctObjectOrientation.yaw));
            currentRoadStruct.Orientation.Attributes.Tilt = num2str(rad2deg(currenctObjectOrientation.pitch));


            %Set attachement point ID of pedesterians to -1 (Prescan should dynamically assign some
            %uniqueID to it
            %Check if object has attachment ID
            attachementIDFieldName = fieldnames(currentRoadStruct.AttachmentPointIds);
            if attachementIDFieldName(1) == "item"
                currentRoadStruct.AttachmentPointIds.item.value.int.Text = num2str(-1);
            end

            loadedPexFile.Experiment.Actors.Actor{1,roadIndex} = currentRoadStruct;
            roadIndex = roadIndex + 1;




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
