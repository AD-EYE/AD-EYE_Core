% add roads to pex file
% create an experiment
%prescan.api.experiment.Experiment;

% extract gps data from file bus_signal
points_data=GPS_data('20180810150607_bus_signals');
% now we have a matrix with x,y and z coordinates

%we will define point for add bezier road or flex road 
data=suppr_duplicates(points_data);
len=length(data);
i=1;
while i<(len-1)
    x1=data(i,1);
    x2=data(i+1,1);
    x3=data(i+2,1);
    y1=data(i,2);
    y2=data(i+1,2);
    y3=data(i+2,2);
    z1=data(i,3);
    z2=data(i+1,2);
    z3=data(i+2,3);

    position.x=x1;
    position.y=y1;
    position.z=z1;
% %     egal=points_egal_test(x1,y1,z1,x2,y2,z2,x3,y3,z3);
%     if x1==x2 && y1==y2 && z1==z2
%         i=i+1;
%         disp('3 points equal');
%     elseif x2==x3 && y2==y3 && z2==z3
%         orient=orientation(x1,y1,x2,y2);
%         delta=calculate_delta(x1,y1,z1,x2,y2,z2);
%         heading=0;
%         tension.entry=10;
%         tension.exit=10;
%         add_bezierRoad(position,orient,heading,delta,tension);
%         i=i+2;
%     else
        orient=orientation(x1,y1,x2,y2);
        delta=calculate_delta(x1,y1,z1,x2,y2,z2);
        heading=relative_heading(x1,y1,x2,y2,x3,y3);
        tension.entry=10;
        tension.exit=10;
        add_bezierRoad(position,orient,heading,delta,tension);
        i=i+1;
end
% end
if i==len-1
    x1=points_data(i,1);
    x2=points_data(i+1,1);
    y1=points_data(i,2);
    y2=points_data(i+1,2);
    z1=points_data(i,3);
    z2=points_data(i+1,2);
%     if x1==x2 && y1==y2 && z1==z2
%         i=i+1;
%     else
        orient=orientation(x1,y1,x2,y2);
        delta=calculate_delta(x1,y1,z1,x2,y2,z2);
        heading=0;
        tension.entry=10;
        tension.exit=10;
        add_bezierRoad(position,orient,heading,delta,tension);
% 
end
%end
%or=orientation(points_data(1,1),points_data(1,2),points_data(2,1),points_data(2,2))
%he=relative_heading(points_data(1,1),points_data(1,2),points_data(2,1),points_data(2,2))

function dist=distance(x1,y1,x2,y2)
    x=(x2-x1)^2;
    y=(y2-y1)^2;
    dist=sqrt(x+y); 
end
function orient=orientation(x1,y1,x2,y2)
    dist=distance(x1,y1,x2,y2);
     orient=asin( (y2-y1)/dist); %result in rad
end

function delta=calculate_delta(x1,y1,z1,x3,y3,z3)
    delta.x=x3-x1;
    delta.y=y3-y1;
    delta.z=z3-z1;
end

function heading=relative_heading(x1,y1,x2,y2,x3,y3)
%     alpha=orientation(x1,y1,x2,y2);
%     dist=distance(x2,y2,x3,y3);
%     beta=asin( (x3-x2)/dist);
%     heading=pi/2-beta-alpha;
    a=distance(x1,y1,x2,y2);
    b=distance(x2,y2,x3,y3);
    c=distance(x1,y1,x3,y3);
    d=(a^2+b^2-c^2)/(2*a*b);
    heading=acos(d);
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
