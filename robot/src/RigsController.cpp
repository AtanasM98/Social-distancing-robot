#include "../../include/RigsController.h"
#include "../../include/Socket.h"
#include <iostream>

#define ROBOT_ID "ROBOT01"

RigsController::RigsController()
{
    this->socketConnection = new Socket();
}

RigsController::~RigsController()
{
    delete driveMotor;
    driveMotor = NULL;

    delete liftMotor;
    liftMotor = NULL;

    delete ledController;
    ledController = NULL;

    delete audioHandler;
    audioHandler = NULL;

    delete vision;
    vision = NULL;
    
    delete lidar;
    lidar = NULL;
}

Order constructTempOrder()
{
    //construct an Order
    std::vector<Product> products;
    Product product1(1, 20);
    Product product2(2, 10);
    products.push_back(product1);
    products.push_back(product2);
    Order order(1, false, products, 69, 420);

    return order;
}

void RigsController::StartUp()
{
    bool state = this->socketConnection->Connect();
    if(state)
    {
        JsonParser p;
        nlohmann::json jsonObject = p.SerializeId(ROBOT_ID);

        this->socketConnection->SendMsg(jsonObject.dump(4).c_str());
        this->socketConnection->ProcessIncoming();
    }
}

void RigsController::HandleStartOrder()
{
    //TODO
}

void RigsController::HandleSendUpdate()
{
    //TODO
}

void RigsController::HandleReturn()
{
    //TODO
}