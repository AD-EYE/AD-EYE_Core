function compareinitialfinalvalues(outputs)

adeye_base = "C:\Users\adeye\AD-EYE_Core\AD-EYE\";
cd(adeye_base+"OpenSCENARIO");

%Add to the text file the checking
fid = fopen('scenario_review.txt', 'a');
isOkSpeed = 1;
isOkAngle = 1;
isOkEgoSpeed = 1;

for i=0:length(outputs)-1
fprintf(fid, strcat('Actor', num2str(i), '\n'));
simout=outputs{i+1,1};
    if (i==0)
        for p=2:length(simout.signals.values)
            compareEgoSpeed = simout.signals.values(p) - simout.signals.values(p-1);
            if not(compareEgoSpeed == 0)
                break
            end
        end

        if (compareEgoSpeed == 0)
            isOkEgoSpeed = 0;
            fprintf(fid, 'Same speed for the Ego car between the begin and the end\n');
        end
    else
        if strcmp(simout.blockName, strcat( 'Run_1_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty/Workspace_', num2str(i), '_1'))
           for p=2:length(simout.signals.values)
            compareSpeed = simout.signals.values(p) - simout.signals.values(p-1);
            if not(compareSpeed == 0)
                break
            end
           end

        if (compareSpeed == 0)
            isOkSpeed = 0;
            fprintf(fid, 'Same speed between the begin and the end\n');
        end
        else
            for p=2:length(simout.signals.values)
                compareAngle = simout.signals.values(p) - simout.signals.values(p-1);
                if not(compareAngle == 0)
                    break
                end
            end

        if (compareAngle == 0)
            isOkAngle = 0;
            fprintf(fid, 'Same angle between the begin and the end\n');
        end
        end
    end
end

if (isOkSpeed && isOkAngle && isOkEgoSpeed)
    fprintf(fid, 'Ok\n');
else
    fprintf(fid, 'Failed\n');
end
fclose(fid);
    
end