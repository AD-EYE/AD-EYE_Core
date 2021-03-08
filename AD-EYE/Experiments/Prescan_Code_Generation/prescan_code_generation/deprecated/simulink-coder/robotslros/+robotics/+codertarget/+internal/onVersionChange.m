function onVersionChange(hObj, hDlg, tag, ~)
%This function is for internal use only. It may be removed in the future.

%ONVERSIONCHANGE

% Copyright 2014 The MathWorks, Inc.

cs = hObj.getConfigSet();

% Check if version satisfies ROS conventions
curVal = codertarget.data.getParameterValue(cs, 'Packaging.Version');
newVal = hDlg.getWidgetValue(tag); 

% Note: curVal and newVal are strings

if robotics.codertarget.internal.Util.isValidPackageVersion(newVal)
    codertarget.data.setParameterValue(cs, 'Packaging.Version', newVal);
else
    % Restore old value and throw an error
    hDlg.setWidgetValue(tag, curVal);
    error(message('robotics:robotslros:cgen:IncorrectPackageVersion', newVal));
end

end
