#ifndef CMMC_SENSOR_MPU6050_H
#define CMMC_SENSOR_MPU6050_H

#include <Arduino.h>
#include <CMMC_Sensor.h>
#include <Wire.h>

void readMPU(void);

#define A_R 16384.0 // 32768 / 2
#define G_R 131.0   // 32768 / 250

class CMMC_MPU6050 : public CMMC_Sensor
{
public:
  const int MPU = 0x68;
  int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;
  float Acc[2];
  float Gy[3];
  float Angle[3];

  float GyroX, GyroY, GyroZ;

  long time_prev;
  float dt;

  void readMPU(void)
  {
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);

    AcX = Wire.read() << 8 | Wire.read();
    AcY = Wire.read() << 8 | Wire.read();
    AcZ = Wire.read() << 8 | Wire.read();
    Acc[1] = atan(-1 * (AcX / A_R) / sqrt(pow((AcY / A_R), 2) + pow((AcZ / A_R), 2))) * RAD_TO_DEG;
    Acc[0] = atan((AcY / A_R) / sqrt(pow((AcX / A_R), 2) + pow((AcZ / A_R), 2))) * RAD_TO_DEG;

    Wire.beginTransmission(MPU);
    Wire.write(0x43);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);

    GyX = Wire.read() << 8 | Wire.read();
    GyY = Wire.read() << 8 | Wire.read();
    GyZ = Wire.read() << 8 | Wire.read();

    Gy[0] = GyX / G_R;
    Gy[1] = GyY / G_R;
    Gy[2] = GyZ / G_R;

    dt = (millis() - time_prev) / 1000.0;
    time_prev = millis();

    //  Complementary
    Angle[0] = 0.98 * (Angle[0] + Gy[0] * dt) + 0.02 * Acc[0];
    Angle[1] = 0.98 * (Angle[1] + Gy[1] * dt) + 0.02 * Acc[1];

    //  Integration
    Angle[2] = Angle[2] + Gy[2] * dt;

    GyroX = Angle[1];
    GyroY = Angle[0];
    GyroZ = Angle[2];

    // print debug
    Serial.printf("MPU6050 --> Gx : %2f   Gy : %2f   Gz : %2f \r\n", Angle[1], Angle[0], Angle[2]);
  }

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
    Serial.println("I2C pin SDA:4, SCL:5 ESPresso Lite V2.0");
    Wire.begin(a, b);
    Wire.beginTransmission(MPU);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);

    readMPU();
    data.field1 = GyroX;
    data.field2 = GyroY;
    data.field3 = GyroZ;
  };

  void read()
  {
    static CMMC_MPU6050 *that = this;
    that->interval.every_ms(that->everyMs, []() {
      // that->readMPU();
      // that->data.field1 = GyroX;
      // that->data.field2 = GyroY;
      // that->data.field3 = GyroZ;
      // that->data.ms = millis();
      that->cb((void *)&that->data, sizeof(that->data));
    });
  };
};

#endif