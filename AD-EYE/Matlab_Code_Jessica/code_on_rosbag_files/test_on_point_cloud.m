%% side left camera
filename='20180810_150607_cam_side_right_lidar.bag';
bag_left = rosbag(filename);
%Select a specific topic.
bSel_lidar_left = select(bag_left,'Topic','/a2d2/20180810_150607_cam_side_right/lidar');
msg_lidar_left= readMessages(bSel_lidar_left,140:145);
ptcloud_l=msg_lidar_left{1,1}; %read one message
azimuth=readField(ptcloud_l,'pcloud_attr.azimuth');
X=readField(ptcloud_l,'x');pcobj
Y=readField(ptcloud_l,'y');
Z=readField(ptcloud_l,'z');
xyz=[X Y Z];  
theta=find_theta_x(-0.05,-0.98,1,0);
xyz=translate_to_origin(0.65,-0.58,0.94,xyz);
xyz=rotation_across_z(theta,xyz);
theta=find_theta_y(-0.06,0.01,1,0);
xyz=rotation_across_x(theta,xyz);
% 20180810_150607_cam_side_left_camera.bag
% 20180810_150607_cam_side_left_lidar.bag
% 20180810150607_bus_signals.bag
% 20180810150607_bus_signals_tf.bag
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
% and x and y, coordonate of x axis of the vehicul
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
