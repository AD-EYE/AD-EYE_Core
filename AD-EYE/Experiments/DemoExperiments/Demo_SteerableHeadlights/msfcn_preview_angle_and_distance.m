function msfcn_preview_angle_and_distance(block)
setup(block);

%endfunction

%% ==========================  SETUP FCN  =================================
function setup(block)

% Register number of input and output ports
block.NumInputPorts  = 3;   % vehicle position
                            % preview point position
                            % reference point position
block.NumOutputPorts = 1;   % preview angle
                            % distance

% Setup functional port properties to dynamically
% inherited.
block.SetPreCompInpPortInfoToDynamic;
block.SetPreCompOutPortInfoToDynamic;

% Set port dimensions
block.InputPort(1).DirectFeedthrough = true;
block.InputPort(2).DirectFeedthrough = true;
block.InputPort(3).DirectFeedthrough = true;

block.OutputPort(1).Dimensions       = 1; % preview angle
%block.OutputPort(2).Dimensions       = 1; % preview distance


% Set block sample time to inherited
block.SampleTimes = [-1 0];

% Run accelerator on TLC
% block.SetAccelRunOnTLC(false)

% Register methods
block.RegBlockMethod('Outputs',                  @Output);
block.RegBlockMethod('SetInputPortSamplingMode', @SetInpPortFrameData); % due to multiple outputs

%% ========================= Input =================================
function SetInpPortFrameData(block, idx, fd)

block.InputPort(idx).SamplingMode = fd;
block.OutputPort(1).SamplingMode  = fd;
%block.OutputPort(2).SamplingMode  = fd;

%endfunction

%% =========================  OUTPUT FCN  =================================
function Output(block)

% This function determines:
% - the angle between the points pref-p0-pvp
% - the distance from pvp to pref (pvp is a rectangular projection on line p1-p2.
%
%  Y
%  ^
%  |            *
%  |           /p2
%  |          /
%  |         /
%  |   pref *
%  |       /     *pvp
%  |      /      |
%  |     /       | preview length
%  |    *        |
%  |   /p1       * 
%  |  /          p0
%  ---------------------> x
%
% INPUTS:
% pref  : reference point position (= point on reference trajectory)
% p0    : current vehicle position
% pvp   : preview point position
%
% OUPUTS:
% pvp: position of the preview point
% pva: angle of the line through p0 and pvp
%
% AUTHOR: S. de Hair

% GET INPUT DATA:
%============================
% obtain input data
pref   = block.InputPort(2).Data; %[m,m] reference point position (= point on reference trajectory)
p0     = block.InputPort(3).Data; %[m,m] current vehicle position
pvp    = block.InputPort(1).Data; %[m,m] preview point position

% preview angle
v_p02pvp = (pvp - p0) ./ norm(pvp - p0); %unit vector from p0 to pvp
v_p02pref = (pref - p0) ./ norm(pref - p0); %unit vector from p0 to pref

%third term of vector outer product 
%+:pref is on left side of pvp -:pref is on right side of pvp
VectorSign=(v_p02pvp(1)*v_p02pref(2) - v_p02pvp(2)*v_p02pref(1)); 
%vector inner product
VectorInnerProduct = v_p02pvp(1)*v_p02pref(1) + v_p02pvp(2)*v_p02pref(2); 

alpha=real(acos(VectorInnerProduct))*sign(VectorSign);

% distance pvp to the line (reference point) (pvp - pref)
% +:pref is on left side of pvp -:pref is on right side of pvp
ha = norm(pvp-pref)*sign(VectorSign);

% produce output
block.OutputPort(1).Data = alpha;

% end function