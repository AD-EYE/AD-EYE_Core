function onHardwareSelect(hCS)
%This function is for internal use only. It may be removed in the future.

%ONHARDWARESELECT Executed when ROS hardware is selected
%   See also robotics.codertarget.internal.onHardwareDeselect
%
%   Copyright 2014-2015 The MathWorks, Inc.

validateattributes(hCS, {'Simulink.ConfigSet'}, {'nonempty'});

% Note: The setProp commands below will work even if the properties are
% already disabled
 
% Set code generation language to C++
val = getProp(hCS, 'TargetLang');
if ~strcmpi(val, 'C++')
    setProp(hCS, 'TargetLang', 'C++');
end

% Set solver to Fixed Step
val = getProp(hCS, 'SolverType');
if ~strcmpi(val, 'Fixed-step')
    setProp(hCS, 'SolverType', 'Fixed-step');
end

% Disable Pack N Go
val = getProp(hCS, 'PackageGeneratedCodeAndArtifacts');
if ~strcmpi(val, 'off')
    setProp(hCS, 'PackageGeneratedCodeAndArtifacts', 'off');
end

% Set ERTFilePackagingFormat to Modular (this is in Config Params > Code
% Generation > Code Placement pane). This setting is required for the
% generated code to have a separate <model>_types.h file (g1320866) with
% either Simulink Coder or Embedded Coder
val = getProp(hCS, 'ERTFilePackagingFormat');
if ~strcmpi(val, 'modular')
    setProp(hCS, 'ERTFilePackagingFormat', 'Modular');
end


% Lock down properties so that they cannot be accidentally modified by the
% user.
%
% NOTE: When disabling properties here, be sure to enable them
% in onHardwareDeselect

hCS.setPropEnabled('TargetLang', false);
hCS.setPropEnabled('PackageGeneratedCodeAndArtifacts', false);
hCS.setPropEnabled('ERTFilePackagingFormat', false);

end
