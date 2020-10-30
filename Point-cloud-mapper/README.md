# Point-cloud-mapper

Pre-req: 

Installation: 

Run the following commands: 

sudo apt install libpcl-dev

sudo apt install libopenni2-dev 

sudo apt install libproj-dev

sudo ln -s /usr/lib/x86_64-linux-gnu/libvtkCommonCore-6.2.so /usr/lib/libvtkproj4.so

To compile and build:  

mkdir build && cd build && cmake .. && make 


Filepath /home/vhane/Point-cloud-mapper/pcds/autoware-car-first-strongest.pcd

How to run:
./main -f [filename] -o [output_name] --voxel --view
Flags:
-f [filename] , required, PCD file path/name
-o [output_name] , optional, default mesh.obj, output path/name
--voxel , optional, run voxel grid dilation !!! Need to swap input to normal generation
--view , optional, launch viewers after mesh generation


Todo: 

* Load a file using flags [DONE]
* Load into point cloud [DONE?]
* Apply filter  [POSSIBLE, IMPROVE?]
* Apply segementation 
* Render in window [DONE]
* Calculate number outliners/total_points [DONE]
* Create mesh [DONE]
