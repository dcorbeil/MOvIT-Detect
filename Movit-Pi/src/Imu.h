#ifndef IMU_H
#define IMU_H

#include "FileManager.h"
#include "MPU6050.h"
#include <string>

#define ACCELEROMETER_DEADZONE 8 // Accelerometer error allowed, make it lower to get more precision, but sketch may not converge (default: 8)
#define BUFFER_SIZE 1000         // Amount of readings used to average, make it higher to get more precision but sketch will be slower (default: 1000)
#define GYROSCOPE_DEADZONE 1     // Gyroscope error allowed, make it lower to get more precision, but sketch may not converge (default: 1)
#define GRAVITY 9.80665
#define LSB_SENSITIVITY -16384
#define NUMBER_OF_AXIS 3

class Imu
{
  public:
    Imu();
    bool isInitialized();
    void CalibrateAndSetOffsets();
    void GetAccelerations(double *accelerations);
    virtual bool isSetup() = 0;

  protected:
    FileManager _fileManager;
    std::string _imuName;
    MPU6050 _imu;

    int _calibrationArray[NUMBER_OF_AXIS] = {LSB_SENSITIVITY, 0, 0};
    int _accelerometerOffsets[NUMBER_OF_AXIS] = {0, 0, 0};
    int _gyroscopeOffsets[NUMBER_OF_AXIS] = {0, 0, 0};

    void Calibrate(MPU6050 &mpu, std::string name);
    void CalibrateAccelerometer(MPU6050 &mpu);
    void CalibrateGyroscope(MPU6050 &mpu);

    void SetImuOffsets(MPU6050 &mpu);
    void SetImuAccelOffsets(MPU6050 &mpu);
    void SetImuGyroOffsets(MPU6050 &mpu);
    void ResetIMUOffsets(MPU6050 &mpu);
    void ResetIMUAccelOffsets(MPU6050 &mpu);
    void ResetIMUGyroOffsets(MPU6050 &mpu);

    void GetAccelerometerMeans(MPU6050 &mpu, int accbuff[]);
    void GetGyroscopeMeans(MPU6050 &mpu, int gyrobuff[]);
};

#endif // IMU_H
