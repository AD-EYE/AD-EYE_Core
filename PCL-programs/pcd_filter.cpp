#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include "args.hxx"
int main (int argc, char ** argv)
{
    args::ArgumentParser p("Initiating argparser");
  
    //Define input arguments that can be given as flags, pcd file and output required
    args::ValueFlag<std::string> file_arg(p, "filename", "Path to PCD file", {'f', "filename"}, "Please enter a valid PCD file path.");
    


    // Check if input args are OK
    try
    {
      p.ParseCLI(argc, argv);
    }
    catch (args::Completion &e)
    {
      std::cout << e.what();
    }

    std::string pcd_filename =args::get(file_arg);


    pcl::PCLPointCloud2::Ptr cloud (new pcl::PCLPointCloud2 ());
    pcl::PCLPointCloud2::Ptr cloud_filtered (new pcl::PCLPointCloud2 ());

    pcl::PCDReader reader;
    reader.read(pcd_filename , *cloud);

    pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
    sor.setInputCloud(cloud);
    sor.setLeafSize(0.1f,0.1f,0.1f);
    sor.filter(*cloud_filtered);

     std::string output_file = pcd_filename+"_F.pcd";
    pcl::PCDWriter writer;
    writer.write(output_file, *cloud_filtered, Eigen::Vector4f::Zero() , Eigen::Quaternionf::Identity (), false);

    return(0);
}