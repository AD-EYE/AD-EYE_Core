function [y_gt z_gt] = getGroundTruth(targetid, gridWidth)
    z_gt = rem(targetid, gridWidth);
    y_gt = floor( targetid ./ gridWidth );
    
    % put the center of the grid back at (y,z) = (0,6)
    y_gt = y_gt - (gridWidth-1)/2;
    z_gt = z_gt - (gridWidth-1)/2 + 6;
end

