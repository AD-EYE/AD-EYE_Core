Wrote by Zacharie Baeumlin (zbaeumlin@gmail.com) on September 22, 2022

This README file aims to explain how to use the c++ code database_influence_local_planning which influence the local planner in simulations so the ego car avoids obstacles.

The goal is to integrate and use the data from the SQL database in AD-EYE simulation – how it can influence the planning stack.
This project consists in linking the database and the simulation, to use realistic data, such as potholes that must be avoided by the car.

Steps of the code database_influence_local_planning:
First the ROS and visualisation objects are initialised. 
Then a request is sent to the SQL database and the data bout the obstacles is parsed and printed.
After that, for every waypoint of each lane, it checks if the waypoint is inside any obstacle area, i.e. if any lane collides with the obstacle.
In that case the lane is blocked, so the ego car has to find another trajectory.
The parameters of each lane are printed.

A SQL database has to exist with the right format. It can be created by using Workbench and running SQL scripts in the folder "SQL script for local planner influencer" in src.

The code was tested on the world W01_Base_Map. On Prescan, dirt spots were added at the location of the potholes, and a WorldViewer was added to the ego car. 

The code has to run separately from the simulation launcher. 
So start a simulation and when the car is initialized on RVIZ, launch this code with ros in a new terminal.
Then add the marker array in RVIZ, the one published on the topic "/adeye/obstacle_visualisation".



For more information, here is the link to my subproject folder on Onedrive with my reports:
https://kth-my.sharepoint.com/personal/naveenm_ug_kth_se/_layouts/15/onedrive.aspx?ga=1&id=%2Fpersonal%2Fnaveenm%5Fug%5Fkth%5Fse%2FDocuments%2FADEYE%5FOD%2FSub%20Projects%2FInternship%5FZacharie%5FBaeumlin%5FJune%5F2022  
