#include <iostream>
#include <pcl/common/common.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/search/kdtree.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/surface/grid_projection.h>
#include <pcl/point_types.h>
#include <pcl/surface/mls.h>
#include <pcl/surface/poisson.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/filters/passthrough.h>
#include <pcl/surface/processing.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <stdlib.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/surface/gp3.h>
#include <pcl/io/vtk_io.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/surface/organized_fast_mesh.h>
#include <pcl/surface/marching_cubes_hoppe.h>
#include <boost/thread/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include "args.hxx"

void set_pcd_file(
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,
  std::string file_name
  ){
     // Fill in the cloud data
    pcl::PCDReader reader;
    cout << "Loading pcd file: " << file_name << "\n" << std::endl;
    
    if (reader.read<pcl::PointXYZ> (file_name, *cloud) < 0) {
        cerr << "Cant read file. Closing program ..." << std::endl;
        exit(1);
    }
}

int
  main (int argc, const char** argv)
{
    args::ArgumentParser p("Initiating argparser");
  
    //Define input arguments that can be given as flags, pcd file and output required
    args::ValueFlag<std::string> file_arg(p, "filename", "Path to PCD file", {'f', "filename"});

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    
    try
    {
      p.ParseCLI(argc, argv);
    }
    catch (args::Completion &e)
    {
      std::cout << e.what();
    }

    std::string pcd_filename =args::get(file_arg);  

    //Load PCD file    
    set_pcd_file(cloud, pcd_filename); 

    pcl::PointXYZ minPt, maxPt;
    pcl::getMinMax3D (*cloud, minPt, maxPt);

    cout << "Corners: " << std::endl;
    cout << "x: "<< minPt.x << ", y: "<< minPt.y << std::endl;
    cout << "x: "<< minPt.x << ", y: "<< maxPt.y << std::endl;
    cout << "x: "<< maxPt.x << ", y: "<< minPt.y << std::endl;
    cout << "x: "<< maxPt.x << ", y: "<< maxPt.y << std::endl;

}
