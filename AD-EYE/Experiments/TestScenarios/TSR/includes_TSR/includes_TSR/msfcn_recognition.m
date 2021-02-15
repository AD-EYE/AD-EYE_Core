function msfcn_recognition(block)

setup(block);
end %endfunction

%%
function setup( block )

%% define number of input and output ports
block.NumInputPorts  = 10;
block.NumOutputPorts = 3;

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

block.InputPort(3).Complexity = 'real';     % BBID
block.InputPort(3).DataTypeId = -1;
block.InputPort(3).SamplingMode = 'Sample';
block.InputPort(3).Dimensions = [NumLimit,1];

block.InputPort(4).Complexity = 'real';     % BBID previous
block.InputPort(4).DataTypeId = -1;
block.InputPort(4).SamplingMode = 'Sample';
block.InputPort(4).Dimensions = [NumLimit,1];

block.InputPort(5).Complexity = 'real';     % BBID previous to previous
block.InputPort(5).DataTypeId = -1;
block.InputPort(5).SamplingMode = 'Sample';
block.InputPort(5).Dimensions = [NumLimit,1];

block.InputPort(6).Complexity = 'real';     % DetID
block.InputPort(6).DataTypeId = -1;
block.InputPort(6).SamplingMode = 'Sample';
block.InputPort(6).Dimensions = [NumLimit,1];

block.InputPort(7).Complexity = 'real';     % RecID 1/z
block.InputPort(7).DataTypeId = -1;
block.InputPort(7).SamplingMode = 'Sample';
block.InputPort(7).Dimensions = [NumLimit,1];

block.InputPort(8).Complexity = 'real';     % RecID 1/z/z
block.InputPort(8).DataTypeId = -1;
block.InputPort(8).SamplingMode = 'Sample';
block.InputPort(8).Dimensions = [NumLimit,1];

block.InputPort(9).Complexity = 'real';     % y
block.InputPort(9).DataTypeId = -1;
block.InputPort(9).SamplingMode = 'Sample';
block.InputPort(9).Dimensions = ImgRes;

block.InputPort(10).Complexity = 'real';     % cr
block.InputPort(10).DataTypeId = -1;
block.InputPort(10).SamplingMode = 'Sample';
block.InputPort(10).Dimensions = ImgRes;

%%
block.OutputPort(1).Complexity = 'real';    % Number of recognitions
block.OutputPort(1).DataTypeId = 0; %double
block.OutputPort(1).SamplingMode = 'Sample';
block.OutputPort(1).Dimensions   = 1;

block.OutputPort(2).Complexity = 'real';    % RecIDfinal
block.OutputPort(2).DataTypeId = 6; %int32
block.OutputPort(2).SamplingMode = 'Sample';
block.OutputPort(2).Dimensions   = [NumLimit 1];

block.OutputPort(3).Complexity = 'real';    % RecID
block.OutputPort(3).DataTypeId = 6; %int32
block.OutputPort(3).SamplingMode = 'Sample';
block.OutputPort(3).Dimensions   = [NumLimit 1];



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
BBes    = block.InputPort(1).Data;
NoBB    = block.InputPort(2).Data;
BBID    = block.InputPort(3).Data;
BBIDp   = block.InputPort(4).Data;
BBIDpp  = block.InputPort(5).Data;
DetID   = block.InputPort(6).Data;
RecIDp  = block.InputPort(7).Data;
RecIDpp = block.InputPort(8).Data;
RecognitionTemplates = block.DialogPrm(1).Data;
NoR   = block.DialogPrm(2).Data;
NumLimit = block.DialogPrm(4).Data;
RecognitionTreshholdValue = block.DialogPrm(5).Data;

%% Declarations
RecID      = zeros(NumLimit, 1, 'int32'); % Vector for recognition templates IDs
RecIDfinal = zeros(NumLimit, 1, 'int32'); % Vector for recognition templates IDs - output
dist       = 0.1;                    % Search diameter in correlation matrix
TmpVct     = zeros(NoR, 1);          % Auxiliary variable to storage correlation values for one bounding box and each pattern
checksize  = zeros(2,2);             % To make sure that index number is not exceeded
BBesM      = BBes;                   % Auxiliary to resize images
incomp = 0;                          % if input image was prepared

%% Recognition

% Reassign BBes values: [row, column, height, width] -> [rowS, columnS, rowE, rowE] (S - start, E - end)
BBesM(3:4,1:NoBB) = BBes(3:4,1:NoBB) + BBes(1:2,1:NoBB);
BBesM(1:2,1:NoBB) = BBesM(1:2,1:NoBB) + 1;

% Compare paterns versus all BBes
for jj = 1 : NoBB   % BBes
    
    % Find two previous (1/z & 1/z/z) RecID value for jj-th BBox using BBIDs
    indx1 = find(BBID(jj) == BBIDp, 1);
    indx2 = find(BBID(jj) == BBIDpp, 1);
    
    % Find current RecID
    if ~isempty(indx1) && ~isempty(indx2) && RecIDp(indx1) && RecIDpp(indx2) && (RecIDp(indx1) == RecIDpp(indx2))
          
            % Rewrite previous recognition
            RecID(jj) = RecIDp(indx1);

    % Calculate correlation for jj-th BBox
    elseif DetID(jj)    % if detected

        if ~incomp
            % process the input if there is anything to recognize
            % if-end statement makes sure it will be done only once
            imgY   = block.InputPort(9).Data;
            imgCR  = block.InputPort(10).Data;

            CR = imfill(imclearborder(255*uint8(~(imgCR >= 135))),'holes');
            imgY(~CR) = 0;            

            doubleY = double(imgY);
            minvalue = min(min(doubleY));
            maxvalue = max(max(doubleY));
            valueDiff = maxvalue - minvalue;

            if valueDiff > 0
                ImgIn = intmax('uint8')/valueDiff * ( imgY - minvalue );
            else
                ImgIn = imgY;
            end
        end


        ImA = ImgIn( BBesM(1,jj):BBesM(3,jj), BBesM(2,jj):BBesM(4,jj) );    % BB
        [ner, nec] = cutimage(ImA>128);
        ImA = ImA(ner, nec);
        [nA, mA] = size(ImA);   % BB
        
        if DetID(jj) == 4
            for ti=1 : nA
                for tj =1 : mA
                    if ImA(ti, tj) < 125
                        ImA(ti, tj) = 0;
                    else
                        ImA(ti, tj) = 255;
                    end
                end
            end
        end
        
        % Check size of the BBox
        if (nA > 5 && mA > 5)
        % Calculate TmpVct
            for ii = 1 : NoR    

                % check recognition patterns which have appropriate detection template only
                if (RecognitionTemplates(ii).detID == DetID(jj))
                    ImB = RecognitionTemplates(ii).img;  % Temp

                    % Resize chosen image and compute normalized correlation
                    [nB, mB] = size(ImB);   % Temp
                    if nA <= nB
                        % Resize template to the size of the BB and compute correlation between images
                        ImAm = imresize(ImA, [2*nA 2*mA], 'bilinear');
                        ImBm = imresize(ImB, [2*nA 2*mA], 'bilinear');
                        coor = normxcorr2(ImBm, ImAm);
                        checksize(1,1) = round(4*nA*(0.5-dist));
                        checksize(2,1) = round(4*nA*(0.5+dist));
                        checksize(1,2) = round(4*mA*(0.5-dist));
                        checksize(2,2) = round(4*mA*(0.5+dist));
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

                else
                    TmpVct(ii) = 0;
                end          

            end
        end
        

        % Check which template best matches the BB
        [TempCorrValue, TempRecIndx] = max(TmpVct);
        if TempCorrValue > RecognitionTreshholdValue
            RecID(jj) = RecognitionTemplates(TempRecIndx).recID;
               
        else
            % Recognition failure cause of threshold
            RecID(jj) = 0;
        end
        
    else
        % Recognition failure cause of no detection
        RecID(jj) = 0;
    end
    % End Calculate correlation for jj-th BBox
    
    % Set output
    if ~isempty(indx1) && (RecID(jj) == RecIDp(indx1))
        RecIDfinal(jj) = RecID(jj);
    else
        RecIDfinal(jj) = 0;
    end
    
end
    
%% Set outputs
block.OutputPort(1).Data = nnz(RecID);
block.OutputPort(2).Data = RecIDfinal;
block.OutputPort(3).Data = RecID;

end %endfunction
