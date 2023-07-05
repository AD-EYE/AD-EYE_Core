/* ROS to CAN listener */
/* 
  Code written to enable listening to ROS topics and their published messages in order to send
  datagram packages containing the data in the ROS messages to the CANoe software. This script
  was made as part of the AD-EYE project by mechatronics students of KTH during 2022.
  Code written by Axel Hedvall, Ehab Raheem, Oscar Poveda and Shaya Rahmanian.
*/
#include "roslisten.h"
#include "rossocketUDP.h"
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/Bool.h>

// Declare external variables where values will be stored
struct sockaddr_in si_ros;
int s_ros;
struct group frames[20];

/** Initialize the Data Frame of the Group Structure
 * @brief 
 * This function will initialize the group structure if it hasn't already,
 * by inputting the parameters the structure will be allocated with the necessary
 * memory in order to save the variables needed to construct the datagram package
 * 
 * @param arg_index
 * Group ID for the FDX datagram, specified in the CANoe FDX xml editor
 * @param arg_csize 
 * Command size for the FDX datagram, specified in the CANoe FDX xml editor
 */
void InitDataFrame(int arg_index, int arg_csize){
  if (frames[arg_index].cSize==(uint16_t)arg_csize) return;
  frames[arg_index].cGroupID=(uint16_t)arg_index;
  frames[arg_index].cSize=(uint16_t)arg_csize;
  frames[arg_index].commandlist = (uint8_t*) malloc(sizeof(uint8_t)*arg_csize);
}

/** Activate AD through XBOX 360 controller
 * @brief 
 * if the start button on the XBOX 360 controller is pressed, AD mode will be activated.
 * Function saves the values to the specified group structure as the correct datatype (uint8_t), 
 * and then sends it using the socketSend_FDX function as specified in the rossocketUDP.cpp
 * 
 * @param btn
 * bool for start btn to check if true or not
 */
void sendStart(bool btn)
{
  if (!btn) return;

  ROS_INFO("Start\n");
  InitDataFrame(0,7);

  // Values required to enter AD mode
  frames[0].commandlist[0] = (uint8_t) 2;
  frames[0].commandlist[1] = (uint8_t) 1;
  frames[0].commandlist[2] = (uint8_t) 1;
  frames[0].commandlist[3] = (uint8_t) 1;
  frames[0].commandlist[4] = (uint8_t) 1;
  frames[0].commandlist[5] = (uint8_t) 1;
  frames[0].commandlist[6] = (uint8_t) 1;

  socketSend_FDX(s_ros, si_ros, DataExchange, frames[0]);
}

//Old Steering structure, should be used in the future to connect instead to twist topic?
/*
void JoyCon(const sensor_msgs::Joy::ConstPtr& msg){
  
   //Using the callback function just for subscribing  
   //Subscribing the message and storing it in 'linx' and 'angZ'
  ROS_INFO("Joy axes: [%f]\n ", msg->axes[0]);

  InitDataFrame(1,4);

  //declare integers
  //frames[1].commandlist[0] = (uint8_t) ((msg->axes[0] +1)*255/2);
  string s = float2ASCII(msg->axes[0]/100);
  frames[1].commandlist[0] = s[0];
  frames[1].commandlist[1] = s[1];
  frames[1].commandlist[2] = s[2];
  frames[1].commandlist[3] = s[3];
  
  socketSend_FDX(s_ros, si_ros, DataExchange, frames[1]);
}
*/

/*values to be used for open loop controller*/
float lastRef = 0;
float ref_val;
int   kp = 1;
int   ki = 0.5;

/** Joystick Steering for XBOX 360 controller
 * @brief 
 * Function receives the joysticks directional value from the left directional stick,
 * saves the values to the specified group structure as the correct datatype (uint8_t)
 * and then sends it using the socketSend_FDX function as specified in the rossocketUDP.cpp
 * 
 * @param f
 * float containing values ranging from [-1, 1] where -1 is rightmost and 1 is leftmost
 * 
 */
void JoyCon(float f){
  
  // For steering 32388 is maximum left, 0 maximum right, 32388/2 neutral
  ROS_INFO("Joy axes: [%f]\n ", f);

  // Initialize the group
  InitDataFrame(1,2);

  // Shitty PI controller 
  ref_val = kp*(f +1) + ki*(lastRef);
  lastRef += (f+1)-ref_val;

  // uint16_t expected by the CANoe (taken from the database),
  // the values were reverse engineered from the CANoe software,
  // might cause issues so proper values should be asked from Volvo
  uint16_t convert = (uint16_t) ((ref_val)*16194);
  if(convert < 0){convert =0;}
  else if(convert > 32388){convert = 32388;}
  // Declare integers
  // (As the FDX expects a uint16_t this needs to be broken
  // down into uint8_t to follow the structure and be sent)
  frames[1].commandlist[0] = (convert & 0x00FF);
  frames[1].commandlist[1] =(convert & 0xFF00) >> 8;


  socketSend_FDX(s_ros, si_ros, DataExchange, frames[1]);
}

/** Shift gears using the XBOX 360 controller
 * @brief 
 * Function receives the status of the A button, if the button is pressed
 * the gears will shift into normal driving position.
 * 
 * @param btn
 * bool for the A btn 
 * 
 */
void shiftGears(bool btn)
{
  if (!btn) return;

  ROS_INFO("Start\n");
  // Initialize the group
  InitDataFrame(3,5);

  // Values required to shift into drive
  frames[3].commandlist[0] = (uint8_t)2;
  frames[3].commandlist[1] = (uint8_t)1;
  frames[3].commandlist[2] = (uint8_t)2;
  frames[3].commandlist[3] = ((uint16_t)1 & 0x00FF);
  frames[3].commandlist[4] = ((uint16_t)1 & 0xFF00)>>8;


  socketSend_FDX(s_ros, si_ros, DataExchange, frames[3]);
}

//Activate HazardLights
int lastHazard = 0;
/** Activate Hazardlights using the XBOX 360 controller
 * @brief 
 * Function receives the status of the Y button, if the button is pressed
 * the hazard lights will activate
 * 
 * @param msg
 * Following the ROS structure of sensor_msgs::Joy::ConstPtr to receive
 * the msg published and extract the button status
 * 
 */
void frame2(const sensor_msgs::Joy::ConstPtr& msg)
{
  if (msg->buttons[3] == 1){ lastHazard = 1 - lastHazard; }

  ROS_INFO("Joy buttons: [%d]\n", lastHazard);
  InitDataFrame(2,2);
  //declare integers
  frames[2].commandlist[0] = (uint8_t) (msg->buttons[3]);
  frames[2].commandlist[1] = (uint8_t) (1 - msg->buttons[3]);  

  socketSend_FDX(s_ros, si_ros, DataExchange, frames[2]);
  //send here?
}

// Bool declarations
bool lastYBtn;
bool lastStartBtn;
bool lastGearBtn;
float lastXAxis;

/** Callback function from ROS 
 * @brief 
 * Simple callback function that then calls the required vehicle function depending on the
 * joystick state (i.e. is the start button pressed in -> go to activate)
 * 
 * @param msg
 * Following the ROS structure of sensor_msgs::Joy::ConstPtr to receive
 * the msg published and extract the button status
 * 
 */
void ControllerCallback(const sensor_msgs::Joy::ConstPtr& msg)
{
  // Activate Hazardlights using the Y button
  if ((msg->buttons[3] == 1) != lastYBtn) 
  {
    lastYBtn = msg->buttons[3] == 1;

    frame2(msg);
  }

  // Old defunct callback to joy steering, not in use
  if (msg->axes[0] != lastXAxis)
  {
    lastXAxis = msg->axes[0];
    //JoyCon(lastXAxis);
  }

  // Activate AD mode using the Start button
  if ((msg->buttons[7] == 1) != lastStartBtn)
  {
    lastStartBtn = msg->buttons[7] == 1;
    sendStart(lastStartBtn);
  }

  // Shift gear into drive using the A button
  if ((msg->buttons[0] == 1) != lastGearBtn)
  {
    lastGearBtn = msg->buttons[0] == 1;
    shiftGears(lastGearBtn);
  }
}

/** 
 * @brief 
 * Main function that connects the callback function to the ROS topic by subscribing to it
 * Initializes the node ros2can
 * 
 * @param argc
 * Pass through to ROS node
 * @param argv
 * Pass through to ROS node
 * @param si_other
 * structure containing adress and port of socket 
 * 
 */
int rosMain(int argc, char **argv, int s, struct sockaddr_in si_other){
    si_ros = si_other;
    s_ros = s;
    ros::init(argc, argv, "ros2can");
    ros::NodeHandle n;
    //Arguments: Topic, queue size, functioncall
    //ros::Subscriber sub1 = n.subscribe("Twist", 1000, frame0);
    //ros::Subscriber sub2 = n.subscribe("joy", 10, JoyCon);
    //ros::Subscriber sub3 = n.subscribe("joy", 10, frame2);
    ros::Subscriber sub3 = n.subscribe("joy", 10, ControllerCallback);  
    ros::Rate r(5); // 5 hz
    while (ros::ok())
    {
      JoyCon(lastXAxis);
      ros::spinOnce();
      r.sleep();
    }

    return 0;
}