
#include <CMMC_Legend.h>
#include <CMMC_Sensor.h>
#include "modules/LatteModule.h"

CMMC_Legend os;

void setup()
{
  os.addModule(new LatteModule());
  os.setup();
  Serial.printf("APP VERSION: %s\r\n", LEGEND_APP_VERSION);
}

void loop()
{
  os.run();
}