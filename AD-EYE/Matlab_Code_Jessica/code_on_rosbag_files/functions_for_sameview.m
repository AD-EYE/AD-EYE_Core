point=[0 -1 0;0 1 0;0 1 0];
translate_to_origin(1,0,0,point)

function point= translate_to_origin(x,y,z,points)
l=length(points);
point=zera(l,3);
for i=[1:l]
    point(i,1)=points(i,1)-x;
    point(i,2)=points(i,2)-y;
    point(i,3)=points(i,3)-z;
end
end

function point =rotation_across_z(theta,points) %theta in radian
    
    l=length(points);
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

    
