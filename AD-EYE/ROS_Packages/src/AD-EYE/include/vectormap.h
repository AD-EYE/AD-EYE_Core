#ifndef VECTORMAP_H
#define VECTORMAP_H

// csv handling
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

/*!
 * \brief This structure handles data from the vector map.
 * \details It loads the data from .csv files
 */
class VectorMap
{

public:

    std::vector<int> points_id_;
    std::vector<float> points_x_;
    std::vector<float> points_y_;

    std::vector<int> lanes_id_;
    std::vector<int> lanes_did_;
    std::vector<int> lanes_prevlane_;
    std::vector<int> lanes_nextlane_;
    std::vector<int> lanes_startpoint_;
    std::vector<int> lanes_endpoint_;

    std::vector<int> nodes_nid_;
    std::vector<int> nodes_pid_;

    std::vector<int> dtlanes_did_;
    std::vector<float> dtlanes_leftwidth_;
    std::vector<float> dtlanes_rightwidth_;
    

    /*!
     * \brief Loads the data of the vector map from the given .csv files
     * \param points_file The path to point.csv
     * \param lanes_file The path to lane.csv
     * \param nodes_file The path to node.csv
     * \param dtlanes_file The path to dtlane.csv
     * \details The function parses files and stores the data into the structure.
     */
    void load_vectormap(std::string points_file, std::string lanes_file, std::string nodes_file, std::string dtlanes_file);
    


private:

    /*!
     * \brief Checks if a file has successfully been opened
     * \param input_file_stream the std::ifstream of the file
     * \param file_name the name of the file
     * \return true if the file has been successfully opened
     * \details If the file cannot be opened, the function throws a std::runtime_error
     * and also writes a ROS_ERROR message
     */
    bool checkFileOpening(const std::ifstream &input_file_stream, const std::string &file_name);

    void readPoints(std::string points_file);
    
    void readLanes(std::string lanes_file);

    void readNodes(std::string nodes_file);
    
    void readDtLanes(std::string dtlanes_file);
    
};

#endif
