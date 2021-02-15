function msfcn_PPS_radar_graph(block)

setup(block);
end
%endfunction

function setup( block)

%% define number of input and output ports
block.NumInputPorts  = 4;
block.NumOutputPorts = 0;

block.SetPreCompInpPortInfoToDynamic;
block.SetPreCompOutPortInfoToDynamic;

%% Register parameters
block.NumDialogPrms     = 5;
dfreq = block.DialogPrm(1).Data;
TISdet = block.DialogPrm(2).Data;

%% Input ports properties
block.InputPort(1).Complexity = 'real'; % Range
block.InputPort(1).DataTypeId = 0; %real
block.InputPort(1).SamplingMode = 'Sample';
block.InputPort(1).Dimensions = TISdet;

block.InputPort(2).Complexity = 'real'; % Theta
block.InputPort(2).DataTypeId = 0; %real
block.InputPort(2).SamplingMode = 'Sample';
block.InputPort(2).Dimensions = TISdet;

block.InputPort(3).Complexity = 'real'; % All flags
block.InputPort(3).DataTypeId = -1; % logical
block.InputPort(3).SamplingMode = 'Sample';
block.InputPort(3).Dimensions = TISdet;

block.InputPort(4).Complexity = 'real'; % Braking flag
block.InputPort(4).DataTypeId = -1; % logical
block.InputPort(4).SamplingMode = 'Sample';
block.InputPort(4).Dimensions = 1;

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
	block.Dwork(1).Dimensions = 5;
	block.Dwork(1).DatatypeID = 0;
	block.Dwork(1).Complexity = 'Real';
end
% endfunction

function Start(block)

if block.DialogPrm(3).Data
    
    try%#ok<TRYNC>
        close(PPS_radar_graph);
    end
    
    % Params
%     TISdet      = block.DialogPrm(2).Data;
    TISMaxRange = block.DialogPrm(4).Data;
    TISMaxTheta = block.DialogPrm(5).Data;
    
    % Useful handles
    h_Rdlg = PPS_radar_graph;
    set(h_Rdlg, 'Name', 'PPS Radar');
    h_axes = findobj(h_Rdlg, 'Tag', 'radar_axes');
    set(h_axes,'fontsize',7);
    
    % Auxiliary variables for resizing
    scale = 1;
    kx = 423/70*scale;    % horizontally, meters per pixel
    ky = 308/51*scale;    % vertically,   meters per pixel
    hleg = 60;            % pixels for legend
    
    maxX = max(TISMaxRange .* sin(TISMaxTheta/2))+4;      % Max horizontal distance in meters plus some offset
    maxY = max(TISMaxRange .* cos(TISMaxTheta/2))+10;      % Max vertical distance in meters plus some offset 
    
    % Set additional offset/size for axes and figure, to allow for ticklabels
    dx_ticklabels = 25;
    dy_ticklabels = 15;
    
    % Set window size
    set(h_Rdlg,'Units','Pixels');           % make sure pixels are used as units
    position = get(h_Rdlg, 'Position');     % get old settings
    position([1 2]) = [50   520]; 
    position(3) = max(2*(maxX*kx+dx_ticklabels), 330);               % set width (horizontally)
    position(4) = max(maxY*ky+dy_ticklabels, 280);          % set width (vertically)
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
    set(h_axes,'XTick', 10*floor(-maxX/10) : 10 : 10*ceil( maxX/10) );
    set(h_axes,'YTick', -10 : 10 : 10*ceil( (maxY+4)/10) )
    
    % Initialize plotting markers and retrieve plot handles
    r        = plot(h_axes,NaN,NaN,'b-');
    hpd1     = plot(h_axes,NaN,NaN,'*', 'Color','b', 'MarkerSize',6);
    hpd2     = plot(h_axes,NaN,NaN,'og', 'MarkerEdgeColor','g', 'LineWidth',3,'MarkerSize',14);
    hpd3     = plot(h_axes,NaN,NaN,'or','MarkerFaceColor','r','MarkerSize',10);
    
    % Save the graphic handles for future timesteps
    block.Dwork(1).Data = [double(h_Rdlg) double(h_axes) double(hpd1) double(hpd2) double(hpd3)];
    
    % Plot fixed graphics
    TISMaxTheta = TISMaxTheta / 2;
    xr1=[0 -TISMaxRange*sin(TISMaxTheta)];
    yr1=[0 TISMaxRange*cos(TISMaxTheta)];
    xr2=[0 TISMaxRange*sin(TISMaxTheta)];
    plot(h_axes,xr1,yr1,'b-');
    plot(h_axes,xr2,yr1,'b-');
    a=1;
    xcircle = zeros(length(-TISMaxTheta:0.01:TISMaxTheta),1);
    ycircle = zeros(length(-TISMaxTheta:0.01:TISMaxTheta),1);
    for j=-TISMaxTheta:0.01:TISMaxTheta
        xcircle(a)=TISMaxRange*sin(j);
        ycircle(a)=TISMaxRange*cos(j);
        a=a+1;
    end
    plot(h_axes, xcircle,ycircle,'b-');      %  Plot the true and the noisy
    rectangle('Position',[-1,-4,2,4],'EdgeColor','k','LineWidth',3,'Parent',h_axes);
    
    % Create plots legend of 4 plots
    h_leg   = legend(h_axes,[r; hpd1; hpd2; hpd3],{'Radar range','Detected objects','Collidable objects','Major risk'},'Location','SouthWest');
    set(h_leg, 'FontSize', 8, 'Units', 'pixels', 'Position',[0 0 position(3)+1 hleg]);
    
end
end
% End of Start function

function Outputs(block)

hpd1        = block.Dwork(1).Data(3);
hpd2        = block.Dwork(1).Data(4);
hpd3        = block.Dwork(1).Data(5);

TISMaxRange = block.DialogPrm(4).Data;

TISrange    = block.InputPort(1).Data;
TIStheta    = block.InputPort(2).Data;
Flags       = block.InputPort(3).Data;
Flags_06     = block.InputPort(4).Data;

xs = TISrange .* sin(-TIStheta);
ys = TISrange .* cos(-TIStheta);

% Set marker positions of detected objects
    % Case 1 (i_d1): all detected objects
    i_id1 = TISrange<TISMaxRange & TISrange>0;
    set(hpd1,'XData',xs(i_id1),'YData',ys(i_id1));
    
    % Case 2: Collidable
    i_id2 = i_id1 & Flags>0;
    set(hpd2,'XData',xs(i_id2),'YData',ys(i_id2));
    
    % Case 3: Major risk
    i_id3 = i_id2 & Flags_06>0;
    set(hpd3,'XData',xs(i_id3),'YData',ys(i_id3));
   
end
% endfunction Outputs
