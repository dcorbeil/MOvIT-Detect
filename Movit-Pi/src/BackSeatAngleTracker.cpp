#include "BackSeatAngleTracker.h"
#include "Utils.h"
#include <algorithm> 
#include <unistd.h>
#include <math.h>
#include <string>

enum _axis { x, y, z };
const std::string fixedImuName = "fixedImu";
const std::string mobileImuName = "mobileImu";

BackSeatAngleTracker::BackSeatAngleTracker()
{
}

bool BackSeatAngleTracker::Initialize()
{
	_fileManager.ReadImuCalibrationOffsetsFromFile(fixedImuName, mobileImuName);
	return InitializeMobileImu() && InitializeFixedImu();
}

bool BackSeatAngleTracker::InitializeImu(MPU6050 &mpu, std::string name, int* accelerometerOffsets, int* gyroscopeOffsets)
{
    printf("MPU6050 %s initializing ... ", name.c_str());
    fflush(stdout);

    if (!mpu.testConnection())
    {
        printf("FAIL\n");
        return false;
    }

    mpu.initialize();
    
    ResetIMUOffsets(mpu);

    if (accelerometerOffsets == NULL || gyroscopeOffsets == NULL)
    {
        Calibrate(mpu, name);
    }
    else
    {
        std::copy(accelerometerOffsets, accelerometerOffsets + NUMBER_OF_AXIS, std::begin(_accelerometerOffsets));
        std::copy(gyroscopeOffsets, gyroscopeOffsets + NUMBER_OF_AXIS, std::begin(_gyroscopeOffsets));
    }

    SetImuOffsets(mpu);
    return true;
}

bool BackSeatAngleTracker::InitializeFixedImu()
{
    int * accelerometerOffsets = _fileManager.GetFixedImuAccelOffsets();
    int * gyroscopeOffsets = _fileManager.GetFixedImuGyroOffsets();

    return InitializeImu(_fixedImu, fixedImuName, accelerometerOffsets, gyroscopeOffsets);
}

bool BackSeatAngleTracker::InitializeMobileImu()
{
    int * accelerometerOffsets = _fileManager.GetMobileImuAccelOffsets();
    int * gyroscopeOffsets = _fileManager.GetMobileImuGyroOffsets();

    return InitializeImu(_mobileImu, mobileImuName, accelerometerOffsets, gyroscopeOffsets);
}

void BackSeatAngleTracker::ResetIMUOffsets(MPU6050 &mpu)
{
    ResetIMUAccelOffsets(mpu);
    ResetIMUGyroOffsets(mpu);
}

void BackSeatAngleTracker::ResetIMUAccelOffsets(MPU6050 &mpu)
{
    mpu.setXAccelOffset(0);
    mpu.setYAccelOffset(0);
    mpu.setZAccelOffset(0);
}

void BackSeatAngleTracker::ResetIMUGyroOffsets(MPU6050 &mpu)
{
    mpu.setXGyroOffset(0);
    mpu.setYGyroOffset(0);
    mpu.setZGyroOffset(0);
}

void BackSeatAngleTracker::SetImuOffsets(MPU6050 &mpu)
{
    SetImuAccelOffsets(mpu);
    SetImuGyroOffsets(mpu);
}

void BackSeatAngleTracker::SetImuAccelOffsets(MPU6050 &mpu)
{
    mpu.setXAccelOffset(_accelerometerOffsets[_axis::x]);
    mpu.setYAccelOffset(_accelerometerOffsets[_axis::y]);
    mpu.setZAccelOffset(_accelerometerOffsets[_axis::z]);
}

void BackSeatAngleTracker::SetImuGyroOffsets(MPU6050 &mpu)
{
    mpu.setXGyroOffset(_gyroscopeOffsets[_axis::x]);
    mpu.setYGyroOffset(_gyroscopeOffsets[_axis::y]);
    mpu.setZGyroOffset(_gyroscopeOffsets[_axis::z]);
}

int * BackSeatAngleTracker::GetGyroscopeMeans(MPU6050 &mpu)
{
    const int numberOfDiscardedMeasures = 100;
    const int timeBetweenMeasures = 2000;

    uint16_t i = 0;
    int16_t gx, gy, gz;
    int gyroscopeMeans[NUMBER_OF_AXIS] = { 0, 0, 0 };
    int* pointer;
    pointer = gyroscopeMeans;

    while (i < (BUFFER_SIZE + numberOfDiscardedMeasures))
    {
        mpu.getRotation(&gx, &gy, &gz);

        if (i++ > numberOfDiscardedMeasures)
        {
            gyroscopeMeans[_axis::x] += gx;
            gyroscopeMeans[_axis::y] += gy;
            gyroscopeMeans[_axis::z] += gz;
        }

        usleep(timeBetweenMeasures);
    }

    gyroscopeMeans[_axis::x] /= BUFFER_SIZE;
    gyroscopeMeans[_axis::y] /= BUFFER_SIZE;
    gyroscopeMeans[_axis::z] /= BUFFER_SIZE;
    return pointer;
}

int * BackSeatAngleTracker::GetAccelerometerMeans(MPU6050 &mpu)
{
	const int numberOfDiscardedMeasures = 100;
	const int timeBetweenMeasures = 2000;

	uint16_t i = 0;
	int16_t ax, ay, az;
    int accelerationBuffer[NUMBER_OF_AXIS] = { 0, 0, 0 };
    int* pointer;
    pointer = accelerationBuffer;

	while (i < (BUFFER_SIZE + numberOfDiscardedMeasures))
	{
		mpu.getAcceleration(&ax, &ay, &az);

		if (i++ > numberOfDiscardedMeasures)
		{
			accelerationBuffer[_axis::x] += ax;
			accelerationBuffer[_axis::y] += ay;
			accelerationBuffer[_axis::z] += az;
		}

		usleep(timeBetweenMeasures);
	}

    accelerationBuffer[_axis::x] /= BUFFER_SIZE;
    accelerationBuffer[_axis::y] /= BUFFER_SIZE;
    accelerationBuffer[_axis::z] /= BUFFER_SIZE;
    return pointer;
}

void BackSeatAngleTracker::CalibrateAccelerometer(MPU6050 &mpu)
{
    uint8_t ready = 0;
    int * accelerometerMeans = GetAccelerometerMeans(mpu);

    _accelerometerOffsets[_axis::x] = (_calibrationArray[_axis::x] - accelerometerMeans[_axis::x]) / 8;
    _accelerometerOffsets[_axis::y] = (_calibrationArray[_axis::y] - accelerometerMeans[_axis::y]) / 8;
    _accelerometerOffsets[_axis::z] = (_calibrationArray[_axis::z] - accelerometerMeans[_axis::z]) / 8;

    while (ready < NUMBER_OF_AXIS)
    {
        ready = 0;
        SetImuAccelOffsets(mpu);
        accelerometerMeans = GetAccelerometerMeans(mpu);

        for (uint8_t i = 0; i < NUMBER_OF_AXIS; i++)
        {
            if (abs(_calibrationArray[i] - accelerometerMeans[i]) <= ACCELEROMETER_DEADZONE)
            {
                ready++;
            }
            else
            {
                _accelerometerOffsets[i] = _accelerometerOffsets[i] + (_calibrationArray[i] - accelerometerMeans[i]) / ACCELEROMETER_DEADZONE;
            }
        }
    }
}

void BackSeatAngleTracker::CalibrateGyroscope(MPU6050 &mpu)
{
    uint8_t ready = 0;
    int * gyroscopeMeans = GetGyroscopeMeans(mpu);

    _gyroscopeOffsets[_axis::x] = -gyroscopeMeans[_axis::x] / 4;
    _gyroscopeOffsets[_axis::y] = -gyroscopeMeans[_axis::y] / 4;
    _gyroscopeOffsets[_axis::z] = -gyroscopeMeans[_axis::z] / 4;

    while (ready < NUMBER_OF_AXIS)
    {
        ready = 0;
        SetImuGyroOffsets(mpu);
        gyroscopeMeans = GetGyroscopeMeans(mpu);

        for (uint8_t i = 0; i < NUMBER_OF_AXIS; i++)
        {
            if (abs(gyroscopeMeans[i]) <= GYROSCOPE_DEADZONE)
            {
                ready++;
            }
            else
            {
                _gyroscopeOffsets[i] = _gyroscopeOffsets[i] - gyroscopeMeans[i] / (GYROSCOPE_DEADZONE + 1);
            }
        }
    }
}

void BackSeatAngleTracker::Calibrate(MPU6050 &mpu, std::string name)
{
    CalibrateAccelerometer(mpu);
    CalibrateGyroscope(mpu);

    _fileManager.WriteImuCalibrationOffsetsToFile(_accelerometerOffsets, _gyroscopeOffsets, name);

}

void BackSeatAngleTracker::Calibrate()
{
    // Calibrate fixed IMU:
    ResetIMUOffsets(_fixedImu);
    Calibrate(_fixedImu, fixedImuName);
    SetImuOffsets(_fixedImu);

    _fileManager.WriteImuCalibrationOffsetsToFile(_accelerometerOffsets, _gyroscopeOffsets, fixedImuName);

    // Calibrate mobile IMU:
    ResetIMUOffsets(_mobileImu);
    Calibrate(_mobileImu, mobileImuName);
    SetImuOffsets(_mobileImu);

    _fileManager.WriteImuCalibrationOffsetsToFile(_accelerometerOffsets, _gyroscopeOffsets, mobileImuName);
}

void BackSeatAngleTracker::GetAcceleration(MPU6050 &mpu, double *acceleration)
{
    int16_t ax, ay, az;
    mpu.getAcceleration(&ax, &ay, &az);

    // TODO: Add low-pass filter

    acceleration[_axis::x] = double(ax) * 2 / 32768.0f;
    acceleration[_axis::y] = double(ay) * 2 / 32768.0f;
    acceleration[_axis::z] = double(az) * 2 / 32768.0f;
}

double BackSeatAngleTracker::GetPitch(double acceleration[])
{
    return atan2(acceleration[_axis::x], sqrt(acceleration[_axis::y] * acceleration[_axis::y] + acceleration[_axis::z] * acceleration[_axis::z])) * radiansToDegrees;
}

int BackSeatAngleTracker::GetBackSeatAngle()
{
    double fixedImuAccelerations[NUMBER_OF_AXIS] = { 0, 0, 0 };
    double mobileImuAccelerations[NUMBER_OF_AXIS] = { 0, 0, 0 };

    GetAcceleration(_fixedImu, fixedImuAccelerations);
    GetAcceleration(_mobileImu, mobileImuAccelerations);

    double fixedPitch = GetPitch(fixedImuAccelerations);
    double mobilePitch = GetPitch(mobileImuAccelerations);

    return abs(int(fixedPitch - mobilePitch));
}