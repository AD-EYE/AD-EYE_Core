function compareinitialfinalvalues()

adeye_base = "C:\Users\adeye\AD-EYE_Core\AD-EYE\";
cd(adeye_base+"OpenSCENARIO");

fid = fopen('scenario_review.txt', 'a');

if exist('simout1')
    compareSpeed = simout1.signals.values(length(simout1.signals.values)) - simout1.signals.values(1);
    if (compareSpeed == 0)
        fprintf(fid, 'Same speed between the begin and the end\n');
    else
        fprintf(fid, 'Speed have changed between the begin and the end\n');
    end
else
   fprintf(fid,'There are no longitudinal action\n'); 
end

if exist('simout2')
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