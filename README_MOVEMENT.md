# file contents explained

## pid.cpp and pid.h
in these files a simple pid is defined.

## carrot following
tns of maths, follows a path. 
limitations:
 - currently only finds a goal, can be easily edited to follow a path
 - Panicks when it moves more than _look-ahead-distance_ away. should be fixed to wait (maybe ask) for a new path to follow when this happens (shouldnt happen tho)
## movement_node.cpp
In this file most of the movement happens. Assuming the carrot is found. It will go in the function `getDesiredSpeed()` Here the angular and linear speed ar calculated.
To tune the PID look at line numbers *116 and 117*

the emergency brake is initiated by a message from the lidar, this will set a global boolean causing the program to exit quickly.
A new way to deal with this emergency brake,mainly being able to turn it off should be implemented. Another fix could be to go into escape behaviour by using an arbiter.

