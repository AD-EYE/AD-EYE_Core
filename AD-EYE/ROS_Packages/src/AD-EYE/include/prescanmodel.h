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
// #define SAFEAREA 17
#define ROADSIDEPARKING_ID 17
#define RESTAREA_ID 17
#define ROAD_SIDE_PARKING_VALUE 30
#define REST_AREA_VALUE 40
#define STATICCAR 1
#define ATTR_SET ".<xmlattr>"
#define DECIMAL_BASE 10
// #define SAFE_STRING_POS 4
#define ROAD_SIDE_PARKING_STRING_POS 15
#define REST_AREA_STRING_POS 8
int is_ego_vehicle = 0;

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
        // int safetyAreaValue;
		int roadSideParkingValue;
		int restAreaValue;
    };

	// Containers to save the objects based on object ID
	// std::vector<PrescanObject> safeAreaObjects;
	std::vector<PrescanObject> roadSideParkingObjects;
	std::vector<PrescanObject> restAreaObjects;
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
	void load_actor(boost::property_tree::ptree::value_type& local_ptree, int u_id, int type_id, int road_side_parking_value, int rest_area_value)
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
		// Obj.safetyAreaValue = safe_value;
		Obj.roadSideParkingValue = road_side_parking_value;
		Obj.restAreaValue = rest_area_value;
		
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
		// if(type_id == SAFEAREA)
		// {
		// 	safeAreaObjects.push_back(Obj);
		// }
		if(type_id == ROADSIDEPARKING_ID && road_side_parking_value != 0)
		{
			roadSideParkingObjects.push_back(Obj);
		}
		if(type_id == RESTAREA_ID && rest_area_value != 0)
		{
			restAreaObjects.push_back(Obj);
		}
		if(type_id == STATICCAR && road_side_parking_value != -1 && rest_area_value != -1)
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

		ptree pt_experiment = pt.get_child("Experiment");

		// int safety_area_value = 0;
		int road_side_parking_value = 0;
		int rest_area_value = 0;
		int u_id = 0;
		int obj_id = 0;
        
		
		// looping through the entire xml
		BOOST_FOREACH(ptree::value_type& val_experiment, pt.get_child("Experiment"))
		{
			// checking if the child node is "Actors" in "Experiment"
			if (val_experiment.first == "Actors")
			{
				// tree with all the child nodes inside "Actors"
				ptree pt_actors = pt_experiment.get_child("Actors");
				// looping through all the child nodes inside "Actors"
				BOOST_FOREACH(ptree::value_type& val_actors, pt_actors)
				{
					// tree with all the attributes of each "Actor"
					ptree pt_actor_attr = val_actors.second.get_child("<xmlattr>");
					// tree whose all the child nodes of Trajectories
					ptree pt_tra = val_actors.second.get_child("Trajectories");
					// looping through the attributes of "Actor"
					BOOST_FOREACH(ptree::value_type& val_actor_attr, pt_actor_attr)
					{
						//std::cout << "Values: " << val_actor_attr.first.data() << ":" <<val_actor_attr.second.data()<< std::endl;
						// populating the u_id with the data of the attribute name "UniqueId"
						if(val_actor_attr.first == "UniqueId")
						{
							u_id = strtol(val_actor_attr.second.data().c_str(),NULL,DECIMAL_BASE);
						}
						// populating the obj_id with the data of the attribute name "ObjectTypeID"
						if(val_actor_attr.first == "ObjectTypeID")
						{
							obj_id = strtol(val_actor_attr.second.data().c_str(),NULL,DECIMAL_BASE);
						}
                        if(val_actor_attr.first == "Description")
                        {
                            std::string abc = val_actor_attr.second.data();
                            if(abc == "EGO_VEHICLE")
                            {
                                // safety_area_value = -1;
								road_side_parking_value = -1;
								rest_area_value = -1;
                            }
                        }

						//std::cout << "After Values: " << val_actor_attr.first.data() << ":" <<u_id<<":" <<obj_id<< std::endl;
					}
					
					// Checking if the "Trajectory" node has a child named "TrajectoryBase"
					optional< ptree& > child = pt_tra.get_child_optional("TrajectoryBase");
					if( !child )
                    {
                        //std::cout << "Trajectory not found" << u_id <<std::endl;
                        load_actor(val_actors, u_id, obj_id, road_side_parking_value, rest_area_value);
                        // safety_area_value = 0;
						road_side_parking_value = 0;
						rest_area_value = 0;

                    }
                    else
                    {
                        //std::cout << "Dynamic Actor" << u_id <<std::endl;
                        //is_ego_vehicle = 0;
                    }				
				}
			}

			// checking if the child node is "Environment" in "Experiment"
            if (val_experiment.first == "Environment")
            {
                // looping through all the child nodes inside "Environment"
                BOOST_FOREACH(ptree::value_type& val_environment, pt_experiment.get_child("Environment"))
                {
                    // checking if the child node is "Underlays" in "Environment"
                    if (val_environment.first == "Underlays")
                    {
                        // looping through all the child nodes inside "Underlays"
                        BOOST_FOREACH(ptree::value_type& val_underlays, val_experiment.second.get_child("Underlays"))
                        {
                            road_side_parking_value = 0;
                            rest_area_value = 0;
                            // tree with all the attributes of each "Underlay"
                            ptree pt_Underlay_Attr = val_underlays.second.get_child("<xmlattr>");
                            BOOST_FOREACH(ptree::value_type& val_underlay_attr, pt_Underlay_Attr)
                            {
                                // populating the safety_area_value with the data of the attribute name "Description"
                                if(val_underlay_attr.first == "Description")
                                {
                                    // checking the codition if the attribute "Description" has the value "SAFE" in it
                                    // if(val_underlay_attr.second.data().size()>=SAFE_STRING_POS && val_underlay_attr.second.data().substr(0,SAFE_STRING_POS) == "SAFE")
                                    // {
                                    //     safety_area_value = strtol(val_underlay_attr.second.data().substr(SAFE_STRING_POS).c_str(),NULL,DECIMAL_BASE);
                                    // }
									// checking the condition if the attritbute "Description" has the value "roadSideParking" in it
									if(val_underlay_attr.second.data().size()>=ROAD_SIDE_PARKING_STRING_POS && val_underlay_attr.second.data().substr(0,ROAD_SIDE_PARKING_STRING_POS) == "roadSideParking")
									{
										road_side_parking_value = ROAD_SIDE_PARKING_VALUE;
									}
									// checking the condition if the attribute "Description" has the value "restArea" in it
									if(val_underlay_attr.second.data().size()>=REST_AREA_STRING_POS && val_underlay_attr.second.data().substr(0,REST_AREA_STRING_POS) == "restArea")
									{
										rest_area_value = REST_AREA_VALUE;
									}
                                }
                                // populating the u_id with the data of the attribute name "UniqueId"
                                if(val_underlay_attr.first == "UniqueId")
                                {
                                    u_id = strtol(val_underlay_attr.second.data().c_str(),NULL,DECIMAL_BASE);
                                }
                                // populating the obj_id with the data of the attribute name "ObjectTypeID"
                                if(val_underlay_attr.first == "ObjectTypeID")
                                {
                                    obj_id = strtol(val_underlay_attr.second.data().c_str(),NULL,DECIMAL_BASE);
                                }
                            }
                            load_actor(val_underlays, u_id, obj_id, road_side_parking_value, rest_area_value);						
                        }
                    }
                }
            }
		}
	}
};

#endif