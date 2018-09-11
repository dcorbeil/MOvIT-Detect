#ifndef MOVING_SENSOR_H
#define MOVING_SENSOR_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <thread>

#include "PMW3901.h"
#include "VL53L0X.h"
#include "Utils.h"
#include "Timer.h"

class MotionSensor
{
  public:
    // Singleton
    static MotionSensor &GetInstance()
    {
      static MotionSensor instance;
      return instance;
    }

    void Initialize();
    bool GetIsMoving();

  private:
    //Singleton
    MotionSensor();
    MotionSensor(MotionSensor const &);   // Don't Implement.
    void operator=(MotionSensor const &); // Don't implement.

    std::thread GetDeltaXYThread();
    bool InitializeOpticalFlowSensor();
    bool InitializeRangeSensor();
    bool ValidDistanceToTheGround();

    float PixelsToMeters(float pixels);
    float GetAverageRange();

    void UpdateTravel(int16_t *deltaX, int16_t *deltaY);
    void updateRangeDeque();
    void readRangeSensor();
    void readFlowSensor();
    void GetDeltaXY();

    std::chrono::high_resolution_clock::time_point _timeoutStartMs;
    PMW3901 _opticalFLowSensor; // Optical Flow Sensor
    VL53L0X _rangeSensor;       // Range Sensor
    std::deque<uint16_t> _rangeDeque;
    Timer _timer;
};

#endif // MOVING_SENSOR_H
