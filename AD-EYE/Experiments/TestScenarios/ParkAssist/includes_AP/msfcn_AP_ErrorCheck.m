function msfcn_AP_ErrorCheck(block)
setup(block);
%endfunction

function setup( block )
%% define number of input and output ports
block.NumInputPorts  = 0;
block.NumOutputPorts = 1;

%% port properties
block.SetPreCompInpPortInfoToDynamic;
block.SetPreCompOutPortInfoToDynamic;

block.OutputPort(1).Complexity = 'real'; % STOP
block.OutputPort(1).DataTypeId = 0; %real
block.OutputPort(1).SamplingMode = 'Sample';
block.OutputPort(1).Dimensions = 1;

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
%endfunction

function DoPostPropSetup( block )
	block.NumDworks = 1;
	block.Dwork(1).Name = 'handles';
	block.Dwork(1).Dimensions = 12;
	block.Dwork(1).DatatypeID = 0;
	block.Dwork(1).Complexity = 'Real';
%endfunction

function Start(block)
h_dlg              = AP_PlotSpeed;

h_start = findobj(h_dlg, 'Tag', 'start');
h_pause = findobj(h_dlg, 'Tag', 'pause');
h_stop =  findobj(h_dlg, 'Tag', 'stop');
h_continue = findobj(h_dlg, 'Tag', 'pushbutton12');
h_bay = findobj(h_dlg, 'Tag', 'text_bay');
h_parallel = findobj(h_dlg, 'Tag', 'text_parallel');
h_left = findobj(h_dlg, 'Tag', 'text_left');
h_right = findobj(h_dlg, 'Tag', 'text_right');
h_text_init_vel    = findobj(h_dlg, 'Tag', 'text_init_vel');
h_text_des_vel     = findobj(h_dlg, 'Tag', 'text_des_vel');

Path = find_system(bdroot,'LookUnderMasks','all','Regexp','on','Name','AP_DEMO');

if(get(h_bay,'Value'))
        set_param([Path{1} '/MainSwitch'],'sw','1');
else
        set_param([Path{1} '/MainSwitch'],'sw','0');
end

if(get(h_left,'Value'))
        set_param([Path{1} '/Braking_&_Graph_Subsystem/Braking_Control_Subsystem/LeftRight'],'Value','1');
else
        set_param([Path{1} '/Braking_&_Graph_Subsystem/Braking_Control_Subsystem/LeftRight'],'Value','-1');
end

myArray = [h_pause h_stop];
set(myArray, 'Enable', 'On');

myArray = [h_start h_continue h_bay h_parallel h_left h_right h_text_init_vel h_text_des_vel];
set(myArray, 'Enable', 'Off');

PathName = block.DialogPrm(2).Data;

Sim_Stop = 0;
b = (str2num(get(h_text_des_vel,'String'))/3.6);
if (b<1 || b>5)
    ed = errordlg('Vehicle Desired Velocity must be a number between 3.6 - 18 km/h','Error');
    set(ed, 'WindowStyle', 'modal');
    uiwait(ed);
    Sim_Stop = 1;
    
elseif isempty(b)
    ed = errordlg('Vehicle Desired Velocity must be a number between 3.6 - 18 km/h','Error');
    set(ed, 'WindowStyle', 'modal');
    uiwait(ed);
    Sim_Stop = 1;
end

b = (str2num(get(h_text_init_vel,'String'))/3.6);
if (b<0 || b>5)
    ed = errordlg('Vehicle Initial Velocity must be a number between 0 - 18 km/h','Error');
    set(ed, 'WindowStyle', 'modal');
    uiwait(ed);
    Sim_Stop = 1;
  
elseif isempty(b)
    ed = errordlg('Vehicle Initial Velocity must be a number between 0 - 18 km/h','Error');
    set(ed, 'WindowStyle', 'modal');
    uiwait(ed);
    Sim_Stop = 1;
end

block.Dwork(1).Data = [double(h_dlg) double(h_start) double(h_pause) double(h_stop) double(h_continue) double(h_bay) double(h_parallel) double(h_left) double(h_right) double(h_text_init_vel) double(h_text_des_vel) double(Sim_Stop)];
%endfunction Start

function Outputs(block)
Sim_Stop                 = block.Dwork(1).Data(12);
block.OutputPort(1).Data = Sim_Stop;