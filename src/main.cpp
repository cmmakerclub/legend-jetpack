
#include <CMMC_Legend.h>
<<<<<<< HEAD
// #include <modules/KadyaiModule.h>
#include <modules/ESPNowModule.h>
// #include <modules/OLEDModule.h>
// #include <modules/MPU6050Module.h>
=======
#include <modules/KadyaiModule.h>
#include <modules/ESPNowModule.h>
// #include <modules/OLEDModule.h>
#include <modules/MPU6050Module.h>
#include <CMMC_Sensor.h>
>>>>>>> 5e7e2ce1153c5a62974ba32a943788e261e74665

CMMC_Legend os;
char userEspnowSensorName[16]; 
CMMC_SENSOR_DATA_T userKadyaiData;

// for BME680Module.cpp
// int temp = 0; 

// for MPU6050Module.cpp
// float axisX = 0.0;
// float axisY = 0.0;
// float axisZ = 0.0;

void setup()
{
  // os.addModule(new KadyaiModule());
  os.addModule(new ESPNowModule());
  // os.addModule(new OLEDModule());
<<<<<<< HEAD
  // os.addModule(new MPU6050Module());
=======
  os.addModule(new KadyaiModule());
  os.addModule(new ESPNowModule()); 
>>>>>>> 5e7e2ce1153c5a62974ba32a943788e261e74665
  os.setup();
  Serial.printf("APP VERSION: %s\r\n", LEGEND_APP_VERSION);
}

void loop()
{
  os.run();
}