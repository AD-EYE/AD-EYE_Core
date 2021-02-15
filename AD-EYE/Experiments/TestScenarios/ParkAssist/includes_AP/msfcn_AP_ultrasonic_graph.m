function msfcn_AP_ultrasonic_graph(block)

setup(block);
end
%endfunction

function setup(block)

%% define number of input and output ports
block.NumInputPorts  = 10;
block.NumOutputPorts =  0;

block.SetPreCompInpPortInfoToDynamic;
block.SetPreCompOutPortInfoToDynamic;

%% Register parameters
block.NumDialogPrms = 7;
dfreq   = block.DialogPrm(1).Data;

%% Input ports properties
block.InputPort(1).Complexity = 'real'; % ultrasonic2
block.InputPort(1).DataTypeId = 0; %real
block.InputPort(1).SamplingMode = 'Sample';

block.InputPort(2).Complexity = 'real'; % ultrasonic3
block.InputPort(2).DataTypeId = 0; %real
block.InputPort(2).SamplingMode = 'Sample';

block.InputPort(3).Complexity = 'real'; % xpos
block.InputPort(3).DataTypeId = 0; %real
block.InputPort(3).SamplingMode = 'Sample';

block.InputPort(4).Complexity = 'real'; % ypos
block.InputPort(4).DataTypeId = 0; %real
block.InputPort(4).SamplingMode = 'Sample';

block.InputPort(5).Complexity = 'real'; % heading
block.InputPort(5).DataTypeId = 0; %real
block.InputPort(5).SamplingMode = 'Sample';

block.InputPort(6).Complexity = 'real'; % xpos_delayed
block.InputPort(6).DataTypeId = 0; %real
block.InputPort(6).SamplingMode = 'Sample';

block.InputPort(7).Complexity = 'real'; % ypos_delayed
block.InputPort(7).DataTypeId = 0; %real
block.InputPort(7).SamplingMode = 'Sample';

block.InputPort(8).Complexity = 'real'; % heading_delayed
block.InputPort(8).DataTypeId = 0; %real
block.InputPort(8).SamplingMode = 'Sample';

block.InputPort(9).Complexity = 'real'; % ultra2_delayed
block.InputPort(9).DataTypeId = 0; %real
block.InputPort(9).SamplingMode = 'Sample';

block.InputPort(10).Complexity = 'real'; % ultra3_delayed
block.InputPort(10).DataTypeId = 0; %real
block.InputPort(10).SamplingMode = 'Sample';

%% block sample time
block.SampleTimes = [1/dfreq 0];

%% register methods
block.RegBlockMethod('PostPropagationSetup', @DoPostPropSetup);
block.RegBlockMethod('Start', @Start);
block.RegBlockMethod('Outputs', @Outputs);

%% Block runs on TLC in accelerator mode.
block.SetAccelRunOnTLC(true);

function DoPostPropSetup( block )
    block.NumDworks = 1;
    block.Dwork(1).Name = 'handles';
    block.Dwork(1).Dimensions = 2;
    block.Dwork(1).DatatypeID = 0;
    block.Dwork(1).Complexity = 'Real';
end
% endfunction

end
%endfunction

function Start(block)

try %#ok<TRYNC>
    close (AP_ultrasonic_graph)
end
    
% Useful handles
h_Rdlg = AP_ultrasonic_graph;
set(h_Rdlg, 'Name', 'AP Ultrasonic');
h_axes = findobj(h_Rdlg, 'Tag', 'radar_axes');
  
% Set window size
set(h_Rdlg,'Units','Pixels');           % make sure pixels are used as units
position(1) = 80;                       % horizontal position   
position(2) = 660;                      % vertical position     
position(3) = 450;                      % set width (horizontally)
position(4) = 225;                      % set width (vertically)
set(h_Rdlg,'Position',position);        % update
    
% Set plot size
plot_position = get(h_axes, 'Position');
plot_position(1) = 1;
plot_position(3:4) = position(3:4);
set(h_axes,'Position',plot_position);
    
% Set plot
cla(h_axes);
set(h_axes,'XGrid','on','YGrid','on');
set(h_axes,'XTickLabel',[],'YTicklabel',[]);

block.Dwork(1).Data = [double(h_Rdlg) double(h_axes)];
    
end
% End of Start function

function Outputs(block)
% cla(h_axes);
h_axes = block.Dwork(1).Data(2);

w       = block.DialogPrm(2).Data - 0.1;    %Small error correction is added to the length to account for the bounding box (instead of actual vehcile shape) inaccuracy during visualization.
h       = block.DialogPrm(3).Data;
b       = block.DialogPrm(4).Data;
p1      = block.DialogPrm(5).Data;
S_XOffset = block.DialogPrm(6).Data;
S_YOffset = block.DialogPrm(7).Data;

ultra2 = block.InputPort(1).Data;
ultra3 = block.InputPort(2).Data;
xpos = block.InputPort(3).Data;
ypos = block.InputPort(4).Data;
heading = block.InputPort(5).Data;
xpos_delayed = block.InputPort(6).Data;
ypos_delayed = block.InputPort(7).Data;
heading_delayed = block.InputPort(8).Data;
ultra2_delayed = block.InputPort(9).Data;
ultra3_delayed = block.InputPort(10).Data;

set(h_axes,'XLim', [xpos-16, xpos+16],'YLim',[ypos-8, ypos+8]);

set(h_axes,'NextPlot', 'add');
% sensors locations
xpos2 = [xpos_delayed+(S_XOffset-b)*cos(-heading_delayed)-S_YOffset*sin(-heading_delayed), xpos+(S_XOffset-b)*cos(-heading)-S_YOffset*sin(-heading)];
ypos2 = [ypos_delayed+(S_XOffset-b)*sin(-heading_delayed)+S_YOffset*cos(-heading_delayed), ypos+(S_XOffset-b)*sin(-heading)+S_YOffset*cos(-heading)];
xpos3 = [xpos_delayed+(S_XOffset-b)*cos(-heading_delayed)+S_YOffset*sin(-heading_delayed), xpos+(S_XOffset-b)*cos(-heading)+S_YOffset*sin(-heading)];
ypos3 = [ypos_delayed+(S_XOffset-b)*sin(-heading_delayed)-S_YOffset*cos(-heading_delayed), ypos+(S_XOffset-b)*sin(-heading)-S_YOffset*cos(-heading)];
% detection locations
xpos4 = [xpos2(1)-abs(ultra3_delayed)*sin(-heading_delayed), xpos2(2)-abs(ultra3)*sin(-heading)];
ypos4 = [ypos2(1)+abs(ultra3_delayed)*cos(-heading_delayed), ypos2(2)+abs(ultra3)*cos(-heading)];
xpos5 = [xpos3(1)+abs(ultra2_delayed)*sin(-heading_delayed), xpos3(2)+abs(ultra2)*sin(-heading)];
ypos5 = [ypos3(1)-abs(ultra2_delayed)*cos(-heading_delayed), ypos3(2)-abs(ultra2)*cos(-heading)];
if xpos_delayed ~= 0 && ultra3 < 1e3 && ultra2 > -1e3
%     plot(h_axes, xpos2, ypos2,'g','LineWidth',2,'HandleVisibility','off'); % left sens
%     plot(h_axes, xpos3, ypos3,'g','LineWidth',2,'HandleVisibility','off'); % right sens
    plot(h_axes, xpos4, ypos4,'b','LineWidth',2,'HandleVisibility','off'); % left/up
    plot(h_axes, xpos5, ypos5,'b','LineWidth',2,'HandleVisibility','off'); % right/down
end
plot(h_axes, xpos-b*cos(heading), ypos+b*sin(heading), '.', 'LineWidth', 8, 'MarkerEdgeColor', 'k', 'HandleVisibility','off');

xpos6 = xpos-b*cos(heading);
ypos6 = ypos+b*sin(heading);

x = xpos6-p1; y = ypos6-h/2;
xv=[x x+w x+w x x]; yv=[y y y+h y+h y];
tx = x+p1; ty = y+h/2;
xv = xv-tx; yv = yv-ty;

R(1,:)=xv; R(2,:)=yv;
XY = [cos(-heading) -sin(-heading); sin(-heading) cos(-heading)]*R;
XY = [XY(1,:)+tx; XY(2,:)+ty];
set(h_axes,'NextPlot','replacechildren');
plot(h_axes, XY(1,:),XY(2,:),'r','LineWidth',2);
end

