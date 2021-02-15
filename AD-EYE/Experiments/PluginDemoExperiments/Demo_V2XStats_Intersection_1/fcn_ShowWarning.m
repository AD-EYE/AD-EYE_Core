function fcn_ShowWarning(block)
% Level-2 M file S-Function for system identification using
% Least Mean Squares (LMS).
%   Copyright 1990-2004 The MathWorks, Inc.
%   $Revision: 1.1.6.3 $

setup(block);
%endfunction

function setup(block)
%global simclient

%   %% Register dialog parameter: LMS step size
block.NumDialogPrms = 4;
block.DialogPrmsTunable = {'Tunable','Tunable','Tunable','Tunable'};

%% Regieste number of input and output ports
block.NumInputPorts  = 3;
block.NumOutputPorts = 0;

%% Setup functional port properties to dynamically
%% inherited.
  block.SetPreCompInpPortInfoToDynamic;
  %block.SetPreCompOutPortInfoToDynamic;
 
for i=1:block.NumInputPorts
%     block.InputPort(i).Complexity   = 'Real';
%     block.InputPort(i).DataTypeId   = 0;
%     block.InputPort(i).SamplingMode = 'Sample';
     block.InputPort(i).Dimensions=1;
end



%  SetInputPortSamplingMode
block.SampleTimes = [-1 0];

%% Register methods
block.RegBlockMethod('SetInputPortSamplingMode', @SetInpPortFrameData);
block.RegBlockMethod('PostPropagationSetup',    @DoPostPropSetup);
block.RegBlockMethod('Start',                   @Start);
block.RegBlockMethod('Outputs',                 @Outputs);

%% Block runs on TLC in accelerator mode.
block.SetAccelRunOnTLC(false)
%endfunction

function SetInpPortFrameData(block, idx, fd)

block.InputPort(idx).SamplingMode = fd;
%endfunction
function DoPostPropSetup(block)
  block.NumDworks             = 1;
  block.Dwork(1).Name         = 'PlotHandles';
  block.Dwork(1).Dimensions   = 6;
  block.Dwork(1).DatatypeID   = 0;
  block.Dwork(1).Complexity   = 'Real';
%endfunction DoPostPropSetup

function Start(block)
figure(block.DialogPrm(2).Data)
im=imread(block.DialogPrm(1).Data);
Size_ = size(im);

image(im)
axis equal
axis tight
axis off

block.Dwork(1).Data = zeros(1,6);

blkh = block.BlockHandle;
set_param(blkh,'UserData', Size_);

function Outputs(block)
blkh = block.BlockHandle;
Size_ = get_param(blkh,'UserData');
WarningColor = block.DialogPrm(3).Data;

line1 = [0 0; 0, -Size_(1)/8];
line2 = [0 Size_(1)/64; 0, Size_(1)/32];
x0 = Size_(2)*0.95;

figure(block.DialogPrm(2).Data)
hold on
PlotHandles = block.Dwork(1).Data;
for i=1:6
    try
        delete(PlotHandles(i))
    catch
    end
end
for i=1:3
    if block.InputPort(i).Data
        y0 = Size_(1)*((i-1)*3/8+0.18);
        PlotHandles(2*i-1) = plot(line1(:,1)+x0,line1(:,2)+y0,WarningColor,'LineWidth',3);
        PlotHandles(2*i) = plot(line2(:,1)+x0,line2(:,2)+y0,WarningColor,'LineWidth',3);
    end
end
block.Dwork(1).Data = PlotHandles;
%endfunction


