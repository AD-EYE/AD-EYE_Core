function [message] = ps_test(model)
%PS_TEST test PS for Windows target
%
% Test PS target
% Generates code, compiles and runs PS model
% Using local Windows host as target


try
    
    % Locate key folders and files
    experiment = mbxutils.UBI2Experiment(model);
    expfolder = fileparts(get_param(model,'FileName'));
    rtwfolder = fullfile(expfolder,[model '_ps_rtw']);
    rtwzip    = fullfile(expfolder,[model '.zip']);
    
    chdir(expfolder);
    
    
    % Delete any old code generation output
    if exist('slprj','dir')
        rmdir('slprj','s');
    end
    if exist(rtwfolder,'dir')
        rmdir(rtwfolder,'s');
    end
    if exist(rtwzip,'file')
        delete(rtwzip);
    end
    
    % Create PS build object
    b=builders.PS('Windows');
    
    % Set instalpath to "host"
    setInstallPath(b,'host');
    
    
    % generate the PS zip
    [status] = build(b,model);
    if ~status
        error('PS code generation error');
    end
    
    
    % unzip code to temporary folder
    unzipfolder = tempname;
    mkdir(unzipfolder);
    unzip(rtwzip,unzipfolder);
    
    tmprunfolder   = fullfile(unzipfolder,experiment);
    tmpbuildfolder = fullfile(tmprunfolder,[model '_ps_rtw']);
    
    % build the model
    chdir(tmpbuildfolder);
    buildcmd = 'nmake -f make_ps_vcx64.mk';
    disp(sprintf('Executing %s',buildcmd)); %#ok
    [status] = system(buildcmd);
    disp('Build command finished')
    
    % run the model
    chdir(tmprunfolder);
    exefile = [model '.exe'];
    disp(sprintf('Running  %s',exefile)); %#ok
    [status] = system(exefile);
    disp('Run command finished')
    
    % no errors!
    message = 'OK';
    
catch ME
    message = ME.message;
end

chdir(expfolder);

% cleanup temporary folder and PS rtw folder
if exist(unzipfolder,'dir')
    try
        rmdir(unzipfolder,'s');
    catch
    end
end
if exist(rtwfolder,'dir')
    try
        rmdir(rtwfolder,'s');
    catch
    end
    if exist(rtwzip,'file')
        try
            delete(rtwzip);
        catch
        end
    end
end