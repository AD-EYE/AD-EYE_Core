% With this function, we extract gps data from the bus_signals rosbag file,
% and put it on a matrix.After we convert it into cartesian data The matrix have three columns. The 1st is for
% latiture, the 2nd for longitude and the 3rd for altitude. 
% in enter we have the name of the file without the extension. For example:
% '20180810150607_bus_signals'


function cart_data=GPS_data(filename)

bag_bus = rosbag(strcat(filename,'.bag'));
%%
%Select a specific topic: latitude degree value.
bSel_lat_deg_val = select(bag_bus,'Topic',strcat('/a2d2/',filename,'/latitude_degree/value'));
msg_lat_deg_val= readMessages(bSel_lat_deg_val,1:25);


%%
%Select a specific topic: latitude direction value.
bSel_lat_dir_val = select(bag_bus,'Topic',strcat('/a2d2/',filename,'/latitude_direction/value'));
msg_lat_dir_val= readMessages(bSel_lat_dir_val,1:25);


%%
%Select a specific topic: longitude degree value.
bSel_long_deg_val = select(bag_bus,'Topic',strcat('/a2d2/',filename,'/longitude_degree/value'));
msg_long_deg_val= readMessages(bSel_long_deg_val,1:25);


%%
%Select a specific topic: longitude direction value.
bSel_long_dir_val = select(bag_bus,'Topic',strcat('/a2d2/',filename,'/longitude_direction/value'));
msg_long_dir_val= readMessages(bSel_long_dir_val,1:25);

%%
altitude= zeros(25,1);
latitude= read_message(msg_lat_deg_val,msg_lat_dir_val);
longitude= read_message(msg_long_deg_val,msg_long_dir_val);
gps_data=[latitude longitude altitude];
mercato_data=Mercator_conversion(gps_data);
cart_data=center_origin_on_first_point(mercato_data);

%sub function to read data on messages
function array =read_message(messages,direction)
    size= length(messages);
    mat=zeros(size,1);
    for i=1:size
        coord= messages{i,1}.Data;
        orientation= direction{i,1}.Data;
        if orientation==0
            mat(i,1)= coord;
        else
            mat(i,1)=-coord;
        end
    end
    array=mat;
end

function Cartesian_data= Mercator_conversion (GPS_data)
    a= 6378137.0; %[meter] so results are in meter
    x=0;    %initialisation
    y=0;
    vect=[];
    coord=[];
    for i=[1:length(GPS_data)] %we cross all line of the matrix GPS_data
        x=a*GPS_data(i,2);
        y=a*0.5*log((1+sin(GPS_data(i,1)))/(1-sin(GPS_data(i,1))));
        vect=[x y GPS_data(i,3)];
        coord=[coord;vect]; %add line with cartesian data
    end
    Cartesian_data=coord;
end

function data_to_origin=center_origin_on_first_point(cart_data)
    X0=cart_data(1,1);
    Y0=cart_data(1,2);
    Z0=cart_data(1,3);
    le=length(cart_data);
    data_to_origin=zeros(le,3);
    for i=2:le
        data_to_origin(i,1)=cart_data(i,1)-X0;
        data_to_origin(i,2)=cart_data(i,2)-Y0;
        data_to_origin(i,3)=cart_data(i,3)-Z0;
    end
end

end
