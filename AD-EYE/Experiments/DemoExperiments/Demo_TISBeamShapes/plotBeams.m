%Plot all the beam shapes for at most the first nine iterations.
%
%This script analyzes the output of the TIS_BeamShapes experiment.
%This experiment is set-up in a particular way, such that the id
%of the objects is easily converted to their location in the 3D world.
%
%See also plotbeam.
function plotBeams()
[gridWidth, beamspec, nIters, nBeams, numObjects]=getSettings();

figure(1);
set(gcf,'Color','white');
nIters = min(nIters,9);
for i = 1:nIters
    for b = 0:nBeams-1
        [t, beamid, range, theta, psi, targetid] = getBeamData(b,i);
        [y_gt, z_gt] = getGroundTruth(targetid, gridWidth);
        
        h = subplot(nBeams, nIters, b*nIters + i);
        p = get(h, 'pos');
        p(3) = p(3) + 0.02;
        p(4) = p(4) + 0.02;
        set(h, 'pos', p);
        
        plot(y_gt,z_gt,'r.');
        
        % Mark detected objects whose center lies outside the beam.
        if true %experimental code for boundary check
            type  = beamspec(b+1,1);
            theta = beamspec(b+1,2);
            psi   = beamspec(b+1,3);
            hold on;
            x = 20 - 30*t;
            %compute the radii of the ellipse
            
            y_radius = x * tan(0.5 * theta*pi/180);
            z_radius = x * tan(0.5 * psi*pi/180);
            y_out = [];
            z_out = [];
            if type==1
                for iter = 1:numel(y_gt)
                    y = y_gt(iter);
                    z = z_gt(iter);
                    %y^2 / y_radius^2  + (z-6)^2 / z_radius^2
                    if y^2 / y_radius^2  + (z-6)^2 / z_radius^2 > 1
                        % point (y,z) is outside the ellipse
                        y_out = [y_out ; y];
                        z_out = [z_out ; z];
                    end
                end
            else
                for iter = 1:numel(y_gt)
                    y = y_gt(iter);
                    z = z_gt(iter);
                    if abs(y) > abs(y_radius) ||  abs((z-6)) > abs(z_radius)
                        % point (y,z) is outside the ellipse
                        y_out = [y_out ; y];
                        z_out = [z_out ; z];
                    end
                end
                
            end
            plot(y_out,z_out,'b.');

            %y_out
            %z_out
            hold off;
        end
        
        if b < nBeams-1
            set(gca,'xtick',[]) ;
        end
        if i > 1
            set(gca,'ytick',[]) ;
        end
        %axis off;
        if b == 0 % i is the beamid index, so, this is per timestep
            t_string = sprintf('t=%3.2f', t);
            title(t_string);
        end

        if i == 1
            y_string = sprintf('beam_{%d}', b+1);
            ylabel(y_string);
        end

        axis( 'equal' );
        axis( 'square' );
        axis([-5 5 1 11]);
    end
    
end

