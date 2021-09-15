# Settings for lidar

If you want to change the settings for the lidar goto: "catkin_ws/src/project/models/bot/bierBot/model.sdf" find the sensor named "head_hokuyo_sensor".

Here you can change the settings for the lidar:

### scan:
- Samples: means how many times the lidar scans per revolution.
- Resolution: is the step between the scans.
- Min/max: angle is the range the lidar scans in.

### range:
- Min: the minimal scan distance the lidar sees.
- Max: the max range of the lidar.
- Resolution: the sensitivity of the lidar.


# Settings for driving

If you want to change the settings for the driving goto: "catkin_ws/src/project/models/bot/bierBot/model.sdf" find the plugin named "differential_drive_controller".

Here you can change the settings for driving:

- AlwaysOn: change this to false if you want to turn the driving module on via software.
- LeftJoint: is the left wheel link.
- RightJoint: is the right wheel link.
- WheelSeparation: the distance between the center of the wheels.
- WheelDiameter: the diameter of the wheels.
- Torque: the max torque that can be aplied to the robot.
- CommandTopic: the topic the robot uses to get commands.
- OdometryTopic: the topic you want to publish odometry to.
- OdometryFrame: the frame you want to use for odometry.
- RobotBaseFrame: the base link of the robot.