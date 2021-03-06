#ifndef CHAIR_MANAGER_H
#define CHAIR_MANAGER_H

#include "MosquittoBroker.h"
#include "Utils.h"
#include "Timer.h"
#include "DeviceManager.h"
#include <string>
#include <unistd.h>

class ChairManager
{
  public:
    ChairManager(MosquittoBroker *mosquittoBroker, DeviceManager *devicemgr);
    ~ChairManager();

    inline bool TestPattern() { return _devicemgr->TestDevices(); }

    void UpdateDevices();
    void ReadFromServer();
    void CheckNotification();

  private:

    MosquittoBroker *_mosquittoBroker;
    DeviceManager *_devicemgr;

    uint32_t _secondsCounter = 0;
    uint8_t _state = 0;

    int _currentChairAngle = 0;
    int _prevChairAngle = 0;
    Coord_t _copCoord;
    std::string _currentDatetime = "";

    bool _isSomeoneThere = false;
    bool _prevIsSomeoneThere = false;
    bool _isMoving = false;

    bool _overrideNotificationPattern = false;
    bool _setAlarmOn = false;

    int _requiredBackRestAngle = 0;
    uint32_t _requiredPeriod = 0;
    uint32_t _requiredDuration = 0;

    Timer _timer;
    Timer _keepAliveTimer;
    Timer _vibrationTimer;

    void CheckIfUserHasBeenSittingForRequiredTime();
    void CheckIfBackRestIsRequired();
    void CheckIfRequiredBackSeatAngleIsReached();
    void CheckIfRequiredBackSeatAngleIsMaintained();
    void CheckIfBackSeatIsBackToInitialPosition();
    void OverrideNotificationPattern();
};

#endif // CHAIR_MANAGER_H
