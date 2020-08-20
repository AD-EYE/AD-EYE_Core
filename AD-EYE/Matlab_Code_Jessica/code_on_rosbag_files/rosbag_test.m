nb_msg=100:101;

%% rear center camera
filename='20180810_150607_cam_rear_center_lidar.bag';
bag_rear = rosbag(filename);
%to visualise all informations and particularly all topics:
% rosbag info '20180810_150607_cam_rear_center_lidar.bag'
%Select a specific topic. We would like type topic PointCloud2
bSel_lidar_rear = select(bag_rear,'Topic','/a2d2/20180810_150607_cam_rear_center/lidar');
%Read messages as a structure. Specify the DataFormat name-value pair when 
%reading the messages. Inspect the first structure in the returned cell 
%array of structures.
msg_lidar_rear= readMessages(bSel_lidar_rear,nb_msg); % we get only 3 messages to don't use too much memory
ptcloud_rear=msg_lidar_rear{1,1}; %read one message
X=readField(ptcloud_rear,'x');
Y=readField(ptcloud_rear,'y');
Z=readField(ptcloud_rear,'z');
xyz_rear=[X Y Z];
theta=find_theta_x(-1,0.01,1,0); % search the angle of rotation necessara to have the same frame that car
xyz_rear=translate_to_origin(-0.41,3.7,0.94,xyz_rear); %translate points to the origin of the frame of the car
xyz_rear=rotation_across_z(theta,xyz_rear); % rotate the frame of the camera to correspond to the frame of the car
% theta=find_theta_y(-1,-0.002,1,0);
% xyz_rear=rotation_across_x(theta,xyz_rear);

%% We redo this process for all lidar data we have.
%% front center camera
filename='20180810_150607_cam_front_center_lidar.bag';
bag_front = rosbag(filename);
%Select a specific topic.
bSel_lidar_front = select(bag_rear,'Topic','/a2d2/20180810_150607_cam_front_center/lidar');
msg_lidar_front= readMessages(bSel_lidar_rear,nb_msg);
ptcloud_front=msg_lidar_front{1,1}; %read one message
X=readField(ptcloud_front,'x');
Y=readField(ptcloud_front,'y');
Z=readField(ptcloud_front,'z');
xyz_front=[X Y Z];
theta=find_theta_x(1,0.02,1,0);
xyz_front=translate_to_origin(1.71,-5.7,0.94,xyz_front);
xyz_front=rotation_across_z(theta,xyz_front);
% theta=find_theta_y(1,-0.02,1,0);
% xyz_front=rotation_across_x(theta,xyz_front);

%% side left camera
filename='20180810_150607_cam_side_left_lidar.bag';
bag_left = rosbag(filename);
%Select a specific topic.
bSel_lidar_left = select(bag_left,'Topic','/a2d2/20180810_150607_cam_side_left/lidar');
msg_lidar_left= readMessages(bSel_lidar_left,nb_msg);
ptcloud_left=msg_lidar_left{1,1}; %read one message
X=readField(ptcloud_left,'x');
Y=readField(ptcloud_left,'y');
Z=readField(ptcloud_left,'z');
xyz_left=[X Y Z];
theta=find_theta_x(-0.019,0.98,1,0);
xyz_left=translate_to_origin(0.65,0.58,0.94,xyz_left);
xyz_left=rotation_across_z(theta,xyz_left);
% theta=find_theta_y(-0.02,-0.009,1,0);
% xyz_left=rotation_across_x(theta,xyz_left);

%% side right camera
filename='20180810_150607_cam_side_right_lidar.bag';
bag_right = rosbag(filename);
%Select a specific topic.
bSel_lidar_right = select(bag_right,'Topic','/a2d2/20180810_150607_cam_side_right/lidar');
msg_lidar_right= readMessages(bSel_lidar_right,nb_msg);
ptcloud_right=msg_lidar_right{1,1}; %read one message
X=readField(ptcloud_right,'x');
Y=readField(ptcloud_right,'y');
Z=readField(ptcloud_right,'z');
xyz_right=[X Y Z];

theta=find_theta_x(-0.05,-0.98,1,0);
xyz_right=translate_to_origin(0.65,-0.58,0.94,xyz_right);
xyz_right=rotation_across_z(-theta,xyz_right);
% theta=find_theta_y(-0.05,0.01,1,0);
% xyz_right=rotation_across_x(theta,xyz_right);


%%
xyz=[xyz_rear;xyz_front;xyz_left;xyz_right]; % concatenate all points in the same frame
%%
pcobj = pointCloud(xyz);
lower = min([pcobj.XLimits pcobj.YLimits]);
upper = max([pcobj.XLimits pcobj.YLimits]);
  
xlimits = [lower upper];
ylimits = [lower upper];
zlimits = pcobj.ZLimits;
x = pi/180; 
R = [ cos(x) sin(x) 0 0
     -sin(x) cos(x) 0 0
      0         0   1 0
      0         0   0 1];

tform = affine3d(R);
player=pcplayer(xlimits,ylimits,zlimits);
for i = 1:360      
    ptcloud = pctransform(pcobj,tform);     
    view(player,ptcloud);     
end

%% usefull function

%this fonction is for translate points
function point= translate_to_origin(x,y,z,points)
l=length(points);
point=zeros(l,3);
for i=[1:l]
    point(i,1)=points(i,1)-x;
    point(i,2)=points(i,2)-y;
    point(i,3)=points(i,3)-z;
end
end

%this fonction rotate points with the angle tetha across z axis
function point =rotation_across_z(theta,points) %theta in radian
    
    l=length(points);
    point=zeros(l,3);
    for i=[1:l]
        point(i,1)=points(i,1)*cos(theta)-points(i,2)*sin(theta);
        point(i,2)= points(i,1)*sin(theta)+ points(i,2)*cos(theta);
        point(i,3)=points(i,3);
    end
end

%this fonction rotate points with the angle tetha across x axis
function point =rotation_across_x(theta,points) %theta in radian
    
    l=length(points);
    point=zeros(l,3);
    for i=[1:l]
        point(i,2)=points(i,2)*cos(theta)-points(i,3)*sin(theta);
        point(i,3)= points(i,2)*sin(theta)+ points(i,3)*cos(theta);
        point(i,1)=points(i,1);
    end
end

%This function calculate the angle theta between the objective frame and
%the current frame
% in enter we have x1 and y1 x and y coordonate of the x axis of the camera
function theta= find_theta_x(x1,y1,x,y)
theta=acos((x1*x+y1*y)/(x^2+y^2)); %retourn value between 0 ad pi
val_check=(y1*x-x1*y)/(x^2+y^2);
if sin(theta)~=val_check
    theta= - theta;
end
end

%This function calculate the angle theta between the objective frame and
%the current frame
% in enter we have x1 and y1 y and z coordonate of the y axis of the camera
% and y and z, coordonate of y axis of the vehicul
function theta= find_theta_y(y1,z1,y,z)
theta=acos((y1*y+z1*z)/(y^2+z^2)); %retourn value between 0 ad pi
val_check=(z1*y-y1*z)/(y^2+z^2);
if sin(theta)~=val_check
    theta= - theta;
end
end