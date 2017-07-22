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
#include <baxter_core_msgs/EndEffectorState.h>
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
float ten_x;
float nine_x;
float eight_x;
float ten_y;
float nine_y;
float eight_y;
float ten_z;
float nine_z;
float eight_z;


bool test_right = false;
bool test_left = false;
bool test_center = false;
bool goal_left = false;
bool goal_right = false;
bool case1 = true;
bool case2 = false;
bool case3 = false;
bool case4 = false;
bool case5 = false;
bool case6 = false;
bool case7 = false;
bool case8 = false;
bool case9 = false;
bool case10 = false;

int left_done;
int right_done;

void cb1(geometry_msgs::Pose posMsg){
    pos_mark8 = posMsg;   
    test_left = true; 
}

/*void callBackFunction_left(baxter_core_msgs::EndEffectorState::ConstPtr& stateMsg){
    left_done = stateMsg->gripping;
}

void callBackFunction_right(baxter_core_msgs::EndEffectorState::ConstPtr& stateMsg2){
    right_done = stateMsg2->gripping;
}
*/
void cb2(geometry_msgs::Pose posMsg){
    pos_mark9 = posMsg;   
    test_right = true; 
}


void cb3(geometry_msgs::Pose posMsg){
    pos_mark10 = posMsg;   
    test_center = true; 
}

void call(std_msgs::Int32 GoalMsg){
    goal_n = GoalMsg.data; 
    if (goal_n == 0) goal_left = true; 
    if (goal_n == 1) goal_right = true; 
    std::cout << "goal received = " << goal_n << std::endl;
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

    // ros::Subscriber left_grasp = node.subscribe("/robot/end_effector/left_gripper/state", 1, callBackFunction_left);
    //ros::Subscriber right_grasp = node.subscribe<baxter_core_msgs::EndEffectorState>("/robot/end_effector/right_gripper/state", 1, callBackFunction_right);

    ros::Subscriber final_position  = node.subscribe<std_msgs::Int32>("/controllerGoalReached",1,call) ;

        ros::Publisher go_to = node.advertise<std_msgs::String>("/control_baxter/ros_cmd_bridge", 1000);

        ros::Rate rate(50);   // Or other rate.
        //pause(1);
    sleep(1);
        while (ros::ok()){
        if (test_center && case1) {
                std::stringstream cmdStr_l;
                cmdStr_l << "cartPos left ";
                cmdStr_l << "-1.811 -0.059 -2.989 " << pos_mark10.position.x << " " << (pos_mark10.position.y+0.08) << " " << (pos_mark10.position.z-0.037);

                    // cmdStr_l.str();
                    std_msgs::String cmdstring;
                    cmdstring.data = cmdStr_l.str();
            go_to.publish(cmdstring);
            case1 = false;
            case2 = true;
        }
        if (case2 && goal_left) {
            goal_left = false;
                std::stringstream cmdStr_l;
                cmdStr_l << "closeGrip left";
                    // cmdStr_l.str();
                    std_msgs::String cmdstring;
                    cmdstring.data = cmdStr_l.str();
            go_to.publish(cmdstring);
            case2 = false;
            case3 = true;
        }
        if (case3 && test_right) {
                std::stringstream cmdStr_r;
                cmdStr_r << "cartPos right ";
                nine_x = pos_mark9.position.x;
                nine_y = pos_mark9.position.y;
                nine_z = pos_mark9.position.z;
                cmdStr_r << "-1.657 -0.052 3.115 " << (pos_mark9.position.x-0.07) << " " << (pos_mark9.position.y+0.08) << " " << (pos_mark9.position.z-0.037) ;

                    // cmdStr_l.str();
                    std_msgs::String cmdstring;
                    cmdstring.data = cmdStr_r.str();
            go_to.publish(cmdstring);
            case3 = false;
            case4 = true;
        }
        
        if (case4 && goal_right) {
            goal_right = false;
                std::stringstream cmdStr_l;
                cmdStr_l << "cartPos right ";
        
                cmdStr_l << "-1.657 -0.052 3.115 " << (nine_x-0.07) << " " << (nine_y-0.15) << " " << (nine_z-0.037);

                    // cmdStr_l.str();
                    std_msgs::String cmdstring2;
                    cmdstring2.data = cmdStr_l.str();
            go_to.publish(cmdstring2);
            case4 = false;
            case5 = true;
        }
        if (case5 && goal_right) {
            goal_right = false;
                std::stringstream cmdStr_l;
                cmdStr_l << "cartPos right ";
        
                cmdStr_l << "-1.657 -0.052 3.115 " << (nine_x+0.18) << " " << (nine_y-0.15) << " " << (nine_z-0.037);

                    // cmdStr_l.str();
                    std_msgs::String cmdstring2;
                    cmdstring2.data = cmdStr_l.str();
            go_to.publish(cmdstring2);
            case5 = false;
            case6 = true;
        }
        if (case6 && goal_right) {
            goal_right = false;
                std::stringstream cmdStr_l;
                cmdStr_l << "cartPos right ";
        
                cmdStr_l << "-1.657 -0.052 3.115 " << (nine_x+0.18) << " " << (nine_y) << " " << (nine_z-0.037);

                    // cmdStr_l.str();
                    std_msgs::String cmdstring2;
                    cmdstring2.data = cmdStr_l.str();
            go_to.publish(cmdstring2);
            case6 = false;
            case7 = true;
        }
        if (case7 && goal_right) {
            goal_right = false;
                std::stringstream cmdStr_l;
                cmdStr_l << "cartPos right ";
        
                cmdStr_l << "-1.657 -0.052 3.115 " << (nine_x+0.1) << " " << (nine_y) << " " << (nine_z+0.1);

                    // cmdStr_l.str();
                    std_msgs::String cmdstring2;
                    cmdstring2.data = cmdStr_l.str();
            go_to.publish(cmdstring2);
            case7 = false;
            case8 = true;
        }
        if (case8 && goal_right) {
            goal_right = false;
                std::stringstream cmdStr_l;
                cmdStr_l << "cartPos right ";
        
                cmdStr_l << "-1.657 -0.052 3.115 " << (pos_mark10.position.x) << " " << (pos_mark10.position.y-0.8) << " " << (pos_mark9.position.z-0.037);

                    // cmdStr_l.str();
                    std_msgs::String cmdstring2;
                    cmdstring2.data = cmdStr_l.str();
            go_to.publish(cmdstring2);
            case8 = false;
            case9 = true;
        }
        if (case9 && goal_right) {
            goal_right = false;
                std::stringstream cmdStr_l;
                cmdStr_l << "closeGrip right";

                    // cmdStr_l.str();
                    std_msgs::String cmdstring2;
                    cmdstring2.data = cmdStr_l.str();
            go_to.publish(cmdstring2);
            case9 = false;
            case10 = true;
        }
            ros::spinOnce();
        }

        rate.sleep();
}


