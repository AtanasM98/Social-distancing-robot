#ifndef ILEDCONTROLLER_H
#define ILEDCONTROLLER_H

/** 
* Enum that represents colors for usage inside the ILedController interface.
*/
enum COLORS
{
    GREEN,
    RED,
    BLUE,
};

/** 
* Enum that represents ledstrip types for usage inside the ILedController interface.
*/
enum LEDTYPE
{
    /** 
    * Default setting, enables the ledstrip.
    */
    DEFAULT,

    /** 
    * Makes the ledstrip blink.
    */
    BLINK,

    /** 
    * Makes the ledstrip fade.
    */
    FADE,
};

/** 
* Interface that includes ledstrip related operations.
*/
class ILedController
{
public:
    virtual ~ILedController() {}
    
    /**
    * sets the color of the ledstrip.
    * @param color The color to set.
    * @return void
    */
    virtual void setColor(COLORS color) = 0;

    /**
    * Sets the brightness of the ledstrip.
    * @param brightness Birghtness as integer between 1, 100.
    * @return void
    */
    virtual void setBrightness(int brightness) = 0;

    /**
    * Enables the ledstrip.
    * @return void
    */
    virtual void enable() = 0;

    /**
    * Disables the ledstrip.
    * @return void
    */
    virtual void disable() = 0;

    /**
    * Sets the led type.
    * @param type The ledstrip type to use.
    * @return void
    */
    virtual void setType(LEDTYPE type) = 0;
};

#endif