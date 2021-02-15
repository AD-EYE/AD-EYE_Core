% Script to run Euro NCAP VRU test protocol
% for AEB systems: Car-to-Bicyclist Nearside Adult 50% (CPBA-50)
% Last modified: 11/01/2019

% Source: Euro NCAP AEB C2C Test Protocol v2.0.1 From January 2018
% https://cdn.euroncap.com/media/26997/euro-ncap-aeb-vru-test-protocol-v20.pdf
% -------------------------------------------------------------------------

% Acronyms
% -------------------------------------------------------------------------
% AEB : Autonomous Emergency Braking
% Car-to-Bicyclist Nearside Adult 50% : CBNA-50
% Euro NCAP : European New Car Assessment Programme
% VUT : Vehicle Under Test
% VRU : Vulnerable Road Users
%

%% Data Model API (DMAPI)
% Read Prescan data model
model = prescan.experiment.readDataModels('EuroNCAP_AEB_VRU_nearside_bicyclist.pb');

%
% ImpactOffset which needs to be set in the simulink is 
% defined as distance from the center.
%
impactOffset = [0];     %50 percent overlap
DispOffset=[50];

% The specification of the test is given in section 7.2.4
velocity = 20:5:60; % km/h
cyclist_velocity = 15; % km/h

Num_v_idx=size(velocity,2);
for v_idx = 1:size(velocity,2)
    Num_c_idx=size(cyclist_velocity,2);
    for c_idx = 1:size(cyclist_velocity,2)
        Num_of_idx=size(impactOffset,2);
        for of_idx = 1:size(impactOffset,2)
            % Set these variables in the workspace
            HostVelocity = velocity(v_idx);
            Target1Velocity = cyclist_velocity(c_idx);
            ImpactOffset = impactOffset(of_idx);
            % Validation, writing and running of new model
            vali = prescan.experiment.validate(model);              % Validate model
            if vali == 1
                disp(['Running AEB VRU nearside bicyclist test ' num2str((v_idx-1)*Num_c_idx*Num_of_idx+(c_idx-1)*Num_of_idx+of_idx) '/' num2str(Num_v_idx*Num_c_idx*Num_of_idx) ': Velocity VUT ' num2str(velocity(v_idx)) ' km/h, Velocity VRU ' num2str(cyclist_velocity(c_idx)) ' km/h, Impact location ' num2str(DispOffset(of_idx)) '%']);
                simOut = prescan.experiment.runWithDataModels(model, 'Regenerate', 'off');   % Run model
            else
                disp('Model validation failed');
                return
            end
        end
    end
end
disp('All AEB VRU nearside bicyclist tests completed')