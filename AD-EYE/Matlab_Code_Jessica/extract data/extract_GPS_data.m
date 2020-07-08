%use 'pose' file to extract GPS data

%-------------------------------------------------------------------------
%__________command to extract adn convert____________________________

%on gps_data we have matrix with on line latitude longitude and altitude
gps_data=recup_data; %recuperation GPS data
%cart_data= basic_conversion(gps_data); %conversion GPS data into cartesian data
cart_data= Mercato_conversion(gps_data); %conversion with Mercato method
close; %close all figures
plot(cart_data(:,1),cart_data(:,2)); %draw cartesian point
%plot3(cart_data(:,1),cart_data(:,2),cart_data(:,3));


%-------------------------------------------------------------------
%______________________functions____________________________________

%with this fonction we separate numbers but the function str2num can do
%this and transform string to integer. So this function is not necessary.
function vect_val = suppr_comma(line_of_val)
    max=length(line_of_val); 
    count=1; %initialisation. the count will serve to now length of nombers
    vect=[];
    for i=[1:max] % we check all caracters
        if line_of_val(i)== ',' %we search the split
            vect=[vect line_of_val(count:(i-1))];
            count=i+1;
        end
    end
    vect_val=vect;
end

%with this function we finally have just 3 number. 1st: latitude, 2nd:
%longitude, 3rd: altitude. In parameter we have a line of number come from
%data file
function val_gps_data= suppr_useless_numb(val_without_comma)
    val_gps_data= val_without_comma(2:4);
end

%we this function we fallow all line of the file and put the matrix the gps
%data. 
function gps_data= recup_data
%insert below the path of the file where is GPS data
  Path_to_file='C:\Users\adeye\Desktop\rec1\data\AutoDrive\recording\2019_9_10\rec1\gnss\pose.txt';
  file=fopen(Path_to_file);
  data=[];
  vect=[];
  vect_data=[];
  while feof(file) == 0 %we cross al file
      tline=fgetl(file); %extract the line
      vect=str2num(tline); %convert string into number
      vect=suppr_useless_numb(vect);% suppress first and last numbers which are not use
      data=[data;vect];  %add data in a new line of the matrix
  end
  gps_data=data;
end


% first method: we suppose the Earth is round and we use the average
% radius
function Cartesian_data= basic_conversion (GPS_data)
    R=6371.009; %km so the results ar in km
    x=0;
    y=0;
    vect=[1:3];
    cart=[];
    for i=[1:length(GPS_data)] %length suppose there is more line than column
        x=R*cos(GPS_data(i,1))*cos(GPS_data(i,2));
        y=R*cos(GPS_data(i,1))*sin(GPS_data(i,2));
        vect=[x y GPS_data(i,3)];
        cart=[cart;vect]; %add line with cartesian data
    end
    Cartesian_data=cart;
end

%second method: pseudo-Mercato conversion. It is the most use methode to
%have a plan
function Cartesian_data= Mercato_conversion (GPS_data)
    a= 6378137.0; %m so results are in m
    x=0;    %initialisation
    y=0;
    vect=[];
    coord=[];
    for i=[1:length(GPS_data)] %we cross alle line of the matrix GPS_data
        x=a*GPS_data(i,2);
        y=a*0.5*log((1+sin(GPS_data(i,1)))/(1-sin(GPS_data(i,1))));
        vect=[x y GPS_data(i,3)];
        coord=[coord;vect]; %add line with cartesian data
    end
    Cartesian_data=coord;
end
