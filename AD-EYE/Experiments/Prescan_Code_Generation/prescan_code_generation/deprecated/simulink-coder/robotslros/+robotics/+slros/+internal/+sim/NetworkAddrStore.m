classdef NetworkAddrStore < handle
    %This class is for internal use only. It may be removed in the future.
    
    %  NetworkAddrStore is an interface for managing ROS network address
    %  profiles (currently, only a single "Standard" profile is supported).
    %  This information is stored in MATLAB Preferences, and  applies to
    %  all Simulink models.
    %
    %  Methods:
    %    updateStore  - Update MATLAB preferences with modified information
    %
    %    getProfile   - Get Standard profile (if it exists) else return default
    %    hasProfile   - Return true if a Standard profile exists
    %    setProfile   - Set the Standard profile
    %    clearProfile - Remove profile from MATLAB preferences    
    %
    %  See also: sim.ROSMaster, sim.NetworkAddrProfile
    
    %   Copyright 2014-2016 The MathWorks, Inc.

    properties(Constant)
        PreferenceGroup = robotics.slros.internal.Constants.PreferenceGroup
        PreferenceName = 'ROS_NetworkAddress_Profiles'
        ProfileName = 'Standard'
    end
    
    
    properties(Access=private)
        ProfileMap
        DataIsModified = false
    end
    
    
    methods
        
        % In 15a, The user can have a single profile, or not at all.
        function obj = NetworkAddrStore()            
            obj.ProfileMap = obj.loadPrefs();
            assert( isa(obj.ProfileMap, 'containers.Map') );            
            obj.DataIsModified = false;
        end

        
        function profile = getProfile(obj)
            if obj.ProfileMap.isKey(obj.ProfileName)
                profile = obj.ProfileMap(obj.ProfileName);
                assert(isa(profile, 'robotics.slros.internal.sim.NetworkAddrProfile'));
            else
                profile = robotics.slros.internal.sim.NetworkAddrProfile;
                profile.ProfileName = obj.ProfileName;
            end
        end
        
        
        function out= hasProfile(obj)
            out = obj.ProfileMap.isKey(obj.ProfileName);
        end

        
        function setProfile(obj, profile)
            validateattributes(profile, {'robotics.slros.internal.sim.NetworkAddrProfile'}, {'scalar'});
            profile.ProfileName = obj.ProfileName;
            obj.ProfileMap(obj.ProfileName) = profile;
            obj.DataIsModified = true;
        end
        
        
        function clearProfile(obj)
           if obj.ProfileMap.isKey(obj.ProfileName)
              obj.ProfileMap.remove(obj.ProfileName);
              obj.DataIsModified = true; 
           end            
        end
        
        
        function updateStore(obj)
            if obj.DataIsModified
                obj.savePrefs(obj.ProfileMap);
            end
        end

    end
    
    %%
    
    methods (Access=private)

        % Don't save the containers.Map with the NetworkAddrProfile objects
        % If RST is not on the path for any reason, this leads to warnings
        % at MATLAB load time & whenever any MATLAB preference is accessed.

        function savePrefs(obj, prefs)
            validateattributes(prefs, {'containers.Map'}, {});
            % Save the map as an array of raw structs
            profileNames = keys(prefs);
            profileStructs = cell(size(profileNames));
            for i=1:numel(profileNames)
               profileStructs{i} = prefs(profileNames{i}).getPropsStruct;
            end
            setpref(obj.PreferenceGroup, obj.PreferenceName, profileStructs);
        end
        
        
        function prefs = loadPrefs(obj)
            if ispref(obj.PreferenceGroup, obj.PreferenceName)
                profileStructs = getpref(obj.PreferenceGroup, obj.PreferenceName);
            else
                profileStructs = {};
            end
            
            if ~(iscell(profileStructs) && all(cellfun(@isstruct, profileStructs)))
                % The stored variable got corrupted somehow
                warning(message('robotics:robotslros:netaddr:CorruptedProfile'));
                % Overwrite saved prefs with a null entry, so this warning
                % doesn't show up again 
                obj.savePrefs(containers.Map);
                profileStructs = [];
            end
            
            % convert the array of structs to a ProfileName -> NetworkAddrProfile map
            prefs = containers.Map;
            for i=1:numel(profileStructs)
                s = profileStructs{i};
                prefs(s.ProfileName) = ...
                    robotics.slros.internal.sim.NetworkAddrProfile.setPropsStruct(s);
            end
        end
        
    end
    
    
    methods (Static,Hidden)
        % Used for testing
        function removePrefs()
            import robotics.slros.internal.sim.*
            if ispref(NetworkAddrStore.PreferenceGroup, NetworkAddrStore.PreferenceName)
                rmpref(NetworkAddrStore.PreferenceGroup, NetworkAddrStore.PreferenceName);
            end
        end        
        
    end
    
end
