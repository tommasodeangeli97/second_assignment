#include "ros/ros.h"
#include "second_assignment/manualplus.h"
#include "geometry_msgs/Twist.h"
#include "std_srvs/Empty.h"

ros::ServiceClient client;
std_srvs::Empty pos;
int util=2;
int count =1;

bool add (second_assignment::manualplus::Request &req, second_assignment::manualplus::Response &res){  // I verify the answers and increase or decrease the velocity or reset the position
	
	
	if (req.req == "plus"){
		count= count+1;
			
	}
	if (req.req == "less"){
		count = count-1;
		
	}
	
	if (req.req == "reset"){
		client.call(pos);
		count = 0;
	}
	res.res = 1.5*count;
	return true;
}

int main (int argc, char **argv){ //I give the instructions
	ROS_INFO("service manual: write -plus- to encrease the velocity, write -less- to decrease the velocity, write -reset- to reset the position, however the recommended speed is 1.5", util);
	ros::init(argc, argv, "splus");
	ros::NodeHandle n;
	
	client = n.serviceClient<std_srvs::Empty>("/reset_positions");
	
	ros::ServiceServer service= n.advertiseService("manualplus", add );
	
	
	ros::spin();
	
	return 0;
}
