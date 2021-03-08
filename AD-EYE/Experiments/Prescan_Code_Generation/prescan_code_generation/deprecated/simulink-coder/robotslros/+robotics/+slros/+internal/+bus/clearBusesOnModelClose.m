function clearBusesOnModelClose(block)
%This function is for internal use only. It may be removed in the future.

%   Copyright 2018 The MathWorks, Inc.

%clearBusesOnModelClose Clear buses from global scope on model close

% Use the handle to the top-level system (instead of the full
% path) to avoid a call to "load_system" during model close
% time.
topLevelSystem = bdroot(getSimulinkBlockHandle(block));
robotics.slros.internal.bus.Util.clearSLBusesInGlobalScope(topLevelSystem);

end

