#ifndef VECTORMAP_H
#define VECTORMAP_H

// csv handling
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

/*!
 * \brief This structure handles data from the vector map.
 * \details It loads the data from .csv files
 */
struct VectorMap
{

    std::vector<std::string> header;
    std::vector<int> point_id;
    std::vector<float> point_x;
    std::vector<float> point_y;

    std::vector<int> lane_id;
    std::vector<int> lane_did;
    std::vector<int> lane_prevlane;
    std::vector<int> lane_nextlane;
    std::vector<int> lane_startpoint;
    std::vector<int> lane_endpoint;

    std::vector<int> node_nid;
    std::vector<int> node_pid;

    std::vector<int> dtlane_did;
    std::vector<float> dtlane_leftwidth;
    std::vector<float> dtlane_rightwidth;

    /*!
     * \brief Checks if a file has successfully been opened
     * \param inputFile the std::ifstream of the file
     * \param fileName the name of the file
     * \return true if the file has been successfully opened
     * \details If the file cannot be opened, the function throws a std::runtime_error
     * and also writes a ROS_ERROR message
     */
    bool checkFileOpening(const std::ifstream &inputFile, const std::string &fileName) {
        if (!inputFile.is_open()){
            std::stringstream ss;
            ss << "Couldn't open file" << fileName;
            ROS_ERROR_STREAM(ss.str());
            throw std::runtime_error(ss.str());
            return false;
        } else {
            return true;
        }
    }

    /*!
     * \brief Loads the data of the vector map from the given .csv files
     * \param filePoint The path to point.csv
     * \param fileLane The path to lane.csv
     * \param fileNode The path to node.csv
     * \param fileDtlane The path to dtlane.csv
     * \details The function parses files and stores the data into the structure.
     */
    void load_vectormap(std::string filePoint, std::string fileLane, std::string fileNode, std::string fileDtlane) {
        // parsing variables
        std::string line;
        std::string element;
        float value;

        // === Reading:  POINTS  ===

        std::ifstream inputFile;
        inputFile.open (filePoint);

        if(checkFileOpening(inputFile, filePoint)) {
            while (inputFile.good()){
                std::getline (inputFile,line);
                if(!line.empty()){
                    std::stringstream ss(line);
                    int i = 0;
                    while(ss.good()){
                        getline( ss, element, ',' );
                        if(!element.empty()){
                            value = strtof(element.c_str(),0); // string to float
                            switch (i) {
                                case 0:
                                    this->point_id.push_back(value);
                                    break;
                                case 1: // is unimportant for this code
                                case 2: // is unimportant for this code
                                case 3: // is unimportant for this code
                                    break;
                                case 4:
                                    this->point_y.push_back(value);
                                    break;
                                case 5:
                                    this->point_x.push_back(value);
                                    break;
                                case 6: // is unimportant for this code
                                case 7: // is unimportant for this code
                                case 8: // is unimportant for this code
                                case 9: // is unimportant for this code
                                    break;
                                default:
                                    ROS_ERROR_STREAM("Unknown parsing case : " << i << " for Points");
                                    break;
                            }
                        }
                        i++;
                    }
                }
            }
        }
        inputFile.close();

        // === Reading:  LANES  ===

        inputFile.open (fileLane);

        if(checkFileOpening(inputFile, fileLane)) {
            while (inputFile.good()){
                std::getline (inputFile,line);
                if(!line.empty()){
                    std::stringstream ss(line);
                    int i = 0;
                    while(ss.good()){
                        getline( ss, element, ',' );
                        if(!element.empty()){
                            value = strtof(element.c_str(),0); // string to float
                            switch (i) {
                                case 0:
                                    this->lane_id.push_back(value);
                                    break;
                                case 1:
                                    this->lane_did.push_back(value);
                                    break;
                                case 2:
                                    this->lane_prevlane.push_back(value);
                                    break;
                                case 3:
                                    this->lane_nextlane.push_back(value);
                                    break;
                                case 4:
                                    this->lane_startpoint.push_back(value);
                                    break;
                                case 5:
                                    this->lane_endpoint.push_back(value);
                                    break;
                                case 6: // is unimportant for this code
                                case 7: // is unimportant for this code
                                case 8: // is unimportant for this code
                                case 9: // is unimportant for this code
                                case 10: // is unimportant for this code
                                case 11: // is unimportant for this code
                                case 12: // is unimportant for this code
                                case 13: // is unimportant for this code
                                case 14: // is unimportant for this code
                                case 15: // is unimportant for this code
                                case 16: // is unimportant for this code
                                case 17: // is unimportant for this code
                                case 18: // is unimportant for this code
                                case 19: // is unimportant for this code
                                case 20: // is unimportant for this code
                                case 21: // is unimportant for this code
                                    break;
                                default:
                                    ROS_ERROR_STREAM("Unknown parsing case : " << i << " for Lanes");
                                    break;
                            }
                        }
                        i++;
                    }
                }
            }
        }
        inputFile.close();

        // === Reading:  NODES  ===

        inputFile.open (fileNode);

        if(checkFileOpening(inputFile, fileNode)) {
            while (inputFile.good()){
                std::getline (inputFile,line);
                if(!line.empty()){
                    std::stringstream ss(line);
                    int i = 0;
                    while(ss.good()){
                        getline( ss, element, ',' );
                        if(!element.empty()){
                            value = strtof(element.c_str(),0); // string to float
                            switch (i) {
                                case 0:
                                    this->node_nid.push_back(value);
                                    break;
                                case 1:
                                    this->node_pid.push_back(value);
                                    break;
                                default:
                                    ROS_ERROR_STREAM("Unknown parsing case : " << i << " for Nodes");
                                    break;
                            }
                        }
                        i++;
                    }
                }
            }
        }
        inputFile.close();


        // === Reading:  DT LANES  ===

        inputFile.open (fileDtlane);

        if(checkFileOpening(inputFile, fileDtlane)) {
            while (inputFile.good()){
                std::getline (inputFile,line);
                if(!line.empty()){
                    std::stringstream ss(line);
                    int i = 0;
                    while(ss.good()){
                        getline( ss, element, ',' );
                        if(!element.empty()){
                            value = strtof(element.c_str(),0); // string to float
                            switch (i) {
                                case 0:
                                    this->dtlane_did.push_back(value);
                                    break;
                                case 1: // is unimportant for this code
                                case 2: // is unimportant for this code
                                case 3: // is unimportant for this code
                                case 4: // is unimportant for this code
                                case 5: // is unimportant for this code
                                case 6: // is unimportant for this code
                                case 7: // is unimportant for this code
                                    break;
                                case 8:
                                    this->dtlane_leftwidth.push_back(value);
                                    break;
                                case 9:
                                    this->dtlane_rightwidth.push_back(value);
                                    break;
                                default:
                                    ROS_ERROR_STREAM("Unknown parsing case : " << i << " for DtLanes");
                                    break;
                            }
                        }
                        i++;
                    }
                }
            }
        }
        inputFile.close();
    }

};

#endif
