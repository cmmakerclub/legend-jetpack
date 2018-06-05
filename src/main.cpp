#include <CMMC_Legend.h>
#include <modules/MqttModule.h>
#include <modules/ESPNowModule.h>
#include <modules/WiFiModule.h>

CMMC_Legend os;

void setup()
{
  os.setup();
  Serial.printf("APP VERSION: %s\r\n", LEGEND_APP_VERSION);
}

void loop()
{
  os.run();
}