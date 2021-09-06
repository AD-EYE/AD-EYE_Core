function rewritetrajectorydynamics()

adeye_base = "C:\Users\adeye\AD-EYE_Core\AD-EYE\";
cd(adeye_base + "OpenSCENARIO\Code");

% Read the code
    file = fopen('trajectory_dynamics_2.m');
    line = fgetl(file);
    k = 1;
    while k<336
       out{k,1}=line;
       line=fgetl(file);
       k=k+1;
    end
    
    %Insert lines to go to the compareinitialfinalvalues function
    out{1,1} = 'function  trajectorydynamics3(name_simulink,models,Struct_OpenSCENARIO,trajectory_variable,Lateral_events,Longitudinal_events,name_ego)';

    out{337,1} = '                                                        if ( p ==p_L(1,q))';
    out{338,1} = '                                                           add_block("simulink/Sinks/To Workspace", strcat(locationDynamicsEmpty, "Workspace_", num2str(z)));';
    out{339,1} = '                                                           add_line(locationDynamicsEmpty, strcat(trajectory_type(1,z),"_Dynamics/1"), strcat("Workspace_", num2str(z),"/1"));';
    out{340,1} = strcat('                                                        set_param(strcat(locationDynamicsEmpty, "Workspace_", num2str(z)), ', "'Saveformat'", ', ', "'Structure With Time'", ');');
    out{341,1} = strcat('                                                        set_param(strcat(locationDynamicsEmpty, "Workspace_", num2str(z)), ', "'Variablename'", ', ', "'simout1'", ');');
    out{342,1} = '                                                        end';
    
    % Read the end of the code
    j = 343;
    while k<582
       out{j,1}=line;
       line=fgetl(file);
       k=k+1;
       j=j+1;
    end
    fclose(file);
    
    %Write the new code in the old one
    file= fopen('trajectorydynamics3.m','w');
    for k=1:numel(out)
       fprintf(file,'%s\n',out{k});
    end
    fclose(file);
end