#ifndef PRESCANMODEL_H
#define PRESCANMODEL_H

// csv handling
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#define NATURE 0
#define BUILDING 1
#define TRAFFICLIGHT 2
#define SAFEAREA 3

/*!
 * \brief This structure handles data from the Prescan Experiment.
 * \details It loads the data from .pex files
 */

struct PrescanObject
{
    int ID;
    float posX;
    float posY;
    float yaw;
    float sizeX;
    float sizeY;
    float sizeZ;
};

struct PrescanModel
{
    std::vector<PrescanObject> buildingObjects;
    std::vector<PrescanObject> natureObjects;
    std::vector<PrescanObject> trafficlightObjects;
    std::vector<PrescanObject> safeAreaObjects;

    bool ULElementFound = false;

    /*!
     * \brief Loads the data of the Prescan Experiment from the given file
     * \param filePex The path to the .pex file
     */
    void load_pexmap(std::string filePex) {
        // parsing variables
        std::string line;
        std::string element;
        float value;

        PrescanObject object;
        int type;

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
                if(line.find("ObjectTypeID=\"9\"") != std::string::npos) {
                    ULElementFound = true;
                }
                if(line.find("<NatureElement xsi") != std::string::npos ||
                        line.find(" ObjectTypeID=\"12\"") != std::string::npos ||
                        line.find(" ObjectTypeID=\"17\"") != std::string::npos || // Concrete areas can be declared as safe area
                        line.find("<InfraOther xsi") != std::string::npos ||
                        line.find("<AbstractObject ") != std::string::npos ) {

                    // get type
                    if(line.find("Description=\"SAFE") != std::string::npos) {
                        type = SAFEAREA;
                    }
                    else if(line.find("Nature") != std::string::npos){
                        type = NATURE;
                    }
                    else if(line.find(" ObjectTypeID=\"12\"") != std::string::npos){
                        type = BUILDING;
                    }
                    else if(line.find("xsi:type=\"RectangularBox") != std::string::npos) {
                        type = BUILDING;
                    }
                    else if(line.find("InfraOther") != std::string::npos){
                        type = TRAFFICLIGHT;
                    } else {
                        continue;
                    }

                    // Get ID
                    element = line.substr(line.find("UniqueId")+10, line.find("Sensor")-2-line.find("UniqueId")+10);
                    value = strtof(element.c_str(),0);
                    object.ID = value;

                    // Get Position
                    std::getline (inputFile,line);
                    element = line.substr(line.find("X=")+3, line.find("Y=")-2-line.find("X=")+3);
                    value = strtof(element.c_str(),0);
                    object.posX = value;
                    element = line.substr(line.find("Y=")+3, line.find("Z=")-2-line.find("Y=")+3);
                    value = strtof(element.c_str(),0);
                    object.posY = value;

                    // Get Orientation
                    std::getline (inputFile,line);
                    element = line.substr(line.find("Heading=")+9, line.find("/>")-2-line.find("Heading=")+9);
                    value = strtof(element.c_str(),0);
                    object.yaw = value;

                    //Get Size
                    std::getline (inputFile,line);
                    std::getline (inputFile,line);
                    element = line.substr(line.find("X=")+3, line.find("Y=")-2-line.find("X=")+3);
                    value = strtof(element.c_str(),0);
                    object.sizeX = value;
                    element = line.substr(line.find("Y=")+3, line.find("Z=")-2-line.find("Y=")+3);
                    value = strtof(element.c_str(),0);
                    object.sizeY = value;
                    element = line.substr(line.find("Z=")+3, line.find("/>")-2-line.find("Z=")+3);
                    value = strtof(element.c_str(),0);
                    object.sizeZ = value;

                    // Save the object
                    if(type == SAFEAREA) {
                        this->safeAreaObjects.push_back(object);
                    }
                    else if(type == NATURE){
                        this->natureObjects.push_back(object);
                    }
                    else if(type == BUILDING){
                        this->buildingObjects.push_back(object);
                    }
                    else if(type == TRAFFICLIGHT){
                        this->trafficlightObjects.push_back(object);
                    } else {
                        continue;
                    }


                }
            }
        }
        inputFile.close();
    }

};


#endif
