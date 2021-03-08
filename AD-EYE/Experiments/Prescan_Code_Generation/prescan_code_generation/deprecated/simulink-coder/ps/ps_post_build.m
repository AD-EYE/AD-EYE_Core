function [] = ps_post_build(modelName,installPath,psBuildInfo,postBuildExt)
%PS_POST_BUILD Post build actions for PS target

% NOTE: This is NOT a MATLAB Post-Code-Generation command, as run by slbuild.
%       Instead this script is run by the PreScan Build Procedure
%       after slbuild has completely finished.

% Determine ps target type
templateMakefile = get_param(modelName,'TemplateMakefile');
[~,targetFile]   = fileparts(templateMakefile);

% Determine build directory
bdinfo   = RTW.getBuildDir(modelName);
buildDir = bdinfo.BuildDirectory;

% Inject PreScan symbols in make file
switch targetFile
    case 'ps_linux'
        makeInfoFile = builders.common.LinuxMakeInfoFile(modelName,installPath,psBuildInfo);
    case 'ps_vcx64'
        perlInfoFile = fullfile(buildDir,'info_perl.mk');
        PerlFile(perlInfoFile, installPath);
        makeInfoFile = builders.common.WindowsMakeInfoFile(modelName,installPath,psBuildInfo);
end
makeInfoFile.setupAndWriteFile(targetFile,buildDir);

ps_tunability_loss_check(buildDir);

% Prepare for multi-target builds:
% rename makefile name so that subsequent builds of the same model
% with different tmf files have their own make files
movefile(fullfile(buildDir,[modelName '.mk']),...
    fullfile(buildDir,['make_' targetFile '.mk']));

% Pack the generated code + experiment files in a target zip
if nargin >= 4
    ps_pack(modelName,buildDir,true,postBuildExt);
else
    ps_pack(modelName,buildDir,true);
end

end
