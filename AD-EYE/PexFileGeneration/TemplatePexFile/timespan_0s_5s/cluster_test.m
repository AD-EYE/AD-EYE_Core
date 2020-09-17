filename='20180810_150607_cam_rear_center_lidar.bag';
bSel_lidar = select(bag,'Topic','/a2d2/20180810_150607_cam_rear_center/lidar');
msgStructs_lidar= readMessages(bSel_lidar);
ptcloud=msgStructs_lidar{3,1};
%loaded(filename);
%Detect the ground plane and store the points in inliers. Distance is measured in meters
maxDistance = 0.3;
referenceVector = [0,0,1];
[~,inliers,outliers] = pcfitplane(ptCloud,maxDistance,referenceVector);
%Cluster the points, ignoring the ground plane points. Specify a minimum
%Euclidean distance of 0.5 meters between clusters.
ptCloudWithoutGround = select(ptCloud,outliers,'OutputSize','full');
distThreshold = 0.5;
[labels,numClusters] = pcsegdist(ptCloudWithoutGround,distThreshold);
% Add an additional label for the ground plane.
numClusters = numClusters+1;
labels(inliers) = numClusters;
% Plot the labeled results. Display the ground plane in black.
labelColorIndex = labels+1;
pcshow(ptCloud.Location,labelColorIndex)
colormap([hsv(numClusters);[0 0 0]])
title('Point Cloud Clusters')