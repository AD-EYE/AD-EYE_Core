function ScatterPlot3D(simout)
% =========================================================================
% Demo of making .bmp files and a .avi movie of 3D scanning of a motorcycle
% at various yaw angles.
%
% Author:   Erik Vermeer, Floris Leneman 
% Company:  TNO Automotive, Helmond, the Netherlands
% Date:     19 June 2007
%
% This demo plot tool is based on the simulation Experiment_3D_Scan_cs.mdl
% of TNO Automotive.
%
% Input:
% - simout:     Structure with time (corresponding to 'To Workspace' block)
%
% Default TIS settings: #Beams              = [10, 10]
%                       Sweep rate [Hz]     = 10
%                       Beam Type           = Pencil
%                       FoV [deg]           = [10, 10]
%                       Range [m]           = 50
% =========================================================================



% =========================================================================
% Simulation Settings
% =========================================================================
SensorTilt = 2.5;%[degrees]
YawStep = 20;%[degrees]

% =========================================================================
% Plot Settings
% =========================================================================
colorRange = [-0.5 1.5];%[m]

% =========================================================================
% Derived Settings
% =========================================================================
NrTimeSteps = size(simout.time,1);
dirout = sprintf('Results/Results_%04.0f%02.0f%02.0f_%02.0f%02.0f%02.0f',clock);
mkdir(dirout);

h=figure('Position',[40 60 420 320]);
for indexTime = 1:NrTimeSteps

    YawAngle = YawStep*(indexTime-1);
    
    % Define the output of the Sensor
    Range     =  simout.signals.values(end*1/5+1:end*2/5,:,indexTime);
    Theta     = -simout.signals.values(end*2/5+1:end*3/5,:,indexTime)/180*pi; % Difference in definition between cartesian and sensor coordinates
    Phi       =  (simout.signals.values(end*3/5+1:end*4/5,:,indexTime)+SensorTilt)/180*pi;
    
    [r,c] = find(Range>10*eps);
    [X,Y,Z] = sph2cart(Theta(r,c),Phi(r,c),Range(r,c));
    surf(X,Y,Z,'marker','.','linestyle','none','markeredgecolor','flat','facecolor','none');
    set(gca,'CLim',colorRange);
    axis equal
    axis([8 12 -1 1 colorRange])
    colorbar
    
    % Create the textbox to indicate the Yaw Angle
    try
        delete(annotation3);
    catch
    end
    annotation3 = annotation(...
      gcf,'textbox',...
      'Position',[0.05  0.9 0.285 0.05],...
      'Color',[1 0 0],...
      'FitHeightToText','on',...
      'FontWeight','bold',...
      'EdgeColor','r',...
      'String',{['Angle = ',num2str(YawAngle,3),' [deg]']});
    drawnow

    % Create a png output file of figure 1 for every step of yaw angle
    set(gcf, 'InvertHardCopy', 'off');
    Outputfilename = '3DScatterPlot';
    fileout = sprintf('%s/%s_%06.0f.png',dirout,Outputfilename, indexTime-1);
    %disp(['Creating: ' fileout])
    im=getframe(gcf);
    imwrite(im.cdata,fileout);
end
close(h)
