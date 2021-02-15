%Compute cartesian coordinates of the center of a center of a sphere with
%radius 0.05 that is detected (on its surface) at
%  distance  range
%  azimuth   theta
%  elevation ps
function [ y, z, x ] = computeLocations(range, theta, psi)

    % Note, the range is the distance to the surface of the sphere.
    % As we compare the centers of the spheres, furst add the radius
    % of the sphere to the range. Also not that small errors may occur
    % for spheres that intersect the beam but whos centers our located
    % outside the beam.
    range = range + 0.05;
    
    % we have that sin(psi) = z/range =>
    z =  range .* sin(psi);
    y = -range .* cos(psi) .* sin(theta);
    x =  range .* cos(psi) .* cos(theta);
end
