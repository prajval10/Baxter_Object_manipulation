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
bool test_center = false;
bool goal_left = false;
bool goal_right = false;
bool case1 = true;
bool case2 = false;
bool case3 = false;
void cb1(geometry_msgs::Pose posMsg){
	pos_mark8 = posMsg;   
	test_right = true; 
}


void cb2(geometry_msgs::Pose posMsg){
    pos_mark9 = posMsg;   
    test_left = true; 
}


void cb3(geometry_msgs::Pose posMsg){
    pos_mark10 = posMsg;   
    test_center = true; 
}

void call(std_msgs::Int32 GoalMsg){
	goal_n = GoalMsg.data; 
	if (goal_n == 0) goal_left = true; 
	if (goal_n == 1) goal_right = true; 
}

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

	ros::Subscriber position8  = node.subscribe<geometry_msgs::Pose>("/geometryMsgPose_mark8",1,cb1) ;
	ros::Subscriber position9  = node.subscribe<geometry_msgs::Pose>("/geometryMsgPose_mark9",1,cb2) ;
	ros::Subscriber position10  = node.subscribe<geometry_msgs::Pose>("/geometryMsgPose_mark10",1,cb3) ;

	ros::Subscriber final_position  = node.subscribe<std_msgs::Int32>("/controllerGoalReached",1,call) ;

    	ros::Publisher go_to = node.advertise<std_msgs::String>("/control_baxter/ros_cmd_bridge", 1000);

    	ros::Rate rate(50);   // Or other rate.
    	//pause(1);
	sleep(1);
    	while (ros::ok()){
		if (test_center && case1) {
    			std::stringstream cmdStr_l;
    			cmdStr_l << "cartPos left ";
    	
    			cmdStr_l << "-1.811 -0.059 -2.989 " << pos_mark10.position.x << " " << pos_mark10.position.y << " " << (pos_mark10.position.z+0.05);

            		// cmdStr_l.str();
            		std_msgs::String cmdstring;
            		cmdstring.data = cmdStr_l.str();
			go_to.publish(cmdstring);
			case1 = false;
			case2 = true;
		}
		if (case2 && goal_left) {
			goal_left = true;
    			std::stringstream cmdStr_l;
    			cmdStr_l << "closeGrip left";
            		// cmdStr_l.str();
            		std_msgs::String cmdstring;
            		cmdstring.data = cmdStr_l.str();
			go_to.publish(cmdstring);
			case2 = false;
			case3 = true;
		}
/*		if (test_right && case3 && goal_left) {
			goal_left = false;
    			std::stringstream cmdStr_r;
    			cmdStr_r << "cartPos right ";

    			cmdStr_r << "0 0 0 " << pos_mark8.position.x << " " << pos_mark8.position.y << " " << (pos_mark8.position.z+0.1) ;

            		// cmdStr_l.str();
            		std_msgs::String cmdstring;
            		cmdstring.data = cmdStr_r.str();
			go_to.publish(cmdstring);
			case3 = false;
			case4 = true;
		}*/
    	
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


