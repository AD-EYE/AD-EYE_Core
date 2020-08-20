function  [ q ] =xosc_generation(name_experiment_template,models)




%Go to folder to load xml file
cd( convertStringsToChars(strcat("..\","OpenSCENARIO_experiments\")) )
Struct_OpenSCENARIO = xml2struct(convertStringsToChars(strcat(name_experiment_template,".xosc")));

%Allow for mulitiple stories, maneuvers and Events
%make cell of Story to allow for multiple stories
if(length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story) == 1)
    Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story=  {Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story};
end

for k = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story)
    
    %make cell of Maneuvers to allow for multiple Maneuvers
    if(length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver) == 1)
        Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver=  {Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver};
    end
    
    for i = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver)
        %make cell of Events to allow for multiple Events
        if(length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,i}.Event) == 1)
            Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,i}.Event=  {Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,i}.Event};
        end
        
    end
end



for j =1:length(models.worldmodel.object) %main for loop
    
    
    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard),'Init') == 1 )  %if Init exists
        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init),'Actions') == 1 )  %if Actions exists
            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions),'Private') == 1 )  %if Private exists                
                for k = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private) %for each private
                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}),'Action') == 1 )  %if Action exists
                        for p = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Action) %for each Action
                            
                            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Longitudinal
                            
                            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Action{1,p}),'Longitudinal') == 1 )  %if Speed exists
                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Action{1,p}.Longitudinal),'Speed') == 1 )  %if Longitudinal exists                               
                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Action{1,p}.Longitudinal.Speed),'Target') == 1 )  %if Longitudinal exists
                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Action{1,p}.Longitudinal.Speed.Target),'Absolute') == 1 )  %if Absolute exists
                                            
                                              %creating multiple xosc files
                                            L = length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Action{1,p}.Longitudinal.Speed.Target.Absolute.Attributes.value);                                            
                                            if(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Action{1,p}.Longitudinal.Speed.Target.Absolute.Attributes.value(1) == '[' &&...
                                                    Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Action{1,p}.Longitudinal.Speed.Target.Absolute.Attributes.value(L)== ']' )
                                                
                                                ERROR = 0;
                                                array =  str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Action{1,p}.Longitudinal.Speed.Target.Absolute.Attributes.value);
                                                q = length(array);
                                                Main_struct(1:length(array),1) = Struct_OpenSCENARIO;
                                                for x = 1:length(array)
                                                    Main_struct(x).OpenSCENARIO.Storyboard.Init.Actions.Private{1, k}.Action{1,p}.Longitudinal.Speed.Target.Absolute.Attributes.value= array(x);
                                                    struct2xml(Main_struct(x),convertStringsToChars(strcat(name_experiment_template,int2str(x) )));
                                                end                                                
                                                end

                                            
                                        end %check Absolute                                        
                                    end %check Target                                    
                                end %check Speed
                            end %check Longitudinal                                                     
                        end %end third for loop                        
                    end %check Action
                end %end second for loop, private               
            end %check Private
        end %check Actions
    end %check Init    
end %main for loop, number of objects in Prescan





for k = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story  ) %Number of Stories    
    %check if Entity field exists
    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Actors),'Entity') == 1 )
        %check if Maneuver field exists
        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence),'Maneuver') == 1 )
            for m = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver)%Number of Maneuvers
                %check if Event field exists
                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,m}),'Event') == 1 )
                    for j =1:length(models.worldmodel.object) %Thrid for loop
                        if(convertCharsToStrings(models.worldmodel.object{j, 1}.name) == convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Actors.Entity.Attributes.name))
                            for i = 1:length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,m}.Event  ) %Number of events
                                
                                
                                %OSCPrivateAction
                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                        .Sequence.Maneuver{1,m}.Event{1, i }.Action), "Private" )== 1)
                                    %Check if in Longitudinal field
                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,m}.Event{1, i }...
                                            .Action.Private),'Longitudinal') == 1 )
                                        
                                        %Check if in Speed field
                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,m}.Event{1, i }...
                                                .Action.Private.Longitudinal),'Speed') == 1 )
                                            %Check if in Dynamics field
                                            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,m}.Event{1, i }...
                                                    .Action.Private.Longitudinal.Speed),'Dynamics') == 1 )
                                                
                                                  %creating multiple xosc files
                                                L = length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}...
                                                    .Act.Sequence.Maneuver{1,m}.Event{1, i}.Action.Private.Longitudinal.Speed.Dynamics.Attributes.time);                                                
                                                if(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}...
                                                        .Act.Sequence.Maneuver{1,m}.Event{1, i}.Action.Private.Longitudinal.Speed.Dynamics.Attributes.time(1) == '[' && Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}...
                                                        .Act.Sequence.Maneuver{1,m}.Event{1, i}.Action.Private.Longitudinal.Speed.Dynamics.Attributes.time(L)== ']' )
                                                    
                                                     ERROR = 0;
                                                    array =  str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}...
                                                        .Act.Sequence.Maneuver{1,m}.Event{1, i}.Action.Private.Longitudinal.Speed.Dynamics.Attributes.time);
                                                    q = length(array)
                                                    Main_struct(1:length(array),1) = Struct_OpenSCENARIO;
                                                    for x = 1:length(array)
                                                        Main_struct(x).OpenSCENARIO.Storyboard.Story{1,k}...
                                                            .Act.Sequence.Maneuver{1,m}.Event{1, i}.Action.Private.Longitudinal.Speed.Dynamics.Attributes.time= array(x);
                                                        struct2xml(Main_struct(x),convertStringsToChars(strcat(name_experiment_template,int2str(x) )));
                                                    end
                                                    
                                                end
                                                
                                                
                                                
                                                %Check if in Target field
                                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,m}.Event{1, i }...
                                                        .Action.Private.Longitudinal.Speed),'Target') == 1 )
                                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,m}.Event{1, i }...
                                                            .Action.Private.Longitudinal.Speed.Target),'Relative') == 1 )
                                                        
                                                          %creating multiple xosc files
                                                        L = length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,m}.Event{1, i }...
                                                            .Action.Private.Longitudinal.Speed.Target.Relative.Attributes.value);                                                        
                                                        if(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,m}.Event{1, i }...
                                                                .Action.Private.Longitudinal.Speed.Target.Relative.Attributes.value(1) == '[' && Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,m}.Event{1, i }...
                                                                .Action.Private.Longitudinal.Speed.Target.Relative.Attributes.value(L)== ']' )
                                                                                                                       
                                                             ERROR = 0;
                                                            array =  str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,m}.Event{1, i }...
                                                                .Action.Private.Longitudinal.Speed.Target.Relative.Attributes.value);
                                                            q = length(array);
                                                            Main_struct(1:length(array),1) = Struct_OpenSCENARIO;
                                                            for x = 1:length(array)
                                                                Main_struct(x).OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,m}.Event{1, i }...
                                                                    .Action.Private.Longitudinal.Speed.Target.Relative.Attributes.value= array(x);
                                                                struct2xml(Main_struct(x),convertStringsToChars(strcat(name_experiment_template,int2str(x) )));
                                                            end
                                                            
                                                        end
                                                        
                                                        
                                                        
                                                    end %Relative field check
                                                end %Target field check
                                            end  %Dynamics field check                                            
                                        end %Speed field check
                                    end %Longitudinal field check
                                    
                                    
                                    
                                    
                                    %Check if in Lateral field
                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,m}.Event{1, i }...
                                            .Action.Private),'Lateral') == 1 )
                                        %Check if in LaneChange field
                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,m}.Event{1, i }...
                                                .Action.Private.Lateral),'LaneChange') == 1 )
                                            %Check if in Dynamics field
                                            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,m}.Event{1, i }...
                                                    .Action.Private.Lateral.LaneChange),'Dynamics') == 1 )
                                                
                                                  %creating multiple xosc files
                                                L = length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}...
                                                    .Act.Sequence.Maneuver{1,m}.Event{1, i}.Action.Private.Lateral.LaneChange.Dynamics.Attributes.time);                                                
                                                if(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}...
                                                        .Act.Sequence.Maneuver{1,m}.Event{1, i}.Action.Private.Lateral.LaneChange.Dynamics.Attributes.time(1) == '[' && Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}...
                                                        .Act.Sequence.Maneuver{1,m}.Event{1, i}.Action.Private.Lateral.LaneChange.Dynamics.Attributes.time(L)== ']' )
                                                    
                                                     ERROR = 0;
                                                    array =  str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}...
                                                        .Act.Sequence.Maneuver{1,m}.Event{1, i}.Action.Private.Lateral.LaneChange.Dynamics.Attributes.time);
                                                    q = length(array);
                                                    Main_struct(1:length(array),1) = Struct_OpenSCENARIO;
                                                    for x = 1:length(array)
                                                        Main_struct(x).OpenSCENARIO.Storyboard.Story{1,k}...
                                                            .Act.Sequence.Maneuver{1,m}.Event{1, i}.Action.Private.Lateral.LaneChange.Dynamics.Attributes.time= array(x);
                                                        struct2xml(Main_struct(x),convertStringsToChars(strcat(name_experiment_template,int2str(x) )));
                                                    end
                                                    
                                                end
                                                
                                                
                                                
                                                
                                                %Check if in Target field
                                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,m}.Event{1, i }...
                                                        .Action.Private.Lateral.LaneChange),'Target') == 1 )
                                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,m}.Event{1, i }...
                                                            .Action.Private.Lateral.LaneChange.Target),'Relative') == 1 )
                                                        
                                                          %creating multiple xosc files
                                                        L = length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,m}.Event{1, i }...
                                                            .Action.Private.Lateral.LaneChange.Target.Relative.Attributes.value);                                                        
                                                        if(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,m}.Event{1, i }...
                                                                .Action.Private.Lateral.LaneChange.Target.Relative.Attributes.value(1) == '[' && Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,m}.Event{1, i }...
                                                                .Action.Private.Lateral.LaneChange.Target.Relative.Attributes.value(L) == ']')
                                                       
                                                             ERROR = 0;
                                                            array = str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,m}.Event{1, i }...
                                                                .Action.Private.Lateral.LaneChange.Target.Relative.Attributes.value);
                                                            q = length(array);
                                                            Main_struct(1:length(array),1) = Struct_OpenSCENARIO;
                                                            for x = 1:length(array)
                                                                Main_struct(x).OpenSCENARIO.Storyboard.Story{1,k}.Act.Sequence.Maneuver{1,m}.Event{1, i }...
                                                                    .Action.Private.Lateral.LaneChange.Target.Relative.Attributes.value= array(x);
                                                                struct2xml(Main_struct(x),convertStringsToChars(strcat(name_experiment_template,int2str(x) )));
                                                            end
                                                        end
                                                        
                                                        
                                                    end %Relative field check
                                                end %Target field check
                                            end %Dynamics field check                                            
                                        end %LaneChange field check
                                    end %Lateral field check                                   
                                end%Private field check
                                
                                
                                
                                
                                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Conditions
                                
                                %Check Startconditions field
                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                        .Sequence.Maneuver{1,m}.Event{1, i}), "StartConditions") == 1)
                                    %Check ConditionGroup field
                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                            .Sequence.Maneuver{1,m}.Event{1, i}.StartConditions), "ConditionGroup") == 1)
                                        %Check Condition field
                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                .Sequence.Maneuver{1,m}.Event{1, i}.StartConditions.ConditionGroup), "Condition") == 1)
                                            %Check ByEntity field
                                            if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                    .Sequence.Maneuver{1,m}.Event{1, i}.StartConditions.ConditionGroup.Condition), "ByEntity") == 1)
                                                %Check EntityCondition field
                                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                        .Sequence.Maneuver{1,m}.Event{1, i}.StartConditions.ConditionGroup.Condition.ByEntity), "EntityCondition") == 1)
                                                    %Check Distance field
                                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                            .Sequence.Maneuver{1,m}.Event{1, i}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition), "Distance") == 1)
                                                        
                                                        a =1;%Distance indicator for AfterTermination                                                        
                                                          %creating multiple xosc files
                                                        L = length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                            .Sequence.Maneuver{1,m}.Event{1, i}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.Distance.Attributes.value);                                                        
                                                        if(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .Sequence.Maneuver{1,m}.Event{1, i}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.Distance.Attributes.value(1) == '[' &&Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .Sequence.Maneuver{1,m}.Event{1, i}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.Distance.Attributes.value(L) == ']')
                                                            

                                                             ERROR = 0;
                                                            array = str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .Sequence.Maneuver{1,m}.Event{1, i}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.Distance.Attributes.value);
                                                            q = length(array);
                                                            Main_struct(1:length(array),1) = Struct_OpenSCENARIO;
                                                            for x = 1:length(array)
                                                                Main_struct(x).OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                    .Sequence.Maneuver{1,m}.Event{1, i}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.Distance.Attributes.value= array(x);
                                                                struct2xml(Main_struct(x),convertStringsToChars(strcat(name_experiment_template,int2str(x) )));
                                                            end
                                                        end
                                                        
                                                    end %Distance field check
                                                    
                                                        %Check TimeHeadWay field
                                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .Sequence.Maneuver{1,m}.Event{1, i}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition), "TimeHeadWay") == 1)
                                                            
                                                            a= 0; %TimeHeadWay indicator for AfterTermination
                                                            %creating multiple xosc files
                                                            L = length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .Sequence.Maneuver{1,m}.Event{1, i}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.TimeHeadWay.Attributes.value);
                                                            if(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                    .Sequence.Maneuver{1,m}.Event{1, i}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.TimeHeadWay.Attributes.value(1) == '[' &&Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                    .Sequence.Maneuver{1,m}.Event{1, i}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.TimeHeadWay.Attributes.value(L) == ']')                                                                
                                                               
                                                                ERROR = 0;
                                                                array = str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                    .Sequence.Maneuver{1,m}.Event{1, i}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.TimeHeadWay.Attributes.value);
                                                                q = length(array);
                                                                Main_struct(1:length(array),1) = Struct_OpenSCENARIO;
                                                                for x = 1:length(array)
                                                                    Main_struct(x).OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                        .Sequence.Maneuver{1,m}.Event{1, i}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.TimeHeadWay.Attributes.value= array(x);
                                                                    struct2xml(Main_struct(x),convertStringsToChars(strcat(name_experiment_template,int2str(x) )));
                                                                end
                                                            end                                                           
                                                            
                                                        end %TimeHeadWay field check
                                                    end % EntityCondition field check
                                                end %ByEntity field  check
                                                
                                                
                                                
                                                
                                                %Check ByState field
                                                if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                        .Sequence.Maneuver{1,m}.Event{1, i}.StartConditions.ConditionGroup.Condition), "ByState") == 1)
                                                    %Check AfterTermination field
                                                    if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                            .Sequence.Maneuver{1,m}.Event{1, i}.StartConditions.ConditionGroup.Condition.ByState), "AfterTermination") == 1)
                                                        %Check type,name,rule field
                                                        if(isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .Sequence.Maneuver{1,m}.Event{1, i}.StartConditions.ConditionGroup.Condition.ByState.AfterTermination.Attributes), "type") == 1 &&...
                                                                isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .Sequence.Maneuver{1,m}.Event{1, i}.StartConditions.ConditionGroup.Condition.ByState.AfterTermination.Attributes), "name") == 1 &&...
                                                                isfield(convertCharsToStrings(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .Sequence.Maneuver{1,m}.Event{1, i}.StartConditions.ConditionGroup.Condition.ByState.AfterTermination.Attributes), "rule") == 1 )
                                                            
                                                            if(a == 0)
                                                                %creating multiple xosc files
                                                                L = length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                    .Sequence.Maneuver{1,m}.Event{1,  i-1}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.TimeHeadWay.Attributes.value);
                                                                if(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                        .Sequence.Maneuver{1,m}.Event{1, i-1}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.TimeHeadWay.Attributes.value(1) == '[' &&Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                        .Sequence.Maneuver{1,m}.Event{1, i-1}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.TimeHeadWay.Attributes.value(L) == ']')                                                                    

                                                                     ERROR = 0;
                                                                     array = str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                         .Sequence.Maneuver{1,m}.Event{1, i-1}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.TimeHeadWay.Attributes.value);
                                                                     q = length(array);
                                                                    Main_struct(1:length(array),1) = Struct_OpenSCENARIO;
                                                                    for x = 1:length(array)
                                                                        Main_struct(x).OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                            .Sequence.Maneuver{1,m}.Event{1, i-1}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.TimeHeadWay.Attributes.value= array(x);
                                                                        struct2xml(Main_struct(x),convertStringsToChars(strcat(name_experiment_template,int2str(x) )));
                                                                    end
                                                                end
                                                            end
                                                            
                                                            if(a == 1)
                                                          %creating multiple xosc files
                                                        L = length(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                            .Sequence.Maneuver{1,m}.Event{1, i-1}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.Distance.Attributes.value);                                                        
                                                        if(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .Sequence.Maneuver{1,m}.Event{1, i-1}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.Distance.Attributes.value(1) == '[' &&Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .Sequence.Maneuver{1,m}.Event{1, i-1}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.Distance.Attributes.value(L) == ']')

                                                            ERROR = 0;
                                                            array = str2num(Struct_OpenSCENARIO.OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                .Sequence.Maneuver{1,m}.Event{1, i-1}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.Distance.Attributes.value);
                                                            q = length(array);
                                                            Main_struct(1:length(array),1) = Struct_OpenSCENARIO;
                                                            for x = 1:length(array)
                                                                Main_struct(x).OpenSCENARIO.Storyboard.Story{1,k}.Act...
                                                                    .Sequence.Maneuver{1,m}.Event{1, i-1}.StartConditions.ConditionGroup.Condition.ByEntity.EntityCondition.Distance.Attributes.value= array(x);
                                                                struct2xml(Main_struct(x),convertStringsToChars(strcat(name_experiment_template,int2str(x) )));
                                                            end
                                                        end
                                                        
                                                            end
                                                            
                                                            
                                                        end %%Check type,name,rule field check
                                                    end %AfterTermination field check
                                                end %ByState field  check
                                            end %Condition field check
                                        end %ConditionGroup field check
                                    end %Startcondition field  check
                                end% end fourth  for loop
                            end %check object between OpenSCENARIO and Prescan
                        end %end Thrid for loop
                    end %Entity field check
                end%second for loop maneuvers
            end %Maneuver field check
        end %Event field check
    end%end main for loop
    
        if(ERROR == 1)
        disp('No multiple files created');
    else
        
        disp('Multiple files created');
    end
    
    
    
    
 cd  '..\Code\'
    
    
    
end

