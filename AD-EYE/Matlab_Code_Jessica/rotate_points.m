%we rotate points around y axis

function rotate_points(angle,points)
   len=length(points);
   for i=1:len
       x=points(i,1);
       y=points(i,2);
       z=points(i,3);
       points(i,1)= x*cos(angle)+z*sin(angle);
       points(i,2)=y;
       points(i,3)=z*cos(angle)-x*sin(angle);
   end
   
end
