#ifndef PRESCANMODEL_H
#define PRESCANMODEL_H

// csv handling
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/locale.hpp>
#include <boost/locale/generator.hpp>
#include <boost/foreach.hpp>

#define NATURE 0
#define BUILDING 1
#define TRAFFICLIGHT 2
#define SAFEAREA 3

void load_pexmap(){
 struct PrescanObject
{
    int ID;
    double posX;
    double posY;
    double yaw;
    double sizeX;
    double sizeY;
    double sizeZ;
    int safetyAreaValue;
};

    std::string filePex = "/home/adeye/AD-EYE_Core/AD-EYE/Experiments/W01_Base_Map/Simulation/W01_Base_Map.pex";
        using boost::property_tree::ptree;

        // Populate tree structure (pt):

        ptree pt;
        read_xml(filePex, pt);

        // Traverse pt:

        //AppList List;
        PrescanObject Obj;
        ptree pt_2 = pt.get_child("Experiment");
        BOOST_FOREACH(ptree::value_type& v, pt_2.get_child("Actors"))
        {
            if (v.first == "Actor")
            {                
                
                Obj.posX = v.second.get<double>("Location.X");
                Obj.posY = v.second.get<double>("Location.Y");
                Obj.yaw = v.second.get<double>("Orientation.Heading");
                Obj.sizeX = v.second.get<double>("Size.X");
                Obj.sizeY = v.second.get<double>("Size.Y");
                Obj.sizeZ = v.second.get<double>("Size.Z");
                
                              
               // List.push_back(App);
            }
        }
        BOOST_FOREACH(ptree::value_type& v, pt.get_child("Environment"))
        {
            if (v.first == "Underlays")
            {
                if(v.second.get<std::string>("Underlay.Description").size()>=4 && v.second.get<std::string>("Underlay.Description").substr(0,4) == "SAFE")
                {
                Obj.safetyAreaValue = strtol(v.second.get<std::string>("Underlay.Description").substr(4).c_str(),NULL,10);          
                }
            }
         }

         BOOST_FOREACH(ptree::value_type& v, pt.get_child("Experiment"))
        {
            if (v.first == "Actors")
            {
                Obj.ID = v.second.get<int>("Actor.UniqueId");
            
            }
         }
         
         std::cout<<Obj.ID<<Obj.safetyAreaValue;
};

/*!
 * \brief This structure handles data from the Prescan Experiment.
 * \details It loads the data from .pex files
 */


//struct PrescanModel
int main()
{
   
   

    bool ULElementFound = false;

    
    load_pexmap();
        

        // parsing variables
/*        std::string line;
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
                        line.find("<Actor ") != std::string::npos ) {

                    // get type
                    if(line.find("Description=\"SAFE") != std::string::npos) {
                        type = SAFEAREA;
                        element = line.substr(line.find("Description=\"SAFE")+17, 3);
                        value = strtof(element.c_str(),0);

                        if(value < 1 || value > 256){
                            std::stringstream ss;
                            ss << "Value of the SafeArea out of the range 1-256. Value = " << value << filePex;
                            ROS_ERROR_STREAM(ss.str());
                            throw std::runtime_error(ss.str());
                        }
                        object.safetyAreaValue = value;
                        //std::cout << element << ";" << value << std::endl;
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
                    else if(line.find("TrafficLightRoadSideNL") != std::string::npos){
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
        inputFile.close();*/
    
return 0;
}


#endif