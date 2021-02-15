%   Filename: simulinkmodel_2DOF.m
%
%	description : parameter file for ADVANCE simulink vehicle module (3DOF)
%	author      : J.Zuurbier, S.H.H.M.Buijssen
%
%  ============================================================
%   ADVANCE, TNO, The Netherlands
%   advance@wt.tno.nl
%  ============================================================



% Vehicle data
%----------------------------------
shared_pars;


% Wheel & Tyre data
%----------------------------------
% relaxation length (ON: 1, OFF: 0)
relax_on=0; 
sigma_f=0.65; %[m]		relaxation length front wheels
sigma_r=0.65; %[m]		relaxation length rear wheels 

% TyreType = 1 : Lin. Tyre
% TyreType = 2 : Exponent Tyre
% TyreType = 3 : Borstel Tyre
TyreType = 1;

%tyre road max. friction
Mu = 1;

