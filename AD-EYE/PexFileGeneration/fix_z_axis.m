function fix_z_axis(ptcloud)
    minz=min(ptcloud.Location(:,3));
    maxz=max(ptcloud.Location(:,3));
    point_max=find_point(maxz,ptcloud.location);
    point_min=find_point(minz,ptcloud.location);
    point_z0=point_min(1),point_min(2),point_max(3)];
    angle=calculate_angle(point_z0,point_min,point_max);
    
    rotate_points(angle,ptcloud.Location);
    
    function point=find_point(z,points)
        len=length(points);
        for i=1:len
            if points(i,3)==z
                point=points(i,:);
            end
        end
    end
    function angle= calculate_angle(point1,point2,point3)
        a=calculate_distance(point1,point2);
        b=calculate_distance(point2,point3);
        c=calculate_distance(point1,point3);
        d=a^2+b^2-c^2;
        angle=acos(d/(2*a^2*b^2));
    end

    function distance=calculate_distance(point1,point2) %on point there are x,y and z coordinates but we use only x and z
        a=(point2(1)-point1(1))^2;
        b=(point2(3)-point2(3))^2;
        distance=sqrt(a+b);
    end

end
