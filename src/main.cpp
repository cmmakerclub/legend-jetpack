
#include <CMMC_Legend.h>
// #include <modules/KadyaiModule.h>
// #include <modules/ESPNowModule.h>
#include <modules/OLEDModule.h>

CMMC_Legend os;
int temp = 0;

void setup()
{
  // os.addModule(new KadyaiModule());
  // os.addModule(new ESPNowModule()); 
  os.addModule(new OLEDModule()); 
  os.setup();
  Serial.printf("APP VERSION: %s\r\n", LEGEND_APP_VERSION);
}

void loop()
{
  os.run();
}