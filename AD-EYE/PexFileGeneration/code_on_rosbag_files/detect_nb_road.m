function nb_bezier=detect_nb_road(type_road,ExperimentPBFile)
    
    pbFileName=ExperimentPBFile;
    myExp = prescan.experiment.readDataModels(pbFileName);
    allExpRoads = myExp.worldmodel.object;
    nbRoads=0;  %counter for number of type road
    for i=1:length(allExpRoads)
        objectTypeName=allExpRoads{i,1}.objectTypeName;
            if strcmp(objectTypeName,type_road)
                nbRoads=nbRoads+1;
            end
    end
    nb_bezier=nbRoads;
end
