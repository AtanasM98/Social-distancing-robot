#ifndef RIGSCONTROLLER_H
#define RIGSCONTROLLER_H

#include "ISocket.h"
#include "Socket.h"
#include "IDriveMotor.h"
#include "ILiftMotor.h"
#include "ILedController.h"
#include "IAudio.h"
#include "IVision.h"
#include "ILidar.h"

class RigsController
{
public:
    Socket *socketConnection;
    IDriveMotor const *driveMotor;
    ILiftMotor const *liftMotor;
    ILedController const *ledController;
    IAudio const *audioHandler;
    IVision const *vision;
    ILidar const *lidar;

    RigsController();
    ~RigsController();

    void StartUp();
    void HandleStartOrder();
    void HandleSendUpdate();
    void HandleReturn();
};

#endif