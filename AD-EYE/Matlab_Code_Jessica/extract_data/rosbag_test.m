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
theta=find_theta(-1,0.01);
xyz_rear=translate_to_origin(-0.41,3.7,0.94,xyz_rear);
xyz_rear=rotation_across_z(theta,xyz_rear);

%% front center camera
filename='20180810_150607_cam_front_center_lidar.bag';
bag_front = rosbag(filename);
%Select a specific topic.
bSel_lidar_front = select(bag_rear,'Topic','/a2d2/20180810_150607_cam_front_center/lidar');
msg_lidar_front= readMessages(bSel_lidar_rear,1:3);
ptcloud_front=msg_lidar_front{3,1}; %read one message
xyz_front=readXYZ(ptcloud_front);
theta=find_theta(1,0.02);
xyz_front=translate_to_origin(1.71,-5.7,0.94,xyz_front);
xyz_front=rotation_across_z(theta,xyz_front);

%% side left camera
filename='20180810_150607_cam_side_left_lidar.bag';
bag_left = rosbag(filename);
%Select a specific topic.
bSel_lidar_left = select(bag_left,'Topic','/a2d2/20180810_150607_cam_side_left/lidar');
msg_lidar_left= readMessages(bSel_lidar_left,1:3);
ptcloud_left=msg_lidar_left{3,1}; %read one message
xyz_left=readXYZ(ptcloud_left);
theta=find_theta(-0.019,0.98);
xyz_left=translate_to_origin(0.65,0.58,0.94,xyz_left);
xyz_left=rotation_across_z(theta,xyz_left);


%% side right camera
filename='20180810_150607_cam_side_right_lidar.bag';
bag_right = rosbag(filename);
%Select a specific topic.
bSel_lidar_right = select(bag_right,'Topic','/a2d2/20180810_150607_cam_side_right/lidar');
msg_lidar_right= readMessages(bSel_lidar_right,1:3);
ptcloud_right=msg_lidar_right{3,1}; %read one message
xyz_right=readXYZ(ptcloud_right);

theta=find_theta(-0.05,-0.98);
xyz_right=translate_to_origin(0.65,-0.58,0.94,xyz_right);
xyz_right=rotation_across_z(theta,xyz_right);

%%
xyz=[xyz_rear;xyz_front;xyz_left;xyz_right];
% scatter3(xyz);


%% usefull function

function point= translate_to_origin(x,y,z,points)
l=length(points);
point=zeros(l,3);
for i=[1:l]
    point(i,1)=points(i,1)-x;
    point(i,2)=points(i,2)-y;
    point(i,3)=points(i,3)-z;
end
end

function point =rotation_across_z(theta,points) %theta in radian
    
    l=length(points);
    point=zeros(l,3);
    for i=[1:l]
        point(i,1)=points(i,1)*cos(theta)-points(i,2)*sin(theta);
        point(i,2)= points(i,1)*sin(theta)+ points(i,2)*cos(theta);
        point(i,3)=points(i,3);
    end
end

% in enter we have x1 and y1 x and y coordonate of the x axis of the camera
function theta= find_theta(x1,y1)
x=1;
y=0; %y coordonate of the x axis of the vehicul
theta=acos((x1*x+y1*y)/(x^2+y^2)); %retourn value between 0 ad pi
val_check=(y1*x-x1*y)/(x^2+y^2);
if sin(theta)~=val_check
    theta= - theta;
end
end
