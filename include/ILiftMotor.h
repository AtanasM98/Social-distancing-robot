#ifndef ILIFTMOTOR_H
#define ILIFTMOTOR_H

/** 
* Interface class that contains lift motor operations.
*/
class ILiftMotor
{
    public: 
    
        /**
        * Destructs the class.
        * @return void
        */
        virtual ~ILiftMotor() {}

        /**
        * Moves the lift up.
        * @param height The height to move to.
        * @return void
        */
        virtual void moveUp(int height) = 0;

        /**
        * Moves the lift down.
        * @param height The height to move to.
        * @return void
        */
        virtual void moveDown(int height) = 0;

        /**
        * Moves to a certain height.
        * @param height The height to move to.
        * @return void
        */
        virtual void moveTo(int height) = 0;

        /**
        * Gets the current height.
        * @return void
        */
        virtual int getHeight() = 0;

        /**
        * Emergency stop for the lift system.
        * @return void
        */
        virtual void stop() = 0;
};

#endif