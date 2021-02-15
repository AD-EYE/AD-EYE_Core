function AEBS_EGOplot
% Drawing plot of velocity and acceleration of the ego vehicle at the end of simulation.

%% Data
V = load('plot_data_velocity.mat');
a = load('plot_data_acceleration.mat');
flag26 = load('plot_data_flag26.mat');
flag16 = load('plot_data_flag16.mat');
flag06 = load('plot_data_flag06.mat');
t = load('plot_data_time.mat');
r = load('plot_data_range.mat');

V = V.velocity(2,:);
a = a.acceleration(2,:);
flag26 = flag26.flag26(2,:);
flag16 = flag16.flag16(2,:);
flag06 = flag06.flag06(2,:);
t = t.time(2,:);
r = r.range(2,:);

%% Calculate flags and impact time
i = 2;
T26=0;
while (T26==0) && (i<length(t))
    if ((flag26(i) == 1) && (flag26(i-1) == 0))
        T26 = t(i);
    end
    i = i + 1;
end

i = 2;
T16=0;
while (T16==0) && (i<length(t))
    if ((flag16(i) == 1) && (flag16(i-1) == 0) && (flag26(i) == 1))
        T16 = t(i);
    end
    i = i + 1;
end

i = 2;
T06=0;
while (T06==0) && (i<length(t))
    if ((flag06(i) == 1) && (flag06(i-1) == 0) && (flag16(i) == 1))
        T06 = t(i);
    end
    i = i + 1;
end

if (T26 == 0) && (T16 == 0)
    T06 = 0;
end

%% Impact speed
Timp = 0;
Vimp = 300;

r_temp = r;
indx = find(r==0);
r_temp(indx) = inf;   %#ok<FNDSB>

exitflag = 1;
i = 2;
while (i < length(r_temp)) && exitflag
    if  (r_temp(i) <= r_temp(i-1)) && flag06(i)
        Timp = t(i);
    else
        if Timp ~= 0
            exitflag = 0;
        end
    end
    i = i + 1;
end
i = i - 2;

if i < length(t)-1
    if r(i) > 0.26
        Timp = 0;
    end
else
    if r(i) > 2
        Timp = 0;
    end
end

% Impact velocity
if(Timp ~= 0)
    Vimp = V(i);
end

%Time conversion
t = t - Timp;

if T06 ~= 0
    T06 = T06 - Timp;
end
if T16 ~= 0
    T16 = T16 - Timp;
end
if T26 ~= 0
    T26 = T26 - Timp;
end

%% Cut off needless time before impact
k = 0;
H = length(t);
for i = 1:H
    if t(i)<-5
        k = k+1;
    end
end
V = V(k+1:H);
a = a(k+1:H);
t = t(k+1:H);

%% Compute Vmin i Vmax
Vmin = 500;
Vmax =   0;
for i = 1:length(V)
    if Vmin>V(i)
        Vmin = V(i);
    end
    if Vmax<V(i)
        Vmax = V(i);
    end
end

%% Plot part

% Close old figure if exists
FigureHandle = findobj('Name','AEBS Speed Profile');
if ~isempty(FigureHandle)
    close(FigureHandle)
end

% Draw new one
if ~isempty(t)
    h_fig = figure('Name','AEBS Speed Profile', 'NumberTitle','Off'); %Set width (3rd element) to 700 to make the axis plot visible
    pos = get(h_fig,'Position');
    pos(3) = pos(3)+150;
    set(h_fig,'Position',pos);
    [H, H1, H2] = plotyy(t,V,t,a);
    
    % Set axes properties
    set(H(2),'YTickMode','auto');
    set(H(1),'YTickMode','auto');
    
    set(H, 'XGrid','On');
    set(H(1),'YGrid','On');
    set(H(2),'YGrid','On');
    
    set(H1,'LineWidth',2.5);
    set(H2,'LineWidth',2.5);
    colorBlue  = [0 0 1];
    colorGreen = [0 0.5 0];
    set(H1,'Color',colorBlue);
    set(H2,'Color',colorGreen);
    
    ylabel(H(1),'Velocity [km/h]', 'Color', colorBlue);
    ylabel(H(2),'Acceleration [m/s^2]', 'Color', colorGreen);
    
    H(1).YColor = colorBlue;
    H(2).YColor = colorGreen;
    
    H1Min = Vmin-3;     H1Max = 1.1*Vmax;
    axis([t(1)-0.5 t(length(t))+0.5 H1Min H1Max]);
    set(H,'XLim',[t(1)-0.5 t(length(t))+0.5]);
    
    H2Min = -13.2;      H2Max =  14.1;
    set(H(2),'YLim',[H2Min H2Max]);
    H2a = ( H2Max - H2Min) / (H1Max - H1Min);
    H2b = H2Max - H2a * H1Max;
    H1limits = get(H(1),'YTick');
    H2limits = H2a * H1limits + H2b;
    try
        set(H(2), 'YTick', 0.1*round(H2limits*10));
    catch %#ok<CTCH>
        
    end
    
    %% Lines and text
    
    if T06 ~= 0
        H = line([T06 T06],[Vmin-5.8 1.25*Vmax]);
        set(H,'Color','k');
        set(H,'LineWidth',1);
        set(H,'LineWidth',2);
    end
    if T16 ~= 0
        H = line([T16 T16],[Vmin-5.8 1.25*Vmax]);
        set(H,'Color','k');
        set(H,'LineWidth',1);
        set(H,'LineWidth',2);
    end
    if T26 ~= 0
        H = line([T26 T26],[Vmin-5.8 1.25*Vmax]);
        set(H,'Color','k');
        set(H,'LineWidth',1);
        set(H,'LineWidth',2);
    end
    if Timp ~= 0
        xlabel('Time to impact [s]');
        H = line([0 0],[Vmin-5.8 1.25*Vmax]);
        if abs(Vimp)>3 && exist('Vimp','var');
            set(H,'Color','r');
        else
            set(H,'Color','k');
        end
        set(H,'LineWidth',1);
        set(H,'LineWidth',2);
    else
        xlabel('Time [s]');
    end
    
    
    if T06 ~= 0
        tekst = 'Full deceleration';
        H = text(T06+0.02,1.05*Vmax,tekst);
        set(H,'EdgeColor','k');
        set(H,'FontSize',12);
        set(H,'LineWidth',2);
        set(H,'FontWeight','normal');
    end
    if T16 ~= 0
        tekst = 'Partial braking';
        H = text(T16+0.02,1.05*Vmax-5,tekst);
        set(H,'EdgeColor','k');
        set(H,'FontSize',12);
        set(H,'LineWidth',2);
        set(H,'FontWeight','normal');
    end
    if T26 ~= 0
        tekst = 'Warning ';
        H = text(T26+0.02,1.05*Vmax,tekst);
        set(H,'EdgeColor','k');
        set(H,'FontSize',12);
        set(H,'LineWidth',2);
        set(H,'FontWeight','normal');
    end
    if Timp ~= 0
        tekst = num2str(round(Vimp));
        tekst = ['V_i_m_p = ', tekst,'km/h'];
        H = text(0.02,1.05*Vmax-5,tekst);
        set(H,'EdgeColor','k');
        set(H,'FontSize',12);
        set(H,'LineWidth',2);
        set(H,'FontWeight','normal');
    end
    
end
end