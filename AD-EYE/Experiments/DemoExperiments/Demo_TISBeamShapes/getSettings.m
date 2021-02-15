%GETSETTINGS gets the settings for the experiment. When the 
%experiment is changed, this function needs to be changed manually.
function [gridWidth, beamspec, nIters, nBeams, numObjects]=getSettings()

% Specification of beams. Must match beams spec in advanced tab.
% The first column specifies the beam type:
%   use  0 for pencil or pyramid
%   use  1 for cone or elliptical cone
% The second and third column specifies the azimuth and elevation apex in
% degrees
%          type    azimuth apex [deg]    elevation apes [deg]
beamspec = [
            1,            60         ,   2*180/pi*atan(4/20);
            1,  2*180/pi*atan(4/20)  ,             60;
            1,            15         ,             15;
            0,             8         ,             13;
            0,             0         ,              0
           ];

%-------------------------------------
% DONT CHANGE VALUES BELOW THIS POINT
%-------------------------------------
       
load('Results\beamid.mat');

% Number of iterations
nIters = size(beamids,2);

% The number of beams in the experiment
nBeams = size(beamspec,1);

% Maxiumum number of detectable objects
numObjects = (size(beamids,1)-1)/nBeams;

% The width of the grid.
gridWidth =  9;  % width of the grid
