function [Lateral_events,Longitudinal_events] = trajectory_counter(models,Struct_OpenSCENARIO,trajectory_variable)

Lateral_events = [];
Longitudinal_events = [];

if(isfield(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard,'Story'))
    a = length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,1}.Act);
        Lateral_events = zeros(1,a);
        Longitudinal_events = zeros(1,a);


    for p = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story  ) %Number of Stories
        
        for a= 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,p}.Act) %Number of acts


            if( exist('trajectory_variable','var') == 1)

                for j = 1:length(models.worldmodel.object)
                    %check which j car in prescan it has the same story name
                    if(  convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1, p}.Act{1,a}.ManeuverGroup.Actors.EntityRef.Attributes.entityRef)  == convertCharsToStrings(models.worldmodel.object{j, 1}.name) )
                        if(isfield(convertCharsToStrings(trajectory_variable),convertCharsToStrings(models.worldmodel.object{j, 1}.name)) == 1 )                 

                            %number of Maneuvers
                            for m = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,p}.Act{1,a}.ManeuverGroup.Maneuver)%Number of Maneuvers                        
                                %number of events
                                for i = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,p}.Act{1,a}.ManeuverGroup.Maneuver{1,m}.Event)                         

                                    if(isfield(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,p}.Act{1,a}...
                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name)),"Longitudinal") == 1 )

                                        Longitudinal_events(1,a)=Longitudinal_events(1,a)+1;                                
                                    end

                                    if(isfield(convertCharsToStrings(trajectory_variable.(models.worldmodel.object{j, 1}.name).(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,p}.Act{1,a}...
                                            .ManeuverGroup.Maneuver{1,m}.Event{1, i}.Attributes.name)),"Lateral") == 1 )

                                        Lateral_events(1,a) = Lateral_events(1,a)+1;                                
                                    end


                                end %number of events
                            end%number of Maneuver{1,m}s

                        end %see if name exists in trajectory_variable
                    end %see if name in story p corresponds to which j prescan object



                end %Second  loop
            end%if trajectory_varible exists
        end %Loop for number of acts

    end %Main for loop number of stories

end


end%function