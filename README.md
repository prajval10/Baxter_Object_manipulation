# Baxter_Object_manipulation
This project was developed as part of the Erasmus EMARO Days challenge hackathon. It involves object recognition using a Kinect and two redundant cameras and grasping and manipulation using the Baxter robot.

# Perception
The ROS Node src/listener.cpp contains the perception module to track the AR tags on the object using the kinect and camera on each hand of the basxter.
A priority queue is set up for choosing the camera as sometimes the kinect goes off line of sight due to hand motion.
The ROS node listener publishes the pose commands to another ROS node lookup.cpp.

# Motion Planning
The ROS node src/lookup.cpp subscribes to the listener and publishes kinematic pose commands to the "/control_baxter/ros_cmd_bridge" topic. The controller subscribes to this topic and hence motion is produced.


