function onBuildEntryHook(hCS)
%This function is for internal use only. It may be removed in the future.

%ONBUILDENTRYHOOK Entry hook point for code generation

%   Copyright 2014-2018 The MathWorks, Inc.

% Check that target language is C++ and error out if it is not
targetLang = getProp(hCS, 'TargetLang');
if ~strcmpi(targetLang, 'C++')
    error(message('robotics:robotslros:cgen:CppLanguageRequired', targetLang));
end

% Check that PackageGeneratedCodeAndArtifacts and ERTFilePackagingFormat
% are set appropriately. These parameters are disabled in onHardwareSelect
% hook, but this only applies to new models; a user can open a model from a
% older release that is configured for ROS target but with these parameters
% editable

val = getProp(hCS, 'PackageGeneratedCodeAndArtifacts');
if ~strcmpi(val, 'off')
    error(message('robotics:robotslros:cgen:PackNGoNotSupported'));
end

pkgFormat = getProp(hCS, 'ERTFilePackagingFormat');
if ~strcmpi(pkgFormat, 'modular')
    error(message('robotics:robotslros:cgen:ModularPackagingRequired', pkgFormat));
end

% Create empty lib file, so that build infrastructure for model references
% behaves correctly (it expects to link against <modelName>_rtwlib, but
% that is not needed for ROS targets.
modelName = robotics.codertarget.internal.getModelName(hCS);
libFile = strcat(modelName, '_rtwlib.lib');
fid = fopen(libFile, 'w');
if fid ~= -1
    fclose(fid);
end

end
