#ifndef VECTORMAPLOADER_H // keep this header file from being included multiple times
#define VECTORMAPLOADER_H

// csv handling
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

class VectorMapLoader
{
public:
  VectorMapLoader() {}

  // vectormap struct
  struct vecmap{
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
  };

  void load_vectormap(std::string filePoint, std::string fileLane, std::string fileNode, std::string fileDtlane, vecmap & vm){
    // parsing variables
    std::string line;
    std::string element;
    float value;

    // saved data, sorted in the four files
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

    // open file point and save important data
    std::ifstream inputFile;
    inputFile.open (filePoint);
    if (!inputFile.is_open()){
      std::stringstream ss;
      ss << "ERROR: couldn't open file" << filePoint;
      throw std::runtime_error(ss.str());
    }
    else{
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
                vm.point_id.push_back(value);
                break;
              case 1:
                // is unimportant for this code
                break;
              case 2:
                // is unimportant for this code
                break;
              case 3:
                // is unimportant for this code
                break;
              case 4:
                vm.point_y.push_back(value);
                break;
              case 5:
                vm.point_x.push_back(value);
                break;
              case 6:
                // is unimportant for this code
                break;
              case 7:
                // is unimportant for this code
                break;
              case 8:
                // is unimportant for this code
                break;
              case 9:
                // is unimportant for this code
                break;
              default:
                ROS_INFO_STREAM("ERROR: unknown parsing case");
                break;
              }
            }
            i++;
          }
        }
      }         
    }
    inputFile.close();

    // open file lane and save important data
    inputFile.open (fileLane);
    if (!inputFile.is_open()){
      std::stringstream ss;
      ss << "ERROR: couldn't open file" << fileLane;
      throw std::runtime_error(ss.str());
    }
    else{
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
                vm.lane_id.push_back(value);
                break;
              case 1:
                vm.lane_did.push_back(value);
                break;
              case 2:
                vm.lane_prevlane.push_back(value);
                break;
              case 3:
                vm.lane_nextlane.push_back(value);
                break;
              case 4:
                vm.lane_startpoint.push_back(value);
                break;
              case 5:
                vm.lane_endpoint.push_back(value);
                break;
              case 6:
                // is unimportant for this code
                break;
              case 7:
                // is unimportant for this code
                break;
              case 8:
                // is unimportant for this code
                break;
              case 9:
                // is unimportant for this code
                break;
              case 10:
                // is unimportant for this code
                break;
              case 11:
                // is unimportant for this code
                break;
              case 12:
                // is unimportant for this code
                break;
              case 13:
                // is unimportant for this code
                break;
              case 14:
                // is unimportant for this code
                break;
              case 15:
                // is unimportant for this code
                break;
              case 16:
                // is unimportant for this code
                break;
              case 17:
                // is unimportant for this code
                break;
              case 18:
                // is unimportant for this code
                break;
              case 19:
                // is unimportant for this code
                break;
              case 20:
                // is unimportant for this code
                break;
              case 21:
                // is unimportant for this code
                break;
              case 22:
                // is unimportant for this code
                break;
              default:
                ROS_INFO_STREAM("ERROR: unknown parsing case");
                break;
              }
            }
            i++;
          }
        }
      }         
    }
    inputFile.close();

    // node file and save important data
    inputFile.open (fileNode);
    if (!inputFile.is_open()){
      std::stringstream ss;
      ss << "ERROR: couldn't open file" << fileNode;
      throw std::runtime_error(ss.str());
    }
    else{
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
                vm.node_nid.push_back(value);
                break;
              case 1:
                vm.node_pid.push_back(value);
                break;
              default:
                ROS_INFO_STREAM("ERROR: unknown parsing case");
                break;
              }
            }
            i++;
          }
        }
      }         
    }
    inputFile.close();

    // open file dtlane and save important data
    inputFile.open (fileDtlane);
    if (!inputFile.is_open()){
      std::stringstream ss;
      ss << "ERROR: couldn't open file" << fileDtlane;
      throw std::runtime_error(ss.str());
    }
    else{
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
                vm.dtlane_did.push_back(value);
                break;
              case 1:
                // is unimportant for this code
                break;
              case 2:
                // is unimportant for this code
                break;
              case 3:
                // is unimportant for this code
                break;
              case 4:
                // is unimportant for this code
                break;
              case 5:
                // is unimportant for this code
                break;
              case 6:
                // is unimportant for this code
                break;
              case 7:
                // is unimportant for this code
                break;
              case 8:
                vm.dtlane_leftwidth.push_back(value);
                break;
              case 9:
                vm.dtlane_rightwidth.push_back(value);
                break;
              default:
                ROS_INFO_STREAM("ERROR: unknown parsing case");
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

private:
  vecmap vm;
};


#endif
