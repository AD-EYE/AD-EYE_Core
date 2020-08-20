%% 
% this scipt extract gps data from rosbag file name bus. After add bezier roads to
% pex file of experiment present on the folder of the scipt
% if there is no experiment, the script don't work
% To run the script you just need to modify the name of the file at line 9
%% 

% extract gps data from file bus_signal
points_data=GPS_data('20180810150607_bus_signals');
% now we have a matrix with x,y and z coordinates

%%
%we will define point for add bezier road or flex road. here is bezier road
data=suppr_duplicates(points_data);
len=length(data);
i=1;
xpName = prescan.experiment.getDefaultFilename();
nbBezier=detect_nb_road('BezierRoad',xpName);

%%
while i<(len-1)
    x1=data(i,1);
    x2=data(i+1,1);
    x3=data(i+2,1);
    y1=data(i,2);
    y2=data(i+1,2);
    y3=data(i+2,2);
    z1=data(i,3);
    z2=data(i+1,3);
    z3=data(i+2,3);

    position.x=x1;
    position.y=y1;
    position.z=z1;
    orient=orientation(x1,y1,x2,y2);
    delta=calculate_delta(x1,y1,z1,x2,y2,z2);
    heading=pi-relative_heading(x1,y1,x2,y2,x3,y3);
    tension.entry=50;
    tension.exit=50;
    add_bezierRoad(position,orient,heading,delta,tension);
    if i>1
        add_connection(strcat('CurvedRoad_',num2str(nbBezier)),strcat('CurvedRoad_',num2str(nbBezier+1)),1,0);
    end
    i=i+1;
    nbBezier=nbBezier+1;
    if i==(len-1)
        position.x=x2;
        position.y=y2;
        position.z=z2;
        orient=orientation(x2,y2,x3,y3);
        delta=calculate_delta(x2,y2,z2,x3,y3,z3);
        heading=0;
        tension.entry=50;
        tension.exit=20;
        add_bezierRoad(position,orient,heading,delta,tension);
        add_connection(strcat('CurvedRoad_',num2str(nbBezier)),strcat('CurvedRoad_',num2str(nbBezier+1)),1,0);
    end
%     
end



function dist=distance(x1,y1,x2,y2)
    x=(x2-x1)^2;
    y=(y2-y1)^2;
    dist=sqrt(x+y); 
end
function orient=orientation(x1,y1,x2,y2)
    a=distance(x1,y1,x2,y2);
    b=distance(x1,y1,x2,y1);
    if y2<y1 %&& x2>x1
        orient=pi+acos(b/a);
    elseif x2<x1
        orient=pi-acos(b/a);
    else
        orient=acos(b/a); %result in rad
    end
end

function delta=calculate_delta(x1,y1,z1,x2,y2,z2)
    delta.x=distance(x1,y1,x2,y2);
    delta.y=0;
    delta.z=z2-z1;
end 

function heading=relative_heading(x1,y1,x2,y2,x3,y3)
    a=distance(x1,y1,x2,y2);
    b=distance(x2,y2,x3,y3);
    c=distance(x1,y1,x3,y3); 
    d=(a^2+b^2-c^2)/(2*a*b);
    heading=-acos(d);
end
function data=suppr_duplicates(gps_data)
    len=length(gps_data);
    current=gps_data(1,:);
    data=gps_data(1,:);
    for i=2:len
        x1=current(1);
        y1=current(2);
        z1=current(3);
        x2=gps_data(i,1);
        y2=gps_data(i,2);
        z2=gps_data(i,3);
        
        if x1==x2 && y1==y2 && z1==z2
        else
            data=[data; x2 y2 z2];
            current=[x2 y2 z2];
        end
    end
end
