
#include <CMMC_Legend.h>
#include <modules/KadyaiModule.h>
#include <modules/ESPNowModule.h>
#include <modules/OLEDModule.h>
#include <modules/MPU6050Module.h>

CMMC_Legend os;

// for BME680Module.cpp
// int temp = 0; 

// for MPU6050Module.cpp
float axisX;
float axisY;
float axisZ;

void setup()
{
  // os.addModule(new KadyaiModule());
  // os.addModule(new ESPNowModule());
  // os.addModule(new OLEDModule());
  os.addModule(new MPU6050Module());
  os.setup();
  Serial.printf("APP VERSION: %s\r\n", LEGEND_APP_VERSION);
}

void loop()
{
  os.run();
}