
#include <CMMC_Legend.h>
#include <modules/KadyaiModule.h>
#include <modules/ESPNowModule.h>
#include <modules/OLEDModule.h>
#include <modules/MPU6050Module.h>

CMMC_Legend os;

// for BME680Module.cpp
// int temp = 0; 
// typedef struct __attribute((__packed__)) {
//   uint8_t header[2] = {0x7e, 0x7f};
//   uint8_t version = 1;
//   uint8_t project = 1;
//   uint8_t reserved[4]= {0xff,0xff,0xff,0xff};
//   uint32_t sleepTime;
//   uint32_t ms;
//   CMMC_SENSOR_T data;
//   uint32_t sum;
//   uint8_t tail[2] = {0x0d, 0x0a};
// } CMMC_PACKET_T;

// int temp = 0; // for BME680Module.cpp

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