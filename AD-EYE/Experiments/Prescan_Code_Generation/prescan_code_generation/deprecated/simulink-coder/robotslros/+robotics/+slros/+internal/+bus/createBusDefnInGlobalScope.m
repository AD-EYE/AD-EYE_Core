function createBusDefnInGlobalScope(emptyRosMsg, model)
%This function is for internal use only. It may be removed in the future.

%createBusDefnInGlobalScope - Create Simulink bus object in global scope
%
%   createBusDefnInGlobalScope(MSG, MODEL) creates the Simulink bus
%   objects in the global scope (base workspace or data dictionary attached 
%   to model) corresponding to the ROS message MSG and 
%   any nested messages inside it, using the variable-length array size
%   information from MODEL. MSG should  be an empty message (i.e., created
%   using ROSMESSAGE without any subsequent assignments), since the only
%   way to determine if a property is a variable-length array is to check
%   if its value is [].
%
%   createBusDefnInGlobalScope(MSG) creates the bus object using default
%   sizes for variable-length arrays.
%
%   Note: 
%   * If MODEL is a Simulink block library, the default sizes are
%     applied.

%   Copyright 2014-2017 The MathWorks, Inc.

if exist('model', 'var') && ~isempty(model)
    assert(ischar(model));    
    isLibraryContext = strcmpi(get_param(bdroot(model), 'BlockDiagramType'), 'library');
    nullModel = isLibraryContext;
else
    nullModel = true;
end

if nullModel   
    model = '';
    varlenArrayStore = [];  
    truncateAction = robotics.slros.internal.bus.VarlenArraySizeStore.getDefaultTruncateAction();
else
    varlenArrayStore = robotics.slros.internal.bus.VarlenArraySizeStore(model);
    truncateAction = varlenArrayStore.getTruncateAction();
end

requiredBuses = robotics.slros.internal.bus.getBusDefnForROSMsg(emptyRosMsg, model);
createVarlenInfoBus = false;
for i = 1:numel(requiredBuses)
    bus = requiredBuses(i).Bus;
    elemInfo = robotics.slros.internal.bus.BusItemInfo( bus.Description );
    msgType = elemInfo.MsgType;
    busname = robotics.slros.internal.bus.Util.rosMsgTypeToBusName(msgType, model);
        
    varlenInfo = robotics.slros.internal.bus.VarLenArrayInfo(bus);
    if varlenInfo.hasVarLenArrayProperties()
        if ~isempty(varlenArrayStore)
            % applyMaxLengths will apply user-customizations if present
            varlenArrayStore.applyMaxLengths(varlenInfo);
        else
            robotics.slros.internal.bus.VarlenArraySizeStore.applyDefaultMaxLengths(varlenInfo);
        end
        updatedBus = updateVarlenArrayLimitsInBus(bus, varlenInfo, truncateAction);
        robotics.slros.internal.assigninGlobalScope(model, busname, updatedBus);
        createVarlenInfoBus = true;
    else
        % no variable-length arrays
        robotics.slros.internal.assigninGlobalScope(model, busname, bus);
    end
end

if createVarlenInfoBus
    robotics.slros.internal.bus.Util.createVarlenInfoBusIfNeeded(model);
end

end


%%
function [bus, requiresVarlenInfoBus] = updateVarlenArrayLimitsInBus(bus, varlenInfo, truncateAction)

varlenProps = varlenInfo.PropertyNames;
busElementNames = {bus.Elements.Name};

for j = 1:numel(varlenProps)
    % find corresponding bus element
    idx = find(strcmp(busElementNames, varlenProps{j}));
    assert(numel(idx)==1);
    
    % sanity check - is bus element a variable-length array?
    assert(strcmpi(bus.Elements(idx).DimensionsMode, 'Fixed')); 
    elemInfo = robotics.slros.internal.bus.BusItemInfo( bus.Elements(idx).Description );
    assert(elemInfo.isVarLenDataElement);
    
    % update the max length for the bus element
    bus.Elements(idx).Dimensions = varlenInfo.getMaxLength(varlenProps{j});
    
    if truncateAction == robotics.slros.internal.bus.VarLenArrayTruncationAction.EmitWarning
        elemInfo.TruncateAction = 'warn';
        bus.Elements(idx).Description = elemInfo.toDescription();
    end   
end

requiresVarlenInfoBus = ~isempty(varlenProps);
end
