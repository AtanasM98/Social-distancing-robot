#ifndef ISOCKET_H
#define ISOCKET_H

/** 
* Enum that represents the header of data that will be used in the ISocket interface.
*/
enum HEADER
{
    /** 
    * Order has been placed.
    */
    PLACEORDER = 0,

    /** 
    * Order has been canceled.
    */
    CANCELORDER = 1,

    /** 
    * Order has been started.
    */
    STARTORDER = 2,

    /** 
    * Order has been edited. Should not be received by the robot in any way.
    */
    EDITORDER = 3,

    /** 
    * Status update of an order has been received.
    */
    STATUSUPDATE = 4,

    /** 
    * Robot has to return to idle position
    */
    RETURN = 5,

    /** 
    * Returns if the previous header was handled correctly. This always contains a bool but can contain an error message
    */
    RESULT = 6,

    /** 
    * Used to request the bill. Should not be received by the robot in any way.
    */
    BILL = 7,

    /** 
    * Sent to identify the robot to the server.
    */
    ID = 8,

    /** 
    * Gets the open orders. Should not be received by the robot in any way.
    */
    GETOPENORDERS = 9,
};


/** 
* Interface class that contains socket operations.
*/
class ISocket
{
    public: 
        /**
        * Destructs the class.
        * @return void
        */
       
        /**
        * Sends a message to the endpoint.
        * @param data Bytearray of data to send.
        * @return bool indicating whether the message is sent.
        */
        virtual bool SendMsg(const char data[]) = 0;

        /**
        * Connect the socket to its endpoint.
        * @return bool indicating whether the socket is connected to the endpoint.
        */
        virtual bool Connect() = 0;

        /**
        * Disconnects the currently open connection.
        * @return bool indicating whether the socket is succesfully disconnecte.
        */
        virtual bool Disconnect() = 0;

        virtual void ProcessIncoming() = 0;
};

#endif