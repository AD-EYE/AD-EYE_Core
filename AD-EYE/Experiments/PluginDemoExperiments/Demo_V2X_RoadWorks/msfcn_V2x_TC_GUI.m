function msfcn_V2x_TC_GUI(block)
setup(block);
%endfunction



function setup( block )


%% define number of input and output ports
block.NumInputPorts  = 7;
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
block.InputPort(3).Dimensions = 1;

block.InputPort(4).Complexity = 'real'; % Throttle
block.InputPort(4).DataTypeId = 0; %real
block.InputPort(4).SamplingMode = 'Sample';
block.InputPort(4).Dimensions = 1;

block.InputPort(5).Complexity = 'real'; % Message
block.InputPort(5).DataTypeId = 0;
block.InputPort(5).SamplingMode = 'Sample';
block.InputPort(5).Dimensions = [3 1];


block.InputPort(6).Complexity = 'real'; % Change
block.InputPort(6).DataTypeId = 0;
block.InputPort(6).SamplingMode = 'Sample';
block.InputPort(6).Dimensions = 1;

block.InputPort(7).Complexity = 'real'; % Warning
block.InputPort(7).DataTypeId = 0;
block.InputPort(7).SamplingMode = 'Sample';
block.InputPort(7).Dimensions = 1;


%% Register parameters
block.NumDialogPrms     = 0;

% %% block sample time
% block.SampleTimes = [1/dfreq 0];

%% register methods
block.RegBlockMethod('PostPropagationSetup', @DoPostPropSetup);
block.RegBlockMethod('Start', @Start);
block.RegBlockMethod('Outputs', @Outputs);

%% Block runs on TLC in accelerator mode.
block.SetAccelRunOnTLC(true);
%endfunction

function DoPostPropSetup( ~ )
%endfunction

function Start(block)

try
    close (V2x_TC_GUI)
end
h_dlg = V2x_TC_GUI;
%h_Velocity_image = findobj(h_dlg, 'Tag', 'Speed_image');
h_Vehicle_velocity = findobj(h_dlg, 'Tag', 'text_Vehicle_speed');
h_Engine_velocity = findobj(h_dlg, 'Tag', 'text_Engine_speed');
h_Brake = findobj(h_dlg, 'Tag', 'text_Brake');
h_Throttle = findobj(h_dlg, 'Tag', 'text_Throttle');
V2x_sign = findobj(h_dlg, 'Tag', 'V2x_sign');
V2x_sign2 = findobj(h_dlg, 'Tag', 'V2x_sign2');
V2x_sign3 = findobj(h_dlg, 'Tag', 'V2x_sign3');
h_WarningBlock = findobj(h_dlg, 'Tag', 'Warning');

handles = [h_dlg h_Vehicle_velocity h_Engine_velocity h_Brake h_Throttle V2x_sign h_WarningBlock V2x_sign2 V2x_sign3];
set_param(block.BlockHandle,'UserData',handles);

%endfunction Start

function Outputs(block)

handles = get_param(block.BlockHandle, 'UserData');

h_Engine_velocity = handles(3);
h_Vehicle_velocity = handles(2);
h_Brake = handles(4);
h_Throttle = handles(5);
V2x_sign = handles(6);
h_WarningBlock = handles(7);
V2x_sign2 = handles(8);
V2x_sign3 = handles(9);

set(h_Engine_velocity,'String',num2str(block.InputPort(1).Data));
set(h_Vehicle_velocity,'String',num2str(block.InputPort(2).Data));
set(h_Brake,'String',num2str(block.InputPort(3).Data));
set(h_Throttle,'String',num2str(block.InputPort(4).Data));

% Inputs
warning  = block.InputPort(7).Data;
% change   = block.InputPort(6).Data;
message   = block.InputPort(5).Data;

if any(logical(warning))
    BorderColor = [1 0 0];
else
    BorderColor = [0.5 0.5 0.5];
end
set(h_WarningBlock,'HighlightColor',BorderColor,'ShadowColor',BorderColor, 'ForegroundColor', BorderColor);

if any(logical(warning))
    if message(1) == 60
        axes(V2x_sign3);      % focus on slot SlotNum
        [img, map, alpha] = imread('Models\A01060','png');
        imshow(img);
        axis image;
    end
else
    axes(V2x_sign3);     %#ok<*LAXES> % focus on slot
    set(V2x_sign3, 'Visible', 'Off');
    cla;                    % remove the sign
end

if any(logical(warning))
    if message(2) == 3
        axes(V2x_sign);      % focus on slot SlotNum
        [img, map, alpha] = imread('Models\z123','png');
        imshow(img);
        axis image;
    end
else
    axes(V2x_sign);     %#ok<*LAXES> % focus on slot
    set(V2x_sign, 'Visible', 'Off');
    cla;                    % remove the sign
end

if any(logical(warning))
    if message(3) == 1
        axes(V2x_sign2);      % focus on slot SlotNum
        [img, map, alpha] = imread('Models\z531-20','png');
        imshow(img);
        axis image;
    end
else
    axes(V2x_sign2);     %#ok<*LAXES> % focus on slot
    set(V2x_sign2, 'Visible', 'Off');
    cla;                    % remove the sign
end
%endfunction Outputs

