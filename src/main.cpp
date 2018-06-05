
#include <CMMC_Legend.h>
#include <modules/KadyaiModule.h>
#include <modules/ESPNowModule.h>

CMMC_Legend os;
int temp = 0;

void setup()
{
  os.addModule(new KadyaiModule());
  os.addModule(new ESPNowModule()); 
  os.setup();
  Serial.printf("APP VERSION: %s\r\n", LEGEND_APP_VERSION);
}

void loop()
{
  os.run();
}