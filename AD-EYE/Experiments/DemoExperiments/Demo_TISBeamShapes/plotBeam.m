%PLOTBEAM Plot beam.
%  PLOTBEAM(b) plot beam b as an animation over all iterations.
%
%  PLOTBEAM(b,i) plot beam b for iteration i in a new figure.
%
%  PLOTBEAM(b,i,m) same as previous and scale the error by a factor m.
%
%  PLOTBEAM(b,i,m,h) same as previous but plot in a figure specified by the
%  figure handle h.
%
%  The value of b must range from 1 to the number of beams in the experiment.
%
%  The value of i must range from 1 to the number of iterations in the
%  experiment.
%
%See also plotbeams.

function [ output_args ] = plotBeam( b, i, m, figHandle )
    if nargin==0
        help plotBeam
        return
    end
    
    beamIndex = b-1;
    [gridWidth, beamspec, nIters, nBeams, numObjects]=getSettings();
    
    if b<1 || b>nBeams
        error( 'First argument specifies number of beams. As the current experiment has %d beams this must be a value in the interval [1,%d].',nBeams, nBeams);
    end
 
    
    if nargin<4 %the caller did not provide a figure handle
        h = figure();
    else
        h = figure(figHandle);
    end
    set(gcf,'Color','white');
    

    if nargin<3 %the caller did not provide a figure handle
        m=1;
    end
    
    if nargin<2 %animate the beam for all iterations
        lb=1;
        ub=nIters;
    else
        if i<1 || i>nIters
            error( 'Second argument specifies iteration (starting from one). As the current experiment has %d iterations this must be a value in the interval [1,%d].',nIters, nIters);
        end
        lb=i;
        ub=i;
    end

    warning('off','MATLAB:legend:PlotEmpty')
    for i=lb:ub
        clf;
        [t, beamid, range, theta, psi, targetid] = getBeamData(beamIndex,i);
        [y_gt, z_gt] = getGroundTruth(targetid, gridWidth);
        plot(y_gt,z_gt,'r.', 'MarkerSize',5);
        hold on;
        [y, z, x] = computeLocations(range, theta, psi);
		z=z + 6; %the height of the TIS
        % note that y,z,x are w.r.t. the senor that moves over the x-axis
        
        % Plot the estimated locations with magnified error
        y_err = y - y_gt;
        z_err = z - z_gt;        
        plot(y_gt + m*y_err, z_gt + m*z_err, 'b.', 'MarkerSize',5);

        t_string = sprintf('beam_{%d}, t=%3.2f', b, t);
        title(t_string);
        tis_leg = sprintf('simulated, m=%2.1f',m);
        legend('ground truth', tis_leg, 'Location','EastOutside');

        axis( 'equal' );
        axis( 'square' );
        axis([-5 5 1 11]);

        hold off;
        pause(1);
    end
    warning('on','MATLAB:legend:PlotEmpty')
end

