#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include "Alarm.h"
#include "ForcePlate.h"
#include "ForceSensor.h"
#include "MAX11611.h" 
#include "BackSeatAngleTracker.h"
#include "DateTimeRTC.h"
#include <string>

#define NUMBER_OF_CAPTOR 9

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
    Coord_t GetCenterOfPressure() { return _COPCoord; }
    int GetBackSeatAngle() { return _backSeatAngle; }
    std::string GetDateTime() { return _currentDateTimeStr; }

    bool TestDevices();

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

    bool _imuValid = false;
    bool _forcePlateValid = false;

    bool _isSomeoneThere = false;
    Coord_t _COPCoord;

    unsigned char _dateTimeRaw[DATE_TIME_SIZE] = {0x45, 0x59, 0x12, 0x00, 0x11, 0x03, 0x18}; //En BCD {seconds, minutes, hours, day, date, month, year}
    std::string _currentDateTimeStr = "";

    DateTimeRTC *_datetimeRTC;

    Alarm _alarm;

    BackSeatAngleTracker _imu;
    int _backSeatAngle = 0;

    uint16_t _max11611Data[9];
    ForceSensor _sensorMatrix;
    ForcePlate _globalForcePlate;
    MAX11611 _max11611;
};

#endif // DEVICE_MANAGER_H
