function [ settings ] = TA_settings(selector)
%TA_settings TestAutomation Settings
% This is an example template for TA settings
% rename the file and function as TA_settings


%% Define variations and actions

switch selector
    case 1 %%All Systems
        assignin('base', 'StopSim',18);  %% define when (at which roadID) the simulation should stop
        assignin('base', 'initialV',50/3.6);  %% define the initial velocity of the host vehicle
    
        settings.prescanRun(1).Settings = {
        'LaneWidth', '3';
        'LaneLineType','Solid';
        'DirtSpotLKAS_ZLocation','-10'; %no dirt spot for LKAS
        'DirtSpotLDWS_ZLocation','-10'; %no dirt spot for LDWS
        'TrajectoryHost','Trajectory_Host_AllSystems';
        'Trajectory_CuttingInVehicle','Trajectory_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_stationary_CrossingPedestrian'
        };
    
        settings.prescanRun(2).Settings = {
        'LaneWidth', '3';
        'LaneLineType','Dashed';
        'DirtSpotLKAS_ZLocation','-10'; %no dirt spot for LKAS
        'DirtSpotLDWS_ZLocation','-10'; %no dirt spot for LDWS
        'TrajectoryHost','Trajectory_Host_AllSystems';
        'Trajectory_CuttingInVehicle','Trajectory_stationary_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_R2L_CrossingPedestrian'
        };
    
        settings.prescanRun(3).Settings = {
        'LaneWidth', '3';
        'LaneLineType','Dashed';
        'DirtSpotLKAS_ZLocation','0'; %dirt spot for LKAS
        'DirtSpotLDWS_ZLocation','0'; %dirt spot for LDWS
        'TrajectoryHost','Trajectory_Host_AllSystems';
        'Trajectory_CuttingInVehicle','Trajectory_stationary_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_L2R_CrossingPedestrian'
        };
    
        settings.prescanRun(4).Settings = {
        'LaneWidth', '4';
        'MarkerColorR','Yellow';
        'LaneLineType','Dashed';
        'DirtSpotLKAS_ZLocation','-10'; %no dirt spot for LKAS
        'DirtSpotLDWS_ZLocation','-10'; %no dirt spot for LDWS
        'TrajectoryHost','Trajectory_Host_AllSystems';
        'Trajectory_CuttingInVehicle','Trajectory_stationary_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_L2R_CrossingPedestrian'
        };
    

    case 2 %% LKAS only
        assignin('base', 'StopSim',13);  %% define when (at which roadID) the simulation should stop
        assignin('base', 'initialV',50/3.6);  %% define the initial velocity of the host vehicle
        
        settings.prescanRun(1).Settings = {
        'LaneWidth', '3';
        'LaneLineType','Solid';
        'DirtSpotLKAS_ZLocation','-10'; %no dirt spot for LKAS
        'DirtSpotLDWS_ZLocation','-10'; %no dirt spot for LDWS
        'TrajectoryHost','Trajectory_Host_LKAS';
        'Trajectory_CuttingInVehicle','Trajectory_stationary_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_stationary_CrossingPedestrian'
        };
    
        settings.prescanRun(2).Settings = {
        'LaneWidth', '3';
        'LaneLineType','Dashed';
        'DirtSpotLKAS_ZLocation','-10'; %no dirt spot for LKAS
        'DirtSpotLDWS_ZLocation','-10'; %no dirt spot for LDWS
        'TrajectoryHost','Trajectory_Host_LKAS';
        'Trajectory_CuttingInVehicle','Trajectory_stationary_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_stationary_CrossingPedestrian'
        };
    
        settings.prescanRun(3).Settings = {
        'LaneWidth', '3';
        'LaneLineType','Dashed';
        'DirtSpotLKAS_ZLocation','0'; %dirt spot for LKAS
        'DirtSpotLDWS_ZLocation','-10'; %no dirt spot for LDWS        
        'TrajectoryHost','Trajectory_Host_LKAS';
        'Trajectory_CuttingInVehicle','Trajectory_stationary_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_stationary_CrossingPedestrian'
        };
    
        settings.prescanRun(4).Settings = {
        'LaneWidth', '4';
        'MarkerColorR','Yellow';
        'LaneLineType','Dashed';
        'DirtSpotLKAS_ZLocation','-10'; %no dirt spot for LKAS
        'DirtSpotLDWS_ZLocation','-10'; %no dirt spot for LDWS        
        'TrajectoryHost','Trajectory_Host_LKAS';
        'Trajectory_CuttingInVehicle','Trajectory_stationary_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_stationary_CrossingPedestrian'
        };
    
    
    case 3 %%LDWS only
        assignin('base', 'StopSim',8);  %% define when (at which roadID) the simulation should stop
        assignin('base', 'initialV',50/3.6);  %% define the initial velocity of the host vehicle
        
        settings.prescanRun(1).Settings = {
        'LaneWidth', '3';
        'LaneLineType','Solid';
        'DirtSpotLKAS_ZLocation','-10'; %no dirt spot for LKAS
        'DirtSpotLDWS_ZLocation','-10'; %no dirt spot for LDWS
        'TrajectoryHost','Trajectory_Host_LDWS';
        'Trajectory_CuttingInVehicle','Trajectory_stationary_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_stationary_CrossingPedestrian'
        };
    
        settings.prescanRun(2).Settings = {
        'LaneWidth', '3';
        'LaneLineType','Solid';
        'DirtSpotLKAS_ZLocation','-10'; %no dirt spot for LKAS
        'DirtSpotLDWS_ZLocation','0'; %dirt spot for LDWS
        'TrajectoryHost','Trajectory_Host_LDWS';
        'Trajectory_CuttingInVehicle','Trajectory_stationary_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_stationary_CrossingPedestrian'
        };

        settings.prescanRun(3).Settings = {
        'LaneWidth', '3';
        'LaneLineType','Dashed';
        'DirtSpotLKAS_ZLocation','-10'; %no dirt spot for LKAS
        'DirtSpotLDWS_ZLocation','-10'; %no dirt spot for LDWS
        'TrajectoryHost','Trajectory_Host_LDWS';
        'Trajectory_CuttingInVehicle','Trajectory_stationary_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_stationary_CrossingPedestrian'
         };
     
        settings.prescanRun(4).Settings = {
        'LaneWidth', '4';
        'MarkerColorR','Yellow';
        'LaneLineType','Dashed';
        'DirtSpotLKAS_ZLocation','-10'; %no dirt spot for LKAS
        'DirtSpotLDWS_ZLocation','-10'; %no dirt spot for LDWS
        'TrajectoryHost','Trajectory_Host_LDWS';
        'Trajectory_CuttingInVehicle','Trajectory_stationary_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_stationary_CrossingPedestrian'
         };
    
    case 4 %% AEBS only
        assignin('base', 'StopSim',18);  %% define when (at which roadID) the simulation should stop
        assignin('base', 'initialV',50/3.6);  %% define the initial velocity of the host vehicle
    
        settings.prescanRun(1).Settings = {
        'LaneWidth', '3';
        'TrajectoryHost','Trajectory_Host_AEBS';
        'Trajectory_CuttingInVehicle','Trajectory_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_stationary_CrossingPedestrian'
        };

        settings.prescanRun(2).Settings = {
        'LaneWidth', '3';
        'TrajectoryHost','Trajectory_Host_AEBS';
        'Trajectory_CuttingInVehicle','Trajectory_stationary_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_R2L_CrossingPedestrian'
        };

        settings.prescanRun(3).Settings = {
        'LaneWidth', '3';
        'TrajectoryHost','Trajectory_Host_AEBS';
        'Trajectory_CuttingInVehicle','Trajectory_stationary_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_L2R_CrossingPedestrian'
        };
    

    case 5 %%LKAS & AEBS
        assignin('base', 'StopSim',18);  %% define when (at which roadID) the simulation should stop
        assignin('base', 'initialV',50/3.6);  %% define the initial velocity of the host vehicle
        
        settings.prescanRun(1).Settings = {
        'LaneWidth', '3';
        'LaneLineType','Solid';
        'DirtSpotLKAS_ZLocation','-10'; %no dirt spot for LKAS
        'DirtSpotLDWS_ZLocation','-10'; %no dirt spot for LDWS
        'TrajectoryHost','Trajectory_Host_LKAS_AEBS';
        'Trajectory_CuttingInVehicle','Trajectory_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_stationary_CrossingPedestrian'
        };
    
        settings.prescanRun(2).Settings = {
        'LaneWidth', '3';
        'LaneLineType','Dashed';
        'DirtSpotLKAS_ZLocation','-10'; %no dirt spot for LKAS
        'DirtSpotLDWS_ZLocation','-10'; %no dirt spot for LDWS
        'TrajectoryHost','Trajectory_Host_LKAS';
        'Trajectory_CuttingInVehicle','Trajectory_stationary_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_R2L_CrossingPedestrian'
        };
    
        settings.prescanRun(3).Settings = {
        'LaneWidth', '3';
        'LaneLineType','Dashed';
        'DirtSpotLKAS_ZLocation','0'; %dirt spot for LKAS
        'DirtSpotLDWS_ZLocation','-10'; %no dirt spot for LDWS        
        'TrajectoryHost','Trajectory_Host_LKAS';
        'Trajectory_CuttingInVehicle','Trajectory_stationary_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_L2R_CrossingPedestrian'
        };
    
        settings.prescanRun(4).Settings = {
        'LaneWidth', '4';
        'MarkerColorR','Yellow';
        'LaneLineType','Dashed';
        'DirtSpotLKAS_ZLocation','-10'; %no dirt spot for LKAS
        'DirtSpotLDWS_ZLocation','-10'; %no dirt spot for LDWS        
        'TrajectoryHost','Trajectory_Host_LKAS';
        'Trajectory_CuttingInVehicle','Trajectory_stationary_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_L2R_CrossingPedestrian'
        };
        
    
    case 6 %%LDWS & LKAS
        assignin('base', 'StopSim',13);  %% define when (at which roadID) the simulation should stop
        assignin('base', 'initialV',50/3.6);  %% define the initial velocity of the host vehicle
        
        settings.prescanRun(1).Settings = {
        'LaneWidth', '3';
        'LaneLineType','Solid';
        'DirtSpotLKAS_ZLocation','-10'; %no dirt spot for LKAS
        'DirtSpotLDWS_ZLocation','-10'; %no dirt spot for LDWS
        'TrajectoryHost','Trajectory_Host_AllSystems';
        'Trajectory_CuttingInVehicle','Trajectory_stationary_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_stationary_CrossingPedestrian'
        };
    
        settings.prescanRun(2).Settings = {
        'LaneWidth', '3';
        'LaneLineType','Dashed';
        'DirtSpotLKAS_ZLocation','-10'; %no dirt spot for LKAS
        'DirtSpotLDWS_ZLocation','-10'; %no dirt spot for LDWS
        'TrajectoryHost','Trajectory_Host_AllSystems';
        'Trajectory_CuttingInVehicle','Trajectory_stationary_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_stationary_CrossingPedestrian'
        };
    
        settings.prescanRun(3).Settings = {
        'LaneWidth', '3';
        'LaneLineType','Dashed';
        'DirtSpotLKAS_ZLocation','0'; %dirt spot for LKAS
        'DirtSpotLDWS_ZLocation','0'; %dirt spot for LDWS
        'TrajectoryHost','Trajectory_Host_AllSystems';
        'Trajectory_CuttingInVehicle','Trajectory_stationary_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_stationary_CrossingPedestrian'
        };
    
        settings.prescanRun(4).Settings = {
        'LaneWidth', '4';
        'MarkerColorR','Yellow';
        'LaneLineType','Dashed';
        'DirtSpotLKAS_ZLocation','-10'; %no dirt spot for LKAS
        'DirtSpotLDWS_ZLocation','-10'; %no dirt spot for LDWS
        'TrajectoryHost','Trajectory_Host_AllSystems';
        'Trajectory_CuttingInVehicle','Trajectory_stationary_CuttingInVehicle';
        'Trajectory_CrossingPedestrian','Trajectory_stationary_CrossingPedestrian'
        };
    
end


end