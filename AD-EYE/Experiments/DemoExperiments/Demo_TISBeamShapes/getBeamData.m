%Get the data for:
%  beam index b   (starting from zero)
%  at iteration i (starting from zero)
%  with objects in a g x g grid
%  also return all angles in radians.
function [ t, beamid, range, theta, psi, targetid ] = getBeamData(b, i)
    [gridWidth, beamspec, nIters, nBeams, numObjects]=getSettings();
    load('Results\beamid.mat');
    load('Results\range.mat');
    load('Results\theta.mat');
    load('Results\psi.mat');
    load('Results\targetid.mat');

    t = targetids(1,i);

    % derive the row range for beam b
    rng = find(beamids(:,i)==b+1);

    % get the beam data for row b
    targetid = targetids(rng,i);
    range    = ranges(rng,i);
    theta    = thetas(rng,i);
    psi      = psis(rng,i);
    beamid   = beamids(rng,i);

    % find the non-zero elements in the id vector
    nze = find(targetid);

    % select the non-zero elements in the id vector
    targetid = targetid(nze)-1001;
    range    = range(nze);
    theta    = theta(nze) * pi / 180;
    psi      = psi(nze) * pi / 180;
    beamid   = beamid(nze);
    
end
