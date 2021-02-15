function LaneChangeDetection_msfun(block)
setup(block);
%endfunction

function setup( block )


%% define number of input and output ports
block.NumInputPorts  = 6;
block.NumOutputPorts = 2;


%% port properties
block.InputPort(1).Complexity = 'real'; % Car width
block.InputPort(1).DataTypeId = 0; %real
block.InputPort(1).SamplingMode = 'Sample';


block.InputPort(2).Complexity = 'real'; % Threshold Distance
block.InputPort(2).DataTypeId = 0; %real
block.InputPort(2).SamplingMode = 'Sample';


block.InputPort(3).Complexity = 'real'; % Heading 
block.InputPort(3).DataTypeId = 0; %real
block.InputPort(3).SamplingMode = 'Sample';


block.InputPort(4).Complexity = 'real'; % Threshold Angle
block.InputPort(4).DataTypeId = 0; %real
block.InputPort(4).SamplingMode = 'Sample';


block.InputPort(5).Complexity = 'real'; % Distance left
block.InputPort(5).DataTypeId = 0; %real
block.InputPort(5).SamplingMode = 'Sample';


block.InputPort(6).Complexity = 'real'; % Distance right
block.InputPort(6).DataTypeId = 0; %real
block.InputPort(6).SamplingMode = 'Sample';


block.OutputPort(1).Complexity = 'Real';
block.OutputPort(1).DataTypeId = 8;
block.OutputPort(1).SamplingMode = 'Sample';
block.OutputPort(1).Dimensions = 1;

block.OutputPort(2).Complexity = 'Real';
block.OutputPort(2).DataTypeId = 8;
block.OutputPort(2).SamplingMode = 'Sample';
block.OutputPort(2).Dimensions = 1; 

  
%% Run accelerator on TLC
block.SetAccelRunOnTLC(false);

%% Register methods
block.RegBlockMethod('Outputs', @Output); 

%endfunction

function Output(block)
%% init
    car_width = block.InputPort(1).Data;
    threshold_distance = block.InputPort(2).Data;
    heading = block.InputPort(3).Data;
    threshold_angle = block.InputPort(4).Data;
    dist_left = block.InputPort(5).Data;
    dist_right = block.InputPort(6).Data;
    
    
%% logic    
    departing_left = false;
    departing_right = false;
    if dist_left==0 && dist_right==0;
        departing_left = false;
        departing_right = false;
        elseif (((dist_left - threshold_distance) < (car_width / 2))   && (heading < 0)) || (((dist_left - threshold_distance) < (car_width / 2))   && (heading>=0) && (heading<threshold_angle)); 
        departing_left = true;
        elseif (((dist_right - threshold_distance) < (car_width / 2))   && (heading > 0)) || (((dist_right - threshold_distance) < (car_width / 2)) && (heading>-threshold_angle) && (heading<=0));
        departing_right = true;
    end
   block.OutputPort(1).Data = departing_left; 
   block.OutputPort(2).Data = departing_right;
%endfunction