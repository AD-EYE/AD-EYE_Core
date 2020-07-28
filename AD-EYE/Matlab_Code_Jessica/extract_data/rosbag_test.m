% filename='20180810_150607_cam_rear_center_lidar.bag';
% bag = rosbag(filename);
% bagInfo = rosbag(filename);
% rosbag info '20180810_150607_cam_rear_center_lidar.bag'
%Get a list of available frames.
%frames = bag.AvailableFrames
%%
%Select a specific topic.
% bSel = select(bag,'Topic','/a2d2/20180810_150607_cam_rear_center/depth_map'); %this image of the camera
%Read messages as a structure. Specify the DataFormat name-value pair when 
%reading the messages. Inspect the first structure in the returned cell 
%array of structures.
%msgStructs = readMessages(bSel);
%msgStructs{1}
%%
%Select a specific topic.
% bSel_mask = select(bag,'Topic','/a2d2/20180810_150607_cam_rear_center/depth_map_mask');
%Read messages as a structure. Specify the DataFormat name-value pair when 
%reading the messages. Inspect the first structure in the returned cell 
%array of structures.
% msgStructs_mask = readMessages(bSel_mask,'DataFormat','struct');
%msgStructs_mask{1}
%% rear center camera
filename='20180810_150607_cam_rear_center_lidar.bag';
bag_rear = rosbag(filename);
%Select a specific topic.
bSel_lidar_rear = select(bag_rear,'Topic','/a2d2/20180810_150607_cam_rear_center/lidar');
%Read messages as a structure. Specify the DataFormat name-value pair when 
%reading the messages. Inspect the first structure in the returned cell 
%array of structures.
%msgStructs_lidar = readMessages(bSel_lidar,'DataFormat','struct');
msg_lidar_rear= readMessages(bSel_lidar_rear,1:3);
ptcloud_rear=msg_lidar_rear{3,1}; %read one message
xyz_rear=readXYZ(ptcloud_rear);
%% front center camera
filename='20180810_150607_cam_front_center_lidar.bag';
bag_front = rosbag(filename);
%Select a specific topic.
bSel_lidar_front = select(bag_rear,'Topic','/a2d2/20180810_150607_cam_front_center/lidar');
msg_lidar_front= readMessages(bSel_lidar_rear,1:3);
ptcloud_front=msg_lidar_front{3,1}; %read one message
xyz_front=readXYZ(ptcloud_front);

%% side left camera
filename='20180810_150607_cam_side_left_lidar.bag';
bag_left = rosbag(filename);
%Select a specific topic.
bSel_lidar_left = select(bag_left,'Topic','/a2d2/20180810_150607_cam_side_left/lidar');
msg_lidar_left= readMessages(bSel_lidar_left,1:3);
ptcloud_left=msg_lidar_left{3,1}; %read one message
xyz_left=readXYZ(ptcloud_left);

%% side right camera
filename='20180810_150607_cam_side_right_lidar.bag';
bag_right = rosbag(filename);
%Select a specific topic.
bSel_lidar_right = select(bag_right,'Topic','/a2d2/20180810_150607_cam_side_right/lidar');
msg_lidar_right= readMessages(bSel_lidar_right,1:3);
ptcloud_right=msg_lidar_right{3,1}; %read one message
xyz_right=readXYZ(ptcloud_right);

%%
xyz=[xyz_rear;xyz_front;xyz_left;xyz_right];
% satter3(xyz);