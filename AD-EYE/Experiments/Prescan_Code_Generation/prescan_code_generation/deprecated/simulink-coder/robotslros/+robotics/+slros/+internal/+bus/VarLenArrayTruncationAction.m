classdef VarLenArrayTruncationAction 
    %This class is for internal use only. It may be removed in the future.
    
    %  VarLenArrayTruncationAction is an enumerated type specifying the
    %  different possible actions when a variable-length array is truncated
    %  (during conversion from a MATLAB or C++ ROS message to a Simulink
    %  bus signal).
    
    %   Copyright 2014 The MathWorks, Inc.     
    
    enumeration
      EmitWarning
      DoNothing
    end
   
    methods(Static)
        function out = fromChar(s)
            validateattributes(s, {'char'}, {'nonempty'});
            switch lower(s)
                case {'emitwarning'}
                    out = robotics.slros.internal.bus.VarLenArrayTruncationAction.EmitWarning;
                case {'donothing'}
                    out = robotics.slros.internal.bus.VarLenArrayTruncationAction.DoNothing;
                otherwise
                    assert(false, sprintf('Unexpected string: %s', s));
            end
        end
    end
end
