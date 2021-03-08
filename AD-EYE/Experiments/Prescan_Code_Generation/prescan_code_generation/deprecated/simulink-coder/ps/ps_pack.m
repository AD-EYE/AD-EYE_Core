function ps_pack(modelName,buildDir,addExperiment,postBuildExt)
%PS_PACKN Pack PS generated code for deployment
%
%   Optional: also pack contents of Experiment folder
%   
%
    % Find model and zip names
    modelfile                = get_param(modelName,'FileName');        % Full absolute pathname of the Simulink model file
    expfolder                = fileparts(modelfile);                   % Full pathname of the experiment folder
    [~,expfoldername]        = fileparts(expfolder);                   % Name of the experiment folder
    zipfilename              = fullfile(expfolder,[modelName '.zip']); % Output zip
    
    % Delete old zip file
    if exist(zipfilename,'file')
        delete(zipfilename);
    end

    % create temporary zip creation folder
    zipfolder = tempname;
    mkdir(zipfolder);

    % copy required files from the rtw build directory to <foldername>/<modelbuildfolder> folder
    copy_code(expfoldername,buildDir,zipfolder);
    copy_mainfile(expfoldername,buildDir,zipfolder);
    copy_helpers(expfoldername,buildDir,zipfolder);

    % copy MATLAB rtw files to <Release> folder
    copy_rtw(zipfolder);
    
    % Add PreScan Experiment folder contents
    if addExperiment
        copy_experiment(expfolder,modelName,zipfolder)
    end
        
    if nargin >= 4
        postBuildExt(expfoldername,buildDir,zipfolder);
    end
    
    % create the zip archive
    zipdirs = find_subdirs(zipfolder);       % Zip all subdirectoris of zipfolder
    zip(zipfilename,zipdirs,zipfolder);      % Arg #3: names in zip relative to zipfolder    
    
    % delete the temporary zip folder
    rmdir(zipfolder,'s');

end

function copy_code(expfoldername,buildDir,zipfolder)

    [~,modelbuildfoldername] = fileparts(buildDir);

    ps_copy2subdir(fullfile(buildDir,'*.c'),     zipfolder,  fullfile(expfoldername,modelbuildfoldername));
    ps_copy2subdir(fullfile(buildDir,'*.cpp'),   zipfolder,  fullfile(expfoldername,modelbuildfoldername));
    ps_copy2subdir(fullfile(buildDir,'*.h'),     zipfolder,  fullfile(expfoldername,modelbuildfoldername));
    ps_copy2subdir(fullfile(buildDir,'*.mk'),    zipfolder,  fullfile(expfoldername,modelbuildfoldername));
    ps_copy2subdir(fullfile(buildDir,'*.rsp'),   zipfolder,  fullfile(expfoldername,modelbuildfoldername));
    ps_copy2subdir(fullfile(buildDir,'*.txt'),   zipfolder,  fullfile(expfoldername,modelbuildfoldername));
end

function copy_mainfile(expfoldername,buildDir,zipfolder)
    %COPY_MAINFILE copy PS main file to build folder
    %
    [~,modelbuildfoldername] = fileparts(buildDir);
    ps_copy2subdir(which('model_main.c'), zipfolder, fullfile(expfoldername,modelbuildfoldername));
    ps_copy2subdir(which('ps_main.c'), zipfolder, fullfile(expfoldername,modelbuildfoldername));
end

function copy_rtw(zipfolder)
    %COPY_RTW copy required MATLAB headers and sources files to subfolder 'matlab'
    %
    matlabfolder = 'matlab';

    rtwdir = 'simulink/include';           
    ps_copy2subdir(fullfile(matlabroot,rtwdir,'*.h'),         zipfolder, fullfile(matlabfolder,rtwdir));
    rtwdir = 'simulink/include';           
    ps_copy2subdir(fullfile(matlabroot,rtwdir,'*.hpp'),       zipfolder, fullfile(matlabfolder,rtwdir));
    rtwdir = 'rtw/c/grt';                  
    ps_copy2subdir(fullfile(matlabroot,rtwdir,'*.c'),         zipfolder, fullfile(matlabfolder,rtwdir));
    rtwdir = 'rtw/c/src';                  
    ps_copy2subdir(fullfile(matlabroot,rtwdir,'*.h'),         zipfolder, fullfile(matlabfolder,rtwdir));
    rtwdir = 'rtw/c/src';                  
    ps_copy2subdir(fullfile(matlabroot,rtwdir,'rt_logging.c'),zipfolder, fullfile(matlabfolder,rtwdir));
    rtwdir = 'rtw/c/src';                  
    ps_copy2subdir(fullfile(matlabroot,rtwdir,'rt_sim.c'),    zipfolder, fullfile(matlabfolder,rtwdir));
    rtwdir = 'rtw/c/src/ext_mode/common';  
    ps_copy2subdir(fullfile(matlabroot,rtwdir,'*.h'),         zipfolder, fullfile(matlabfolder,rtwdir));
    rtwdir = 'rtw/c/tools';                
    ps_copy2subdir(fullfile(matlabroot,rtwdir,'*.*'),         zipfolder, fullfile(matlabfolder,rtwdir));
    rtwdir = 'extern/include';             
    ps_copy2subdir(fullfile(matlabroot,rtwdir,'*.h'),         zipfolder, fullfile(matlabfolder,rtwdir));
end

function copy_helpers(expfoldername,buildDir,zipfolder)
    %COPY_HELPERS copy PS helper files to build folder
    %
    [~,modelbuildfoldername] = fileparts(buildDir);

    ps_copy2subdir(which('testpath83.bat'),     zipfolder,  fullfile(expfoldername,modelbuildfoldername));
end

function copy_experiment(expfolder,modelname,zipfolder)
    %COPY_EXPERIMENT copy experiment files to subfolder <modelname> inside zipfolder
    %
    % Excludes a number of PreScan / Simulink / Coder artifacts:
    %   * pseudo folders . and ..
    %   * Results folder
    %   * slprj folder
    %   * coder build folders
    %   * zip files *.zip
    
    % Find all files in experiment folder
    files = dir(expfolder);
    [~,expfoldername] = fileparts(expfolder);
    
    for ii=1:length(files)
        filename = files(ii).name;
        if files(ii).isdir
            % skip '.'
            if strcmp(filename,'.')
                continue;
            end
            % skip '..'
            if strcmp(filename,'..')
                continue;
            end
            % skip 'Results' folder
            if strcmp(filename,'Results')
                continue;
            end
            % skip 'slprj' folder
            if strcmp(filename,'slprj')
                continue;
            end
            % skip build folder
            if is_builddir(expfolder,modelname,filename)
                continue
            end
            % any other folder: copy to zip
            ps_copy2subdir(fullfile(expfolder,filename), zipfolder, fullfile(expfoldername,filename));
        else
            [~,~,ext] = fileparts(filename);
            % skip zip file
            if strcmpi(ext,'.zip')
                continue;
            end
            % any other file: copy to zip
            ps_copy2subdir(fullfile(expfolder,filename), zipfolder, expfoldername);
        end
    end
   
end

function [status] = is_builddir(expfolder,modelname,dirname)
    %IS_BUILDIR return true if subdirectory dirname is a coder build folder
    %
    %   Rules: 
    %       1) build folder name is <modelname>_<build_ext>
    %       2) build folder contains file rtw_proj.tmw
    %
    status = false;
    nc     = length(modelname);

    % dirname is too short, cannot be a build folder name
    if length(dirname)<(nc+1)
        return
    end

    % dirname does not start with '<modelname>_' : cannot be a build folder
    if ~strcmp(dirname(1:nc+1),[modelname,'_'])
        return;
    end

    % does not contain rtw_proj.tmw: cannot be a build folder
    if ~exist(fullfile(expfolder,dirname,'rtw_proj.tmw'),'file')
        return;
    end

    % all rules satisfied: this is considered to be a build folder
    status = true;
end

function [subdirs]=find_subdirs(parentdir)
    %FIND_SUBDIRS finds all top level sub directories in parent directory 

    files = dir(parentdir);
    subdirs = {};
    
    for ii=1:length(files)
        filename = files(ii).name;
        if files(ii).isdir
            % skip '.'
            if strcmp(filename,'.')
                continue;
            end
            % skip '..'
            if strcmp(filename,'..')
                continue;
            end
            % add sub directory to subdirs
            subdirs = [subdirs filename]; %#ok grow
        end
    end
end

