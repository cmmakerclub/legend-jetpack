#include "MPU6050Module.h"

extern float axisX;
extern float axisY;
extern float axisZ;

CMMC_SENSOR_DATA_T data;
void MPU6050Module::config(CMMC_System *os, AsyncWebServer *server)
{
  static MPU6050Module *that = this;
}

void MPU6050Module::configLoop() {}

void MPU6050Module::setup()
{
  mpu = new CMMC_MPU6050();
  mpu->onData([&](void *d, size_t len) {
    Serial.printf("DATA %lu bytes ARRIVED at %lu\r\n", len, millis());
    memcpy(&data, d, len);
    axisX = data.field1;
    axisY = data.field2;
    axisZ = data.field3;
    Serial.printf("onData X=%2f\tY=%2f\tZ=%2f\r\n", axisX, axisY, axisZ);
  });
  mpu->every(3000);
  mpu->setup(4, 5);
}

void MPU6050Module::loop()
{
  mpu->read(); 
}
