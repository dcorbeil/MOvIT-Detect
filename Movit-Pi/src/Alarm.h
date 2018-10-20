#ifndef ALARM_H
#define ALARM_H

#include "Sensor.h"
#include "PCA9536.h"
#include <thread>

#define DEFAULT_BLINK_DURATION 600
#define DEFAULT_BLINK_FREQUENCY 0.1

class Alarm : public Sensor
{
  private:
    PCA9536 _pca9536;

    bool _isRedAlarmOn = false;
    bool _isBlinkLedsAlarmOn = false;
    bool _isBlinkGreenAlarmOn = false;

    bool _isBlinkGreenAlarmRequired = false;

    bool _deactivateVibration = false;

    double _blinkFrequency;
    int _blinkDuration;

    uint8_t GetPinState(pin_t pin);

    void SetBlinkDuration(int blinkDuraction);
    void SetBlinkFrequency(double blinkFrequency);

  public:
    Alarm();
    Alarm(int blinkDuration, double blinkFrequency);
    bool Initialize();
    bool IsConnected();

    void DeactivateVibration(bool state) { _deactivateVibration = state; }

    void TurnOnDCMotor();
    void TurnOffDCMotor();
    void TurnOnRedLed();
    void TurnOffRedLed();
    void TurnOnGreenLed();
    void TurnOffGreenLed();
    void TurnOffAlarm();

    void TurnOnBlinkLedsAlarm();
    void TurnOnRedAlarm();
    void TurnOnGreenAlarm();
    void TurnOnBlinkGreenAlarm();

    void StopBlinkGreenAlarm();

    bool IsRedAlarmOn() { return _isRedAlarmOn; }
    bool IsBlinkLedsAlarmOn() { return _isBlinkLedsAlarmOn; }
    bool IsBlinkGreenAlarmOn() { return _isBlinkGreenAlarmOn; }

    std::thread TurnOnRedAlarmThread();
    std::thread TurnOnBlinkLedsAlarmThread();
    std::thread TurnOnBlinkGreenAlarmThread();
};

#endif // ALARM_H
