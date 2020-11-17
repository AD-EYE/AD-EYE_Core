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
#include <args.hxx>




/*
TODO: 

  1) Check out arg parsers.
    1.1) Are they implementable in C++? yes
    1.2) Are they implementable in our code? yes
  2) Input. 
    2.1) What are the main/important input parameters? file, output, mesh method, viewer, 
    2.2) How does the input method for these look like? (flags/optional arguments?)
  3) Rename poisson file to something more fitting.
  4) Create focused file that only uses greedy triangulation and other useful functions.
  5) Thorough code commenting.

*/


//https://github.com/atduskgreg/pcl-poisson-example/blob/master/poisson_recon.cpp


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


pcl::PolygonMesh poisson_surface_recon(
    pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals
){
 
  pcl::Poisson<pcl::PointNormal> poisson;
  pcl::PolygonMesh mesh;
  poisson.setDepth(10);
  poisson.setInputCloud(cloud_with_normals);
  //poisson.setMinDepth(8); 
  poisson.setOutputPolygons(true);
  //poisson.setScale(0.8);
  poisson.setSamplesPerNode(10);
  poisson.reconstruct(mesh);

  return(mesh); 
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

// TODO: Rename to voxel filter
// voxel_grid_dilation 
// Input: 
// Output: 
void voxel_grid_dilation(
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
  
  args::ArgumentParser p("Testing argparser");
  
  //Define input arguments 
  args::ValueFlag<std::string> file_arg(p, "filename", "Path to PCD file", {'f', "filename"}, "Please enter a valid PCD file path.");
  args::ValueFlag<std::string> output_arg(p, "output", "Path and name of output file", {'o', "output"}, "mesh");
  //--------------- SET ABOVE PARAMS AS REQ AND BELOW NOT REQ ------------------------
  args::Flag voxel_arg(p, "voxel", "Run voxel grid dilation", {'x',"voxel"});
  args::Flag view_arg(p, "view", "Launch viewer", {'v',"view"});

  // Check input args OK
  try
    {
        p.ParseCLI(argc, argv);
    }
    catch (args::Completion &e)
    {
        std::cout << e.what();
    }
  // Fetch input args
  std::string pcd_filename =args::get(file_arg);
  std::string output_filename= args::get(output_arg);
  
  // Setup pcl clouds
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_original (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_inlier (new pcl::PointCloud<pcl::PointXYZ>);

  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_voxel (new pcl::PointCloud<pcl::PointXYZ>);

  pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal>);
  pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals (new pcl::PointCloud<pcl::PointNormal>);
  
  //Load PCD file    
  set_pcd_file(cloud_original, pcd_filename); 

  size_t num_points_cloud = cloud_original->size();
  cout << "Cloud loaded! Number of points: " << num_points_cloud << "\n" << std::endl;
  
  cout << "Starting statistical outlier remover..." << std::endl; 
  remove_outlier(cloud_original, cloud_inlier);
  size_t num_points_cloud_inlier = cloud_inlier->size();
  cout << "Finished statistical outlier remover! Number of points: " << num_points_cloud_inlier << "\n" <<std::endl;
  
  if(bool{voxel_arg}) {
    cout << "------------------------------------------" << std::endl; 
    cout << "Generating mesh using voxel grid dilation " << std::endl; 
    cout << "------------------------------------------" << std::endl; 
    cout << "Starting voxel grid dilation" << std::endl; 
    voxel_grid_dilation(cloud_inlier, cloud_voxel);
    size_t num_points_cloud_voxel = cloud_voxel->size();
    cout << "Finished voxel grid dilation! Number of points: " << num_points_cloud_voxel << "\n" << std::endl; 

    //cloud_inlier
    cout << "Setting normals" << std::endl; 
    set_normals(cloud_voxel, normals, cloud_with_normals);
    cout << "Done with normals \n" << std::endl; 

  }
  else {
    cout << "---------------" << std::endl; 
    cout << "Generating mesh files " << std::endl; 
    cout << "----------------" << std::endl;
    //-----------------------TEST-----------------------
    // FIND MAX/MIN PT AND CALCULATE THÉ LENGHT
    pcl::PointXYZ minPt, maxPt;
    pcl::getMinMax3D (*cloud_inlier, minPt, maxPt);
    int max_x=maxPt.x;
    int max_y=maxPt.y;
    cout << "min x: " << minPt.x << ", max_x: " << maxPt.x << std::endl;
    cout << "min y: " << minPt.y << ", max_y: " << maxPt.y << std::endl;
    int x_lower = minPt.x;
    int cut_size = 50; //TODO: Add in argparser
    int x_upper =  x_lower + cut_size;
    int y_lower = minPt.y;
    int y_upper =  y_lower + cut_size;

    int file_nr = 0;

    pcl::PassThrough<pcl::PointXYZ> pass;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_slice (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_square (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointNormal>::Ptr cloud_chunk_with_normals (new pcl::PointCloud<pcl::PointNormal>);
    pass.setInputCloud (cloud_inlier);
    // TEMP IF FOR TEST
    if(file_nr==0){
      
      while(y_lower < y_max){
        pass.setFilterFieldName ("y");
        pass.setFilterLimits (y_lower, y_upper);
        pass.filter (*cloud_slice);
        pass.setFilterFieldName ("x");
        pass.setInputCloud(cloud_slice);
        if(cloud_slice->size()){
           while(x_lower < max_x){
          
          pass.setFilterLimits (x_lower, x_upper);
          pass.filter (*cloud_square);
          
          if(cloud_square->size()){
            cout << "Setting normals..." << std::endl;
            set_normals(cloud_square, normals, cloud_chunk_with_normals);

            std::string out_file =output_filename+ std::to_string(file_nr) +".stl";

            cout << "Meshing..." << std::endl; 
            pcl::PolygonMesh mesh = greedy_surface_reconstruction(cloud_chunk_with_normals);
            pcl::io::savePolygonFileSTL(out_file, mesh);
            cout << "Mesh generated and saved as: " << out_file<< "\n" << std::endl;
          }
          x_lower=x_upper;
          x_upper += cut_size;
          ++file_nr;
        }
        y_lower=y_upper;
        y_upper += cut_size;
      }
    }
       
      cout << "All meshes generated." << std::endl;
      cout << "---------------------" << std::endl;
    }
    }
    //------------------------TEST END --------------

    // cout << "Setting normals" << std::endl; 
    // set_normals(cloud_inlier, normals, cloud_with_normals);
    // cout << "Done with normals \n" << std::endl; 

  // cout << "Meshing..." << std::endl; 
  // pcl::PolygonMesh mesh = greedy_surface_reconstruction(cloud_with_normals);
  // pcl::io::savePolygonFileSTL(output_filename, mesh);
  // cout << "Mesh generated and saved as: " << output_filename << "\n" << std::endl;
return (0);
}