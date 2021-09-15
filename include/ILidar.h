#ifndef ILIDAR_H
#define ILIDAR_H

/** 
* Interface class that contains lidar operations.
*/
class ILidar
{
public:

    /**
    * Destructs the class.
    * @return void
    */
    virtual ~ILidar() {}

    /**
    * Enabled the lidar.
    * @return void
    */
    virtual void enable() = 0;

    /**
    * Disables the lidar.
    * @return void
    */
    virtual void disable() = 0;

    /**
    * Retrieves the distance available of the direction (?)
    * @param direction The direction to scan.
    * @return double
    */
    virtual double retrieveDistance(double direction) = 0;
};

#endif