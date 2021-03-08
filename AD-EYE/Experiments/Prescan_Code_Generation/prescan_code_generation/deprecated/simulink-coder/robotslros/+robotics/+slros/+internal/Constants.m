classdef Constants
    %This class is for internal use only. It may be removed in the future.

    %Constants Some constants that are used uniformly in Simulink ROS
        
    %   Copyright 2016-2018 The MathWorks, Inc.
    
    properties (Constant)
        %PreferenceGroup - The group name for MATLAB preference storage
        PreferenceGroup = 'Robotics_System_Toolbox'
        
        %TargetHardware - The name of the target selection in Config Params > Hardware Implementation
        TargetHardware = 'Robot Operating System (ROS)'
    end
    
    % All widget tags for widgets in the ROS configuration set
    % See toolbox\robotics\robotsimulink\robotslros\registry\parameters\ros_parameters.xml
    % for the source of the strings
    properties (Constant)
        %CoderTargetParameter - Config set parameter that stores coder targets settings
        CoderTargetParameter = 'HardwareBoard'
        
        %TagCSMaintainerName - Tag for maintainer name edit field
        TagCSMaintainerName = robotics.slros.internal.Constants.fullTagName('ROSMaintainerName')
        
        %TagCSMaintainerEmail - Tag for maintainer e-mail edit field
        TagCSMaintainerEmail = robotics.slros.internal.Constants.fullTagName('ROSMaintainerEmail')
        
        %TagCSLicense - Tag for package license edit field
        TagCSLicense = robotics.slros.internal.Constants.fullTagName('ROSLicense')
        
        %TagCSVersion - Tag for package version edit field
        TagCSVersion = robotics.slros.internal.Constants.fullTagName('ROSVersion')
        
        %TagCSDeviceAddress - Tag for ROS device address edit field
        TagCSDeviceAddress = robotics.slros.internal.Constants.fullTagName('ROSDeviceAddress')
        
        %TagCSUsername - Tag for ROS device username edit field
        TagCSUsername = robotics.slros.internal.Constants.fullTagName('ROSUsername')
        
        %TagCSEditButton1 - Tag for "Edit" button in "Device parameters" group
        TagCSEditButton1 = robotics.slros.internal.Constants.fullTagName('ROSEditDeviceInfo1')
        
        %TagCSEditButton2 - Tag for "Edit" button in "Build options" group
        TagCSEditButton2 = robotics.slros.internal.Constants.fullTagName('ROSEditDeviceInfo2')
        
        %TagCSBuildAction - Tag for build action dropdown
        TagCSBuildAction = robotics.slros.internal.Constants.fullTagName('ROSBuildAction')
        
        %TagCSInstallFolder - Tag for ROS installation folder edit field
        TagCSInstallFolder = robotics.slros.internal.Constants.fullTagName('ROSInstall')
        
        %TagCSCatkinWorkspace - Tag for Catkin workspace folder edit field
        TagCSCatkinWorkspace = robotics.slros.internal.Constants.fullTagName('ROSCatkinWS')
    end
    
    properties (Constant, Access = private)
        %CSWidgetTagPrefix Tag prefix for all widgets
        CSWidgetTagPrefix = 'Tag_ConfigSet_CoderTarget'
    end
    
    methods (Static)
        function fullTag = fullTagName(relativeTag)
            %fullTagName Assemble full tag name from prefix and relative tag
            
            fullTag = [robotics.slros.internal.Constants.CSWidgetTagPrefix ...
                '_' relativeTag];
        end
    end    
end

