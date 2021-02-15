function [s] = msfcn_load_trajectory(file)
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
%endfunction
