#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/String.h"
#include "sensor_msgs/LaserScan.h"
#include "second_assignment/manualplus.h"


#include <sstream>

ros::Publisher pub;
ros::ServiceClient client;

float max=0.0;
double max2=0.0;
float min=0.3;
float max3 =0.0;
float min3=0.3;

void seeCallback (const sensor_msgs::LaserScan::ConstPtr& msg){
	//ROS_INFO("sensor@[ang_min %f,ang_max %f,range_min %f,range_max %f, ranges %f]", 
	//msg->angle_min, msg->angle_max, msg->range_min, msg->range_max, msg->ranges[12]);
	int i=1;
	
	geometry_msgs::Twist vel;
	second_assignment::manualplus srv1;
	
	while (i){     //I control the distance between the robot and the circuit
		i=0;
		while (i<300){
			if (max< msg->ranges[i]){
				max= msg->ranges[i];
			}
			if (min> msg->ranges[i]){
				min= msg->ranges[i];
			}
			//ROS_INFO("fatto1 %f %f %f",max, msg->ranges[i], min);
			i++;
		}
		while (300<=i and i<=400){
			if (max2 < msg->ranges[i]){
				max2 = msg->ranges[i];
			}
			//ROS_INFO("fatto2 %f %f",max2, msg->ranges[i]);
			i++;
		}
		
		while (i>400 and i<700){
			if (max3 < msg->ranges[i]){
				max3 = msg->ranges[i];
			}
			if (min3> msg->ranges[i]){
				min3= msg->ranges[i];
			}
			//ROS_INFO("fatto3 %f %f %f",max3, msg->ranges[i], min3);
			i++;			
		}
		
		
		if (max2 > 1.0){   //here I put differents velocities and angulations
			client.waitForExistence();
			client.call(srv1);
			vel.linear.x=0.0+srv1.response.res;
			
			vel.angular.z=0;
		}
		if (min < 0.3){
			vel.linear.x=0.5;
			vel.angular.z=800;
		}
		if (min3 < 0.3){
			vel.linear.x=0.5;
			vel.angular.z=-800;
		}
		if (max2 <= 1.0){
			vel.linear.x=0;
			if (max3> max){
				vel.angular.z=900;
			}
			else{
				vel.angular.z=-900;
			}
		}
		pub.publish(vel);
		i=0;   //here i reset the parameters
		max=0.0;
		max2=0.0;
		max3=0.0;
		vel.angular.z=0;
		
		min= 0.3;
		min3=0.3;
	}
	
}

int main (int argc, char **argv){

	ros::init( argc, argv, "controllo_node");	
	ros::NodeHandle n;
	
	client = n.serviceClient<second_assignment::manualplus>("/manualplus");
	
	
	
	pub = n.advertise<geometry_msgs::Twist>("cmd_vel",100);
	ros::Subscriber sub = n.subscribe("base_scan", 1, seeCallback);
	
	
	
	ros::spin();

	return 0;
}
