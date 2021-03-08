function varExists = existsInGlobalScope(model, varName)
    %This function is for internal use only. It may be removed in the future.
    
    %EXISTSINGLOBALSCOPE Check for existence of variable in global scope
    %   If the MODEL input is empty, the existence will be checked in the
    %   base workspace. Otherwise, the variable existence will be queried in
    %   the global scope through the existsInGlobalScope function.
    
    %   Copyright 2017-2018 The MathWorks, Inc.
    
    varExists = robotics.slcore.internal.util.existsInGlobalScope(model, varName);
    
end

