function rewriteTA()

adeye_base = "C:\Users\adeye\AD-EYE_Core\AD-EYE\";
cd(adeye_base + "TA");

% Read the code
    file = fopen('TA.m');
    line = fgetl(file);
    k = 1;
    while k<152
       out2{k,1}=line;
       line=fgetl(file);
       k=k+1;
    end
    
    %Insert lines to go to the compareinitialfinalvalues function
    out2{1,1} = 'function TA2(TAOrderFile,firstcolumn,lastcolumn,clear_files)';
    out2{152,1} = '    adeye_base = "C:\Users\adeye\AD-EYE_Core\AD-EYE\";';
    out2{153,1} = '    addpath(adeye_base+"OpenSCENARIO\Code");';
    out2{154,1} = strcat('    if exist(',"'simout1'" , ')');
    out2{155,1} = strcat('       if exist(', "'simout2'", ')');
    out2{156,1} = '          compareinitialfinalvalues(simout1, simout2);';
    out2{157,1} = '       else';
    out2{158,1} = '          compareinitialfinalvalues(simout1, struct([]));';
    out2{159,1} = '       end';
    out2{160,1} = strcat('    elseif exist(', "'simout2'", ')');
    out2{161,1} = '       compareinitialfinalvalues(struct([]), simout2);';
    out2{162,1} = '    else';
    out2{163,1} = '       compareinitialfinalvalues(struct([]), struct([]));';
    out2{164,1} = '    end';
    
    % Read the end of the code
    j = 165;
    while k<399
       out2{j,1}=line;
       line=fgetl(file);
       k=k+1;
       j=j+1;
    end
    fclose(file);
    
    %Write the new code in the old one
    file= fopen('TA2.m','w');
    for k=1:numel(out2)
       fprintf(file,'%s\n',out2{k});
    end
    fclose(file);
end