%first step detect straight road and crossing
%we will used cartesian data extract with the matlab file: extract_GPS_data


%know if it is a straight road or crossing
function type=road_type(x1,x2,x3,y1,y2,y3)
    m1=(y2-y1)/(x2-x1);
    m2=(y3-y2)/(x3-x2);
    if m1==m2
        type='straight road';
    else
        type='crossing';
    end
end

function add_straight_raod(length,x0,y0,z0)
end

function add_crossing()
end

function detect_road(coord)
    max=length(coord);
    i=1;
    while i <=(max-2) %-2 becaus we use thrid coord
        x1=coord(i,1);
        x2=coord(i+1,1);
        x3=coord(i+2,1);
        y1=coord(i,2);
        y2=coord(i+1,2);
        y3=coord(i+2,2);
        long_str=0
        if detect_road_type(x1,x2,x3,y1,y2,y3)=='straight road'
            xo=x1;
            yo=y1;
            z0=coord(i,3);
            while detect_road_type(x1,x2,x3,y1,y2,y3)=='straight road'
                long_str=sqrt((x3-x1)^2+(y3-y1)^2)+long_str;
                x1=x2;y1=y2;x2=x3;y2=y3;
                i=i+1;
                x3=coord(i+2,1);y3=coord(i+2,2);
            end
            add_straight_road(long_str,x0,y0,z0);
            i=i+1;
        else
            add_crossing;
        end
    end
    
        
end
