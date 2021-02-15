function msfcn_AEBS_PlotSpeed(block)
setup(block);
%endfunction

function setup( block )


%% define number of input and output ports
block.NumInputPorts  = 5;
block.NumOutputPorts = 0;


%% port properties
block.SetPreCompInpPortInfoToDynamic;
block.SetPreCompOutPortInfoToDynamic;

block.InputPort(1).Complexity = 'real'; % Engine velocity
block.InputPort(1).DataTypeId = 0; %real
block.InputPort(1).SamplingMode = 'Sample';
block.InputPort(1).Dimensions = 1;

block.InputPort(2).Complexity = 'real'; % Vehicle velocity
block.InputPort(2).DataTypeId = 0; %real
block.InputPort(2).SamplingMode = 'Sample';
block.InputPort(2).Dimensions = 1;

block.InputPort(3).Complexity = 'real'; % Brake
block.InputPort(3).DataTypeId = 0; %real
block.InputPort(3).SamplingMode = 'Sample';

block.InputPort(4).Complexity = 'real'; % Throttle
block.InputPort(4).DataTypeId = 0; %real
block.InputPort(4).SamplingMode = 'Sample';
 
block.InputPort(5).Complexity = 'real'; % Warning sign
block.InputPort(5).DataTypeId = -1; %logical
block.InputPort(5).SamplingMode = 'Sample';

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
    block.Dwork(1).Dimensions = 7;
    block.Dwork(1).DatatypeID = 0;
    block.Dwork(1).Complexity = 'Real';
%endfunction
    
function Start(block)

if block.DialogPrm(2).Data % Display switch ON / OFF
    try%#ok<TRYNC>
        close (AEBS_PlotSpeed)
    end
    h_dlg = AEBS_PlotSpeed;
    h_Vehicle_velocity = findobj(h_dlg, 'Tag', 'text_Vehicle_speed');
    h_Engine_velocity = findobj(h_dlg, 'Tag', 'text_Engine_speed');
    h_Brake = findobj(h_dlg, 'Tag', 'text_Brake');
    h_Throttle = findobj(h_dlg, 'Tag', 'text_Throttle');
    h_Warning = findobj(h_dlg, 'Tag', 'text_Warning');
    h_WarningBlock = findobj(h_dlg, 'Tag', 'Warning');
       
    block.Dwork(1).Data = [double(h_dlg) double(h_Vehicle_velocity) double(h_Engine_velocity) double(h_Brake) double(h_Throttle) double(h_Warning) double(h_WarningBlock)];
end
% endfunction Start

        
function Outputs(block)

    h_Engine_velocity = block.Dwork(1).Data(3);
    h_Vehicle_velocity = block.Dwork(1).Data(2);
    h_Brake = block.Dwork(1).Data(4);
    h_Throttle = block.Dwork(1).Data(5);
    h_Warning = block.Dwork(1).Data(6);
    h_WarningBlock = block.Dwork(1).Data(7);
        
    set(h_Engine_velocity,'String',num2str(block.InputPort(1).Data));
    set(h_Vehicle_velocity,'String',num2str(block.InputPort(2).Data));
    set(h_Brake,'String',num2str(block.InputPort(3).Data));
    set(h_Throttle,'String',num2str(block.InputPort(4).Data));

    if logical(block.InputPort(5).Data)
        TextColor = [1 0 0];
        BorderColor = [1 0 0];
    else
        TextColor = [0.9 0.9 0.9];
        BorderColor = [0.5 0.5 0.5];
    end
    set(h_Warning,'String','Warning','ForegroundColor',TextColor);
    set(h_WarningBlock,'HighlightColor',BorderColor,'ShadowColor',BorderColor);

%endfunction Outputs
