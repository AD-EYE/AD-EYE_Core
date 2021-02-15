function [phi_deg u] = position_based_steer_angle_calc_parallel(S,p_1,p_2,leftright,w,phi_max,SteerRatio,l)

x0 = p_1(1)-0.7;
y0 = p_1(2);

x7 = p_2(1);
y7 = p_2(2);

% Maximum wheel steer angle
PHI_max = phi_max*SteerRatio;
BETA = phi_max / 180*pi;

%% Determine Parking Path
R = l/sin(BETA);
Ri = sqrt(R.^2-l.^2)-w/2;

Rmin_r = Ri+w/2;

xc1 = x7;

yc1 = y7+Rmin_r;
yc2 = y0-Rmin_r;

y4 = (yc1+yc2)/2;
x4 = xc1+sqrt(Rmin_r.^2-(abs(yc1-y4)).^2);

xc2 = 2*x4-xc1;

% Starting position
x1 = xc2;

% Arc dimensions
teta = asin(abs(x1-x4)/Rmin_r);

% Trajectory length (Clothoid length = 0.5)
L01 = abs(x0-x1);
L12 = 0.5;
L23 = teta*Rmin_r-0.45;
L34 = 0.5;
L45 = 0.5;
L56 = teta*Rmin_r-0.45;
L67 = 0.5;

S1 = L01;
S2 = S1+L12;
S3 = S2+L23;
S4 = S3+L34;
S5 = S4+L45;
S6 = S5+L56;
S7 = S6+L67;

% Brake when trajectory is complete
if S >= S7
    u = 1;
else
    u = 0;
end

% Steering angles
if leftright == 1
    if S < S1
        phi = 0;
    elseif S >= S1 && S < S2
        phi = 2*PHI_max*(S-S1);
    elseif S >= S2 && S < S3
        phi = PHI_max;
    elseif S >= S3 && S < S4
        phi = PHI_max-2*PHI_max*(S-S3);
    elseif S >= S4 && S < S5
        phi = -2*PHI_max*(S-S4);
    elseif S >= S5 && S < S6
        phi = -PHI_max;
    elseif S >= S6 && S < S7
        phi = -PHI_max+2*PHI_max*(S-S6);
    else
        phi = 0;
    end
elseif leftright == -1
    if S < S1
        phi = 0;
    elseif S >= S1 && S < S2
        phi = -2*PHI_max*(S-S1);
    elseif S >= S2 && S < S3
        phi = -PHI_max;
    elseif S >= S3 && S < S4
        phi = -PHI_max+2*PHI_max*(S-S3);
    elseif S >= S4 && S < S5
        phi = 2*PHI_max*(S-S4);
    elseif S >= S5 && S < S6
        phi = PHI_max;
    elseif S >= S6 && S < S7
        phi = PHI_max-2*PHI_max*(S-S6);
    else
        phi = 0;
    end
end
phi_deg = phi;
end
