%% Using buildMap function

resolution = 0.25; % meters

shrink_fact = 0.5;

%Getting date from the Experiment
load('scanPositions.mat');
x = pose.Data(:,1);
y = pose.Data(:,2);

path = "../Pointcloud_Files/";

files = dir(path + "*.pcd");
[~, idx] = sort([files.datenum]);
files = files(idx);

if(numel(files) ~= length(pose))
    disp("ERROR : The number of .pcd file doesn't corresponds to the size of the position array.");
    disp("Make sure to clean the Pointcloud_Files folder before running the Mapping Experiment");
end

%% Extracting all point clouds data
% Read all the pcd files to have the point clouds
% Process them to create 2D point clouds.
% and also merge them into a map to have the dimensions informations

fprintf("Reading point clouds");
f = waitbar(0, "Reading point clouds...", 'Name', "Building occupancy grid");

map = 0;
%pcs = repmat(pointCloud([0 0 0]), numel(files), 1);
scans = cell(1, numel(files));
i = 1;
for file = files'
    waitbar(i/numel(files), f, sprintf("Reading point clouds... ( %d / %d )", i, numel(files)));
    pc = pcread(path + file.name);
    scans(i) = {processPC(pc, pose.Data(i, 1:2), shrink_fact)};
    if(map == 0)
        map = pc;
    else
        map = pcmerge(map, pc, 0.01);
    end
    i = i+1;
end

width = map.XLimits(2) - map.XLimits(1);
height = map.YLimits(2) - map.YLimits(1);
offset_X = - map.XLimits(1);
offset_Y = - map.YLimits(1);
x = x + offset_X;
y = y + offset_Y;

disp("  - Done");

%% Building map
% For each scan, get the grid indices under each
% lines that can be traced between the sensor position
% and each point in the scan. Then, put the value 0 in these cells

fprintf("Building map");

waitbar(0, f, "Processing scans...");

p = [x y zeros(size(x))];
%    /_\\    WARNING : In Matlab version >= 2019b
%   /\_/\\   OccupancyGrids are in the base namespace
%  /_(_)_\\  ("robotics." should be removed (everywhere))  
occMap = robotics.OccupancyGrid(width, height, 1/resolution);

for i = 1:numel(scans)
    waitbar(i/numel(scans), f, sprintf("Processing scans... ( %d / %d )", i, numel(scans)));
    scan = scans{i};
    for j = 1:numel(scan.Ranges)
        [~,midPts] = occMap.raycast(p(i,:), scan.Ranges(j), scan.Angles(j));
        occMap.setOccupancy(midPts, zeros(length(midPts),1), 'grid');
    end
end

disp("  - Done");
delete(f);
show(occMap);

%% Write data into the file

fprintf("Converting occupancyGrid data to binary values");
occValues = occMap.occupancyMatrix;
occValues(occValues(:,:) < 0.3) = 0;
occValues(occValues(:,:) ~= 0) = 3;
occValues = flipud(occValues); % Don't know why, but we have to
disp(" - Done");

fprintf("Writing data to file");

% Creating metadata
Xlimits = sprintf("%g,%g", map.XLimits);
Ylimits = sprintf("%g,%g", map.YLimits);
arraySize = sprintf("%d,%d", fliplr(size(occValues))); % width,height

metadata = sprintf("#%s\n#%s\n#%s\n#%g", Xlimits, Ylimits, arraySize, resolution);

% Creating filename from experiment folder
expFolder = strsplit(pwd, "\");
expName = expFolder{end-1};

fileName = strcat(expName, '_', replace(string(resolution), '.', ''), '.csv');

% Writing data
writematrix(occValues, fileName)
prepend2file(metadata, fileName)

disp(" - done");

%% Functions

function scan = processPC(pc, position, shrink)
    % Remove inf and nan values inside the point cloud,
    % Extract the ground and then find the boundaries of
    % the resulting point cloud (which is now called a 'scan')
    pc_clean = extractGround(pc);
    xyz = double(pc_clean.Location);
    xyz = xyz( ~any( isnan(xyz) | isinf(xyz), 2),:);
    xyz(:,1) = xyz(:, 1) - position(1);
    xyz(:,2) = xyz(:, 2) - position(2);
    k = boundary(xyz(:,1:2), shrink);
    scan = lidarScan(xyz(k,1:2));
end

function ground_pc = extractGround(pc)
    not_ground_pts = zeros(1, pc.Count);
    N = 1;

    for pt = 1 : pc.Count
        if(pc.Location(pt, 3) >= 0.01)
            not_ground_pts(N) = pt;
            N = N+1;
        end
    end
    not_ground_pts = not_ground_pts(1:N-1);

    ground_pts = true(pc.Count, 1);
    ground_pts(not_ground_pts) = false;

    ground_pc = select(pc, find(ground_pts));
end

function prepend2file( string, filename, newline )
% newline:  is an optional boolean, that if true will append a \n to the end 
% of the string that is sent in such that the original text starts on the 
% next line rather than the end of the line that the string is on 
% string:  a single line string 
% filename:  the file you want to prepend to 
      tempFile = 'tempData';
      fw = fopen( tempFile, 'wt' );
      if nargin < 3
          newline = true;
      end
      if newline
          fprintf( fw, sprintf('%s\n', string ) );
      else
          fprintf( fw, string );
      end
      fclose( fw );
      appendFiles( filename, tempFile );
      copyfile( tempFile, filename );
      delete(tempFile);
end
% append readFile to writtenFile
function status = appendFiles( readFile, writtenFile )
      fr = fopen( readFile, 'rt' );
      fw = fopen( writtenFile, 'at' );
      while feof( fr ) == 0
          tline = fgetl( fr );
          fwrite( fw, sprintf('%s\n',tline ) );
      end
      fclose(fr);
      fclose(fw);
end