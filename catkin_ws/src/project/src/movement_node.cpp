#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "math.h"
#include "../include/pid.h"
#include "geometry_msgs/Point.h"
#include "std_msgs/Float32.h"
#include "tf/tf.h"
#include "tf2_msgs/TFMessage.h"
#include "nav_msgs/Odometry.h"
#include "carrot_following.cpp"

float STOPPING_DISTANCE = 1.8;


std::vector<geometry_msgs::Point>* pathPoints = new std::vector<geometry_msgs::Point>(); 
geometry_msgs::Twist currentspeed;
geometry_msgs::Pose currentPose;
PID* linpid;
PID* angpid;
bool GoalReached = true;
bool currentposeAvailable = false;
bool emergencyBrake = false;
geometry_msgs::Pose goal;

void onGoal(const geometry_msgs::Pose& msg)
{
    goal = msg;
    GoalReached= false;

}

void onTF( const tf2_msgs::TFMessage& msg )//const geometry_msgs::PoseStamped& msg )
{    
    // if( msg.transforms[0].child_frame_id == "base_footprint")
    // {
    //     currentPose.position.x = msg.transforms[0].transform.translation.x;
    //     currentPose.position.y = msg.transforms[0].transform.translation.y;
    //     currentPose.position.z = msg.transforms[0].transform.translation.z;
    //     currentPose.orientation = msg.transforms[0].transform.rotation;
    // }  
  
}

geometry_msgs::Twist limitLinSpeedByAngspeed(geometry_msgs::Twist SpeedProposal, double Threshold)
{
    double lin = SpeedProposal.linear.x;
    double ang = SpeedProposal.angular.z;
    
    if( abs(ang) < MAX_ANG_SPD * 0.5 )
    {
        lin = lin;
    }
    else
    {
        lin = lin - ( abs(ang) / 2 );
    }

    SpeedProposal.linear.x = lin;
    return SpeedProposal;
}

void updateSpeed(const nav_msgs::Odometry& msg)
{
    currentspeed=msg.twist.twist;
    currentPose = msg.pose.pose;
    currentposeAvailable = true;
}

geometry_msgs::Twist GetCurrentSpeed()
{
    return currentspeed;
}

//testing only.
double driveForward()
{
    return MAX_SPEED;
}

geometry_msgs::Twist GetdesiredSpeed(geometry_msgs::Pose currentPose, geometry_msgs::Pose carrot, double threshold)
{
    double linSpd, angSpd;
    geometry_msgs::Twist ret;
    geometry_msgs::Twist currentspd = GetCurrentSpeed();
    angSpd = CalcAngSpd(currentPose, carrot);
    
    linSpd = CalcLinSpd(currentPose,carrot);
    linSpd = linpid->calculate(linSpd,currentspd.linear.x);
    angSpd = angpid->calculate(angSpd, currentspd.angular.z);

    if (abs(angSpd) < 0.1)
    {
        ret.linear.x = linSpd;
        ret.angular.z = angSpd;
    }
    else
    {
        ret.linear.x = 0;
        ret.angular.z = angSpd;
    }
    ret = limitLinSpeedByAngspeed(ret,3);
        
    
    return ret;
}

void OnEmergencyBrake(const std_msgs::Float32& msg)
{
    emergencyBrake = true;        
}

void GoToGoal(ros::Publisher& pub)
{
    ros::Rate rate(ROBOT_FREQUENCY);

    linpid = new PID(1.0/ROBOT_FREQUENCY ,MAX_LIN_SPD, -MAX_LIN_SPD, 1, 0, 0);// last 3 values: Kp, Kd, Ki respectively.
    angpid = new PID(1.0/ROBOT_FREQUENCY, MAX_ANG_SPD, -MAX_ANG_SPD, 1, 0, 0);// last 3 values: Kp, Kd, Ki respectively.
    
    
    while ( ros::ok() && !emergencyBrake)
    {
        ros::spinOnce();

        while (! currentposeAvailable )
        {
            ros::spinOnce();
        }
        std::cout << "got a tf message" <<std::endl;//DEBUG
        
        // DEFINE CARROT
        geometry_msgs::Point carrot;
        carrot = calculateCarrot(currentPose, goal, 1);
        // now the carrot is defined, we have to calculate how to get there.
        geometry_msgs::Pose carrotPose;
        carrotPose.position = carrot;
        carrotPose.orientation.w = 1; // normalization with 0 rotation on each axis.
        
        geometry_msgs::Twist speed = GetdesiredSpeed(currentPose, carrotPose, 10);

        if (abs(goal.position.x - currentPose.position.x ) < 0.1 && abs(goal.position.y - currentPose.position.y ) < 0.1 && speed.angular.z < 0.05 && speed.linear.x < 0.05)
        {

            speed.linear.x = 0;
            speed.angular.z = 0;
            pub.publish(speed);
            break;
        }
        if (emergencyBrake)
        {
            speed.linear.x = 0;
        }
                std::cout << speed.linear.x;
        std::cout << speed.angular.z; 
        pub.publish( speed ); 
        rate.sleep(); 
    }

    // while (ros::ok() && !emergencyBrake)
    // {

    // }
    geometry_msgs::Twist speed;
    speed.linear.x = 0;
    speed.angular.z = 0;
    GoalReached = true;
    pub.publish(speed);
}


int main(int argc, char** argv)
{
    geometry_msgs::Point pt;
    
    ros::init(argc, argv, "Movement_node");
    ros::NodeHandle node;
    ros::Publisher pub = node.advertise<geometry_msgs::Twist>("/cmd_vel", 10, false);
    ros::Subscriber sub = node.subscribe("/odom",1,updateSpeed);
    ros::Subscriber posSub = node.subscribe("/tf", 1, onTF);
    ros::Subscriber EBsub = node.subscribe("/emergency_brake", 1, OnEmergencyBrake);
    ros::Subscriber goalsub = node.subscribe("/goal", 1, onGoal);
    while (ros::ok() && !emergencyBrake)
    {
        ros::spinOnce();
        if (!GoalReached )
        {
            std::cout << "New goal" << std::endl;
            GoToGoal(pub);
        }
    }
    

}








