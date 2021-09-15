#ifndef IDRIVEMOTOR_H
#define IDRIVEMOTOR_H

/** 
* Interface that includes drive operations for the robot.
*/
class IDriveMotor
{
    public: 
        /**
        * Called when destructing the IDriveMotor interface.
        */
        virtual ~IDriveMotor() {}

        /**
        * Moves the motor with the given speed forward.
        * @param speed speed as integer value.
        * @return void
        */
        virtual void moveForward(int speed) = 0;

        /**
        * Moves the motor with the given speed backwards.
        * @param speed speed as integer value.
        * @return void
        */
        virtual void moveBackwards(int speed) = 0;

        /**
        * Moves the motor a certain distance and direction.
        * @param distance The distance to cover.
        * @param direction The direction to move to.
        * @param maxSpeed The maximum speed.
        * @return void
        */
        virtual void move(double distance, double direction, int maxSpeed) = 0;

        /**
        * Brakes if the motor is currently moving.
        * @return void
        */
        virtual void brake() = 0;

        /**
        * Invokes a emergency stop.
        * @return void
        */
        virtual void emergencyStop() = 0;
};

#endif