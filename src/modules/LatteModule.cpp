#include "LatteModule.h"

void LatteModule::config(CMMC_System *os, AsyncWebServer* server) {
  static LatteModule *that = this;
}

void LatteModule::configLoop() { }

void LatteModule::setup() {
  bme = new CMMC_BME680();
  bme->onData([&](void *d, size_t len) {
    Serial.printf("DATA %lu bytes ARRIVED at %lu\r\n", len, millis()); 
  }); 
  bme->every(1000);
  bme->setup(0, 0);
}

void LatteModule::loop() { 
  bme->read(); 
}
