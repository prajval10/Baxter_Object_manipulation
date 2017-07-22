//Cpp
#include <sstream>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <math.h>

#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <tf/transform_broadcaster.h>
#include <ros/service_client.h>
#include <sensor_msgs/JointState.h>
#include <baxter_core_msgs/JointCommand.h>
#include <string.h>
#include "std_msgs/Int32.h"
#include "std_msgs/String.h"

// #include "inv_jac_baxter/InvJacBaxter.h"
#include <sensor_msgs/JointState.h>
#include <baxter_core_msgs/JointCommand.h>
#include <ros/service_client.h>
//ROS
#include "ros/ros.h"
//...
double Kp=1;
// Callback functions...
int goal_n;
geometry_msgs::Pose pos_mark8;
geometry_msgs::Pose pos_mark9;
geometry_msgs::Pose pos_mark10;


bool test_right = false;
bool test_left = false;
bool test = false;
bool goal_left = false;
bool goal_right = false;

// void cb1(geometry_msgs::Pose posMsg){
// 	pos_mark8 = posMsg;   
// 	test_right = true; 
// }


// void cb2(geometry_msgs::Pose posMsg){
//     pos_mark9 = posMsg;   
//     test_left = true; 
// }


// void cb3(geometry_msgs::Pose posMsg){
//     pos_mark10 = posMsg;   
//     test = true; 
// }

// void call(std_msgs::Int32 GoalMsg){
// 	goal_n = GoalMsg.data; 
// 	if (goal_n == 0) goal_left = true; 
// 	if (goal_n == 1) goal_right = true; 
// }

ros::Publisher go_to;

int main (int argc, char** argv)
{

	//ROS Initialization
	ros::init(argc, argv, "lookup");

    	// Define your node handles
    	// ...
	ros::NodeHandle node;
   	// Read the node parameters if any
    	// ...
	// ros::ServiceClient baxter_serv = node.serviceClient<inv_jac_baxter::InvJacBaxter>("inv_jac_baxter");

	// ros::Subscriber position8  = node.subscribe<geometry_msgs::Pose>("/geometryMsgPose_mark8",1,cb1) ;
	// ros::Subscriber position9  = node.subscribe<geometry_msgs::Pose>("/geometryMsgPose_mark9",1,cb2) ;
	// ros::Subscriber position10  = node.subscribe<geometry_msgs::Pose>("/geometryMsgPose_mark10",1,cb3) ;

	// ros::Subscriber final_position  = node.subscribe<std_msgs::Int32>("/controllerGoalReached",1,call) ;

    go_to = node.advertise<std_msgs::String>("/control_baxter/ros_cmd_bridge", 5);

    ros::Rate rate(50);   // Or other rate.

    sleep(1);

     bool firstTime(true);
     int count(0);

     while (ros::ok()){
		//if (test_right & goal_right == false) {

        if(count == 5){
           std::stringstream cmdStr_r;
           cmdStr_r << "cartPos right ";

           cmdStr_r << "2.62 0.43 -3.04 0.5 -0.2 0.1";

           std::cout<< cmdStr_r.str() << std::endl;
            		// cmdStr_l.str();
           std_msgs::String cmdstring;
           cmdstring.data = cmdStr_r.str();
           go_to.publish(cmdstring);
           firstTime=false;
       }
       count++;

		//}

		/*if (test_left & goal_left == false) {
    			std::stringstream cmdStr_l;
    			cmdStr_l << "cartPos left ";
    	
    			cmdStr_l << "0 0 0 " << pos_mark9.position.x << " " << pos_mark9.position.y << " " << pos_mark9.position.z;

            		// cmdStr_l.str();
            		std_msgs::String cmdstring2;
            		cmdstring2.data = cmdStr_l.str();
			go_to.publish(cmdstring2);
		}*/
       ros::spinOnce();
   }

   rate.sleep();
}


