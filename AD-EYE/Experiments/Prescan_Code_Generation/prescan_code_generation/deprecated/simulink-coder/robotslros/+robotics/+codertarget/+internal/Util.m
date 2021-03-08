classdef Util
%This class is for internal use only. It may be removed in the future.

%codertarget.Util - Utility functions related to generating ROS node
%                   using Coder Target infrastructure

%   Copyright 2014-2018 The MathWorks, Inc.

    methods(Static)

        function pkgName = modelNameToValidPackageName(modelName)
        %modelNameToValidPackageName Convert model name to ROS package name
        %   ROS package names should start with a lower case letter and
        %   only contain lower case letters, digits and underscores.

            validateattributes(modelName, {'char'}, {'nonempty'});

            % Make model name lowercase. Then remove all non-word
            % characters (\W regexp), i.e. keep only alphabet characters,
            % underscores & numbers.
            pkgName = regexprep(lower(modelName), '\W', '');
            if isempty(pkgName)
                error(message('robotics:robotslros:cgen:UnableToCreateROSPkgName', modelName));
            end
        end

        function isValid = isValidPackageVersion(versionStr)
        %isValidPackageVersion Verify that ROS package version is valid
        %   Required to be 3 dot-separated integers. See
        %   http://wiki.ros.org/catkin/package.xml.

        % Explicitly make sure that input string is non-empty, since
        % regular expression would match an empty string and falsely
        % return TRUE.
            validateattributes(versionStr, {'char'}, {'nonempty'});
            isValid = strcmpi(versionStr, regexp(versionStr, '^\d+\.\d+\.\d+$', 'match', 'once'));
        end

        function isTopLevel = isTopLevelModel(buildInfo)
        %isTopLevelModel Determine if a given model is a top-level or referenced model
        %   ISTOPLEVELMODEL(BUILDINFO) returns TRUE if the model
        %   represented by BUILDINFO is a top-level model.
        %
        %   ISTOPLEVELMODEL(BUILDINFO) returns FALSE if the model is
        %   used as a referenced model

            validateattributes(buildInfo, {'RTW.BuildInfo'}, {'scalar'}, 'isTopLevelModel', 'buildInfo');

            [~, buildArgValue] = findBuildArg(buildInfo, 'MODELREF_TARGET_TYPE');
            isTopLevel = strcmp(buildArgValue, 'NONE');
        end

        function modelRefNames = uniqueModelRefNames(buildInfo)
        %uniqueModelRefNames Get names of all model references in model
        %   MODELREFNAMES = uniqueModelRefNames(BUILDINFO) returns the
        %   names of all model references listed in the BUILDINFO for
        %   the current model. The list of MODELREFNAMES will only
        %   contain unique entries.

            validateattributes(buildInfo, {'RTW.BuildInfo'}, {'scalar'}, 'uniqueModelRefNames', 'buildInfo');

            modelRefNames = {};
            if ~isempty(buildInfo.ModelRefs)
                modelRefPaths = arrayfun(@(ref) ref.Path, buildInfo.ModelRefs, 'UniformOutput', false);

                modelRefNames = cell(1,numel(modelRefPaths));
                for i = 1:numel(modelRefPaths)
                    [~, modelRefNames{i}, ~] = fileparts(modelRefPaths{i});
                end

                % Only find the unique model reference names
                modelRefNames = unique(modelRefNames, 'stable');
            end
        end

        function sharedDir = sharedUtilsDir(buildInfo, isAbsolute)
        %sharedUtilsDir Retrieve relative or absolute path to shared utility sources
        %    SHAREDDIR = sharedUtilsDir(BUILDINFO, false) returns the
        %    path to the shared utility folder relative the current
        %    folder (pwd). If no shared utility folder exists, return
        %    ''.
        %
        %    SHAREDDIR = sharedUtilsDir(BUILDINFO, true) returns the
        %    absolute path to the utility folder.
            sharedDir = '';
            for i = 1:length(buildInfo.BuildArgs)
                if strcmpi(buildInfo.BuildArgs(i).Key, 'SHARED_SRC_DIR')
                    sharedDir = strtrim(buildInfo.BuildArgs(i).Value);
                    break;
                end
            end
            if ~isempty(sharedDir) && isAbsolute
                % Convert relative path to absolute path if needed
                sharedDir = robotics.ros.internal.FileSystem.relativeToAbsolute(sharedDir);
            end
        end
    end

end
