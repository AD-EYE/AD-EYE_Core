%load laser scan data from file
%load('C:\Users\adeye\AD-EYE_Core\AD-EYE\Experiments\Real_world\scans_data.mat');

%create lidarSLAM object and set the map resolution and the max lidar range
maxLidarRange = 8; %need to be smaller than the max scan range
mapResolution = 20; %cells per meter
slamAlg = lidarSLAM(mapResolution, maxLidarRange);

%loop closure parameters
slamAlg.LoopClosureThreshold = 210;  
slamAlg.LoopClosureSearchRadius = 8;

%observe the map building process with initial 10 scans
for i=1:10
    [isScanAccepted, loopClosureInfo, optimizationInfo] = addScan(slamAlg, scans{i});
    if isScanAccepted
        fprintf('Added scan %d \n', i);
    end
end
%plot the scans and poses tracked by slamAlg
figure;
show(slamAlg);
title({'Map of the Environment','Pose Graph for Initial 10 Scans'});

%obserce effect of loop closures and optimization process
firstTimeLCDetected = false;

figure;
for i=10:length(scans)
    [isScanAccepted, loopClosureInfo, optimizationInfo] = addScan(slamAlg, scans{i});
    if ~isScanAccepted
        continue;
    end
    % visualize the first detected loop closure, if you want to see the
    % complete map building process, remove the if condition below
    if optimizationInfo.IsPerformed && ~firstTimeLCDetected
        show(slamAlg, 'Poses', 'off');
        hold on;
        show(slamAlg.PoseGraph); 
        hold off;
        firstTimeLCDetected = true;
        drawnow
    end
end
title('First loop closure');

%visualize the constructed map and trajectory of the car
figure
show(slamAlg);
title({'Final Built Map of the Environment', 'Trajectory of the car'});

%build occupancy grid map
[scans, optimizedPoses]  = scansAndPoses(slamAlg);
map = buildMap(scans, optimizedPoses, mapResolution, maxLidarRange);
%visualize
[scans, optimizedPoses]  = scansAndPoses(slamAlg);
map = buildMap(scans, optimizedPoses, mapResolution, maxLidarRange);
