# Point-cloud-mapper

Pre-req: 

## Installation of dependencies: 

Run the following commands: 

sudo apt install libpcl-dev

sudo apt install libopenni2-dev 

sudo apt install libproj-dev

sudo ln -s /usr/lib/x86_64-linux-gnu/libvtkCommonCore-6.2.so /usr/lib/libvtkproj4.so

To compile and build:  

mkdir build && cd build && cmake .. && make 


## How to run:
./pcd_to_sqaure_mesh -f [filename] -o [output_name] -s [size] --voxel --pcd

Flags:
-f [filename] , required, PCD file path/name
-o [output_name] , required, output path/name
-s [size] , optional, default 50, size of each chunk 
--voxel , optional, run voxel grid dilation !!! Need to swap input to normal generation
--pcd , optional, saves pcds after voxel and/or cutting 

Filepath example: /home/vhane/Point-cloud-mapper/pcds/autoware-car-first-strongest.pcd

TODO: Gather all the functions in one file and import to other scripts instead, to allow smaller scripts to utilize the functions without copy pasting (not a prio)