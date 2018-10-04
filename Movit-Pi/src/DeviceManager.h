#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include "Imu.h"
#include "Alarm.h"
#include "ForcePlate.h"
#include "ForceSensor.h"
#include "FixedImu.h"
#include "MobileImu.h"
#include "BackSeatAngleTracker.h"
#include "DateTimeRTC.h"
#include "MotionSensor.h"
#include "MAX11611.h"
#include <string>

//Center of pressure coordinate
struct Coord_t
{
    float x;
    float y;
};

class DeviceManager
{
  public:
    void InitializeDevices();

    // Called periodicaly to update all the data
    void Update();

    Alarm *GetAlarm() { return &_alarm; }

    bool IsSomeoneThere() { return _isSomeoneThere; }
    bool IsChairInclined() { return _isChairInclined; }
    Coord_t GetCenterOfPressure() { return _COPCoord; }
    int GetBackSeatAngle() { return _backSeatAngle; }
    int GetTimeSinceEpoch() { return _timeSinceEpoch; }
    bool GetIsMoving() { return _isMoving; }
    double GetXAcceleration();
    void CalibratePressureMat();
    void CalibrateIMU();
    void TurnOff();

    bool TestDevices();

    bool GetIsAlarmInitialized() { return _isAlarmInitialized; }
    bool GetIsFixedImuInitialized() { return _isFixedImuInitialized; }
    bool GetIsMobileInitialized() { return _isMobileImuInitialized; }
    bool GetIsMotionSensorInitialized() { return _isMotionSensorInitialized; }
    bool GetIsForcePlateInitialized() { return _isForcePlateInitialized; }

    // Singleton
    static DeviceManager *GetInstance()
    {
        static DeviceManager instance;
        return &instance;
    }

  private:
    //Singleton
    DeviceManager();
    DeviceManager(DeviceManager const &);  // Don't Implement.
    void operator=(DeviceManager const &); // Don't implement.

    void UpdateForcePlateData();
    bool InitializeForcePlate();

    bool _isAlarmInitialized = false;
    bool _isFixedImuInitialized = false;
    bool _isMobileImuInitialized = false;
    bool _isMotionSensorInitialized = false;
    bool _isForcePlateInitialized = false;

    bool _isMoving = false;
    bool _isSomeoneThere = false;
    bool _isChairInclined = false;

    Coord_t _COPCoord;
    int _timeSinceEpoch = 0;

    DateTimeRTC *_datetimeRTC;
    Alarm _alarm;
    MobileImu *_mobileImu;
    FixedImu *_fixedImu;
    BackSeatAngleTracker _backSeatAngleTracker;
    int _backSeatAngle = 0;

    uint16_t _max11611Data[9];
    ForceSensor _sensorMatrix;
    ForcePlate _globalForcePlate;
    MAX11611 _max11611;
    MotionSensor *_motionSensor;
};

#endif // DEVICE_MANAGER_H
