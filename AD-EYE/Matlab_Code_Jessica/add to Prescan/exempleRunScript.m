%Refreshes the PB file based on the content of PEX file
prescan.experiment.convertPexToDataModels()

%Get exp name and load it for use in DMAPI
xpName = prescan.experiment.getDefaultFilename();
xp = prescan.api.experiment.loadExperimentFromFile(xpname);

%This is a struct of all objects you can create via DMAPI (user imported models also work)
supportedObjectTypes = xp.objectTypes;
objTypeToAdd = supportedObjectTypes.Audi_A8_Sedan;

%Some random function to place the objects in the scene
numOfobjToAdd = 30;
x = 2*pi*linspace(0,10,numOfobjToAdd);
y = 10*sin(x);
z = 10*cos(x) + 20;

%Create objects and set their position
for i=1:numOfobjToAdd
    
    obj = xp.createObject(objTypeToAdd);
    obj.pose.position.setXYZ(x(i),y(i),z(i));
    
end

%Save the xp's changes to the PB file
xp.saveToFile(xpName);

%Convert the PB to PEX using the writeToPexFile function
pathToTemplatePex = [pwd '\TemplatePexfile\TemplatePexFile.pex'];
experimentPexFile = [prescan.experiment.getExperimentName '.pex'];
writeToPexFile(xpName,experimentPexFile,pathToTemplatePex);

%Run the experiment directly from Matlab
prescan.api.simulink.run(xp,'StopTime','0','Regenerate','on');