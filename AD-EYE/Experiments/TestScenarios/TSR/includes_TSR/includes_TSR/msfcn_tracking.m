function msfcn_tracking(block)

setup(block);
end %endfunction

%%
function setup( block )

%% define number of input and output ports
block.NumInputPorts  = 5;
block.NumOutputPorts = 1;

%% Register parameters
block.NumDialogPrms = 1;
NumLimit = block.DialogPrm(1).Data;

%% port properties
block.SetPreCompInpPortInfoToDynamic;
block.SetPreCompOutPortInfoToDynamic;

%% Inputs
block.InputPort(1).Complexity = 'real';     % NoBB
block.InputPort(1).DataTypeId = -1;
block.InputPort(1).SamplingMode = 'Sample';
block.InputPort(1).Dimensions = 1;

block.InputPort(2).Complexity = 'real';     % NoBB previous
block.InputPort(2).DataTypeId = -1;
block.InputPort(2).SamplingMode = 'Sample';
block.InputPort(2).Dimensions = 1;

block.InputPort(3).Complexity = 'real';     % Centroids
block.InputPort(3).DataTypeId = -1;
block.InputPort(3).SamplingMode = 'Sample';
block.InputPort(3).Dimensions = [2 NumLimit];

block.InputPort(4).Complexity = 'real';     % Centroids previous
block.InputPort(4).DataTypeId = -1;
block.InputPort(4).SamplingMode = 'Sample';
block.InputPort(4).Dimensions = [2 NumLimit];

block.InputPort(5).Complexity = 'real';     % BB IDs previous
block.InputPort(5).DataTypeId = -1;
block.InputPort(5).SamplingMode = 'Sample';
block.InputPort(5).Dimensions = [NumLimit 1];

%% Outputs
block.OutputPort(1).Complexity = 'real';    % BB IDs
block.OutputPort(1).DataTypeId = 6; %int32
block.OutputPort(1).SamplingMode = 'Sample';
block.OutputPort(1).Dimensions   = [NumLimit, 1];

%% register methods
block.RegBlockMethod('PostPropagationSetup', @DoPostPropSetup);
block.RegBlockMethod('Start', @Start);
block.RegBlockMethod('Outputs', @Outputs);
block.RegBlockMethod('SetInputPortDimensionsMode',  @SetInputDimsMode);

%% Block runs on TLC in accelerator mode.
block.SetAccelRunOnTLC(true);
end %endfunction

%%
function DoPostPropSetup( block )

block.NumDworks = 1;
block.Dwork(1).Name = 'x1';
block.Dwork(1).Dimensions = 1;
block.Dwork(1).DatatypeID = 0;
block.Dwork(1).Complexity = 'Real';
end %endfunction

%%
function Start(block)

block.Dwork(1).Data = 0;
end %endfunction

%%
function Outputs(block)

%% Parse inputs and parameters
NoBBn = block.InputPort(1).Data;
NoBBp = block.InputPort(2).Data;
Centn = block.InputPort(3).Data;
Centp = block.InputPort(4).Data;
BBIDp = block.InputPort(5).Data;
NumLimit = block.DialogPrm(1).Data;

%% Variables declaration
BBIDn  = zeros(NumLimit,1,'int32');      % Output declaration
NumMatch = min(NoBBp, NoBBn);       % Number of matching needed  to perform
TreshholdValue = 24;                % Maximum distance allowed between present and previous BBox
wn = 1 : NoBBn;
wp = 1 : NoBBp;
IDunqP = unique(BBIDp(1:NoBBp));    % Previous unique IDs

%% Perform BB tracking
if NoBBn        % is any action needed?
    if NoBBp    % is anything to match?
        
        % Compute distances between moving BBs
        tab1x = Centn(1,1:NoBBn).' * ones(1,NoBBp);
        tab2x = ones(NoBBn,1) * Centp(1,1:NoBBp);
        tab1y = Centn(2,1:NoBBn).' * ones(1,NoBBp);
        tab2y = ones(NoBBn,1) * Centp(2,1:NoBBp);
        Dists = abs(tab1x-tab2x) + abs(tab1y-tab2y);    % table storing distances ('street metric'), size: NoBBn x NoBBp
        
        % Match previous and present BBes
        iter = 1;
        MinValue = 0;
        while (iter <= NumMatch) && (MinValue < TreshholdValue)
            [MinValue, indx] = min(Dists(:));
            if MinValue >= TreshholdValue
                break;
            end
            [i,j] = ind2sub([NoBBn-iter+1, NoBBp-iter+1], indx);
            BBIDn(wn(i)) = BBIDp(wp(j));
            Dists(i,:) = [];
            Dists(:,j) = [];
            wn(i) = [];
            wp(j) = [];
            iter = iter + 1;
        end
        
        % New assignments
        if ~isempty(wn)               % is anything to assign?
            for ii = 1 : size(wn,2)
                IDunqN = unique(BBIDn(1:NoBBn));   % already used ID numbers
                jj = 1;
                while any(IDunqN==jj) || any(IDunqP==jj)   % look for not used ID and not previously used ID
                    jj = jj + 1;
                end
                if jj <= NumLimit
                    kk = 1;
                    while ( kk <= NumLimit ) && ( BBIDn(kk) )
                        kk = kk + 1;                        % Determine first empty place in ID vector
                    end
                    if kk <= NumLimit
                        BBIDn(kk) = jj;
                    end
                end
            end
        end
    else
        BBIDn(1:NoBBn,1) = 1:NoBBn;
    end
    
end

% Output
block.OutputPort(1).Data = BBIDn;
end %endfunction
