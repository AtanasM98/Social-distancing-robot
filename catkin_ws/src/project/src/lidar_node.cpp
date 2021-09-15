#include "ros/ros.h"
#include <stdio.h>
#include <sensor_msgs/LaserScan.h>
#include "std_msgs/Float32.h"


double closestDistance;
double robotSize = 0.6;


double minDistance = 2;
int minRange = 150;
int maxRange = 195;

ros::Publisher EmergencyPublisher;

void emergencyStop(double range)
{
  std_msgs::Float32 msg;
  msg.data = range;
  EmergencyPublisher.publish(msg);
}

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan_msg)
{
  closestDistance = scan_msg->range_max; 
  for (int i = 0; i < (int) scan_msg->ranges.size(); i++) 
  {
    if(i >= minRange && i <= maxRange)
    {
      double range = scan_msg->ranges[i];
      if ((range > 0.2) && (range < minDistance)) 
      { // closest distance to obstacle, excluding parts of the robot
        closestDistance = range;
        emergencyStop(closestDistance);
          
      }
    }

  }
//   std::cout << "closest_distance: " << closestDistance << ", closest i: " << closestI << "\n";
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "escape_behavior");
  ros::NodeHandle n;
  n.param("minRange", minRange, minRange);
  n.param("maxRange", maxRange, maxRange);
  n.param("minDistance", minDistance, minDistance);
  EmergencyPublisher = n.advertise<std_msgs::Float32>("/emergency_brake",1, false);
  ros::Subscriber scanSub = n.subscribe("/scan", 100, scanCallback);
  ros::spin();
  return 0;
}