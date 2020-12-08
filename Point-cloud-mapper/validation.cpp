#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>
#include <boost/thread/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <pcl/filters/passthrough.h>
#include <string>
// #include <pcl/io/auto_io.h>

int
main (int argc, char** argv)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_original (new pcl::PointCloud<pcl::PointXYZ>);
    
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_inlier (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_outlier (new pcl::PointCloud<pcl::PointXYZ>);

    // Fill in the cloud data
    pcl::PCDReader reader;
    // Replace the path below with the path where you saved your file
    std::string file_name;
    cout <<"Enter file name: ";
    cin >> file_name;
    cout << "Your filename is: " << file_name << std::endl;
    
    if (reader.read<pcl::PointXYZ> (file_name, *cloud_original) < 0) {
        cout << "File not found" << std::endl;
        return(1);
    }
    
    pcl::PassThrough<pcl::PointXYZ> pass;
    pass.setInputCloud (cloud_original);
    pass.setFilterFieldName ("z");
    pass.setFilterLimits (0.0, 3.0);
    //pass.setFilterLimitsNegative (true);
    pass.filter (*cloud);

    size_t num_points = cloud->size();

    std::cerr << "Number of points before filtering: " << std::endl;
    std::cerr << num_points << std::endl;

    // Create the filtering object
    pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
    sor.setInputCloud (cloud);
    sor.setMeanK (50);
    sor.setStddevMulThresh (1.0);
    sor.filter (*cloud_inlier);

    size_t num_points_inlier = cloud_inlier->size();

    std::cerr << "Number of points remaining after filtering: " << std::endl;
    std::cerr << num_points_inlier << std::endl;

    
    sor.setNegative (true);
    sor.filter (*cloud_outlier);

    size_t num_points_outlier = cloud_outlier->size();

    std::cerr << "Number of points filtered: " << std::endl;
    std::cerr << num_points_outlier << std::endl;

    std::cerr << "Percentage of filtered points: " << std::endl;
    double percentage = float(cloud_outlier->size())/float(cloud->size())*100.0;
    std::cerr << percentage << " %" << std::endl;

    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));

    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> red (cloud_inlier, 255, 0, 0);
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> blue (cloud_outlier, 0, 0, 255);

    viewer->addPointCloud<pcl::PointXYZ> (cloud_inlier, red, "inlier");
    viewer->addPointCloud<pcl::PointXYZ> (cloud_outlier, blue, "outlier");

    viewer->setBackgroundColor (0, 0, 0);
    viewer->addCoordinateSystem (1.0);
    viewer->initCameraParameters ();

    pcl::io::savePCDFile("preprocessed.pcd", *cloud_inlier);

    while (!viewer->wasStopped ()){
        viewer->spinOnce (100);
        boost::this_thread::sleep (boost::posix_time::microseconds (100000));
    }

    return (0);
}