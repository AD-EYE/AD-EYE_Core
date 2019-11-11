function delete_files(name_experiment,folder_name)

cd(strcat("..\..\Experiments\",folder_name,"\Simulation\"))

delete(strcat(name_experiment,".pex"))
delete(strcat(name_experiment,".pb"))
delete(strcat(name_experiment,".slx"))

% files =dir(strcat(name_experiment,"*"));
%       files_changed = files;
% % Loop through each file
% for id = 1:length(files)
% %rename file_name
% files_changed(id).name = convertStringsToChars(strrep(convertCharsToStrings(files(id).name),name_experiment,folder_name));
% %save file with new name
%       movefile(strcat( files(id).folder,"\",files(id).name), strcat( files_changed(id).folder,"\",files_changed(id).name) );
% end
% 
% end

%Go to folder to load xml file
cd( '..\..\..\OpenSCENARIO\Code\')