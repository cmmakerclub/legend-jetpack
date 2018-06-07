#ifndef CMMC_SENSOR_MPU6050_H
#define CMMC_SENSOR_MPU6050_H

#include <Arduino.h>
#include <CMMC_Sensor.h>
#include <Wire.h>

#define A_R 16384.0 // 32768 / 2
#define G_R 131.0   // 32768 / 250
const int MPU = 0x68;

class CMMC_MPU6050 : public CMMC_Sensor
{
public:
  int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;
  float Acc[2];
  float Gy[3];
  float Angle[3];
  float GyroX, GyroY, GyroZ;

  long time_prev;
  float dt;

  CMMC_MPU6050()
  {
    this->data.type = 0;
  }

  void setup()
  {
    setup(0, 0);
  }

  // set default I2C Pin on 4 (SDA) and 5 (SCL) from ESPresso Lite V2.0
  void setup(int a = 0, int b = 0)
  {
    Serial.println("MPU6050 begin..");
    Serial.println("I2C pin SDA:4, SCL:5");

    Wire.begin(4, 5);
    Wire.beginTransmission(0x68);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);

    Wire.beginTransmission(0x68);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(0x68, 6, true);

    AcX = Wire.read() << 8 | Wire.read();
    AcY = Wire.read() << 8 | Wire.read();
    AcZ = Wire.read() << 8 | Wire.read();

    Acc[1] = atan(-1 * (AcX / A_R) / sqrt(pow((AcY / A_R), 2) + pow((AcZ / A_R), 2))) * RAD_TO_DEG;
    Acc[0] = atan((AcY / A_R) / sqrt(pow((AcX / A_R), 2) + pow((AcZ / A_R), 2))) * RAD_TO_DEG;

    // Wire.beginTransmission(0x68);
    // Wire.write(0x43);
    // Wire.endTransmission(false);
    // Wire.requestFrom(0x68, 6, true);

    // GyX = Wire.read() << 8 | Wire.read();
    // GyY = Wire.read() << 8 | Wire.read();
    // GyZ = Wire.read() << 8 | Wire.read();

    // Gy[0] = GyX / G_R;
    // Gy[1] = GyY / G_R;
    // Gy[2] = GyZ / G_R;

    // dt = (millis() - time_prev) / 1000.0;
    // time_prev = millis();

    //  Complementary
    // Angle[0] = 0.98 * (Angle[0] + Gy[0] * dt) + 0.02 * Acc[0];
    // Angle[1] = 0.98 * (Angle[1] + Gy[1] * dt) + 0.02 * Acc[1];

    //  Integration
    // Angle[2] = Angle[2] + Gy[2] * dt;

    // Serial.printf("Gy : %2f     Gx : %2f     Gz : %2f \r\n", Angle[0], Angle[1], Angle[2]);

    // readMPU();
    Serial.printf("Gy:%f   Gx:%f\r\n", Angle[0], Angle[1]);

    data.field1 = Angle[1];
    data.field2 = Angle[0];
  };

  void read()
  {
    static CMMC_MPU6050 *that = this;
    that->interval.every_ms(that->everyMs, []() {
      // that->readMPU();
      // that->data.field1 = Angle[1];
      // that->data.field2 = Angle[0];
      // that->data.field3 = Angle[2];
      that->data.ms = millis();
      that->cb((void *)&that->data, sizeof(that->data));
    });
  };
};

#endif