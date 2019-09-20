#ifndef PRESCANMODEL_H
#define PRESCANMODEL_H

// csv handling
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

struct PrescanModel
{

  std::vector<std::string> header;
  std::vector<int> ID;
  std::vector<int> type;
  std::vector<float> posX;
  std::vector<float> posY;
  std::vector<float> yaw;
  std::vector<float> sizeX;
  std::vector<float> sizeY;
  std::vector<float> sizeZ;

  void load_pexmap(std::string filePex) {
    // parsing variables
    std::string line;
    std::string element;
    float value;

    // open file pex and save important data
    std::ifstream inputFile;
    inputFile.open (filePex);
    if (!inputFile.is_open()){
      std::stringstream ss;
      ss << "Couldn't open file" << filePex;
      ROS_ERROR_STREAM(ss.str());
      throw std::runtime_error(ss.str());
    }
    else{
      while (inputFile.good()){
        std::getline (inputFile,line);
        if(line.find("<NatureElement xsi") != std::string::npos || line.find(" ObjectTypeID=\"12\"") != std::string::npos || line.find("<InfraOther xsi") != std::string::npos){
          // get type
          if(line.find("Nature") != std::string::npos){
            this->type.push_back(0);
          }
          if(line.find(" ObjectTypeID=\"12\"") != std::string::npos){
            this->type.push_back(1);
          }
          if(line.find("InfraOther") != std::string::npos){
            this->type.push_back(2);
          }

          // get ID
          element = line.substr(line.find("UniqueId")+10, line.find("Sensor")-2-line.find("UniqueId")+10);
          value = strtof(element.c_str(),0);
          this->ID.push_back(value);

          // get Position
          std::getline (inputFile,line);
          element = line.substr(line.find("X=")+3, line.find("Y=")-2-line.find("X=")+3);
          value = strtof(element.c_str(),0);
          this->posX.push_back(value);
          element = line.substr(line.find("Y=")+3, line.find("Z=")-2-line.find("Y=")+3);
          value = strtof(element.c_str(),0);
          this->posY.push_back(value);

          // get Orientation
          std::getline (inputFile,line);
          element = line.substr(line.find("Heading=")+9, line.find("/>")-2-line.find("Heading=")+9);
          value = strtof(element.c_str(),0);
          this->yaw.push_back(value);

          // get Size
          std::getline (inputFile,line);
          std::getline (inputFile,line);
          element = line.substr(line.find("X=")+3, line.find("Y=")-2-line.find("X=")+3);
          value = strtof(element.c_str(),0);
          this->sizeX.push_back(value);
          element = line.substr(line.find("Y=")+3, line.find("Z=")-2-line.find("Y=")+3);
          value = strtof(element.c_str(),0);
          this->sizeY.push_back(value);
          element = line.substr(line.find("Z=")+3, line.find("/>")-2-line.find("Z=")+3);
          value = strtof(element.c_str(),0);
          this->sizeZ.push_back(value);
        }
      }
    }
    inputFile.close();
  }

};


#endif
