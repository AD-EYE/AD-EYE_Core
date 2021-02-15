function msfcn_find_closest_trajectory_points(block)
setup(block);

%endfunction

%% ==========================  SETUP FCN  =================================
function setup(block)

% Register number of input and output ports
block.NumInputPorts  = 1;   % current vehicle position

block.NumOutputPorts = 1;   % first reference point on trajectory
                            % second reference point on trajectory
                            % exception

block.NumDialogPrms  = 1;   % the trajectory in (x,y)


% Setup functional port properties to dynamically
% inherited.
block.SetPreCompInpPortInfoToDynamic;
block.SetPreCompOutPortInfoToDynamic;

% Set port dimensions
block.InputPort(1).DirectFeedthrough = true;
block.OutputPort(1).Dimensions       = 2; % ps: preview point on trajectory

% Set block sample time to inherited
block.SampleTimes = [-1 0];

% Run accelerator on TLC
% block.SetAccelRunOnTLC(false)

% Register methods
block.RegBlockMethod('Outputs',                  @Output);
block.RegBlockMethod('PostPropagationSetup',     @DoPostPropSetup);
block.RegBlockMethod('InitializeConditions',     @InitConditions);
block.RegBlockMethod('SetInputPortSamplingMode', @SetInpPortFrameData); % due to multiple outputs

%% ========================= Set-up the Memory vector Dwork ===============
function DoPostPropSetup(block)

%% Setup Dwork
block.NumDworks = 1;
block.Dwork(1).Name = 'preview_index1';
block.Dwork(1).Dimensions      = 1;
block.Dwork(1).DatatypeID      = 0; % double?
block.Dwork(1).Complexity      = 'Real';
block.Dwork(1).UsedAsDiscState = false;

%endfunction

%% ========================= Initialise ===================================
function InitConditions(block)

%% Initialize Dwork
block.Dwork(1).Data = 1;     % Initial index of trajectory
%endfunction

%% ========================= Input =================================
function SetInpPortFrameData(block, idx, fd)

block.InputPort(idx).SamplingMode = fd;
block.OutputPort(1).SamplingMode  = fd;

%endfunction



%% =========================  OUTPUT FCN  =================================
function Output(block)

% This function determines the reference point from the vehicle on a given
% line through p1 and p2 at the preview distance (all in 2D).
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
% p0    : current vehicle position
%
% INPUTS:
% pvp   : preview point position
%
% OUPUTS:
% p1: first reference point on trajectory
% p2: second reference point on trajectory
% pref: reference point on trajectory
%
% DIALOG:
% reference trajectory

% dialog parameters
%-------------------
para.traject  = block.DialogPrm(1).Data;

% INPUT DATA:
%============================
% obtain input data
pvp  = block.InputPort(1).Data; %[m,m] vehicle position

% ASSUMPTION: error of vehicle is smaller than preview length
% search loop through trajectory
% init for while loop
ii = block.Dwork(1).Data; % get index from last step (out of memory)

p2 = [para.traject(ii,1) para.traject(ii,2)]';

if ii == 1  % exception! p2 is first point of trajectory
    exception = 1;
    p1 = p2;
else
    exception = 0;
    p1 = [para.traject(ii-1,1) para.traject(ii-1,2)]';
end

p3 = [para.traject(ii+1,1) para.traject(ii+1,2)]';

dist_p1 = norm(p1-pvp);
dist_p2 = norm(p2-pvp);
dist_p3 = norm(p3-pvp);

%while (dist_p2 < pvl & ii < max(size(para.traject)))
while ((dist_p1) >= (dist_p3) & ii < (max(size(para.traject))-1))
    ii=ii+1;

    p1 = [para.traject(ii-1,1) para.traject(ii-1,2)]';
    p2 = [para.traject(ii,1) para.traject(ii,2)]';
    p3 = [para.traject(ii+1,1) para.traject(ii+1,2)]';
    
    dist_p1 = norm(p1-pvp);  
    dist_p2 = norm(p2-pvp);
    dist_p3 = norm(p3-pvp);
end %while

% update memory with new index
block.Dwork(1).Data = ii;

if ii >= max(size(para.traject))    % p2 lies beyond end of trajectory : extrapolate linearly
    p1 =  [para.traject(end,1) para.traject(end,2)]';
    alph = atan2(para.traject(end,2)-para.traject(end-1,2),para.traject(end,1)-para.traject(end-1,1));
    pvl=1; %extrapolation distance
    p2   = [para.traject(end,1)+pvl*cos(alph) para.traject(end,2)+pvl*sin(alph)]';
end

if exception
    %disp('exception')
    t=0;
    ps=p1;
else % no exception
    % intersection point of line perpendicular to line segment through
    % p1 and p2 and through pvp
    % t is a running parameter: ps = [p1(1) + (p2(1)-p1(1))*t,
    %                                 p1(2) + (p2(2)-p1(2))*t]
    t = -dot(p1-pvp,p2-p1)/(norm(p2 - p1))^2;  
% intersection point of line though pvp, perpendicular to line p1-p2 (ps)
ps = p1 +  t*(p2-p1);
end

% produce output
block.OutputPort(1).Data = ps;


% end function