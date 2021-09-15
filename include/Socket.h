#ifndef SOCKET_H
#define SOCKET_H

#include <arpa/inet.h>
#include "JsonParser.h"
#include "ISocket.h"
#include "OrderCollection.h"
#include <vector>

class Socket : public ISocket
{
    private:         
        JsonParser *jsonParser;
        bool connected;
        int socketFd = 0;
        struct sockaddr_in socAddr;

        bool SetupFd();
        bool ConnectFd();

    public:
        Socket();
        ~Socket();
        bool SendMsg(const char data[]);
        bool Connect();
        void ProcessIncoming();
        bool Disconnect();
};


#endif