//Cpp
#include <sstream>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <math.h>

#include <tf/transform_listener.h>
#include <geometry_msgs/Pose.h>
#include <tf/transform_broadcaster.h>
#include <ros/service_client.h>
#include <sensor_msgs/JointState.h>
#include <baxter_core_msgs/JointCommand.h>
#include <string.h>

// #include "inv_jac_baxter/InvJacBaxter.h"
#include <sensor_msgs/JointState.h>
#include <baxter_core_msgs/JointCommand.h>
#include <ros/service_client.h>
//ROS
#include "ros/ros.h"
//...
ros::Publisher hand_publisher1;
ros::Publisher hand_publisher2;
ros::Publisher hand_publisher3;

double Kp=1;
// Callback functions...
int goalstate;
bool msgAvailable = false;
geometry_msgs::Pose command_pose1;
geometry_msgs::Pose command_pose2;
geometry_msgs::Pose command_pose3;
bool framefail = false;	


// void cb(std_msgs::Int32 goalMsg){
// 	goalstate = goalMsg.data;    
// 	msgAvailable = true;
// }
int main (int argc, char** argv)
{



	//ROS Initialization
	ros::init(argc, argv, "listener_gp6");

    // Define your node handles
    // ...
	ros::NodeHandle node;
    // Read the node parameters if any
    // ...
	// ros::ServiceClient baxter_serv = node.serviceClient<inv_jac_baxter::InvJacBaxter>("inv_jac_baxter");

	// ros::Subscriber goalReached  = node.subscribe<std_msgs::Int32>("/controllerGoalReached",1,cb) ;

	tf::TransformListener listener_1;
	tf::TransformListener listener_2;
	tf::TransformListener listener_3;
	
	hand_publisher1 = node.advertise<geometry_msgs::Pose>("/geometryMsgPose_mark8",1);
	hand_publisher2 = node.advertise<geometry_msgs::Pose>("/geometryMsgPose_mark9",1);
	hand_publisher3 = node.advertise<geometry_msgs::Pose>("/geometryMsgPose_mark10",1);


    ros::Rate rate(10);   // Or other rate.

    while (ros::ok()){
    	
    	tf::StampedTransform transform1;
    	tf::StampedTransform transform2;
    	tf::StampedTransform transform3;

    	//doing for ar_mark 8
    	try{
    		listener_1.lookupTransform("/world","/ar_left_camera_8",ros::Time(0), transform1);
    		std::cout<<"left_cam 8"<<std::endl;
    	}
    	catch (tf::TransformException &ex) {
    		try{
    			listener_1.lookupTransform("/world","/ar_kinect_camera_8",ros::Time(0), transform1);
    			std::cout<<"kinect 8"<<std::endl;
    		}
    		catch(tf::TransformException &ex) {
    			try{listener_1.lookupTransform("/world","/ar_right_camera_8",ros::Time(0), transform1);
    			std::cout<<"right camera 8"<<std::endl;
    			}
    			catch(tf::TransformException &ex){
    				std::cout<<""<<std::endl;
    				ROS_ERROR("%s",ex.what());

    				rate.sleep();
    				continue;
    				}    				
    			// sleep(1);
    			// continue;
    			}
    		// sleep(1);	
    		// continue;
    		}


    	// 	    	//doing for ar_mark 9
    		try{
    			listener_2.lookupTransform("/world","/ar_right_camera_9",ros::Time(0), transform2);
    			std::cout<<"left_cam 9"<<std::endl;
    		}

    		catch (tf::TransformException &ex) {
    			try{
    				listener_2.lookupTransform("/world","/ar_kinect_camera_9",ros::Time(0), transform2);
    				std::cout<<"left_cam 9"<<std::endl;
    			}
    			catch(tf::TransformException &ex) {
    				try{
    					listener_2.lookupTransform("/world","/ar_left_camera_9",ros::Time(0), transform2);
    					std::cout<<"left_cam 9"<<std::endl;
    				}
    					catch(tf::TransformException &ex){
    						ROS_ERROR("%s",ex.what());
    						rate.sleep();
    						continue;
    					}
    					// sleep(1);
    					// continue;    				
    				}
    				// sleep(1);
    				// continue;
    			}


    	    		    	//doing for ar_mark 10
    			try{
    				listener_3.lookupTransform("/world","/ar_right_camera_10",ros::Time(0), transform3);
    				std::cout<<"left_cam 10"<<std::endl;
    			}
    			catch (tf::TransformException &ex) {
    				try{
    					listener_3.lookupTransform("/world","/ar_kinect_camera_10",ros::Time(0), transform3);
    					std::cout<<"left_cam 10"<<std::endl;
    				}
    				catch(tf::TransformException &ex) {
    					try{listener_3.lookupTransform("/world","/ar_left_camera_10",ros::Time(0), transform3);
    					std::cout<<"left_cam 10"<<std::endl;
    				}
    					catch(tf::TransformException &ex){
    						ROS_ERROR("%s",ex.what());
    						rate.sleep();
    						continue;
    					}    
    					// sleep(1);
    					// continue;				
    				}
    				// sleep(1);
    				// continue;
    			}



    			float marker_8x;
    			float marker_8y;
    			float marker_8z;

    			float marker_9x;
    			float marker_9y;
    			float marker_9z;

    			float marker_10x;
    			float marker_10y;
    			float marker_10z;

    			marker_8x = transform1.getOrigin().getX();
    			marker_8y = transform1.getOrigin().getY();
    			marker_8z = transform1.getOrigin().getZ();

    			marker_9x = transform2.getOrigin().getX();
    			marker_9y = transform2.getOrigin().getY();
    			marker_9z = transform2.getOrigin().getZ();

    			marker_10x = transform3.getOrigin().getX();
    			marker_10y = transform3.getOrigin().getY();
    			marker_10z = transform3.getOrigin().getZ();


    			command_pose1.position.x =  marker_8x;
    			command_pose1.position.y =  marker_8y;
    			command_pose1.position.z =  marker_8z;

    			command_pose2.position.x =  marker_9x;
    			command_pose2.position.y =  marker_9y;
    			command_pose2.position.z =  marker_9z;

    			command_pose3.position.x =  marker_10x;
    			command_pose3.position.y =  marker_10y;
    			command_pose3.position.z =  marker_10z;

    			hand_publisher1.publish(command_pose1);
    			hand_publisher2.publish(command_pose2);
    			hand_publisher3.publish(command_pose3);

    			ros::spinOnce();

    		}

    		rate.sleep();
    	}
