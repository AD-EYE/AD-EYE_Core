function nodeinfo = postCodeGenHook(hCS, buildInfo)
%This function is for internal use only. It may be removed in the future.

%   INFO = postCodeGenHook(hCS, BUILDINFO) takes a Simulink.ConfigSet
%   object, hCS, and a RTW.BuildInfo object, BUILDINFO, and generates all
%   the ROS initialization and ROS<->Bus conversion code for the model in
%   the build area. NODEINFO is a struct with fields 'messageList' and
%   'nodeDependencies' (cell arrays of strings). INFO.nodeDependencies is
%   the list of required ROS packages, based upon the set of messages types
%   used in the model.
%
%   This function is called from robotics.codertarget.internal.onAfterCodeGen
%
%   For testing purposes, this function can be invoked as follows:
%     hCS = getActiveConfigSet(gcs); 
%     buildinfo = RTW.BuildInfo; 
%     buildinfo.ModelName = bdroot(gcs); 
%     info = robotics.slros.internal.cgen.postCodeGenHook(hCS, buildinfo)

%   Copyright 2014-2018 The MathWorks, Inc.

validateattributes(hCS, {'Simulink.ConfigSet'}, {'scalar'});
validateattributes(buildInfo, {'RTW.BuildInfo'}, {'scalar'});


model = buildInfo.ModelName;

% Find a header file that looks like <modelname>_types.h. This contains 
% definitions of the bus structs, and needs to be included by the bus
% conversion header
existingIncludeFiles = buildInfo.getIncludeFiles(true, true);
modelTypesHdrIdx = find(contains(existingIncludeFiles, [model '_types.']));
if ~isempty(modelTypesHdrIdx)
    [~, fname, ext] = fileparts( existingIncludeFiles{modelTypesHdrIdx} );
    modelTypesHdr = [fname ext];
else
    modelTypesHdr = '';
end

% Get the build directory (that's where we will put the generated files)
buildDir = getSourcePaths(buildInfo, true, {'BuildDir'});
if isempty(buildDir)
    buildDir = pwd;
else
    buildDir = buildDir{1};
end

modelinfo = robotics.slros.internal.cgen.ROSModelInfo(model);
msgTypes = modelinfo.messageTypesInModel();
svcTypes = modelinfo.serviceTypesInModel();

% Get the dependencies for this node (packages that it requires)
nodeinfo = modelinfo.getNodeDependencies();

% Generate all the conversion functions
conversionFiles = robotics.slros.internal.cgen.generateAllConversionFcns(...
    msgTypes, svcTypes, model, modelTypesHdr, buildDir);

% Generate the initialization functions
initFiles = robotics.slros.internal.cgen.generateInitializationFcns(...
    modelinfo, buildDir, robotics.codertarget.internal.Util.isTopLevelModel(buildInfo));

% Update buildInfo
headers = [conversionFiles.HeaderFiles initFiles.HeaderFiles];
for i=1:numel(headers)
   buildInfo.addIncludeFiles(headers{i});
end

sources = [conversionFiles.SourceFiles initFiles.SourceFiles];
for i=1:numel(sources)
   buildInfo.addSourceFiles(sources{i});
end

