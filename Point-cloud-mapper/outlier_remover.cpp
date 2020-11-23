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

void remove_outlier(
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_inlier
  ){

    // Create the filtering object
    pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
    sor.setInputCloud (cloud);
    sor.setMeanK (20);
    sor.setStddevMulThresh (1.0);
    sor.filter (*cloud_inlier);
}


int
  main (int argc, const char** argv)
{
    args::ArgumentParser p("Initiating argparser");
  
    //Define input arguments that can be given as flags, pcd file and output required
    args::ValueFlag<std::string> file_arg(p, "filename", "Path to PCD file", {'f', "filename"});
    args::ValueFlag<std::string> output_arg(p, "output", "Path and name of output file without extension", {'o', "output"});

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_original (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_inlier (new pcl::PointCloud<pcl::PointXYZ>);

    try
    {
      p.ParseCLI(argc, argv);
    }
    catch (args::Completion &e)
    {
      std::cout << e.what();
    }
    
    std::string pcd_filename =args::get(file_arg);
    std::string output_filename= args::get(output_arg);  

    //Load PCD file    
    set_pcd_file(cloud_original, pcd_filename); 
    size_t num_points_cloud = cloud_original->size();
    cout << "Cloud loaded! Number of points: " << num_points_cloud << "\n" << std::endl;
  
    //Remove statistical outliers
    cout << "Starting statistical outlier remover..." << std::endl; 
    remove_outlier(cloud_original, cloud_inlier);
    size_t num_points_cloud_inlier = cloud_inlier->size();
    cout << "Finished statistical outlier remover! Number of points: " << num_points_cloud_inlier << "\n" <<std::endl;

    std::string pcd_file = output_filename +".pcd";
    pcl::io::savePCDFile(pcd_file, *cloud_inlier);

    return (0);
}