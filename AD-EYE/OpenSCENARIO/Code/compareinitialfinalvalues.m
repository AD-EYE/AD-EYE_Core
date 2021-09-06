function compareinitialfinalvalues(simout1, simout2)

adeye_base = "C:\Users\adeye\AD-EYE_Core\AD-EYE\";
cd(adeye_base+"OpenSCENARIO");

%Add to the text file the checking
fid = fopen('scenario_review.txt', 'a');

if not(isempty(simout1)) %Check if simout1 had been added so if longitudinal action exists
    compareSpeed = simout1.signals.values(length(simout1.signals.values)) - simout1.signals.values(1);
    if (compareSpeed == 0)
        fprintf(fid, 'Same speed between the begin and the end\n');
    else
        fprintf(fid, 'Speed have changed between the begin and the end\n');
    end
else
   fprintf(fid,'There are no longitudinal action\n'); 
end

if not(isempty(simout2)) %Check if simout2 had been added so if lateral action exists
    compareAngle = simout2.signals.values(length(simout2.signals.values)) - simout2.signals.values(1);
    if (compareAngle == 0)
        fprintf(fid, 'Same angle between the begin and the end\n');
    else
        fprintf(fid, 'Angle have changed between the begin and the end\n');
    end
else
   fprintf(fid, 'There are no lateral action\n'); 
end

fclose(fid);
    
end