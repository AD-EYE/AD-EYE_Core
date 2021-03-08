classdef NetworkAddrProfile
    %This class is for internal use only. It may be removed in the future.
    
    %  NetworkAddrProfile is a data class that specifies a single network
    %  address profile (information about ROS Master and Node host).
    %  
    %  Static methods:
    %   getDefaultMasterHost
    %   getDefaultNodeHost
    %
    %  See also: sim.ROSMaster, sim.NetworkAddrStore
    
    %   Copyright 2014 The MathWorks, Inc.         
        
    properties
        ProfileName = ''
        
        MasterUseDefault = true
        MasterHost = 'localhost'
        MasterPort = 11311
        
        NodeUseDefault = true
        NodeHost = ''
    end
    
    methods
        function obj = set.ProfileName(obj, name)
            validateattributes(name, {'char'}, {});
            obj.ProfileName = name;
        end

        function obj = set.MasterUseDefault(obj, value)
            validateattributes(value, {'logical'}, {'scalar'});
            obj.MasterUseDefault = value;
        end
        
        function obj = set.MasterHost(obj, name)
            validateattributes(name, {'char'}, {});
            obj.MasterHost = name;
        end
        
        function obj = set.MasterPort(obj, port)
            validateattributes(port, {'numeric'}, {'scalar'});
            obj.MasterPort = port;
        end        
        
        function obj = set.NodeUseDefault(obj, value)
            validateattributes(value, {'logical'}, {'scalar'});
            obj.NodeUseDefault = value;
        end
        
        function obj = set.NodeHost(obj, name)
            validateattributes(name, {'char'}, {});
            obj.NodeHost = name;
        end
        
    end
    
    methods
        % These are used for LOAD and SAVE. We rely on these intead of just
        % default LOAD/SAVE behavior as the information gets saved to
        % MATLAB Preferences. If RST is not on the path for any reason,
        % this leads to warnings at MATLAB load time & whenever any MATLAB
        % preference is accessed 
        function s = getPropsStruct(obj)
            props = properties(obj);
            s = struct();
            for i=1:numel(props)                
                s.(props{i}) = obj.(props{i});
            end
        end
    end
    
    methods(Static)
        function obj = setPropsStruct(s)
            obj = robotics.slros.internal.sim.NetworkAddrProfile;
            props = properties(obj);
            for i=1:numel(props)
                if isfield(s, props{i})
                    obj.(props{i}) = s.(props{i});
                end
            end
        end        
    end
    
    methods(Static)
        function out = getDefaultMasterHost()
            out = 'localhost';
        end
        
        function out = getDefaultNodeHost()
            addrs = robotics.ros.internal.Net.getAllIPv4Addresses;
            if numel(addrs) > 0
                out = addrs(1).ipAddress;
            else
                out = '';
            end
        end
    end
        
end
