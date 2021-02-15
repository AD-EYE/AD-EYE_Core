function PPS_TTC_Profile
% Drawing plot of velocity and acceleration of the ego vehicle at the end of simulation.

%% Data
load('VRU_simout.mat');
t    = VRU_simout(1,:);
det  = VRU_simout(4,:);	% Detection flag
wrn  = VRU_simout(5,:);	% Warning flag
brk  = VRU_simout(6,:);	% Braking flag
ped  = VRU_simout(7,:);	% Pedestrian flag
ttc  = VRU_simout(8,:);	% TTC

load('VRU_EGO_State_Coll.mat');
coll = VRU_EGO_State_Coll(2,end);       % Collision velocity in km/h
[~,nn] = size(t);                       % Simulation samples

%% Redefine ttc
if ttc == 4
    ttc = 0;
end

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

%% Extreme
TTCmax = 2.5;

%% Shift time
if coll
    %t = t - t(nn);
    indx = 1;
    while t(indx) < t(nn) - 2.5
        indx = indx + 1;
    end
    indx = indx - 1;
    nn = nn - indx;
    t(1:indx) = [];
    ttc(1:indx) = [];
    Idet = Idet - indx;
    Iwrn = Iwrn - indx;
    Iped = Iped - indx;
    Ibrk = Ibrk - indx;
end

%% Plot
try
    % Close old figure if exists
    figureName = 'VRU TTC Profile';
    FigureHandle = findobj('Name',figureName);
    if ~isempty(FigureHandle)
        close(FigureHandle)
    end
    h_fig = figure('Name','VRU TTC Profile', 'NumberTitle','Off');
    hold on
    if Idet
        H(1) = plot(t(Idet:nn),ttc(Idet:nn));
        H(2) = plot(t(1:Idet), zeros(length(1:Idet),1));
        H(3) = plot([t(Idet) t(Idet)], [0 ttc(Idet)]);
    end
    hold off
    
    set(H,'LineWidth',2.5);
    set(H,'Color',[0 0 1]);
    set(gca, 'YLim',[0 2.5]);
    set(gca, 'YTickMode','auto');
    set(gca, 'XLim',[t(1)-0.1 t(nn)+0.6]);
    set(gca, 'XTickMode','auto');
    set(gca, 'XGrid','On');
    set(gca, 'YGrid','On');
    xlabel(gca,'Time [s]');
    ylabel(gca,'Estimated time to collision (TTC) [s]');
    
    %% Lines
    if coll
        H = line([t(nn) t(nn)], [0 TTCmax]);
        set(H,'Color','r');
        set(H,'LineWidth',2);
    end
    if Ibrk
        H = line([t(Ibrk) t(Ibrk)], [0 TTCmax]);
        set(H,'Color','k');
        set(H,'LineWidth',2);
    end
    if Iwrn
        H = line([t(Iwrn) t(Iwrn)], [0 TTCmax]);
        set(H,'Color','k');
        set(H,'LineWidth',2);
    end
    if Iped
        H = line([t(Iped) t(Iped)], [0 TTCmax]);
        set(H,'Color','k');
        set(H,'LineWidth',2);
    end
    if Idet
        H = line([t(Idet) t(Idet)], [0 TTCmax]);
        set(H,'Color','k');
        set(H,'LineWidth',2);
    end
    
    %% Texts
    if Idet
        tekst = 'Detection';
        H = text(t(Idet)+0.01, 2.3, tekst);
        set(H,'EdgeColor','k');
        set(H,'FontSize',12);
        set(H,'LineWidth',1);
        set(H,'FontWeight','normal');
    end
    if Iped
        tekst = 'Pedestrian detection';
        H = text(t(Iped)+0.01, 2, tekst);
        set(H,'EdgeColor','k');
        set(H,'FontSize',12);
        set(H,'LineWidth',1);
    end
    if Iwrn
        tekst = 'Warning';
        H = text(t(Iwrn)+0.01, 1.8, tekst);
        set(H,'EdgeColor','k');
        set(H,'FontSize',12);
        set(H,'LineWidth',1);
    end
    
    
    if Ibrk
        tekst = 'Brake';
        H = text(t(Ibrk)+0.01, 1.1, tekst);
        set(H,'EdgeColor','k');
        set(H,'FontSize',12);
        set(H,'LineWidth',1);
        set(H,'FontWeight','normal');
    end
    if coll
        tekst = {'Collision', sprintf('%.1f km/h',coll)};
        H = text(t(nn)+0.01, 0.5, tekst);
        set(H,'EdgeColor','k');
        set(H,'FontSize',12);
        set(H,'LineWidth',1);
        set(H,'FontWeight','normal');
    end
    
catch
    close(h_fig);
end

%% Clear variables
evalin('base',['clear ','VRU_EGO_State_Coll VRU_simout'])

end