function ps_copy2subdir(src,maindir,subdir)
    %PS_COPY2SUBDIR copy files to subfolder 'subdir' inside maindir
    
    subfolder = fullfile(maindir,subdir);
    try
        if ~exist(subfolder,'dir')
            [status,message,messageId] = mkdir(subfolder); %#ok
        end
    catch ex
        disp([ex.message ': ' subfolder])
    end
    try
        [status,message,messageId]=copyfile(src,subfolder); %#ok
    catch ex
        disp([ex.message ': ' src '->' subfolder])
    end
end

