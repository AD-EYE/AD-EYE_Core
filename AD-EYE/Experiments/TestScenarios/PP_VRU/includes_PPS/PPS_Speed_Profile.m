function PPS_Speed_Profile
% Drawing plot of velocity and acceleration of the ego vehicle at the end of simulation.

%% Data
load('VRU_simout.mat');
t    = VRU_simout(1,:);
vel  = VRU_simout(2,:);	% Velocity in km/h
acc  = VRU_simout(3,:);	% Acceleration in m/s2
det  = VRU_simout(4,:);	% Detection flag
wrn  = VRU_simout(5,:);	% Warning flag
brk  = VRU_simout(6,:);	% Braking flag
ped  = VRU_simout(7,:);	% Pedestrian flag

load('VRU_EGO_State_Coll.mat');
coll = VRU_EGO_State_Coll(2,end);              % Collision velocity in km/h
[~,nn] = size(t);                       % Simulation samples

%% First rise detectors
Idet = 0; ii = 1;
while (ii <= nn) && ~Idet
    if det(ii)
        Idet = ii;
    end
    ii = ii + 1;
end

Iwrn = 0; ii = 1;
while (ii <= nn) && ~Iwrn
    if wrn(ii)
        Iwrn = ii;
    end
    ii = ii + 1;
end

Ibrk = 0; ii = 1;
while (ii <= nn) && ~Ibrk
    if brk(ii)
        Ibrk = ii;
    end
    ii = ii + 1;
end

Iped = 0; ii = 1;
while (ii <= nn) && ~Iped
    if ped(ii)
        Iped = ii;
    end
    ii = ii + 1;
end

%% Extremes of velocity
Vmax = 100;

%% Plot
% Close old figure if exists
figureName = 'VRU Speed Profile';
FigureHandle = findobj('Name',figureName);
if ~isempty(FigureHandle)
    close(FigureHandle)
end

h_fig = figure('Name',figureName, 'NumberTitle','Off');
%Increase the width (3rd element) with 150 to make the axis plot visible
pos = get(h_fig,'Position');
pos(3) = pos(3)+150;
set(h_fig,'Position',pos);
    
if coll
    % Collision occured
    % Shift time
    t = t - t(nn);
    indx = 1;
    while t(indx) < -2.5
        indx = indx + 1;
    end
    indx = indx - 1;
    nn = nn - indx;
    t(1:indx) = [];
    vel(1:indx) = [];
    acc(1:indx) = [];
    Idet = Idet - indx;
    Iwrn = Iwrn - indx;
    Iped = Iped - indx;
    Ibrk = Ibrk - indx;
end

% Plot
try
    [H, H1, H2] = plotyy(t,vel,t,acc);
    set(H1,'LineWidth',2.5);
    set(H2,'LineWidth',2.5);
    colorBlue  = [0 0 1];
    colorGreen = [0 0.5 0];
    set(H1,'Color',colorBlue);
    set(H2,'Color',colorGreen);
    ylabel(H(1),'Velocity [km/h]','Color',colorBlue);
    ylabel(H(2),'Acceleration [m/s^2]','Color',colorGreen);
    set(H,{'ycolor'},{colorBlue;colorGreen}) % Set the color of the Y axises
    set(H(1), 'YLim',[0 Vmax]);
    set(H(1), 'YTickMode','auto');
    set(H(2), 'YLim',[-12 6]);
    set(H(2), 'YTick', -12: (6-(-12))/(length(get(H(1),'YTick'))-1) :6);
    set(H(2), 'YTickLabel', round(10*[-12 : ((6-(-12))/(length(get(H(1),'YTick'))-1)) : 6] )/10);
    set(H(1), 'XGrid','On');
    set(H(2), 'XGrid','On');
    set(H(1), 'YGrid','On');
    set(H(2), 'YGrid','On');
    
    if coll
        xlabel('Time [s]');
        set(H(1), 'XLim',[-2.5 0.75]);
        set(H(2), 'XLim',[-2.5 0.75]);
    else
        xlabel('Time [s]');
    end
    
    
    
    %% Lines
    if coll
        Hl0 = line([t(nn) t(nn)], [0 Vmax]);
        set(Hl0,'Color','r');
        set(Hl0,'LineWidth',2);
    end
    if Ibrk
        Hl1 = line([t(Ibrk) t(Ibrk)], [0 Vmax]);
        set(Hl1,'Color','k');
        set(Hl1,'LineWidth',2);
    end
    if Iwrn
        Hl2 = line([t(Iwrn) t(Iwrn)], [0 Vmax]);
        set(Hl2,'Color','k');
        set(Hl2,'LineWidth',2);
    end
    if Iped
        Hl3 = line([t(Iped) t(Iped)], [0 Vmax]);
        set(Hl3,'Color','k');
        set(Hl3,'LineWidth',2);
    end
    if Idet
        Hl4 = line([t(Idet) t(Idet)], [0 Vmax]);
        set(Hl4,'Color','k');
        set(Hl4,'LineWidth',2);
    end
    
    
    
    %% Texts
    if Idet
        tekst = 'Detection';
        Hl = text(t(Idet)+0.01, 93, tekst);
        set(Hl,'EdgeColor','k');
        set(Hl,'FontSize',12);
        set(Hl,'LineWidth',1);
        set(Hl,'FontWeight','normal');
    end
    if Iped
        tekst = 'Pedestrian detection';
        H3 = text(t(Iped)+0.01, 73, tekst);
        set(H3,'EdgeColor','k');
        set(H3,'FontSize',12);
        set(H3,'LineWidth',1);
    end
    if Iwrn
        tekst = 'Warning';
        Hl = text(t(Iwrn)+0.01, 83, tekst);
        set(Hl,'EdgeColor','k');
        set(Hl,'FontSize',12);
        set(Hl,'LineWidth',1);
    end
    
    
    if Ibrk
        tekst = 'Brake';
        Hl = text(t(Ibrk)+0.01, 63, tekst);
        set(Hl,'EdgeColor','k');
        set(Hl,'FontSize',12);
        set(Hl,'LineWidth',1);
        set(Hl,'FontWeight','normal');
    end
    if coll
        tekst = {'Collision', sprintf('%.1f km/h',coll)};
        H2 = text(t(nn)+0.01, 53, tekst);
        set(H2,'EdgeColor','k');
        set(H2,'FontSize',12);
        set(H2,'LineWidth',1);
        set(H2,'FontWeight','normal');
    end
    
catch
    close(h_fig);
end

end