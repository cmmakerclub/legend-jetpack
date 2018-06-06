
#include <CMMC_Legend.h>
// #include <modules/KadyaiModule.h>
// #include <modules/ESPNowModule.h>
// #include <modules/OLEDModule.h>
#include <modules/MPU6050Module.h>

CMMC_Legend os;

// int temp = 0; // for BME680Module.cpp

float axisX = 0.0;
float axisY = 0.0;
float axisZ = 0.0;

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