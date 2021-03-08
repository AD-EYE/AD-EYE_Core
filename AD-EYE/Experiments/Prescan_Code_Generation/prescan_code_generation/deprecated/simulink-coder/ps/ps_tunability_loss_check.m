function [] = ps_tunability_loss_check(buildDir)
    %PS_TUNABILITY_LOSS_CHECK Detect loss of tunability.
    %
    %Check all tunable variables for loss of tunability. Display a warning
    %whenever tunability loss is detected. Display the number of times
    %that loss of tunability was detected. Only available on Matlab 2015b
    %and higher because of a limitation of the C API interface.
    
    if ~verLessThan('matlab','8.6')
        tunabilityCheck = TunabilityLossDetector(buildDir);
        tunabilityLossCount = tunabilityCheck.getTunabilityLossCount();
        if tunabilityLossCount ~= 0
            plural = '';
            if tunabilityLossCount > 1
                plural = 's';
            end
            disp(['#### Warning: Detected loss of tunability for ' ...
                num2str(tunabilityCheck.getTunabilityLossCount()) ' variable' plural '.']);
        end
    end
end
