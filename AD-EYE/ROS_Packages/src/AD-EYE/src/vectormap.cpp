#include "vectormap.h"
#include <ros/ros.h>

bool VectorMap::checkFileOpening(const std::ifstream &input_file_stream, const std::string &file_name) {
    if (!input_file_stream.is_open()){
        std::stringstream ss;
        ss << "Couldn't open file" << file_name;
        ROS_ERROR_STREAM(ss.str());
        throw std::runtime_error(ss.str());
    } else {
        return true;
    }
}

void VectorMap::loadVectormap(std::string points_file, std::string lanes_file, std::string nodes_file, std::string dtlanes_file) {
    readPoints(points_file);
    readLanes(lanes_file);
    readNodes(nodes_file);
    readDtLanes(dtlanes_file);
}

void VectorMap::readPoints(std::string points_file)
{

    std::ifstream input_file_stream;
    input_file_stream.open(points_file);

    if(checkFileOpening(input_file_stream, points_file)) {
        std::string line;
        while(input_file_stream.good()){
            std::getline (input_file_stream,line);
            if(!line.empty()){
                std::stringstream ss(line);
                int i = 0;
                std::string element;
                float value;
                while(ss.good()){
                    getline( ss, element, ',' );
                    if(!element.empty()){
                        value = strtof(element.c_str(),0); // string to float
                        switch (i) {
                            case 0:
                                this->points_id_.push_back(value);
                                break;
                            case 1: // is unimportant for this code
                            case 2: // is unimportant for this code
                            case 3: // is unimportant for this code
                                break;
                            case 4:
                                this->points_y_.push_back(value);
                                break;
                            case 5:
                                this->points_x_.push_back(value);
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
    input_file_stream.close();
}

void VectorMap::readLanes(std::string lanes_file)
{
    std::ifstream input_file_stream;
    input_file_stream.open(lanes_file);

    if(checkFileOpening(input_file_stream, lanes_file)) {
        std::string line;
        while(input_file_stream.good()){
            std::getline (input_file_stream,line);
            if(!line.empty()){
                std::stringstream ss(line);
                int i = 0;
                std::string element;
                float value;
                while(ss.good()){
                    getline( ss, element, ',' );
                    if(!element.empty()){
                        value = strtof(element.c_str(),0); // string to float
                        switch (i) {
                            case 0:
                                this->lanes_id_.push_back(value);
                                break;
                            case 1:
                                this->lanes_did_.push_back(value);
                                break;
                            case 2:
                                this->lanes_prevlane_.push_back(value);
                                break;
                            case 3:
                                this->lanes_nextlane_.push_back(value);
                                break;
                            case 4:
                                this->lanes_startpoint_.push_back(value);
                                break;
                            case 5:
                                this->lanes_endpoint_.push_back(value);
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
    input_file_stream.close();
}

void VectorMap::readNodes(std::string nodes_file)
{
    std::ifstream input_file_stream;
    input_file_stream.open(nodes_file);

    if(checkFileOpening(input_file_stream, nodes_file)) {
        std::string line;
        while(input_file_stream.good()){
            std::getline (input_file_stream,line);
            if(!line.empty()){
                std::stringstream ss(line);
                int i = 0;
                std::string element;
                float value;
                while(ss.good()){
                    getline( ss, element, ',' );
                    if(!element.empty()){
                        value = strtof(element.c_str(),0); // string to float
                        switch (i) {
                            case 0:
                                this->nodes_nid_.push_back(value);
                                break;
                            case 1:
                                this->nodes_pid_.push_back(value);
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
    input_file_stream.close();
}

void VectorMap::readDtLanes(std::string dtlanes_file)
{
    std::ifstream input_file_stream;
    input_file_stream.open(dtlanes_file);

    if(checkFileOpening(input_file_stream, dtlanes_file)) {
        std::string line;
        while(input_file_stream.good()){
            std::getline (input_file_stream,line);
            if(!line.empty()){
                std::stringstream ss(line);
                int i = 0;
                std::string element;
                float value;
                while(ss.good()){
                    getline( ss, element, ',' );
                    if(!element.empty()){
                        value = strtof(element.c_str(),0); // string to float
                        switch (i) {
                            case 0:
                                this->dtlanes_did_.push_back(value);
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
                                this->dtlanes_leftwidth_.push_back(value);
                                break;
                            case 9:
                                this->dtlanes_rightwidth_.push_back(value);
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
    input_file_stream.close();
}