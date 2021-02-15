function PlotLaneDeparture_msfun(block)
setup(block);
%endfunction



function setup( block )


%% define number of input and output ports
block.NumInputPorts  = 5;
block.NumOutputPorts = 0;


%% port properties
block.InputPort(1).Complexity = 'real'; % departing left
block.InputPort(1).DataTypeId = 8; %boolean
block.InputPort(1).SamplingMode = 'Sample';
block.InputPort(1).Dimensions = 1;

block.InputPort(2).Complexity = 'real'; % departing right
block.InputPort(2).DataTypeId = 8; %boolean
block.InputPort(2).SamplingMode = 'Sample';
block.InputPort(2).Dimensions = 1;

block.InputPort(3).Complexity = 'real'; % driver view Red 
block.InputPort(3).DataTypeId = -1; %uint8
block.InputPort(3).SamplingMode = 'Sample';

block.InputPort(4).Complexity = 'real'; % driver view Green
block.InputPort(4).DataTypeId = -1; %uint8
block.InputPort(4).SamplingMode = 'Sample';

block.InputPort(5).Complexity = 'real'; % driver view Blue
block.InputPort(5).DataTypeId = -1; %uint8
block.InputPort(5).SamplingMode = 'Sample';

%% register methods
block.RegBlockMethod('Start', @Start);
block.RegBlockMethod('Outputs', @Outputs);

%endfunction Setup

function Start(block)
    try
        close (PlotLaneDeparture)
    end
    h_dlg = PlotLaneDeparture;
    h_lane_marker_image = findobj(h_dlg, 'Tag', 'lane_marker_image');
    h_departing_left = findobj(h_dlg, 'Tag', 'departing_left');
    h_departing_right = findobj(h_dlg, 'Tag', 'departing_right');
    handles = [h_dlg h_lane_marker_image h_departing_left h_departing_right];
    set_param(block.BlockHandle,'UserData',handles,'UserDataPersistent','on');
%endfunction Start

function Outputs(block)
    handles     = get_param(block.BlockHandle,'UserData');
    h_lane_marker_image = handles(2);
    h_departing_left = handles(3);
    h_departing_right = handles(4);
    
    color_red = [ 1.0 0 0 ];
    color_gray = [ 0.8 0.8 0.8 ];
    
    %departing left
    if block.InputPort(1).Data
        set(h_departing_left, 'ForegroundColor', color_red)
    else
        set(h_departing_left, 'ForegroundColor', color_gray)
    end
   
    %departing left
    if block.InputPort(2).Data
        set(h_departing_right, 'ForegroundColor', color_red)
    else
        set(h_departing_right, 'ForegroundColor', color_gray)
    end
    
    
    
    R = block.InputPort(3).Data;
    G = block.InputPort(4).Data;
    B = block.InputPort(5).Data;
    IMG = zeros([size(R) 3]);
    IMG(:,:,1)=double(R)/255;
    IMG(:,:,2)=double(G)/255;
    IMG(:,:,3)=double(B)/255;
    
    image(IMG,'Parent',h_lane_marker_image);

%endfunction Outputs