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



// Normal estimation
void set_normals(
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, 
  pcl::PointCloud<pcl::Normal>::Ptr normals,
  pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals
){

  pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
  pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
  tree->setInputCloud (cloud);
  n.setInputCloud (cloud);
  n.setSearchMethod (tree);
  n.setKSearch (20);
  n.compute (*normals);

  for(size_t i = 0; i < normals->size(); ++i){
    normals->points[i].normal_x *= -1;
    normals->points[i].normal_y *= -1;
    normals->points[i].normal_z *= -1;
  }

  pcl::concatenateFields (*cloud, *normals, *cloud_with_normals);
}



pcl::PolygonMesh greedy_surface_reconstruction(
  pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals
){

  // Initialize objects
  pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;
  pcl::PolygonMesh mesh;
  pcl::search::KdTree<pcl::PointNormal>::Ptr tree (new pcl::search::KdTree<pcl::PointNormal>);
  tree->setInputCloud (cloud_with_normals);

  // Set the maximum distance between connected points (maximum edge length)
  gp3.setSearchRadius (15000); // 15000 

  // Set typical values for the parameters
  gp3.setMu (2.9); // 2.9
  gp3.setMaximumNearestNeighbors (2000); //2000
  gp3.setMaximumSurfaceAngle(M_PI/5); // 90 degrees, M_PI/5
  gp3.setMinimumAngle(M_PI/180); // 1 degrees , M_PI/180
  gp3.setMaximumAngle(8*M_PI/9); // 160 degrees, 8*M_PI/9
  gp3.setNormalConsistency(false);
  gp3.setConsistentVertexOrdering(true);

  // Get result
  gp3.setInputCloud (cloud_with_normals);
  gp3.setSearchMethod (tree);
  gp3.reconstruct (mesh);

  return(mesh);
}

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


// voxel_grid_filter
// Input: pcl Point cloud to be filtered
// Output: pcl Point cloud of the filtered cloud
void voxel_grid_filter(
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, 
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_voxel 
  ){
    float lf = 0.5f;
    pcl::VoxelGrid<pcl::PointXYZ> sor;
    sor.setInputCloud (cloud);
    sor.setLeafSize (lf,lf,lf);
    sor.filter (*cloud_voxel);
  }

/*
Main
*/
int
  main (int argc, const char** argv)
{
  
  args::ArgumentParser p("Initiating argparser");
  
  //Define input arguments that can be given as flags, pcd file and output required
  args::ValueFlag<std::string> file_arg(p, "filename", "Path to PCD file", {'f', "filename"}, "Please enter a valid PCD file path.");
  args::ValueFlag<std::string> output_arg(p, "output", "Path and name of output file without extension", {'o', "output"});
  args::ValueFlag<int> size_arg(p, "chunk_size", "Size of chunk side", {'s', "size"}, 50);
  args::Flag voxel_arg(p, "voxel", "Run voxel grid filter", {'v',"voxel"});
  args::Flag save_pcd_arg(p, "save_pcd", "Save filtered/cut pcd files before meshing", {'p',"pcd"});


  // Check if input args are OK
  try
    {
      p.ParseCLI(argc, argv);
    }
    catch (args::Completion &e)
    {
      std::cout << e.what();
    }
  // Fetch input args and save as strings
  std::string pcd_filename =args::get(file_arg);
  std::string output_filename= args::get(output_arg);
  
  // Setup pcl cloud objects TODO? Remove some clouds and re use with overwrites
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_original (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_inlier (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_voxel (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal>);
  pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals (new pcl::PointCloud<pcl::PointNormal>);
  pcl::PassThrough<pcl::PointXYZ> pass_y;
  pcl::PassThrough<pcl::PointXYZ> pass_x;
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_slice (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_square (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointNormal>::Ptr cloud_chunk_with_normals (new pcl::PointCloud<pcl::PointNormal>);

  //Load PCD file    
  set_pcd_file(cloud_original, pcd_filename); 
  size_t num_points_cloud = cloud_original->size();
  cout << "Cloud loaded! Number of points: " << num_points_cloud << "\n" << std::endl;
  
  //Remove statistical outliers
  cout << "Starting statistical outlier remover..." << std::endl; 
  remove_outlier(cloud_original, cloud_inlier);
  size_t num_points_cloud_inlier = cloud_inlier->size();
  cout << "Finished statistical outlier remover! Number of points: " << num_points_cloud_inlier << "\n" <<std::endl;
  
  //Run voxel filter if voxel flag is used
  if(bool{voxel_arg}) {
    cout << "Starting voxel grid filter..." << std::endl; 
    voxel_grid_filter(cloud_inlier, cloud_inlier);
    size_t num_points_cloud_voxel = cloud_inlier->size();
    cout << "Finished voxel grid filtering! Number of points: " << num_points_cloud_voxel << "\n" << std::endl; 
    //Saves a filtered pcd if save_pcd flag is used
    if(bool{save_pcd_arg}){
      std::string voxel_pcd_file = output_filename +"voxel_filtered.pcd";
      pcl::io::savePCDFile(voxel_pcd_file, *cloud_inlier);
      cout << "Voxel filtered pcd saved as: " << voxel_pcd_file << "\n" << std::endl;
    }
    
  }
  else {
    cout << "-------------------------------------" << std::endl; 
    cout << "Generating of mesh files starting... " << std::endl; 
    cout << "-------------------------------------" << std::endl;
    
    // Find min and max points for the point cloud
    pcl::PointXYZ minPt, maxPt;
    pcl::getMinMax3D (*cloud_inlier, minPt, maxPt);
    cout << "Point cloud coordinates:" << std::endl;
    cout << "min x: " << minPt.x << ", max_x: " << maxPt.x << std::endl;
    cout << "min y: " << minPt.y << ", max_y: " << maxPt.y << std::endl;
    
    //Set the size of square side, default 50 (generates 50x50 chunks)
    int cut_size = args::get(size_arg);
    cout << "Chunk size: " << cut_size << "x" << cut_size << std::endl;
    //Numbers for output file numbering
    int x_nr = 0;
    int y_nr = 0;

    //Set pass through boundaries for y and x
    int y_lower = minPt.y;
    int y_upper = y_lower + cut_size;
    int x_lower = minPt.x;
    int x_upper = x_lower + cut_size;

    while(y_lower < maxPt.y){
      //Slice the cloud in y using pass through
      pass_y.setInputCloud (cloud_inlier);
      pass_y.setFilterFieldName ("y");
      pass_y.setFilterLimits (y_lower, y_upper);
      pass_y.filter (*cloud_slice);
      //Setup pass through for x 
      pass_x.setInputCloud(cloud_slice);
      pass_x.setFilterFieldName ("x");
      

      if(cloud_slice->size()){
        
        while(x_lower < maxPt.x){
          //Slice the cloud in x using pass through
          pass_x.setFilterLimits (x_lower, x_upper);
          pass_x.filter (*cloud_square);
      
          if(cloud_square->size()){
            if(bool{save_pcd_arg}){
              //Save a smaller pcd of the sqaure cloud
              std::string pcd_filename= output_filename + "_" + std::to_string(y_nr) + "_" + std::to_string(x_nr) + ".pcd";
              pcl::io::savePCDFile(pcd_filename, *cloud_square);
              cout << "PCD saved as: " << pcd_filename<< "\n" << std::endl;
            }
            //Generate normals, mesh, and save mesh
            cout << "Setting normals..." << std::endl;
            set_normals(cloud_square, normals, cloud_chunk_with_normals);
            
            cout << "Meshing..." << std::endl; 
            pcl::PolygonMesh mesh = greedy_surface_reconstruction(cloud_chunk_with_normals);

            std::string out_file = output_filename + "_" + std::to_string(y_nr) + "_" + std::to_string(x_nr) + ".stl";
            pcl::io::savePolygonFileSTL(out_file, mesh);
            cout << "Mesh generated and saved as: " << out_file<< "\n" << std::endl;
          }
          x_lower = x_upper;
          x_upper += cut_size;
          ++x_nr;
        }
        //Reset x boundaries, update y boundaries
        x_lower = minPt.x;
        x_upper = x_lower + cut_size;
        x_nr = 0;
        y_lower = y_upper;
        y_upper += cut_size;
        ++y_nr;  
      }
    }  
    cout << "All meshes generated." << std::endl;
    cout << "---------------------" << std::endl;
  }
    
  return (0);
}