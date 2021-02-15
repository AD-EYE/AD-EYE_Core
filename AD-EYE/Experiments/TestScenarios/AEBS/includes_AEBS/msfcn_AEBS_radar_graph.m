function msfcn_AEBS_radar_graph(block)

setup(block);
end
%endfunction

function setup( block)

%% define number of input and output ports
block.NumInputPorts  = 7;
block.NumOutputPorts = 0;

block.SetPreCompInpPortInfoToDynamic;
block.SetPreCompOutPortInfoToDynamic;

%% Register parameters
block.NumDialogPrms = 5;
dfreq       = block.DialogPrm(1).Data;
TISdet      = block.DialogPrm(2).Data;

%% Input ports properties
block.InputPort(1).Complexity = 'real'; % TIS1 Range
block.InputPort(1).DataTypeId = 0; %real
block.InputPort(1).SamplingMode = 'Sample';
block.InputPort(1).Dimensions = TISdet(1);

block.InputPort(2).Complexity = 'real'; % TIS1 Theta
block.InputPort(2).DataTypeId = 0; %real
block.InputPort(2).SamplingMode = 'Sample';
block.InputPort(2).Dimensions = TISdet(1);

block.InputPort(3).Complexity = 'real'; % TIS2 Range
block.InputPort(3).DataTypeId = 0; %real
block.InputPort(3).SamplingMode = 'Sample';
block.InputPort(3).Dimensions = TISdet(2);

block.InputPort(4).Complexity = 'real'; % TIS2 Theta
block.InputPort(4).DataTypeId = 0; %real
block.InputPort(4).SamplingMode = 'Sample';
block.InputPort(4).Dimensions = TISdet(2);

block.InputPort(5).Complexity = 'real'; % all flags 1.6
block.InputPort(5).DataTypeId = 0; %real
block.InputPort(5).SamplingMode = 'Sample';
block.InputPort(5).Dimensions = TISdet(1);

block.InputPort(6).Complexity = 'real'; % all flags 2.6
block.InputPort(6).DataTypeId = 0; %real
block.InputPort(6).SamplingMode = 'Sample';
block.InputPort(6).Dimensions = TISdet(1);

block.InputPort(7).Complexity = 'real'; % all flags 0.6
block.InputPort(7).DataTypeId = 0; %real
block.InputPort(7).SamplingMode = 'Sample';
block.InputPort(7).Dimensions = TISdet(2);

%% block sample time
block.SampleTimes = [1/dfreq 0];

%% register methods
block.RegBlockMethod('PostPropagationSetup', @DoPostPropSetup);
block.RegBlockMethod('Start', @Start);
block.RegBlockMethod('Outputs', @Outputs);

%% Block runs on TLC in accelerator mode.
block.SetAccelRunOnTLC(true);

end
%endfunction

function DoPostPropSetup( block )
    block.NumDworks = 1;
	block.Dwork(1).Name = 'handles';
	block.Dwork(1).Dimensions = 6;
	block.Dwork(1).DatatypeID = 0;
	block.Dwork(1).Complexity = 'Real';
end
%endfunction

function Start(block)

if block.DialogPrm(5).Data      % Radar Switch ON / OFF
    
    try %#ok<TRYNC>
        close (AEBS_radar_graph)
    end
    
    % Params
    TISMaxRange = block.DialogPrm(3).Data;
    TISMaxTheta = block.DialogPrm(4).Data;
    TISMaxTheta = pi/180 * TISMaxTheta;
    
    % Useful handles
    h_Rdlg = AEBS_radar_graph;
    set(h_Rdlg, 'Name', 'AEBS Radar');
    h_axes = findobj(h_Rdlg, 'Tag', 'radar_axes');
    set(h_axes,'fontsize',7);
    
    % Auxiliary variables for resizing
    scale = 0.75;
    kx = 423/70*scale;    % horizontally, meters per pixel
    ky = 308/51*scale;    % vertically,   meters per pixel
    hleg = 60;            % pixels for legend
    
    maxX = max(TISMaxRange .* sin(TISMaxTheta/2))+ 8;  % Max horizontal distance in meters plus some offset
    maxY = max(TISMaxRange .* cos(TISMaxTheta/2))+12;  % Max vertical distance in meters plus some offset 
       
    % Set additional offset/size for axes and figure, to allow for
    % ticklabels
    dx_ticklabels = 25;
    dy_ticklabels = 15;
    
    % Set window size
    set(h_Rdlg,'Units','Pixels');           % make sure pixels are used as units
    position = get(h_Rdlg, 'Position');     % get old settings
    position([1 2]) = [5 45]; 
    position(3) = 2*(maxX*kx+dx_ticklabels);                % set width (horizontally)
    position(4) =   maxY*ky+dy_ticklabels;           % set width (vertically)
    set(h_Rdlg,'Position',position + [0 0 0 hleg]);        % update
    
    % Set plot size
    plot_position = get(h_axes, 'Position');
    plot_position(3:4) = position(3:4);
    plot_position(1) = plot_position(1) + dx_ticklabels;
    plot_position(2) = plot_position(2) + hleg + dy_ticklabels;
    plot_position(3) = plot_position(3) - 1.5*dx_ticklabels;
    plot_position(4) = plot_position(4) - 1.5*dy_ticklabels;
    set(h_axes,'Position',plot_position);
    
    % Retains next plots in the current axes
    set(h_axes,'NextPlot', 'add');  % hold on    
        
    % Set plot axis
    set(h_axes,'XLim', [ -maxX maxX],'YLim',[-8, max(TISMaxRange)+4]);
    set(h_axes,'XGrid','on','YGrid','on');
    set(h_axes,'XTick',10*floor(-maxX/10) : 10 : 10*ceil(maxX/10));
    set(h_axes,'YTick',-10 : 10 : 10*ceil((maxY+4)/10) )
    
    % Initialize plotting markers and retrieve plot handles
    % d1 = detected, d2 = warning, d3 = pre-braking, d4 = full braking
    VarMarkerSize = 6;
    hpd1 = plot(h_axes,NaN,NaN, 'b*', 'MarkerSize', VarMarkerSize); % plot just ignores NaN leaving holes in the plot
    hpd2 = plot(h_axes,NaN,NaN, 'r*', 'MarkerSize', 10);
    hpd3 = plot(h_axes,NaN,NaN, 'o', 'LineWidth', 3, 'MarkerEdgeColor', [1.0 0.7 0.0], 'MarkerSize', 14);
    hpd4 = plot(h_axes,NaN,NaN, 'or', 'MarkerFaceColor', 'r', 'MarkerSize', 10);
       
    % Initialize text annotations (coordinates)
    TISdet      = block.DialogPrm(2).Data;
    text(zeros(1,sum(TISdet)),zeros(1,sum(TISdet)),'','Parent',h_axes,'Tag','text_marker','FontSize',8);
        
    % Draw TIS1 boundaries
    xr1=[0 -TISMaxRange(1) .* sin(TISMaxTheta(1)/2) ];
    xr2=[0  TISMaxRange(1) .* sin(TISMaxTheta(1)/2) ];
    yr1=[0  TISMaxRange(1) .* cos(TISMaxTheta(1)/2) ];
    plot(h_axes,xr1,yr1,'b-');
    plot(h_axes,xr2,yr1,'b-');
    xcircle1 = TISMaxRange(1) .* sin( -TISMaxTheta(1)/2 : 0.0016 : TISMaxTheta(1)/2 );
    ycircle1 = TISMaxRange(1) .* cos( -TISMaxTheta(1)/2 : 0.0016 : TISMaxTheta(1)/2 );
    plot(h_axes, xcircle1, ycircle1, 'b-');
    
    % Save the graphic handles for future timesteps
    block.Dwork(1).Data = [double(h_Rdlg) double(h_axes) double(hpd1) double(hpd2) double(hpd3) double(hpd4)];
    
    % Draw TIS2 boundaries
    xr1=[0 -TISMaxRange(2) .* sin(TISMaxTheta(2)/2) ];
    xr2=[0  TISMaxRange(2) .* sin(TISMaxTheta(2)/2)];
    yr1=[0  TISMaxRange(2) .* cos(TISMaxTheta(2)/2)];
    plot(h_axes,xr1,yr1,'m-');
    plot(h_axes,xr2,yr1,'m-');
    xcircle1 = TISMaxRange(2) .* sin( -TISMaxTheta(2)/2 : 0.0016 : TISMaxTheta(2)/2 );
    ycircle1 = TISMaxRange(2) .* cos( -TISMaxTheta(2)/2 : 0.0016 : TISMaxTheta(2)/2 );
    plot(h_axes, xcircle1, ycircle1, 'm-');
    
    % Create plots legend of 4 plots
    h_leg = legend([hpd1,hpd2,hpd3,hpd4],'Detected objects','Warning phase','Pre-braking phase','Full auto-braking','Location','best');
    set(h_leg, 'FontSize', 8, 'Units', 'pixels', 'Position',[0 0 position(3)+1 hleg], 'ButtonDownFcn',[])
    
    % Draw a car
    rectangle('Position',[-1,-4,2,4],'EdgeColor','k','LineWidth',2,'Parent',h_axes);
    
    % Draw TIS signs
    angle = pi/2+TISMaxTheta(1)/2;
    wek = [cos(angle) -sin(angle); sin(angle) cos(angle)] * [TISMaxRange(1); 2];
    text(wek(1), wek(2), 'LRR', 'Parent', h_axes, 'Rotation', 180/pi*TISMaxTheta(1)/2-90, 'Color', 'k')
    angle = pi/2+TISMaxTheta(2)/2;
    wek = [cos(angle) -sin(angle); sin(angle) cos(angle)] * [TISMaxRange(2); 2];
    text(wek(1), wek(2), 'SRR', 'Parent', h_axes, 'Rotation', 180/pi*TISMaxTheta(2)/2-90, 'Color', 'k')
    
end
end
% End of Start function

function Outputs(block)
% Retrieve plot handles
hpd1       = block.Dwork(1).Data(3);
hpd2       = block.Dwork(1).Data(4);
hpd3       = block.Dwork(1).Data(5);
hpd4       = block.Dwork(1).Data(6);


% TISdet      = block.DialogPrm(2).Data;
TISMaxRange = block.DialogPrm(3).Data;
% TISMaxTheta = block.DialogPrm(4).Data;  % in degrees
% TISMaxTheta = pi/180 * TISMaxTheta;     % in radians

TIS1range = block.InputPort(1).Data;
TIS1theta = block.InputPort(2).Data;
TIS2range = block.InputPort(3).Data;
TIS2theta = block.InputPort(4).Data;
Flags_16  = block.InputPort(5).Data;
Flags_26  = block.InputPort(6).Data;
Flags_06  = block.InputPort(7).Data;

xs1 = TIS1range .* sin(-TIS1theta);
ys1 = TIS1range .* cos(-TIS1theta);

xs2 = TIS2range .* sin(-TIS2theta);
ys2 = TIS2range .* cos(-TIS2theta);

% Set marker positions of detected objects
    % Case 1 (i_id1): all detected objects
    i_id1_1 = TIS1range<TISMaxRange(1) & TIS1range>0;
    i_id1_2 = TIS2range<TISMaxRange(2) & TIS2range>0;
    set(hpd1,'XData',[xs1(i_id1_1); xs2(i_id1_2)],'YData',[ys1(i_id1_1); ys2(i_id1_2)]);
    
    %%% Plot text annotations, Slow FOR-loop!
%     h_text_marker = findobj(h_axes,'Tag','text_marker');
%     for ii = 1:TISdet(1)
%        set(h_text_marker(ii),'Position',[xs1(ii)+2,ys1(ii)],'String',['(',num2str(xs1(ii),'%5.1f'),' ',num2str(ys1(ii),'%5.1f'),')']);
%     end
%     for ii = 1:TISdet(2)
%         set(h_text_marker(ii+TISdet(1)),'Position',[xs2(ii)+2,ys2(ii)],'String',['(',num2str(xs2(ii),'%5.1f'),' ',num2str(ys2(ii),'%5.1f'),')']);
%     end
    %%%
    
    % Case 2 (i_d2): detected with flag 2.6 (only exists for TIS1)
    i_d2_1 = (Flags_26 > 0) & (i_id1_1);
    set(hpd2,'XData',xs1(i_d2_1),'YData',ys1(i_d2_1));
     
    % Case 3 (id_3): detected with flag 2.6 and 1.6 (only exists for TIS1)
    i_d3_1 = (Flags_26 > 0) & (Flags_16 > 0) & (i_id1_1);    
    set(hpd3,'XData',xs1(i_d3_1),'YData',ys1(i_d3_1));
    
    % Case 4 (id_4): detected with flag 0.6 (only exists for TIS2)
    i_d4_2 = (Flags_06 > 0) & (i_id1_2);
    set(hpd4,'XData',xs2(i_d4_2),'YData',ys2(i_d4_2));
    
end
% endfunction Outputs
