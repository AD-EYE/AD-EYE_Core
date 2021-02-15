function msfcn_triggered_trajectory(block)
% Level-2 MATLAB file S-Function for event triggered trajectories
% Example created by Jeroen van der Waal
    setup(block);
%endfunction

function [s] = setup_data(block, file)
    trajectory_data = load(strcat('Trajectories\', file));
    sizem = size(trajectory_data.trajectory);
    %%strip time row from table and only use the next 18 rows
    %%because only the rows 2:19 are used for a trajectory.
    row_count = 18;
    column_count = sizem(2);
    data = trajectory_data.trajectory(2:19,:)';
    time = trajectory_data.trajectory(1,:);
    s = struct('column_count', column_count, 'row_count', row_count, ...
        'data', data, 'time', time, 'final_time', time(column_count));
    set_param(block.BlockHandle, 'UserData', s);
%endfunction

function setup(block)
    block.NumDialogPrms  = 2;

    %% Register number of input and output ports
    block.NumInputPorts  = 1;
    block.NumOutputPorts = 1;

    %% Setup functional port properties to dynamically
    %% inherited.
    block.SetPreCompInpPortInfoToDynamic;
    block.SetPreCompOutPortInfoToDynamic;

    block.InputPort(1).Dimensions        = 1;
    block.InputPort(1).DirectFeedthrough = true;

    %%get trajectory data
    file = block.DialogPrm(1).Data;
    s = setup_data(block, file);    
    block.OutputPort(1).Dimensions = s.row_count;

    %% Set block sample time to inherited
    block.SampleTimes = [block.DialogPrm(2).Data 0];

    %% Set the block simStateCompliance to default
    %% (i.e., same as a built-in block)
    block.SimStateCompliance = 'DefaultSimState';

    %% Register methods
    block.RegBlockMethod('PostPropagationSetup',    @DoPostPropSetup);
    block.RegBlockMethod('InitializeConditions',    @InitConditions);
    block.RegBlockMethod('Update',                  @Update);
    block.RegBlockMethod('Outputs',                 @Output);
%endfunction

function DoPostPropSetup(block)
    block.NumDworks = 2;
    
    block.Dwork(1).Name = 'local_time';
    block.Dwork(1).Dimensions = 1;
    block.Dwork(1).DatatypeID = 0;
    block.Dwork(1).Complexity = 'Real';
    
    block.Dwork(2).Name = 'outv';
    block.Dwork(2).Dimensions = 18;
    block.Dwork(2).DatatypeID = 0;
    block.Dwork(2).Complexity = 'Real';
%endfunction

function CalcOutput(block, local_time, gain)
    s = get_param(block.BlockHandle, 'UserData');
    v = interp1(s.time, s.data, local_time);
    
    if (local_time == s.final_time)
        gain = 0;
    end
    
    v = [v(1:6), v(7:18)*gain];
    block.Dwork(2).Data = v;
%endfunction

function InitConditions(block)
    %% initial local time
    block.Dwork(1).Data = 0;

    %%setup initial value     
    CalcOutput(block, 0, 0);      
%endfunction

function Update(block)
    s = get_param(block.BlockHandle, 'UserData');
    inp_gain = max(block.InputPort(1).Data, 0);  
    if ( inp_gain > 0 && ~(block.Dwork(1).Data == s.final_time) )
        %% advance local time
        block.Dwork(1).Data = block.Dwork(1).Data + ...
            inp_gain*block.SampleTimes(1);
        if (block.Dwork(1).Data >= s.final_time)
        	block.Dwork(1).Data = s.final_time;   
        end
    end
    CalcOutput(block, block.Dwork(1).Data, inp_gain);
%endfunction

function Output(block)
    block.OutputPort(1).Data = block.Dwork(2).Data;
%endfunction
