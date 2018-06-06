#include "OLEDModule.h"
extern int temp;

void OLEDModule::config(CMMC_System *os, AsyncWebServer* server) {
  static OLEDModule *that = this;
   oled  = new SSD1306(0x3c, 4, 5);
}

void OLEDModule::configLoop() { }

void OLEDModule::printBuffer(void) {
  // Initialize the log buffer
  // allocate memory to store 8 lines of text and 30 chars per line.
  oled->setLogBuffer(5, 30);

  // Some test data
  const char* test[] = {
      "Setting Up",
  };

  oled->println(test[0]);
  oled->drawLogBuffer(35 /*X*/, /*Y*/25);
  oled->display();
  delay(500);
}

void OLEDModule::setup() {
  oled->init();
  oled->setContrast(255);
  printBuffer();
  oled->clear();
}

void OLEDModule::loop() { 
  if (millis() % 1000 == 0) {
    oled->clear();
    oled->setFont(ArialMT_Plain_10);
    oled->drawString(50, 25, String(millis()));
    oled->display();
  }
}
