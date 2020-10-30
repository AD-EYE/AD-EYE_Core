#include <iostream>
#include <pcl/common/common.h>
#include <pcl/io/pcd_io.h>
#include <pcl/search/kdtree.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/surface/grid_projection.h>
#include <pcl/point_types.h>
#include <pcl/surface/mls.h>
#include <pcl/surface/poisson.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/surface/processing.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <stdlib.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/surface/gp3.h>
#include <pcl/io/vtk_io.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/surface/organized_fast_mesh.h>
#include <pcl/surface/marching_cubes_hoppe.h>
#include <pcl/io/obj_io.h>
#include <pcl/surface/concave_hull.h>
#include <pcl/surface/convex_hull.h>
#include <boost/thread/thread.hpp>
#include <boost/shared_ptr.hpp>
#include "argparse.hpp"



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

// void pass_through_filtering(
//   pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_original, 
//   pcl::PointCloud<pcl::PointXYZ>::Ptr cloud 
// ){
//   pcl::PassThrough<pcl::PointXYZ> pass;
//   pass.setInputCloud (cloud_original);
//   pass.setFilterFieldName ("z");
//   pass.setFilterLimits (0.0, 3.0);
//   //pass.setFilterLimitsNegative (true);
//   pass.filter (*cloud);
// }

// void point_cloud_upsampling(
//   pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, 
//   pcl::PointCloud<pcl::PointXYZ>::Ptr mls_points, 
//   pcl::search::KdTree<pcl::PointXYZ>::Ptr tree
//   ){

//   pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointXYZ> mls; 

//   mls.setComputeNormals (true);

//   // Set parameters
//   mls.setInputCloud (cloud);
//   mls.setPolynomialOrder (20);
//   mls.setSearchMethod (tree);
//   mls.setSearchRadius (1);
//   mls.setUpsamplingMethod(pcl::MovingLeastSquares<pcl::PointXYZ,pcl::PointXYZ>::SAMPLE_LOCAL_PLANE);
//   mls.setUpsamplingRadius(1);
//   mls.setUpsamplingStepSize(0.98);
//   mls.setSqrGaussParam(3);

//   // Reconstruct
//   mls.process (*mls_points);

//}

void voxel_grid_dilation(
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, 
  pcl::PointCloud<pcl::PointXYZ>::Ptr mls_points, 
  pcl::search::KdTree<pcl::PointXYZ>::Ptr tree
  ){

  pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointXYZ> mls; 

  mls.setComputeNormals (true);

  // Set parameters
  mls.setInputCloud (cloud);
  mls.setPolynomialOrder (20); // 20 
  mls.setSearchMethod (tree);
  mls.setSearchRadius (0.9);  // 0.9
  mls.setUpsamplingMethod(pcl::MovingLeastSquares<pcl::PointXYZ,pcl::PointXYZ>::VOXEL_GRID_DILATION);
  mls.setDilationVoxelSize(5); // 0.3
  mls.setDilationIterations(3); // 1
  
  // Reconstruct
  mls.process (*mls_points);
}



/*
Main
*/
int
  main (int argc, const char** argv)
{
  argparse::ArgumentParser parser;
  
  //Define input arguments 
  parser.addArgument("-f", "--filename", 1);
  // parser.addArgument("-m", "--mesh", 1); //Define mesh method, [greedy, poisson]
  parser.addArgument("-o", "--output", 1);
  parser.addArgument("--voxel");
  parser.addArgument("--view");

  parser.parse(argc, argv);
  std::string filename;
  std::string mesh_file;

  if(parser.gotArgument("filename")) {
      std::string get_filename = parser.retrieve<std::string>(get_filename);
      filename=get_filename;
  }
  if(parser.gotArgument("output")) {
      std::string get_meshname = parser.retrieve<std::string>(get_meshname);
      mesh_file=get_meshname + ".obj"; //Custom outputname from --output argument
  } 
  else
  {
      mesh_file = "mesh.obj"; //Default outputname
  }
  
  // Setup pcl 
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_original (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_inlier (new pcl::PointCloud<pcl::PointXYZ>);

  pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr mls_points (new pcl::PointCloud<pcl::PointXYZ>);

  pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal>);
  pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals (new pcl::PointCloud<pcl::PointNormal>);
  
  //Load PCD file    
  set_pcd_file(cloud_original, filename); 

  size_t num_points_cloud = cloud_original->size();
  cout << "Cloud loaded! Number of points: " << num_points_cloud << "\n" << std::endl;
  
  cout << "Starting statistical outlier remover..." << std::endl; 
  remove_outlier(cloud_original, cloud_inlier);
  size_t num_points_cloud_inlier = cloud_inlier->size();
  cout << "Finished statistical outlier remover! Number of points: " << num_points_cloud_inlier << "\n" <<std::endl;
  
  if(parser.gotArgument("voxel")) {
    cout << "------------------------------------------" << std::endl; 
    cout << "Generating mesh using voxel grid dilation " << std::endl; 
    cout << "------------------------------------------" << std::endl; 
    cout << "Starting voxel grid dilation" << std::endl; 
    voxel_grid_dilation(cloud_inlier, mls_points, tree);
    size_t num_points_mls_points = mls_points->size();
    cout << "Finished voxel grid dilation! Number of points: " << num_points_mls_points << "\n" << std::endl; 

    //cloud_inlier
    cout << "Setting normals" << std::endl; 
    set_normals(mls_points, normals, cloud_with_normals);
    cout << "Done with normals \n" << std::endl; 

    //Save filtered cloud (for meshing in Meshmap)
    pcl::io::savePCDFileBinary("filtered_cloud.pcd", *mls_points);

  }
  else {
    cout << "---------------" << std::endl; 
    cout << "Generating mesh " << std::endl; 
    cout << "---------------" << std::endl; 
    cout << "Setting normals" << std::endl; 
    set_normals(cloud_inlier, normals, cloud_with_normals);
    cout << "Done with normals \n" << std::endl; 

    //Save filtered cloud (for meshing in Meshmap)
    pcl::io::savePCDFileBinary("filtered_cloud.pcd", *cloud_inlier);
  }
  
  cout << "Generating mesh" << std::endl; 
  pcl::PolygonMesh mesh = greedy_surface_reconstruction(cloud_with_normals);
  pcl::io::saveOBJFile(mesh_file, mesh);
  cout << "Mesh generated and saved as: " << mesh_file << "\n" << std::endl;


  //Viewer
  if(parser.gotArgument("view")) {
          
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer_normals   (new pcl::visualization::PCLVisualizer ("MLS points"));
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer_original  (new pcl::visualization::PCLVisualizer ("Original"));
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer_mesh      (new pcl::visualization::PCLVisualizer ("Mesh"));

    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointNormal> red (cloud_with_normals,  255, 255, 255);
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> blue (cloud_original, 0, 0, 255);

    viewer_normals  ->  addPointCloud<pcl::PointNormal> (cloud_with_normals, red, "mls");
    viewer_normals  ->  setBackgroundColor (0, 0, 0);
    viewer_normals  ->  addCoordinateSystem (1.0);
    viewer_normals  ->  initCameraParameters ();

    viewer_original ->  addPointCloud<pcl::PointXYZ> (cloud_original, blue, "mls");
    viewer_original ->  setBackgroundColor (0, 0, 0);
    viewer_original ->  addCoordinateSystem (1.0);
    viewer_original ->  initCameraParameters ();

    viewer_mesh     ->  setBackgroundColor (0, 0, 11);
    viewer_mesh     ->  addPolygonMesh(mesh,"meshes",0);
    viewer_mesh     ->  addCoordinateSystem (1.0);
    viewer_mesh     ->  initCameraParameters ();

    while (!viewer_normals->wasStopped ()){
        viewer_normals  ->  spinOnce (100);
        viewer_original ->  spinOnce (100);
        viewer_mesh     ->  spinOnce (100);
        boost::this_thread::sleep (boost::posix_time::microseconds (100000));
    }
  }
return (0);
}