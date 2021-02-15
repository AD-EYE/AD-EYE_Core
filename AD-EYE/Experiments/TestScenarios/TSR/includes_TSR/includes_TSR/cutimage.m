function [NotEmptyRows, NotEmptyCols] = cutimage(imin)
% Returns indexes of not empty rows and columns on the outer area of image.

% Output declaration
NotEmptyRows = true(size(imin,1),1);
NotEmptyCols = true(size(imin,2),1);

if any(imin(:))
    
    % Indexes of non empty rows and cols
    rows = any(imin,1);
    cols = any(imin,2);
    
    % Cumulative sums from all sides
    CumSumLeft  = cumsum(rows);
    CumSumRight = fliplr(cumsum(fliplr(rows)));
    CumSumUp    = cumsum(cols);
    CumSumDown  = flipud(cumsum(flipud(cols)));
    
    % Not empty borders detection
    NotEmptyCols = and(CumSumLeft, CumSumRight).';
    NotEmptyRows = and(CumSumUp,   CumSumDown);
    
end

end
% End of function