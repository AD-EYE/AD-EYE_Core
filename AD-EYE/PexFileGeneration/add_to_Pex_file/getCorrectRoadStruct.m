%Function to get the correct template for each road
% input:
%   - the name of the type of the road: exemple 'BezierRoad'
%   - the template pex file convert into structure format

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