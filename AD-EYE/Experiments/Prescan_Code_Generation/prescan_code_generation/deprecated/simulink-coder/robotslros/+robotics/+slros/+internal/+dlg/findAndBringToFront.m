function [src, dlg] = findAndBringToFront(className, tag, hndlCompare)
% findAndBringToFront find all open dialogs with a given tag and iterate over them

%   Copyright 2018 The MathWorks, Inc.

openDlgs = findDDGByTag(tag);
src = [];
dlg = [];
if (~isempty(openDlgs))
    for i = 1:numel(openDlgs)
        srcTemp = openDlgs(i).getDialogSource();
        if isa(srcTemp,className)
            found = hndlCompare(srcTemp);
            if (found)
                src = srcTemp;
                dlg = openDlgs(i);
                dlg.show();
                break;
            end
        end
    end
end

