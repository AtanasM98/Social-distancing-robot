#ifndef IVISION_H
#define IVISION_H

/** 
* Interface class that contains vision operations.
*/
class IVision
{
    public: 
    
        /**
        * Destructs the class.
        */
        virtual ~IVision() {}
    
        /**
        * Enables the vision process.
        */
        virtual void enable() = 0;

        /**
        * Disable the vision process.
        */
        virtual void disable() = 0;
};

#endif