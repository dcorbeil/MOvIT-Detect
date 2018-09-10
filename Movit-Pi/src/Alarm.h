#ifndef ALARM_H
#define ALARM_H

#include "PCA9536.h"
#include <thread>

#define DEFAULT_BLINK_DURATION 600
#define DEFAULT_BLINK_FREQUENCY 0.1

class Alarm
{
  private:
    PCA9536 _pca9536;

    bool _isRedAlarmOn = false;
    bool _isBlinkLedsAlarmOn = false;

    bool _deactivateVibration = false;

    double _blinkFrequency;
    int _blinkDuration;

    uint8_t GetPinState(pin_t pin);

  public:
    Alarm();
    Alarm(int blinkDuration, double blinkFrequency);

    void Initialize();
    void SetBlinkDuration(int blinkDuraction);
    void SetBlinkFrequency(double blinkFrequency);

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

    std::thread TurnOnRedAlarmThread();
    std::thread TurnOnBlinkLedsAlarmThread();
};

#endif // ALARM_H
