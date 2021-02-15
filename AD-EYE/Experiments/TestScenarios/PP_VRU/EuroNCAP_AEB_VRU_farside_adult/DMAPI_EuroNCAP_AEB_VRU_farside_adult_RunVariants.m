% Script to run Euro NCAP VRU test protocol
% for AEB systems: Car-to-Pedestrian Farside Adult 50% (CPFA-50)
% Last modified: 19/11/2018

% Source: Euro NCAP AEB C2C Test Protocol v2.0.1 From January 2018
% https://cdn.euroncap.com/media/26997/euro-ncap-aeb-vru-test-protocol-v20.pdf
% -------------------------------------------------------------------------

% Acronyms
% -------------------------------------------------------------------------
% AEB : Autonomous Emergency Braking
% Car-to-Pedestrian Farside Adult 50% : CPFA-50
% Euro NCAP : European New Car Assessment Programme
% VUT : Vehicle Under Test
% VRU : Vulnerable Road Users
%

% The specification of the test is given in section 7.2.4
velocity = 20:5:60; % km/h
ped_velocity = 8; % km/h

%% Data Model API (DMAPI)
% Read Prescan data model
model = prescan.experiment.readDataModels('EuroNCAP_AEB_VRU_farside_adult.pb');

Num_v_idx=size(velocity,2);
for v_idx = 1:size(velocity,2)
    Num_p_idx=size(ped_velocity,2);
    for p_idx = 1:size(ped_velocity,2)
        % Set these variables in the workspace
        HostVelocity = velocity(v_idx);
        Target1Velocity = ped_velocity(p_idx);
        
        % Validation, writing and running of new model
        vali = prescan.experiment.validate(model);              % Validate model
        if vali == 1
            disp(['Running AEB VRU farside adult test ' num2str((v_idx-1)*Num_p_idx+p_idx) '/' num2str(Num_v_idx*Num_p_idx) ': Velocity VUT ' num2str(velocity(v_idx)) ' km/h, Velocity VRU ' num2str(ped_velocity(p_idx)) ' km/h']);
            simOut = prescan.experiment.runWithDataModels(model, 'Regenerate', 'off');   % Run model
        else
            disp('Model validation failed');
            return
        end
    end
end
disp('All AEB VRU farside adult tests completed')