function msfcn_detection(block)

setup(block);
end %endfunction

%%
function setup( block )

%% define number of input and output ports
block.NumInputPorts  = 8;
block.NumOutputPorts = 2;

%% Register parameters
block.NumDialogPrms = 5;
ImgRes = block.DialogPrm(3).Data;
NumLimit = block.DialogPrm(4).Data;

%% port properties
block.SetPreCompInpPortInfoToDynamic;
block.SetPreCompOutPortInfoToDynamic;

block.InputPort(1).Complexity = 'real';     % BBes
block.InputPort(1).DataTypeId = -1;
block.InputPort(1).SamplingMode = 'Sample';
block.InputPort(1).Dimensions = [4 NumLimit];

block.InputPort(2).Complexity = 'real';     % NoBB
block.InputPort(2).DataTypeId = -1;
block.InputPort(2).SamplingMode = 'Sample';
block.InputPort(2).Dimensions = 1;

block.InputPort(3).Complexity = 'real';     % NoBB previous
block.InputPort(3).DataTypeId = -1;
block.InputPort(3).SamplingMode = 'Sample';
block.InputPort(3).Dimensions = 1;

block.InputPort(4).Complexity = 'real';     % BBID previous
block.InputPort(4).DataTypeId = -1;
block.InputPort(4).SamplingMode = 'Sample';
block.InputPort(4).Dimensions = [NumLimit,1];

block.InputPort(5).Complexity = 'real';     % BBID
block.InputPort(5).DataTypeId = -1;
block.InputPort(5).SamplingMode = 'Sample';
block.InputPort(5).Dimensions = [NumLimit,1];

block.InputPort(6).Complexity = 'real';     % DetID previous
block.InputPort(6).DataTypeId = -1;
block.InputPort(6).SamplingMode = 'Sample';
block.InputPort(6).Dimensions = [NumLimit,1];

block.InputPort(7).Complexity = 'real';     % cr
block.InputPort(7).DataTypeId = -1;
block.InputPort(7).SamplingMode = 'Sample';
block.InputPort(7).Dimensions = ImgRes;

block.InputPort(8).Complexity = 'real';     % y
block.InputPort(8).DataTypeId = -1;
block.InputPort(8).SamplingMode = 'Sample';
block.InputPort(8).Dimensions = ImgRes;

%%
block.OutputPort(1).Complexity = 'real';    % Number of detections
block.OutputPort(1).DataTypeId = 0; %double
block.OutputPort(1).SamplingMode = 'Sample';
block.OutputPort(1).Dimensions   = 1;

block.OutputPort(2).Complexity = 'real';    % Detected sign IDs
block.OutputPort(2).DataTypeId = 6; %int32
block.OutputPort(2).SamplingMode = 'Sample';
block.OutputPort(2).Dimensions   = [NumLimit 1];

%% register methods
block.RegBlockMethod('PostPropagationSetup', @DoPostPropSetup);
block.RegBlockMethod('Start', @Start);
block.RegBlockMethod('Outputs', @Outputs);

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
BBes   = block.InputPort(1).Data;
NoBB   = block.InputPort(2).Data;
NoBBp  = block.InputPort(3).Data;
BBIDp  = block.InputPort(4).Data;
BBID   = block.InputPort(5).Data;
DetIDp = block.InputPort(6).Data;
DetectTemplates = block.DialogPrm(1).Data;
NoD = block.DialogPrm(2).Data;
NumLimit = block.DialogPrm(4).Data;
DetectionTreshholdValue = block.DialogPrm(5).Data;

%% Declarations
DetID     = zeros(NumLimit, 1, 'int32'); % Vector for detection templates IDs
dist      = 0.1;                    % Search diameter in correlation matrix
TmpVct    = zeros(NoD, 1);          % Auxiliary variable to storage correlation values for one bounding box and each pattern
checksize = zeros(2,2);             % To make sure that index number is not exceeded
BBesM     = BBes;                   % Auxiliary to resize images
incomp = 0;                         % if it is needed to prepare input image

%% Detection

% Reassign BBes values: [row, column, height, width] -> [rowS, columnS, rowE, rowE] (S - start, E - end)
BBesM(3:4,1:NoBB) = BBes(3:4,1:NoBB) + BBes(1:2,1:NoBB);
BBesM(1:2,1:NoBB) = BBesM(1:2,1:NoBB) + 1;

% Compare all paterns versus all BBes
for jj = 1 : NoBB   % BBes
    % Find previous DetID value for jj-th BBox using BBIDs
    indx = find( BBID(jj) == BBIDp(1:NoBBp) );
    
    for iterKK = 1 : length(indx);
        
        if (~DetIDp(indx(iterKK)))   % if not already detected
            
            if ~incomp
                % process the input if there is anything to recognize
                % if-end statement makes sure it will be done only once
                imgCR = block.InputPort(7).Data;
                imgY  = block.InputPort(8).Data;
                ImgIn = imgY .* uint8( imgCR >= 140 );
            end
            
            ImA = ImgIn( BBesM(1,jj):BBesM(3,jj), BBesM(2,jj):BBesM(4,jj) );    % BB
            for ii = 1 : NoD    % patterns
                ImB = DetectTemplates(ii).img;                                  % Temp
                % Resize chosen image and compute normalized correlation
                [nA, mA] = size(ImA);   % BB
                [nB, mB] = size(ImB);   % Temp
                try
                    if nA <= nB
                        % Resize template to the size of the BB and compute correlation between images
                        ImBm = imresize(ImB, [nA mA], 'bilinear');
                        coor = normxcorr2(ImBm, ImA);
                        checksize(1,1) = round(2*nA*(0.5-dist));
                        checksize(2,1) = round(2*nA*(0.5+dist));
                        checksize(1,2) = round(2*mA*(0.5-dist));
                        checksize(2,2) = round(2*mA*(0.5+dist));
                    else
                        % Resize BB to the size of the template
                        ImAm = imresize(ImA, [nB mB], 'bilinear');
                        coor = normxcorr2(ImB, ImAm);
                        checksize(1,1) = round(2*nB*(0.5-dist));
                        checksize(2,1) = round(2*nB*(0.5+dist));
                        checksize(1,2) = round(2*mB*(0.5-dist));
                        checksize(2,2) = round(2*mB*(0.5+dist));
                    end
                    TmpVct(ii) = max(max( coor( checksize(1,1) : checksize(2,1) , checksize(1,2) : checksize(2,2) ) ) );
                catch
                    TmpVct(ii) = 0;
                end
            end
            % Check which template matches the BB
            [TempCorrValue, TempDetIndx] = max(TmpVct);
            if TempCorrValue > DetectionTreshholdValue
                DetID(jj)    = DetectTemplates(TempDetIndx).detID;
            end
        else
            DetID(jj) = DetIDp(indx(iterKK));   % Rewrite previous detection
        end
        
    end
    
end

%% Set outputs
block.OutputPort(1).Data = nnz(DetID);
block.OutputPort(2).Data = DetID;

end %endfunction
