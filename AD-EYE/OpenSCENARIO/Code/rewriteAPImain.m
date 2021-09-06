function rewriteAPImain()

adeye_base = "C:\Users\adeye\AD-EYE_Core\AD-EYE\";
cd(adeye_base + "OpenSCENARIO\Code");

% Read the code
    file = fopen('API_main.m');
    line = fgetl(file);
    k = 1;
    while k<75
       out1{k,1}=line;
       line=fgetl(file);
       k=k+1;
    end
    
    %Insert lines to go to the compareinitialfinalvalues function
    out1{1,1} = 'function  API_main2(name_ego,name_experiment,name_experiment_template)';
    out1{75,1} = 'trajectorydynamics3(name_simulink,models,Struct_OpenSCENARIO,trajectory_variable,Lateral_events,Longitudinal_events,name_ego)';
    
    % Read the end of the code
    j = 76;
    while k<98
       out1{j,1}=line;
       line=fgetl(file);
       k=k+1;
       j=j+1;
    end
    fclose(file);
    
    %Write the new code in the old one
    file= fopen('API_main2.m','w');
    for k=1:numel(out1)
       fprintf(file,'%s\n',out1{k});
    end
    fclose(file);
end