#include "../../../include/Socket.h"
#include <iostream>

#define BUFFER_SIZE 1024
#define PORT 65432

Socket::Socket(){
    this->jsonParser = new JsonParser();
}

Socket::~Socket(){
    delete this->jsonParser;
    this->jsonParser = nullptr;
}

bool Socket::SendMsg(const char data[]) 
{
    if(this->connected){
        size_t sentMsg = send(this->socketFd, data, strlen(data), 0);
        std::cout << sentMsg;
        // this->ProcessIncoming();
        return true;
    }

    return false;
}

bool Socket::Connect() 
{
    if(this->SetupFd())
        return this->ConnectFd();
    
    return false;
}

bool Socket::Disconnect() 
{
    // improve
    this->connected = false;
    return false;
}

bool Socket::SetupFd() 
{
    this->socketFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(this->socketFd == -1)
    {
        perror("[Socket] Failed to open socket");
        return false;
    }

    memset(&this->socAddr, 0, sizeof socAddr);
    this->socAddr.sin_family = AF_INET;
    this->socAddr.sin_port = htons(PORT);

    std::cout << "[Socket] Socket file descriptor created. " << std::endl;
    return true;
}

bool Socket::ConnectFd()
{
    if(this->connected)
    {
        std::cout << "[Socket] The socket is already connected!" << std::endl;
        return false;
    }

    int connected = connect(this->socketFd, (struct sockaddr *)&socAddr, sizeof socAddr);   
    if(connected == -1)
    {
        std::cout << "[Socket] Failed to connect to socket" << std::endl;
        return false;
    }

    std::cout << "[Socket] Connected succesfully!" << std::endl;
    this->connected = true;
    return this->connected;
}

void Socket::ProcessIncoming() 
{
    while(this->connected)
    {
        char buffer[BUFFER_SIZE];
        int recvMsg = recv(this->socketFd, buffer, BUFFER_SIZE, 0);
        if(recvMsg != 0)
        {
            buffer[recvMsg] = '\0';
            std::cout << buffer << std::endl;
            int header = this->jsonParser->GetHeader(buffer);
            
            switch(header)
            {
                case HEADER::STARTORDER:
                {
                    std::cout << "[Socket] STARTORDER header" << std::endl;
                    OrderCollection o = this->jsonParser->DeserializeOrder(buffer);
                    for(Order order : o.GetOrders())
                    {
                        std::cout << "[Socket] Found order: " << order.getId() << std::endl;
                    }

                    //further processing
                }
                break;

                case HEADER::RETURN:
                    std::cout << "[Socket] RETURN header" << std::endl;
                break;

                case HEADER::CANCELORDER:
                    std::cout << "[Socket] CANCELORDER header" << std::endl;
                break;

                case HEADER::PLACEORDER:
                    std::cout << "[Socket] PLACEORDER header" << std::endl;
                break;

                case HEADER::EDITORDER:
                    std::cout << "[Socket] EDITORDER header" << std::endl;
                break;

                case HEADER::STATUSUPDATE:
                    std::cout << "[Socket] STATUSUPDATE header" << std::endl;
                break;

                case HEADER::RESULT:
                    std::cout << "[Socket] RESULT header" << std::endl;
                break;
            }
        }
    }
}
