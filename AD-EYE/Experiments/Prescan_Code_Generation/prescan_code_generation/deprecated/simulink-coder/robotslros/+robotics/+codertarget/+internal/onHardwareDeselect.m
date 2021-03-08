function onHardwareDeselect(hCS)
%This function is for internal use only. It may be removed in the future.

%ONHARDWAREDESELECT Executed when ROS hardware is de-selected
%   See also robotics.codertarget.internal.onHardwareSelect

%  Copyright 2015 The MathWorks, Inc.

validateattributes(hCS, {'Simulink.ConfigSet'}, {'nonempty'});

% Deselect/enable the properties that were disabled during target selection

hCS.setPropEnabled('TargetLang', true);
setProp(hCS, 'TargetLang', 'C');
hCS.setPropEnabled('PackageGeneratedCodeAndArtifacts', true);
hCS.setPropEnabled('ERTFilePackagingFormat', true);
end
