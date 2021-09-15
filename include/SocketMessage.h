#ifndef SOCKETMESSAGE_H
#define SOCKETMESSAGE_H

#include "Order.h"
#include <string>

enum HEADER
{
    PLACEORDER,
    CANCELORDER,
    STARTORDER,
    EDITORDER,
    STATUSUPDATE,
    RETURN,
    RESULT,
};

class SocketMessage
{
public:
    SocketMessage();
};

#endif