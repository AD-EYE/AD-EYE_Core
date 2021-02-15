%   Filename: pars_3dof_r.m
%
%	description : parameter file for ADVANCE simulink vehicle module (3DOF)
%	author      : L.Verhoeff, S.H.H.M.Buijssen
%
%  ============================================================
%   ADVANCE, TNO, The Netherlands
%   advance@wt.tno.nl
%  ============================================================

g = 9.81;   % gravitational acceleration [m/s2]

%initial conditions
V0 = 20;                 %initial velocity

% inertial values vehicle body:
MLV = 555.8;
MRV = 557.4;
MLA = 408.4;
MRA = 394.4;

%Wheel/Tyre parameters
m_wheel		= 30;           % [kg] wheel mass 
J_wheel_y	= 1;            % [kgm^2] wheel inertia

%body parameters
m=MLV+MRV+MLA+MRA;          % total vehicle mass [kg]
m_body = m-4*m_wheel;       % mass vehicle body excluding the wheels/axles [kg]
J_xx = 1000;                % moments of inertia [kgm^2]
J_yy = 2000;  
J_zz = 3000;  

l	= 2.8800;		        %wheel base
lva	= l*(MLA+MRA)/m;        %distance COG front axle
laa	= l - lva;              %distance COG rear axle

SBF = 1.591;		%width
SBR = 1.580;		%width


%For the complete vehicle
Jzz = J_zz + 2*m_wheel*lva^2 + 2*m_wheel*laa^2;

%Tires for controller and estimator
Cf = (MLV+MRV)*g/2;     %front vertical tyre load
Cr = (MLA+MRA)*g/2;     %rear vertical tyre load

Kva = 200000;			%stiffness front tires,   Data for the real Audi  
Kaa = 200000;			%stijfheid rear tires,    Data for the real Audi 

Kf = Kva/(g*(MLV+MRV)); %static Fz normalised cornering stiffness front axle
Kr = Kaa/(g*(MLA+MRA)); %static Fz normalised cornering stiffness rear axle