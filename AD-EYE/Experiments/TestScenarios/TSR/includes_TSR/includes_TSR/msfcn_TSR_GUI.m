
function msfcn_TSR_GUI(block)
setup(block);
%endfunction

function setup( block )


%% define number of input and output ports
block.NumInputPorts  = 12;
block.NumOutputPorts = 6;

%% port properties
block.SetPreCompInpPortInfoToDynamic;
block.SetPreCompOutPortInfoToDynamic;

%% Register parameters
block.NumDialogPrms = 5;
dfreq = block.DialogPrm(1).Data;
NumLimit = block.DialogPrm(5).Data;

%% Inputs / Outputs
block.InputPort(1).Complexity = 'real'; % Vehicle velocity
block.InputPort(1).DataTypeId = 0; %real
block.InputPort(1).SamplingMode = 'Sample';
block.InputPort(1).Dimensions = 1;

block.InputPort(2).Complexity = 'real'; % RPM
block.InputPort(2).DataTypeId = 0; %real
block.InputPort(2).SamplingMode = 'Sample';
block.InputPort(2).Dimensions = 1;

block.InputPort(3).Complexity = 'real'; % Brake percentage
block.InputPort(3).DataTypeId = 0; %real
block.InputPort(3).SamplingMode = 'Sample';
block.InputPort(3).Dimensions = 1;

block.InputPort(4).Complexity = 'real'; % recID vector
block.InputPort(4).DataTypeId = -1; %inherited
block.InputPort(4).SamplingMode = 'Sample';
block.InputPort(4).Dimensions = [NumLimit 1];

block.InputPort(5).Complexity = 'real'; % Clock
block.InputPort(5).DataTypeId = -1; %inherited
block.InputPort(5).SamplingMode = 'Sample';
block.InputPort(5).Dimensions = 1;

block.InputPort(6).Complexity = 'real'; % Slots IDs in
block.InputPort(6).DataTypeId = -1; %inherited
block.InputPort(6).SamplingMode = 'Sample';
block.InputPort(6).Dimensions = [3 1];

block.InputPort(7).Complexity = 'real'; % Slots recognition times in
block.InputPort(7).DataTypeId = -1; %inherited
block.InputPort(7).SamplingMode = 'Sample';
block.InputPort(7).Dimensions = [3 1];

block.InputPort(8).Complexity = 'real'; % previously desired velocity
block.InputPort(8).DataTypeId = -1; %inherited
block.InputPort(8).SamplingMode = 'Sample';
block.InputPort(8).Dimensions = [3 1];

block.InputPort(9).Complexity = 'real'; % impulse generator
block.InputPort(9).DataTypeId = -1; %inherited
block.InputPort(9).SamplingMode = 'Sample';
block.InputPort(9).Dimensions = 1;

block.InputPort(10).Complexity = 'real'; % previous warning on/off
block.InputPort(10).DataTypeId = 8; % bool
block.InputPort(10).SamplingMode = 'Sample';
block.InputPort(10).Dimensions = 1;

block.InputPort(11).Complexity = 'real'; % Display trigger: colour -> gray
block.InputPort(11).DataTypeId = -1; %inherited
block.InputPort(11).SamplingMode = 'Sample';
block.InputPort(11).Dimensions = [3 1];

block.InputPort(12).Complexity = 'real'; % Slots - gray
block.InputPort(12).DataTypeId = -1; %inherited
block.InputPort(12).SamplingMode = 'Sample';
block.InputPort(12).Dimensions = [3 1];

block.OutputPort(1).Complexity = 'real'; % Slots IDs out
block.OutputPort(1).DataTypeId = -1; %inherited
block.OutputPort(1).SamplingMode = 'Sample';
block.OutputPort(1).Dimensions = [3 1];

block.OutputPort(2).Complexity = 'real'; % Slots recognition times out
block.OutputPort(2).DataTypeId = -1; %inherited
block.OutputPort(2).SamplingMode = 'Sample';
block.OutputPort(2).Dimensions = [3 1];

block.OutputPort(3).Complexity = 'real'; % Slots: desired velocity [km/h]
block.OutputPort(3).DataTypeId = -1; %inherited
block.OutputPort(3).SamplingMode = 'Sample';
block.OutputPort(3).Dimensions = [3 1];

block.OutputPort(4).Complexity = 'real'; % Desired velocity [km/h]
block.OutputPort(4).DataTypeId = -1; %inherited
block.OutputPort(4).SamplingMode = 'Sample';
block.OutputPort(4).Dimensions = 1;

block.OutputPort(5).Complexity = 'real'; % warning on / off
block.OutputPort(5).DataTypeId = 8; % bool
block.OutputPort(5).SamplingMode = 'Sample';
block.OutputPort(5).Dimensions = 1;

block.OutputPort(6).Complexity = 'real'; % Slots gray
block.OutputPort(6).DataTypeId = -1; %inherited
block.OutputPort(6).SamplingMode = 'Sample';
block.OutputPort(6).Dimensions = [3 1];

%% block sample time
block.SampleTimes = [1/dfreq 0];

%% register methods
block.RegBlockMethod('PostPropagationSetup', @DoPostPropSetup);
block.RegBlockMethod('Start', @Start);
block.RegBlockMethod('Outputs', @Outputs);

%% Block runs on TLC in accelerator mode.
block.SetAccelRunOnTLC(true);
%endfunction

function DoPostPropSetup( block )
    block.NumDworks = 1;
    block.Dwork(1).Name = 'handles';
    block.Dwork(1).Dimensions = 8;
    block.Dwork(1).DatatypeID = 0;
    block.Dwork(1).Complexity = 'Real';
 %endfunction

function Start(block)
try %#ok<TRYNC>
    close (TSR_GUI)
end

h_dlg   = TSR_GUI;
h_speed = findobj(h_dlg, 'Tag', 'Speed_text');
h_brake = findobj(h_dlg, 'Tag', 'BrakePressure_text');
h_RPM   = findobj(h_dlg, 'Tag', 'RPM_text');
h_TSR_panel = findobj(h_dlg, 'Tag', 'TSR_panel');
h_TrafficSignLeft   = findobj(h_dlg, 'Tag', 'traffic_sign_left');
h_TrafficSignMiddle = findobj(h_dlg, 'Tag', 'traffic_sign_middle');
h_TrafficSignRight  = findobj(h_dlg, 'Tag', 'traffic_sign_right');
uipanel21 = findobj(h_dlg, 'Tag', 'uipanel21');

block.Dwork(1).Data = [ double(h_dlg) double(h_speed) double(h_brake) double(h_RPM) double(h_TrafficSignLeft) double(h_TrafficSignMiddle) double(h_TrafficSignRight) double(h_TSR_panel)];
set(h_TSR_panel, 'BorderWidth',2, 'ForegroundColor','Black', 'HighlightColor',[0.502 0.502 0.502], 'ShadowColor', [0.5 0.5 0.5]);
set(uipanel21, 'BorderWidth',2, 'ForegroundColor','Black', 'HighlightColor',[0.502 0.502 0.502], 'ShadowColor', [0.5 0.5 0.5]);
%endfunction Start

function Outputs(block)
h_speed = block.Dwork(1).Data(2);
h_brake = block.Dwork(1).Data(3);
h_RPM   = block.Dwork(1).Data(4);
h_TSR_panel = block.Dwork(1).Data(8);

% Inputs
RecID   = block.InputPort(4).Data;    % recognition IDs
time    = block.InputPort(5).Data;    % clock
warnp   = block.InputPort(10).Data;   % previous warning
DispTrigger = block.InputPort(11).Data;   % display trigger: colour -> gray
%Des_V = block.InputPort(8).Data; % desired velocity

% Params
RecognitionTemplates = block.DialogPrm(2).Data;
cdt = block.DialogPrm(3).Data;
gdt = block.DialogPrm(4).Data;

% Variables declaration
N  = 3; % Number of slots
slot = struct('t',  block.InputPort(7).Data, ...
    'id', block.InputPort(6).Data, ...
    'DesVel', block.InputPort(8).Data, ...
    'tag', [block.Dwork(1).Data(5); block.Dwork(1).Data(6); block.Dwork(1).Data( 7)], ...
    'gray', block.InputPort(12).Data);

% Set controls
velocity = block.InputPort(2).Data;
set(h_RPM,   'String', num2str(block.InputPort(1).Data) );
set(h_speed, 'String', num2str(round(3.6*velocity)));
set(h_brake, 'String', num2str(block.InputPort(3).Data) );

% Assign handles of axes children
for ii = 1 : N
    a = get(block.Dwork(1).Data(ii+4), 'Children');
    if ~isempty(a)
        slot.htag(ii) = a;
    else
        slot.htag(ii) = 0;
    end
end

%% Remove outdated displays
for ii = 1 : N
    if (slot.t(ii)) && (time > slot.t(ii) + cdt + gdt)
        axes(slot.tag(ii));     %#ok<*LAXES> % focus on slot
        set(slot.htag(ii), 'Visible', 'Off');
        cla;                    % remove the sign
        slot.t(ii) = 0;         % clear corresponding properties
        slot.id(ii) = 0;
        slot.DesVel(ii) = 0;
        slot.gray(ii) = 0;
    end
end

% Check if there is anything to show
RecID(~RecID) = [];     % remove 0s from vector
RecID = unique(RecID);  % remove duplicated recognitions
for ii = 1 : N          % remove already displayed signs
    indx = find(RecID == slot.id(ii));
    if ~isempty(indx)
        slot.t(ii) = time;     % update the time if sign is present on current frame
        if slot.gray(ii)
            % update the dispaly from gray to rgb
            axes(slot.tag(ii));      % focus on slot ii
            cla reset;
            imshow(RecognitionTemplates(slot.id(ii)).imgRGB);
            axis image
            slot.gray(ii) = 0;
        end
        RecID(indx) = [];    
    end
end

%% New assignements (speed limit slot)
SlotNum = 1;    % Slot number of speed limit display slot
if ~isempty(RecID)
    % Choose new speed limit sign to display
    lenRecID = length(RecID);
    NewSpeedLimits = zeros(lenRecID,1);
    for ii = 1 : lenRecID
        NewSpeedLimits(ii) = RecognitionTemplates(RecID(ii)).SpeedLimit;
        if NewSpeedLimits(ii) == 0
            NewSpeedLimits(ii) = inf;
        end
    end
    [NewSpeedLimitValue, NewSpeedLimitIndex] = min(NewSpeedLimits);
    if isinf(NewSpeedLimitValue)
        NewSpeedLimitIndex = [];
    end
    % Display new speed limit sign
    if ~isempty(NewSpeedLimitIndex)
        axes(slot.tag(SlotNum));      % focus on slot SlotNum
        cla reset;
        imshow(RecognitionTemplates(RecID(NewSpeedLimitIndex)).imgRGB);
        axis image
        slot.t(SlotNum) = time;
        slot.id(SlotNum) = RecID(NewSpeedLimitIndex);
        slot.gray(SlotNum) = 0; % not gray as it is new
        slot.DesVel(SlotNum) = NewSpeedLimitValue / 3.6;
    end
    % Remove other speed limit signs from RecID list
    RecID(~isinf(NewSpeedLimits)) = [];
end

%% New assignments (outdated displayed signs, other than speed limit slot)
if ~isempty(RecID)  % if there is something to assign
    SlotNum = 2;    % Start with slot 2 and iterate
    SlotIdx = 1; % iterator
    [~, ReplOrder] = sort(slot.t(SlotNum:N));
    ReplOrder = ReplOrder + 1; % plus numbor of slots for speed limits
    while ~isempty(RecID) && (SlotNum <= N)
        % Display the sign
        axes(slot.tag(ReplOrder(SlotIdx)));     % focus on slot
        cla reset;
        imshow(RecognitionTemplates(RecID(1)).imgRGB);
        axis image
        slot.t(ReplOrder(SlotIdx)) = time;
        slot.id(ReplOrder(SlotIdx)) = RecID(1);
        slot.gray(ReplOrder(SlotIdx)) = 0;
        slot.DesVel(ReplOrder(SlotIdx)) = 0; % it is not a speed limit sign
        RecID(1) = [];
        SlotNum = SlotNum + 1;
        SlotIdx = SlotIdx + 1;
    end
end

%% Compute desired velocity
VelOfGraySigns = slot.DesVel;

%% Change displayed sign to gray
for ii = 1 : N
    if DispTrigger(ii)
        % Display
        axes(slot.tag(ii));     % focus on slot
        cla reset;
        imshow(RecognitionTemplates(slot.id(ii)).GUIy);
        axis image
        slot.gray(ii) = 1;
    end
end

%% Assign handles of axes children (again due to possible changes)
for ii = 1 : N
    a = get(block.Dwork(1).Data(ii+4), 'Children');
    if ~isempty(a)
        slot.htag(ii) = a;
    else
        slot.htag(ii) = 0;
    end
end

%% Speed limit warning - image blinking
imp = block.InputPort(9).Data;
if imp % clock impulse
    for ii = 1 : N % check each slot
        if slot.DesVel(ii) % speed limit sign?
            if ~slot.gray(ii) && (slot.DesVel(ii) < velocity) % traffic rule not respected
                if imp > 0
                    set(slot.htag(ii), 'Visible','off')
                else
                    set(slot.htag(ii), 'Visible','on')
                end
            else
                set(slot.htag(ii), 'Visible','on') % make sure the slot is displayed if traffic rule is respected
            end
        end
    end
end

%% Set outputs
block.OutputPort(1).Data = slot.id;
block.OutputPort(2).Data = slot.t;
block.OutputPort(3).Data = slot.DesVel;
block.OutputPort(6).Data = slot.gray;
FinDesVel = min(VelOfGraySigns(VelOfGraySigns~=0));
if isempty(FinDesVel)
    FinDesVel = 0;
end
block.OutputPort(4).Data = FinDesVel;

%% Panel warning
warn = FinDesVel && (FinDesVel < velocity);
block.OutputPort(5).Data = warn;

% Panel highlight if change in state detected
if warn && (~warnp)
    set(h_TSR_panel, 'BorderWidth',2, 'ForegroundColor','Red','HighlightColor','Red', 'ShadowColor', 'Red');
end
if (~warn) && warnp
    set(h_TSR_panel, 'BorderWidth',2, 'ForegroundColor','Black', 'HighlightColor',[0.502 0.502 0.502], 'ShadowColor', [0.5 0.5 0.5]);
end
%endfunction Outputs
