function assigninGlobalScope(model, varName, varValue)
    %This function is for internal use only. It may be removed in the future.
    
    %ASSIGNINGLOBALSCOPE Assign value to variable
    %   If the MODEL input is empty, the expression will always be assigned in the
    %   base workspace. Otherwise, the expression will be passed along to the
    %   assigninGlobalScope function.
    
    %   Copyright 2017-2018 The MathWorks, Inc.
    
    robotics.slcore.internal.util.assigninGlobalScope(model, varName, varValue);
    
end

