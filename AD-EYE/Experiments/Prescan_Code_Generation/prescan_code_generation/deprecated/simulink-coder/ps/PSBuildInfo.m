classdef PSBuildInfo < builders.common.PrescanBuildInfo
    %PSBuildInfo returns info for building ps
    
% ------------------------ Overridden implementation -----------------------------

    methods(Access = 'public')

        % The following methods can, in the future, be promoted to the base class,
        % when the other targets also need specialize the main and its dependencies.

        function [prescanMain] = getPreScanMain(buildinfo) %#ok
            prescanMain = 'ps_main.c';
        end

        function [additionalSrcs] = getPreScanSrcs(buildinfo) %#ok
            additionalSrcs = 'model_main.c';
        end
        
    end
    
end

