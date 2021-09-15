#ifndef CARROT_FOLLOWING_CPP
#define CARROT_FOLLOWING_CPP
#include "ros/ros.h"
#include "tf/tf.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseStamped.h"
#include "nav_msgs/Path.h"
#include "ros/header.h" 
#include "tf2_msgs/TFMessage.h"
#include "tf2_ros/transform_listener.h"
#include "angles/angles.h"
#include <numeric>

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_LIN_SPD 1// m/s
#define MAX_ANG_SPD 0.5// rad/s
#define ROBOT_FREQUENCY 50 // Hertz
#define MAX_SPEED 1 // m/s

geometry_msgs::Point pointAdd( geometry_msgs::Point a, geometry_msgs::Point b )
{
    geometry_msgs::Point ret;
    ret.x = a.x + b.x;
    ret.y = a.y + b.y;
    ret.z = a.z + b.z;
    return ret;
}

geometry_msgs::Point pointSub( geometry_msgs::Point a, geometry_msgs::Point b )
{
    geometry_msgs::Point ret;
    ret.x = a.x - b.x;
    ret.y = a.y - b.y;
    ret.z = a.z - b.z;
    return ret;
}

double innerProduct( geometry_msgs::Point a, geometry_msgs::Point b )
{
    return a.x * b.x + a.y * b.y;
}

/*
        find two intersections with lookahead circle
        place carrot in intersection closest to p1
        return carrot

        return:
        -2 endpoint is final point, and is closer than r.
*/


const double eps = 1e-14;
 
typedef struct point_t {
    double x, y;
} point;
 
point make_point(double x, double y) {
    point p = { x, y };
    return p;
}
 
void print_point(point p) {
    double x = p.x;
    double y = p.y;
    if (x == 0) {
        x = 0;
    }
    if (y == 0) {
        y = 0;
    }
    printf("(%g, %g)", x, y);
}
 
double sq(double x) {
    return x * x;
}

bool within(double x1, double y1, double x2, double y2, double x, double y) {
    double d1 = sqrt(sq(x2 - x1) + sq(y2 - y1));    // distance between end-points
    double d2 = sqrt(sq(x - x1) + sq(y - y1));      // distance from point to one end
    double d3 = sqrt(sq(x2 - x) + sq(y2 - y));      // distance from point to other end
    double delta = d1 - d2 - d3;
    return fabs(delta) < eps;   // true if delta is less than a small tolerance
}
 
int rxy(double x1, double y1, double x2, double y2, double x, double y, bool segment, point* pt) {
    if (!segment || within(x1, y1, x2, y2, x, y)) {
        //print_point(make_point(x, y));
        *pt = make_point(x, y);
        return 1;
    } else {
        return 0;
    }
}
 
double fx(double A, double B, double C, double x) {
    return -(A * x + C) / B;
}
 
double fy(double A, double B, double C, double y) {
    return -(B * y + C) / A;
}
 
// Prints the intersection points (if any) of a circle, center 'cp' with radius 'r',
// and either an infinite line containing the points 'p1' and 'p2'
// or a segment drawn between those points.
int intersects( point p1, point p2, point cp, double r, bool segment, point* hit1, point* hit2 ) {
    double x0 = cp.x, y0 = cp.y;
    double x1 = p1.x, y1 = p1.y;
    double x2 = p2.x, y2 = p2.y;
    double A = y2 - y1;
    double B = x1 - x2;
    double C = x2 * y1 - x1 * y2;
    double a = sq(A) + sq(B);
    double b, c, d;
    bool bnz = true;
    int cnt = 0;
 
    if (fabs(B) >= eps) {
        // if B isn't zero or close to it
        b = 2 * (A * C + A * B * y0 - sq(B) * x0);
        c = sq(C) + 2 * B * C * y0 - sq(B) * (sq(r) - sq(x0) - sq(y0));
    } else {
        b = 2 * (B * C + A * B * x0 - sq(A) * y0);
        c = sq(C) + 2 * A * C * x0 - sq(A) * (sq(r) - sq(x0) - sq(y0));
        bnz = false;
    }
    d = sq(b) - 4 * a * c; // discriminant
    if (d < 0) {
        // line & circle don't intersect
        printf("No intersection");
        return 0;
    }
 
    if (d == 0) 
    {
        // line is tangent to circle, so just one intersect at most
        if (bnz) 
        {
            double x = -b / (2 * a);
            double y = fx(A, B, C, x);
            point pt;
            cnt = rxy(x1, y1, x2, y2, x, y, segment, &pt);
            if( cnt == 1 )
            {
                *hit1 = pt;
                return 1;
            }
            return 0;
        } 
        else 
        {
            double y = -b / (2 * a);
            double x = fy(A, B, C, y);
            point pt;
            cnt = rxy(x1, y1, x2, y2, x, y, segment, &pt);
            if( cnt == 1 )
            {
                *hit1 = pt;
                return 1;
            }
            return 0;
        }
    } 
    else 
    {
        // two intersects at most
        d = sqrt(d);
        point p1, p2;
        int cnt2 = 0;
        if (bnz) 
        {
            double x = (-b + d) / (2 * a);
            double y = fx(A, B, C, x);
            cnt = rxy(x1, y1, x2, y2, x, y, segment, &p1);
            if( cnt == 1 )
            {
                cnt2++;
                *hit1 = p1;
            }
 
            x = (-b - d) / (2 * a);
            y = fx(A, B, C, x);
            cnt = rxy(x1, y1, x2, y2, x, y, segment, &p2);
            if( cnt == 1 )
            {
                cnt2++;
                if( cnt2 == 1 )
                {
                    *hit1 = p2;
                }
                else
                {
                    *hit2 = p2;
                }
            }
            return cnt2;
        } 
        else 
        {
            double y = (-b + d) / (2 * a);
            double x = fy(A, B, C, y);
            cnt = rxy(x1, y1, x2, y2, x, y, segment, &p1);
            if( cnt == 1 )
            {
                cnt2++;
                *hit1 = p1;
            }
 
            y = (-b - d) / (2 * a);
            x = fy(A, B, C, y);
            cnt = rxy(x1, y1, x2, y2, x, y, segment, &p2);
            if( cnt == 1 )
            {
                cnt2++;
                if( cnt2 == 1 )
                {
                    *hit1 = p2;
                }
                else
                {
                    *hit2 = p2;
                }
            }
            return cnt2;
        }
    }
 
    if (cnt <= 0) {
        printf("No intersections");
        return 0;
    }
}


geometry_msgs::Point calculateCarrot( geometry_msgs::Pose currentPose, geometry_msgs::Pose nextGoal, double lookAheadDist)
{ 
    point p1, p2, center;
    p1 = make_point(currentPose.position.x,currentPose.position.y);
    center = p1;
    p2 = make_point(nextGoal.position.x, nextGoal.position.y);

    geometry_msgs::Point carrot;
    point hit1, hit2;
    int res = intersects( p1, p2, center, lookAheadDist, true, &hit1, &hit2 );
    if( res == 2 )
    {
        if( hypot( hit2.x - p2.x, hit2.y - p2.y ) > hypot( hit1.x - p2.x, hit1.y - p2.y ) )
        {
            carrot.x = hit1.x;
            carrot.y = hit1.y;
        }
        else
        {
            carrot.x = hit2.x;
            carrot.y = hit2.y;
        }
    }
    if( res == 1 )
    {
        if( hypot( center.x - p2.x, center.y - p2.y ) > hypot( center.x - p1.x, center.y - p1.y ) ) // start of line
        {
            carrot.x = hit1.x;
            carrot.y = hit1.y;
        }
        else // end of line
        {
            carrot.x = p2.x;
            carrot.y = p2.y;
        }
    }
    if( res == 0 )
    {
        if( hypot( p1.x - center.x, p1.y - center.y ) < lookAheadDist && hypot( p2.x - center.x, p2.y - center.y ) < lookAheadDist )
        {
            // Completely within
            carrot.x = p2.x;
            carrot.y = p2.y;

        }
        else
        {
            std::cout << "Came from: " << p1.x << " " << p1.y << std::endl;
            std::cout << "Going to: " << p2.x << " " << p2.y << std::endl;
            std::cout << "Robot is currently at: " << center.x << " " << center.y << std::endl;
            std::cout << "Something went very wrong. and the robot lost its path" << std::endl;
            //TODO: throw exception
        }
    }
    return carrot;
}
double CalcAngSpd( geometry_msgs::Pose current, geometry_msgs::Pose goal )
{
    double driveAngle;
    double currentAngle = tf::getYaw( current.orientation );

    double const distThresh = 0.05;
    if( abs(goal.position.x - current.position.x ) < distThresh && abs(goal.position.y - current.position.y ) < distThresh )
    {
        driveAngle = tf::getYaw( goal.orientation );
    }
    else
    {
        double dX = goal.position.x - current.position.x, dY = goal.position.y - current.position.y;
        if( dY == 0 && dX == 0 )
        {
            driveAngle = currentAngle;
        }
        else if( dX == 0 || dY == 0 )
        {
            if( dX == 0 )
            {
                if( dY > 0 )
                {
                    driveAngle = 0.5 * M_PI;
                }
                else
                {
                    driveAngle = -0.5 * M_PI;
                }
            }
            if( dY == 0 )
            {
                if( dX > 0 )
                {
                    driveAngle = 0;
                }
                else
                {
                    driveAngle = M_PI;
                }
            }
        }
        else if( dX > 0 )
        {
            driveAngle = atan( dY / dX );
        }
        else if( dY > 0 )
        {
            driveAngle = M_PI + atan( dY / dX );
        }
        else
        {
            driveAngle = -M_PI + atan( dY / dX );
        }
    }
    
    double dAngle = angles::shortest_angular_distance( currentAngle, driveAngle );
    double angleThreshold = 0.01; //hocus pocus   

    if( abs( driveAngle - currentAngle ) > angleThreshold )
    {
        double speed = MAX_ANG_SPD;
        if( abs(dAngle) < M_PI / 4 )
        {
            speed = ( speed / ( M_PI / 4 ) ) * abs(dAngle);
        }
        if( dAngle < 0 )
        {
            speed = -speed;
        }
        return speed;
    }
    else
    {
        return 0;
    }
}

double CalcLinSpd( geometry_msgs::Pose current, geometry_msgs::Pose goal )
{
    double dX = goal.position.x - current.position.x, dY = goal.position.y - current.position.y;
    double distanceThreshold = 0.10; //because reasons
    double distance = sqrt( dY*dY + dX*dX );
    if( abs(distance) > distanceThreshold ) // move until goal reached ( or at least close enough )
    {
        double speed = MAX_SPEED;
        if( distance < 1 )
        {
            speed = speed * distance * 0.9;
        }
        return speed;
    }
    return 0;
}

#endif