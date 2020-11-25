function delete_files(name_experiment,folder_name)

cd(strcat("..\..\Experiments\",name_experiment,"\OpenScenario\Results\",folder_name,"\OpenScenario\"))

delete(strcat(name_experiment,".pex"))
delete(strcat(name_experiment,".pb"))
delete(strcat(name_experiment,".slx"))

% name_experiment = "Map_pedestrian_autoware"
% folder_name = "Map_pedestrian_autoware2"

% files =dir(strcat(name_experiment,"*"));
%       files_changed = files;
% % Loop through each file
% for id = 1:length(files)
%       delete(files(id).name)
% end


% 
% %Go to folder to load xml file
cd( '..\..\..\..\..\..\OpenSCENARIO\Code\')
end