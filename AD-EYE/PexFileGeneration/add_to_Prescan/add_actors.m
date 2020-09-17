% input:
%     actors:cell with:
%         actors_to_add{i}.position: position.x, position.y, position.z [meter]
%         actors_to_add{i}.ObjectType: the type of the object. It is suppose that the object is a supported Object like 'Audi_A8_Sedan'

        
function add_actors(actors_to_add)
%Refreshes the PB file based on the content of PEX file
prescan.experiment.convertPexToDataModels()

%Get exp name and load it for use in DMAPI
xpName = prescan.experiment.getDefaultFilename();
xp = prescan.api.experiment.loadExperimentFromFile(xpName);

%This is a struct of all objects you can create via DMAPI (user imported models also work)
%supportedObjectTypes = xp.objectTypes;


%Some random function to place the objects in the scene
numOfobjToAdd = length(actors_to_add);

%Create objects and set their position
for i=1:numOfobjToAdd
    
    objTypeToAdd=actors_to_add{i}.ObjectType;
    obj = xp.createObject(objTypeToAdd);
    x=actors_to_add{i}.position.x;
    y=actors_to_add{i}.position.y;
    z=actors_to_add{i}.position.z;
    
    obj.pose.position.setXYZ(x,y,z);
    
end

%Save the xp's changes to the PB file
xp.saveToFile(xpName);

%Convert the PB to PEX using the writeToPexFile function
pathToTemplatePex = ['C:\Users\adeye\Desktop\real_world_data\TemplatePexFile\TemplatePexFile.pex'];
experimentPexFile = [prescan.experiment.getExperimentName '.pex'];
writeToPexFile(xpName,experimentPexFile,pathToTemplatePex);
end
