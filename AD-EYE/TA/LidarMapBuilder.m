
bagFile = "2017-03-15-15-46-19.bag";

% Load the rosbag
fprintf("Loading the rosbag  -  ")
bag = rosbag(bagFile);
disp("Done")

fprintf("Selecting topics    -  ")
pcSelect = select(bag, 'Topic', '/velodyne_points_left');
imuSelect = select(bag, 'Topic', 'communication/dspace/imu');
disp("Done")

clear bag


%% Constants

%folder where to save point cloud data
pointCloudFolder = "PointCloud_Files/";

%Use the IMU data
useIMU = true;

%The number of seconds of data that will
% be processed at once
timeStep = 10;

%The number of pointCloud data that are skipped between iterations
skipFrame = 5;

%Starting and ending point
startTime = 15;
%endTime = min(pcSelect.EndTime - pcSelect.StartTime, imuSelect.EndTime - imuSelect.StartTime);
endTime = 50;


%point cloud Processing
downsamplePercent = 0.2; %Downsampling factor
noiseThreshold = 0.01;

%point cloud Registering
maxNDTiterations = 1000;
ndtTolerance = [0.05 0.01];
%Size of the 3-D cube that voxelizes the fixed point cloud,
%specified as a positive scalar.
regGridStep = 5;

%point cloud Merging
mergeGridStep = 0.3;

%% Map Building

%Initialisation
prevTime = rosStampToDatetime(rostime(pcSelect.MessageList.Time(1)));

map = [];

tform = affine3d;
initMove = affine3d;
fprintf("End time for the whole data : %d\n", endTime);
for time = startTime : timeStep : endTime-timeStep
    %Loading the data
    fprintf("Loading data from time %d to %d\n", time, time+timeStep);
    fprintf("\tpointCloud  -  ")
    ptCloud = loadPointcloudData(pcSelect, time, timeStep);
    fprintf("Done\n\tIMU         -  ")
    imu = loadIMUdata(imuSelect, time, timeStep);
    disp("Done")

    startFrame = 1;

    disp("Processing map ...");
    if(isempty(map))
        %Map initialisation
        fprintf("\tframe %d of %d\n", startFrame, height(ptCloud));
        map = processPointCloud(ptCloud.PointCloud(1), noiseThreshold);
        startFrame = skipFrame;
        initIMU = imu.Orientation(1, :);
    end
    for frame=startFrame:skipFrame:height(ptCloud)
        if(useIMU)
            %Using IMU data:
            currTime = ptCloud.Time(frame);
            %Getting the IMU data around the current time
            timeR = timerange(currTime - timeStep/2, currTime);
            imuReads = imu(timeR, 'Orientation');
            %Getting the current orientation information
            currIMU = imuReads.Orientation(end, :);
            %Computing an initial tranformation with these data
            initMove = computeInitialEstimateFromIMU(initIMU, currIMU, initMove);
        end

        initTform = tform;

        %Getting the next pointcloud
        nextPC_0 = ptCloud.PointCloud(frame);
        %Rotate the pointcloud according to the IMU data
        nextPC = pctransform(nextPC_0, initMove);

        %Processing
        nextPC = processPointCloud(nextPC);
        %Downsampling
        nextPC_downsampled = pcdownsample(nextPC, 'random', downsamplePercent);
        map_downsampled = pcdownsample(map, 'random', downsamplePercent);

        %Registration
        tform = pcregisterndt(nextPC_downsampled, map_downsampled, regGridStep, ...
            'InitialTransform', initTform, ...
            'MaxIterations', maxNDTiterations, ...
            'Tolerance', ndtTolerance, ...
            'OutlierRatio', 0.70);
        nextPCreg = pctransform(nextPC, tform);

        %Visualisation
        fprintf("\tframe %d of %d\n", frame, height(ptCloud));
        visualize(map, nextPC_0, nextPCreg)

        %Save the pointcloud file
        writePointCloud(nextPCreg, pointCloudFolder);

        %merge
        map = pcmerge(map, nextPCreg, mergeGridStep);
    end
end

figure
pcshow(map);
title("Accumulated map")

%% Functions

function visualize(map, nextPC, nextPCreg)
%Visulaization of a registration step
subplot(121)
pcshowpair(nextPC, map)
title("Before Processing")
view(2) %Top - view
subplot(122)
pcshowpair(nextPCreg, map)
title("After Registration")
view(2)
drawnow() %Display
end

function date = rosStampToDatetime(rosStamp)
%Used in order to convert data from ROS Stamp to Matlab
t = double(rosStamp.Sec) + double(rosStamp.Nsec)*10^-9;
date = datetime(t, 'ConvertFrom', 'posixtime', 'Format', 'HH:mm:ss.SSSS');
end

function imu = loadIMUdata(bagIMUselect, start, duration)
%Load a part of the data in bagIMUselect (from start to start+duration)
% and stores it in a timetable

%Time restriction
startTime = bagIMUselect.StartTime + start;
imuSelect = select(bagIMUselect, 'Time', [startTime startTime+duration]);

%Reading messages
rosImu = readMessages(imuSelect);

%Building the data
Time = NaT(length(rosImu), 1);
Time.Format = 'HH:mm:ss.SSSS';

imuData = zeros(length(rosImu), 4);

for i=1:length(rosImu)
    Time(i) = rosStampToDatetime(rosImu{i}.Header.Stamp);
    imuData(i, :) = toIMUOrientation(rosImu{i});
end

imu = timetable(Time, imuData, 'VariableNames', {'Orientation'});
end

function imu = toIMUOrientation(rosImu)
%Used in order to convert data from ROS to Matlab
o = rosImu.Orientation;
imu = [o.X o.Y o.Z o.W];
end

function ptCloud = loadPointcloudData(bagPCselect, start, duration)
%Load a part of the data in bagPCselect (from start to start+duration)
% and stores it in a timetable

%Time restriction
startTime = bagPCselect.StartTime + start;
pcSelect = select(bagPCselect, 'Time', [startTime startTime+duration]);

%Reading messages
rosPointCloud = readMessages(pcSelect);

%Building the data
Time = NaT(length(rosPointCloud), 1);
Time.Format = 'HH:mm:ss.SSSS';

pcData = pointCloud([0 0 0]);

for i=1:length(rosPointCloud)
    Time(i) = rosStampToDatetime(rosPointCloud{i}.Header.Stamp);
    pcData(i,:) = toPointCloud(rosPointCloud{i});
end

ptCloud = timetable(Time, pcData, 'VariableNames', {'PointCloud'});
end

function ptCl = toPointCloud(rosPc)
%Used in order to convert data from ROS to Matlab
ptCl = pointCloud(readXYZ(rosPc));%,'Color',uint8(255*readRGB(rosPc)));
end

function ptCloudProcessed = processPointCloud(ptCloud, noiseThreshold)
%Process a point cloud by removing the car and the ground from the point cloud
% then, removing some noise

% Check if the point cloud is organized
isOrganized = ~ismatrix(ptCloud.Location);

% If the point cloud is organized, use range-based flood fill algorithm
% (segmentGroundFromLidarData). Otherwise, use plane fitting.
groundSegmentationMethods = ["planefit", "rangefloodfill"];
method = groundSegmentationMethods(isOrganized+1);


if method == "planefit"
    % Segment ground as the dominant plane, with reference normal vector
    % pointing in positive z-direction, using pcfitplane. For organized
    % point clouds, consider using segmentGroundFromLidarData instead.
    maxDistance    = 2.5;        % meters
    maxAngDistance = 3;          % degrees
    refVector      = [0, 0, 1];  % z-direction

    [~,groundIndices] = pcfitplane(ptCloud, maxDistance, refVector, maxAngDistance);
elseif method == "rangefloodfill"
    % Segment ground using range-based flood fill.
    groundIndices = segmentGroundFromLidarData(ptCloud);
else
    error("Expected method to be 'planefit' or 'rangefloodfill'")
end

% Segment ego vehicle as points within a given radius of sensor
sensorLocation = [0, 0, 0];
radius         = 2;

egoIndices = findNeighborsInRadius(ptCloud, sensorLocation, radius);

% Remove points belonging to ground or ego vehicle
ptsToKeep = true(ptCloud.Count, 1);
ptsToKeep(groundIndices) = false;
ptsToKeep(egoIndices)    = false;

% If the point cloud is organized, retain organized structure
if isOrganized
    ptCloudProcessed = select(ptCloud, find(ptsToKeep), 'OutputSize', 'full');
else
    ptCloudProcessed = select(ptCloud, find(ptsToKeep));
end

if(nargin >= 2 && noiseThreshold > 0)
    ptCloudProcessed = pcdenoise(ptCloudProcessed, 'Threshold', noiseThreshold);
end

end

function writePointCloud(ptCloud, folder)
%Stores the ptCloud data in a pcd file inside the given folder
c=clock;
filename=strcat(folder, "pcd", num2str(fix(c(4))), num2str(fix(c(5))), num2str(fix(1000*c(6))), ".pcd");
pcwrite(ptCloud,filename);
end

function tform = computeInitialEstimateFromIMU(initIMU, currIMU, prevTform)

% Initialize transformation using previously estimated transform
if(nargin < 3)
    tform = affine3d;
else
    tform = prevTform;
end

% % If no IMU readings are available, return
% if height(imuReadings) <= 1
%     return;
% end

% IMU orientation readings are reported as quaternions representing the
% rotational offset to the body frame. Compute the orientation change
% between the first and last reported IMU orientations during the lidar scan.
q1 = initIMU;
q2 = currIMU;

q1 = [q1(4) q1(1:3)];
q2 = [q2(4) q2(1:3)];

% Convert quaternions to rotation matrix
R1 = vision.internal.quaternion.quaternionToRotation(q1);
R2 = vision.internal.quaternion.quaternionToRotation(q2);

% Compute rotational offset between first and last IMU reading by
%   - Rotating from q2 frame to body frame
%   - Rotating from body frame to q1 frame
R = R1 / R2; % R1 * inv(R2)

% Convert to Euler angles
rollPitchYaw = vision.internal.eul.rotationMatrixToEulerAngle(R);

% Discard pitch and roll angle esimates. Use only heading angle estimate
% from IMU orientation.
rollPitchYaw(1:2) = 0;

% Convert back to rotation matrix
R = vision.internal.eul.eulerAngleToRotationMatrix(rollPitchYaw);

% Use computed rotation
tform.T(1:3, 1:3) = R;
end
