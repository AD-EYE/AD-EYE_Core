function translate_to_origin(x,y,z,points)
l=length(points);
for i=[1:l]
    points(i,1)=points(i,1)-x;
    points(i,2)=points(i,2)-y;
    points(i,3)=points(i,3)-z;
end
end

function rotation_across_z(theta,points) %theta in radian
    
    l=length(points);
    for i=[1:l]
        points(i,1)=points(i,1)*cos(theta)-points(i,2)*sin(theta);
        points(i,2)= points(i,1)*sin(theta)+ points(i,2)*co(theta);
    end
end
