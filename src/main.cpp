
#include <CMMC_Legend.h>
#include <modules/BME680Module.h>
#include <modules/WiFiModule.h>
#include <modules/MqttModule.h>

CMMC_Legend os;
int temp = 0;

void setup()
{
  os.addModule(new BME680Module());
  os.addModule(new WiFiModule());
  os.addModule(new MqttModule());
  os.setup();
  Serial.printf("APP VERSION: %s\r\n", LEGEND_APP_VERSION);
}

void loop()
{
  os.run();
}