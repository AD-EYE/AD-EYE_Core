function msfcn_PPS_PlotSpeed(block)
setup(block);
%endfunction

function setup( block )


%% define number of input and output ports
block.NumInputPorts  = 8;
block.NumOutputPorts = 0;


%% port properties
block.SetPreCompInpPortInfoToDynamic;
block.SetPreCompOutPortInfoToDynamic;

block.InputPort(1).Complexity = 'real'; % Vehicle velocity
block.InputPort(1).DataTypeId = 0; %real
block.InputPort(1).SamplingMode = 'Sample';
block.InputPort(1).Dimensions = 1;

block.InputPort(2).Complexity = 'real'; % RPM
block.InputPort(2).DataTypeId = 0; %real
block.InputPort(2).SamplingMode = 'Sample';
block.InputPort(2).Dimensions = 1;

block.InputPort(3).Complexity = 'real'; % Brake
block.InputPort(3).DataTypeId = 0; %real
block.InputPort(3).SamplingMode = 'Sample';
block.InputPort(3).Dimensions = 1; 

block.InputPort(4).Complexity = 'real'; % Detection flag
block.InputPort(4).DataTypeId = -1; %logical
block.InputPort(4).SamplingMode = 'Sample';
block.InputPort(4).Dimensions = 1; 

block.InputPort(5).Complexity = 'real'; % Warning flag
block.InputPort(5).DataTypeId = -1; %logical
block.InputPort(5).SamplingMode = 'Sample';
block.InputPort(5).Dimensions = 1;

block.InputPort(6).Complexity = 'real'; % Braking flag
block.InputPort(6).DataTypeId = -1; %logical
block.InputPort(6).SamplingMode = 'Sample';
block.InputPort(6).Dimensions = 1;

block.InputPort(7).Complexity = 'real'; % Pedestrian flag
block.InputPort(7).DataTypeId = -1; %logical
block.InputPort(7).SamplingMode = 'Sample';
block.InputPort(7).Dimensions = 1;

block.InputPort(8).Complexity = 'real'; % TTC
block.InputPort(8).DataTypeId = 0; %real
block.InputPort(8).SamplingMode = 'Sample';
block.InputPort(8).Dimensions = 1;

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
	block.Dwork(1).Dimensions = 22;
	block.Dwork(1).DatatypeID = 0;
    block.Dwork(1).Complexity = 'Real';

% endfunction

function Start(block)

if block.DialogPrm(2).Data;
    
    try%#ok<TRYNC>
        close(PPS_PlotSpeed);
    end
    
    h_dlg   = PPS_PlotSpeed;
    
    h_speed = findobj(h_dlg, 'Tag', 'Speed_text');
    h_brake = findobj(h_dlg, 'Tag', 'BrakePressure_text');
    h_RPM   = findobj(h_dlg, 'Tag', 'RPM_text');
    h_coll_value = findobj(h_dlg, 'Tag', 'collision_value');
    h_ped_value  = findobj(h_dlg, 'Tag', 'ped_value');
    h_warn_value = findobj(h_dlg, 'Tag', 'warn_value');
    h_brake_value = findobj(h_dlg, 'Tag', 'brake_value');
    h_cs_value = findobj(h_dlg, 'Tag', 'cs_value');
    
    h_coll_text1 = findobj(h_dlg, 'Tag', 'collision_text1');
    h_coll_text2 = findobj(h_dlg, 'Tag', 'collision_text2');
    h_ped_text1 = findobj(h_dlg, 'Tag', 'ped_text1');
    h_ped_text2 = findobj(h_dlg, 'Tag', 'ped_text2');
    h_warn_text1 = findobj(h_dlg, 'Tag', 'warn_text1');
    h_warn_text2 = findobj(h_dlg, 'Tag', 'warn_text2');
    h_brake_text1 = findobj(h_dlg, 'Tag', 'brake_text1');
    h_brake_text2 = findobj(h_dlg, 'Tag', 'brake_text2');
    
    h_coll_panel = findobj(h_dlg, 'Tag', 'collision_panel');
    h_ped_panel = findobj(h_dlg, 'Tag', 'ped_panel');
    h_warn_panel = findobj(h_dlg, 'Tag', 'warn_panel');
    h_brake_panel = findobj(h_dlg, 'Tag', 'brake_panel');
    h_cs_panel = findobj(h_dlg, 'Tag', 'cs_panel');
    
    
    block.Dwork(1).Data = [double(h_dlg) double(h_speed) double(h_brake) double(h_RPM) double(h_coll_value) double(h_ped_value) ...
        double(h_warn_value) double(h_brake_value) double(h_cs_value) double(h_coll_text1) double(h_coll_text2) double(h_ped_text1) ...
        double(h_ped_text2) double(h_warn_text1) double(h_warn_text2) double(h_brake_text1) double(h_brake_text2) double(h_coll_panel) ...
        double(h_ped_panel) double(h_warn_panel) double(h_brake_panel) double(h_cs_panel)];
end
%endfunction Start

function Outputs(block)

    % Velocity and RPM
    h_speed = block.Dwork(1).Data(2);
    h_brake = block.Dwork(1).Data(3);
    h_RPM = block.Dwork(1).Data(4);
    set(h_speed, 'String', num2str(round(block.InputPort(1).Data)));
    set(h_RPM,   'String', num2str(block.InputPort(2).Data) );
    set(h_brake, 'String', num2str(block.InputPort(3).Data) );
    
    % Get TTC value
    ttcn = block.InputPort(8).Data;
    ttcs = sprintf('%.2f',ttcn);
    
    % Get a value of braking flag
    brake_flag = block.InputPort(6).Data;
    
    % Detection flag
    h_coll_value = block.Dwork(1).Data(5);
    h_coll_text1 = block.Dwork(1).Data(10);
    h_coll_text2 = block.Dwork(1).Data(11);
    h_coll_panel = block.Dwork(1).Data(18);
    if block.InputPort(4).Data
       set(h_coll_panel, 'BorderWidth',2, 'ForegroundColor','Black', 'HighlightColor',[0.502 0.502 0.502], 'ShadowColor', [0.5 0.5 0.5]);
       set(h_coll_value, 'ForegroundColor', 'Black');
       set(h_coll_text1, 'ForegroundColor', 'Black');
       set(h_coll_text2, 'ForegroundColor', 'Black');
       set(h_coll_value, 'ForegroundColor', 'Black');
       if strcmp( get(h_coll_value, 'String'), '_.__')
           set(h_coll_value, 'String', ttcs);
       end
    else
       set(h_coll_panel, 'BorderWidth',1, 'ForegroundColor',[0.9,0.9,0.9], 'HighlightColor',[0.5 0.5 0.5], 'ShadowColor', [0.5 0.5 0.5]);
       set(h_coll_value, 'ForegroundColor', [0.9 0.9 0.9]);
       set(h_coll_text1, 'ForegroundColor', [0.9 0.9 0.9]);
       set(h_coll_text2, 'ForegroundColor', [0.9 0.9 0.9]);
       set(h_coll_value, 'ForegroundColor', [0.9 0.9 0.9]);
       if (~strcmp( get(h_coll_value, 'String'), '_.__')) 
           set(h_coll_value, 'String', '_.__');
       end
    end
    
    % Pedestrian flag
    h_ped_value = block.Dwork(1).Data(6);
    h_ped_text1 = block.Dwork(1).Data(12);
    h_ped_text2 = block.Dwork(1).Data(13);
    h_ped_panel = block.Dwork(1).Data(19);
    if block.InputPort(7).Data
       set(h_ped_panel, 'BorderWidth',2, 'ForegroundColor','Black', 'HighlightColor',[0.502 0.502 0.502], 'ShadowColor', [0.5 0.5 0.5]);
       set(h_ped_value, 'ForegroundColor', 'Black');
       set(h_ped_text1, 'ForegroundColor', 'Black');
       set(h_ped_text2, 'ForegroundColor', 'Black');
       set(h_ped_value, 'ForegroundColor', 'Black');
       if strcmp( get(h_ped_value, 'String'), '_.__')
           set(h_ped_value, 'String', ttcs);
       end
    else
       set(h_ped_panel, 'BorderWidth',1, 'ForegroundColor',[0.9,0.9,0.9], 'HighlightColor',[0.5 0.5 0.5], 'ShadowColor', [0.5 0.5 0.5]);
       set(h_ped_value, 'ForegroundColor', [0.9 0.9 0.9]);
       set(h_ped_text1, 'ForegroundColor', [0.9 0.9 0.9]);
       set(h_ped_text2, 'ForegroundColor', [0.9 0.9 0.9]);
       set(h_ped_value, 'ForegroundColor', [0.9 0.9 0.9]);
       if ~strcmp( get(h_ped_value, 'String'), '_.__')
           set(h_ped_value, 'String', '_.__');
       end
    end
    
    % Warning flag  
    h_warn_value = block.Dwork(1).Data(7);
    h_warn_text1 = block.Dwork(1).Data(14);
    h_warn_text2 = block.Dwork(1).Data(15);
    h_warn_panel = block.Dwork(1).Data(20);
    if block.InputPort(5).Data
       set(h_warn_panel, 'BorderWidth',2, 'ForegroundColor',[1 0.6471 0], 'HighlightColor',[1 0.6471 0], 'ShadowColor', [1 0.6471 0]);
       set(h_warn_value, 'ForegroundColor', [1 0.6471 0]);
       set(h_warn_text1, 'ForegroundColor', [1 0.6471 0]);
       set(h_warn_text2, 'ForegroundColor', [1 0.6471 0]);
       set(h_warn_value, 'ForegroundColor', [1 0.6471 0]);
       if strcmp( get(h_warn_value, 'String'), '_.__')
           set(h_warn_value, 'String', ttcs);
       end
    else
       set(h_warn_panel, 'BorderWidth',1, 'ForegroundColor',[0.9,0.9,0.9], 'HighlightColor',[0.5 0.5 0.5], 'ShadowColor', [0.5 0.5 0.5]);
       set(h_warn_value, 'ForegroundColor', [0.9 0.9 0.9]);
       set(h_warn_text1, 'ForegroundColor', [0.9 0.9 0.9]);
       set(h_warn_text2, 'ForegroundColor', [0.9 0.9 0.9]);
       set(h_warn_value, 'ForegroundColor', [0.9 0.9 0.9]);
       if ~strcmp( get(h_warn_value, 'String'), '_.__')
           set(h_warn_value, 'String', '_.__');
       end
    end
    
    % Braking flag
    h_brake_value = block.Dwork(1).Data(8);
    h_brake_text1 = block.Dwork(1).Data(16);
    h_brake_text2 = block.Dwork(1).Data(17);
    h_brake_panel = block.Dwork(1).Data(21);
    if brake_flag
       set(h_brake_panel, 'BorderWidth',2, 'ForegroundColor','Red', 'HighlightColor','Red', 'ShadowColor', 'Red');
       set(h_brake_value, 'ForegroundColor', 'Red');
       set(h_brake_text1, 'ForegroundColor', 'Red');
       set(h_brake_text2, 'ForegroundColor', 'Red');
       set(h_brake_value, 'ForegroundColor', 'Red');
       if strcmp( get(h_brake_value, 'String'), '_.__')
           set(h_brake_value, 'String', ttcs);
       end
    else
       set(h_brake_panel, 'BorderWidth',1, 'ForegroundColor',[0.9,0.9,0.9], 'HighlightColor',[0.5 0.5 0.5], 'ShadowColor', [0.5 0.5 0.5]);
       set(h_brake_value, 'ForegroundColor', [0.9 0.9 0.9]);
       set(h_brake_text1, 'ForegroundColor', [0.9 0.9 0.9]);
       set(h_brake_text2, 'ForegroundColor', [0.9 0.9 0.9]);
       set(h_brake_value, 'ForegroundColor', [0.9 0.9 0.9]);
       if ~strcmp( get(h_brake_value, 'String'), '_.__')
           set(h_brake_value, 'String', '_.__');
       end
    end
%endfunction Outputs
