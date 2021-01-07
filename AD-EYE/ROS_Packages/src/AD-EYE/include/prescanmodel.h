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
#include <boost/optional/optional.hpp>

#define NATURE 13
#define BUILDING 12
#define TRAFFICLIGHT 15
#define SAFEAREA 17
#define STATICCAR 1
#define ATTR_SET ".<xmlattr>"
#define DECIMAL_BASE 10
#define SAFE_STRING_POS 4

struct PrescanModel
{
    /*!
    * \brief This structure handles data from the Prescan Experiment.
    * \details It loads the data from .pex files
    */
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

	// Containers to save the objects based on object ID
	std::vector<PrescanObject> safeAreaObjects;
	std::vector<PrescanObject> natureObjects;
	std::vector<PrescanObject> buildingObjects;
	std::vector<PrescanObject> trafficlightObjects;
	std::vector<PrescanObject> staticCarsObjects;

	
    /*!
     * \brief Loads the data from the xml into the respective vectors
     * \param local_ptree 	The child node from the xml file to be inserted into the vector
	 * \param u_id 			The unique id of the Actor
	 * \param type_id 		The object id of the Actor
	 * \param safe_value 	The safe area value of the actor
     */
	void load_actor(boost::property_tree::ptree::value_type& local_ptree, int u_id, int type_id, int safe_value)
	{		
		// Populating the containers with data from the xml
		PrescanObject Obj;
		Obj.ID = u_id;
		Obj.posX = local_ptree.second.get<double>("Location.<xmlattr>.X");
		Obj.posY = local_ptree.second.get<double>("Location.<xmlattr>.Y");
		Obj.yaw = local_ptree.second.get<double>("Orientation.<xmlattr>.Heading");
		Obj.sizeX = local_ptree.second.get<double>("Size.<xmlattr>.X");
		Obj.sizeY = local_ptree.second.get<double>("Size.<xmlattr>.Y");
		Obj.sizeZ = local_ptree.second.get<double>("Size.<xmlattr>.Z");
		Obj.safetyAreaValue = safe_value;
		
		// Inserting data into the respective containers 
		if(type_id == BUILDING)
		{
			buildingObjects.push_back(Obj);
		}
		if(type_id == NATURE)
		{
			natureObjects.push_back(Obj);
		}
		if(type_id == TRAFFICLIGHT)
		{
			trafficlightObjects.push_back(Obj);
		}
		if(type_id == SAFEAREA)
		{
			safeAreaObjects.push_back(Obj);
		}
		if(type_id == STATICCAR)
		{
			staticCarsObjects.push_back(Obj);
		}
	}
	
    /*!
     * \brief Loads the data of the Prescan Experiment from the given file
     * \param filePex The path to the .pex file
     */
	void load_pexmap(std::string filePex)
	{
		using boost::property_tree::ptree;
		using boost::optional;

		ptree pt;
		read_xml(filePex, pt);

		ptree pt_Experiment = pt.get_child("Experiment");

		int safetyAreaValue = 0;
		int u_id = 0;
		int obj_id = 0;
        bool isEgoVehicle = false;
		
		// looping through the entire xml
		BOOST_FOREACH(ptree::value_type& val_Experiment, pt.get_child("Experiment"))
		{
			// checking if the child node is "Actors" in "Experiment"
			if (val_Experiment.first == "Actors")
			{
				// tree with all the child nodes inside "Actors"
				ptree pt_Actors = pt_Experiment.get_child("Actors");
				// looping through all the child nodes inside "Actors"
				BOOST_FOREACH(ptree::value_type& val_Actors, pt_Actors)
				{
					// tree with all the attributes of each "Actor"
					ptree pt_Actor_Attr = val_Actors.second.get_child("<xmlattr>");
					// tree whose all the child nodes of Trajectories
					ptree pt_tra = val_Actors.second.get_child("Trajectories");
					// looping through the attributes of "Actor"
					BOOST_FOREACH(ptree::value_type& val_Actor_Attr, pt_Actor_Attr)
					{
						//std::cout << "Values: " << val_Actor_Attr.first.data() << ":" <<val_Actor_Attr.second.data()<< std::endl;
						// populating the u_id with the data of the attribute name "UniqueId"
						if(val_Actor_Attr.first == "UniqueId")
						{
							u_id = strtol(val_Actor_Attr.second.data().c_str(),NULL,DECIMAL_BASE);
						}
						// populating the obj_id with the data of the attribute name "ObjectTypeID"
						if(val_Actor_Attr.first == "ObjectTypeID")
						{
							obj_id = strtol(val_Actor_Attr.second.data().c_str(),NULL,DECIMAL_BASE);
						}
                        if(val_Actor_Attr.first == "Description")
                        {
                            if(val_Actor_Attr.second.data() == "EGO_VEHICLE")
                            {
                                isEgoVehicle = true;
                            }
                        }

						//std::cout << "After Values: " << val_Actor_Attr.first.data() << ":" <<u_id<<":" <<obj_id<< std::endl;
					}
					
					// Checking if the "Trajectory" node has a child named "TrajectoryBase"
					optional< ptree& > child = pt_tra.get_child_optional("TrajectoryBase");
					if( !child && !isEgoVehicle)
                    {
                        //std::cout << "Trajectory not found" << u_id <<std::endl;
                        load_actor(val_Actors, u_id, obj_id, safetyAreaValue);
                    }
                    else
                    {
                        //std::cout << "Dynamic Actor" << u_id <<std::endl;
                        isEgoVehicle = false;
                    }				
				}
			}

			// checking if the child node is "Environment" in "Experiment"
            if (val_Experiment.first == "Environment")
            {
                // looping through all the child nodes inside "Environment"
                BOOST_FOREACH(ptree::value_type& val_Environment, pt_Experiment.get_child("Environment"))
                {
                    // checking if the child node is "Underlays" in "Environment"
                    if (val_Environment.first == "Underlays")
                    {
                        // looping through all the child nodes inside "Underlays"
                        BOOST_FOREACH(ptree::value_type& val_Underlays, val_Experiment.second.get_child("Underlays"))
                        {
                            // tree with all the attributes of each "Underlay"
                            ptree pt_Underlay_Attr = val_Underlays.second.get_child("<xmlattr>");
                            BOOST_FOREACH(ptree::value_type& val_Underlay_Attr, pt_Underlay_Attr)
                            {
                                // populating the safetyAreaValue with the data of the attribute name "Description"
                                if(val_Underlay_Attr.first == "Description")
                                {
                                    // checking the codition if the attribute "Description" has the value "SAFE" in it
                                    if(val_Underlay_Attr.second.data().size()>=SAFE_STRING_POS && val_Underlay_Attr.second.data().substr(0,SAFE_STRING_POS) == "SAFE")
                                    {
                                        safetyAreaValue = strtol(val_Underlay_Attr.second.data().substr(SAFE_STRING_POS).c_str(),NULL,DECIMAL_BASE);          
                                    }
                                }
                                // populating the u_id with the data of the attribute name "UniqueId"
                                if(val_Underlay_Attr.first == "UniqueId")
                                {
                                    u_id = strtol(val_Underlay_Attr.second.data().c_str(),NULL,DECIMAL_BASE);
                                }
                                // populating the obj_id with the data of the attribute name "ObjectTypeID"
                                if(val_Underlay_Attr.first == "ObjectTypeID")
                                {
                                    obj_id = strtol(val_Underlay_Attr.second.data().c_str(),NULL,DECIMAL_BASE);
                                }
                            }
                            load_actor(val_Underlays, u_id, obj_id, safetyAreaValue);						
                        }
                    }
                }
            }
		}
	}
};

#endif