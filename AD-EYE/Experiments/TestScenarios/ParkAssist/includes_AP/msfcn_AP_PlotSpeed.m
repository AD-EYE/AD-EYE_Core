function msfcn_AP_PlotSpeed(block)
setup(block);
%endfunction msfcn_AP_PlotSpeed

function setup( block )
%% define number of input and output ports
block.NumInputPorts  = 6;
block.NumOutputPorts = 0;

%% port properties
block.SetPreCompInpPortInfoToDynamic;
block.SetPreCompOutPortInfoToDynamic;

block.InputPort(1).Complexity = 'real'; % Velocity
block.InputPort(1).DataTypeId = 0; %real
block.InputPort(1).SamplingMode = 'Sample';
block.InputPort(1).Dimensions = 1;

block.InputPort(2).Complexity = 'real'; % Gear
block.InputPort(2).DataTypeId = 0; %real
block.InputPort(2).SamplingMode = 'Sample';
block.InputPort(2).Dimensions = 1;

block.InputPort(3).Complexity = 'real'; % Brake
block.InputPort(3).DataTypeId = 0; %real
block.InputPort(3).SamplingMode = 'Sample';

block.InputPort(4).Complexity = 'real'; % Throttle
block.InputPort(4).DataTypeId = 0; %real
block.InputPort(4).SamplingMode = 'Sample';

block.InputPort(5).Complexity = 'real'; % Steering Angle
block.InputPort(5).DataTypeId = -1; %inherited
block.InputPort(5).SamplingMode = 'Sample';

block.InputPort(6).Complexity = 'real'; % Vehicle State
block.InputPort(6).DataTypeId = 0; %inherited
block.InputPort(6).SamplingMode = 'Sample';

%% Register parameters
block.NumDialogPrms     = 2;
dfreq = block.DialogPrm(1).Data;

%% block sample time
block.SampleTimes = [1/dfreq 0];

%% register methods
block.RegBlockMethod('PostPropagationSetup', @DoPostPropSetup);
block.RegBlockMethod('Start', @Start);
block.RegBlockMethod('Outputs', @Outputs);

%% Block runs on TLC in accelerator mode.
block.SetAccelRunOnTLC(true);
%endfunction setup

function DoPostPropSetup( block )
block.NumDworks = 1;
block.Dwork(1).Name = 'handles';
block.Dwork(1).Dimensions = 7;
block.Dwork(1).DatatypeID = 0;
block.Dwork(1).Complexity = 'Real';
%endfunction DoPostPropSetup

function Start(block)
h_dlg              = AP_PlotSpeed;
h_speed            = findobj(h_dlg, 'Tag', 'text_speed');
h_gear             = findobj(h_dlg, 'Tag', 'text_gear');
h_brake            = findobj(h_dlg, 'Tag', 'text_brake');
h_throttle         = findobj(h_dlg, 'Tag', 'text_throttle');
h_steering_angle   = findobj(h_dlg, 'Tag', 'text_steering_angle');
h_vehicle_state    = findobj(h_dlg, 'Tag', 'text_vehicle_state');
h_text_init_vel    = findobj(h_dlg, 'Tag', 'text_init_vel');
h_text_des_vel     = findobj(h_dlg, 'Tag', 'text_des_vel');

b1 = num2str(str2num(get(h_text_init_vel,'String'))/3.6);

b = round(str2num(get(h_text_init_vel,'String'))/3.6);
if (isempty(b))
    b1 = num2str(0);     %default value
end

b2 = num2str(str2num(get(h_text_des_vel,'String'))/3.6);

b = round(str2num(get(h_text_des_vel,'String'))/3.6);
if (isempty(b))
    b2 = num2str(10);     %default value
end

PathName = block.DialogPrm(2).Data;
if str2num(get_param([PathName '/AP_DEMO/V0'],'Value')) ~= str2num(b1)
    set_param([PathName '/AP_DEMO/V0'],'Value',b1);
end

if str2num(get_param([PathName '/AP_DEMO/V1'],'Value')) ~= str2num(b2)
    set_param([PathName '/AP_DEMO/V1'],'Value',b2);
end

set(h_dlg,'Units','Pixels');       % make sure pixels are used as units
position(1) = 80;                  % horizontal position
position(2) = 80;                  % vertical position
position(3) = 450;                 % set width (horizontally)
position(4) = 520;                 % set width (vertically)
set(h_dlg,'Position',position);    % update

block.Dwork(1).Data = [double(h_dlg) double(h_speed) double(h_gear) double(h_steering_angle) double(h_throttle) double(h_brake) double(h_vehicle_state)];
%endfunction Start

function Outputs(block)
h_speed            = block.Dwork(1).Data(2);
h_gear             = block.Dwork(1).Data(3);
h_steering_angle   = block.Dwork(1).Data(4);
h_throttle         = block.Dwork(1).Data(5);
h_brake            = block.Dwork(1).Data(6);
h_vehicle_state    = block.Dwork(1).Data(7);

% Setting Strings on gui
set(h_speed,         'String', sprintf('%0.1f',(block.InputPort(1).Data)));
set(h_gear,          'String', sprintf('%0.0f',(block.InputPort(2).Data)));
set(h_brake,         'String', sprintf('%0.0f',(block.InputPort(3).Data)));
set(h_throttle,      'String', sprintf('%0.0f',(block.InputPort(4).Data)));
set(h_steering_angle,'String', sprintf('%0.0f',(block.InputPort(5).Data)));
set(h_vehicle_state, 'String', num2str(block.InputPort(6).Data));
if block.InputPort(6).Data == 1
    set(h_vehicle_state, 'String', 'Searching Parking Area');
elseif block.InputPort(6).Data == 2
    set(h_vehicle_state, 'String', 'Executing Parking Maneuver');
else
    set(h_vehicle_state, 'String', 'Vehicle is Parked');
end
%endfunction Outputs

