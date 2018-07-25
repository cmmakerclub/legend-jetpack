
#include <CMMC_Legend.h>
#include <modules/BME680Module.h>
#include <CMMC_Sensor.h>

CMMC_Legend os;
CMMC_SENSOR_DATA_T userKadyaiData;
char userEspnowSensorName[16];

void setup()
{
  os.addModule(new BME680Module());
  os.setup();
  Serial.printf("APP VERSION: %s\r\n", LEGEND_APP_VERSION);
}

void loop()
{
  os.run();
}