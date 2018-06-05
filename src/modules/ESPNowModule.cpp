#include "ESPNowModule.h"

void ESPNowModule::config(CMMC_System *os, AsyncWebServer* server) {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  uint8_t* slave_addr = CMMC::getESPNowSlaveMacAddress();
  memcpy(self_mac, slave_addr, 6);
  this->led = ((CMMC_Legend*) os)->getBlinker();;
  strcpy(this->path, "/api/espnow");

  static ESPNowModule *that = this;
  this->os = os;
  this->_serverPtr = server;
  this->_managerPtr = new CMMC_ConfigManager("/espnow.json");
  this->_managerPtr->init();

  this->_managerPtr->load_config([](JsonObject * root, const char* content) {
    if (root == NULL) {
      Serial.print("espnow.json failed. >");
      Serial.println(content);
      return ;
    }
    else {
      Serial.println("[user] json loaded..");
      Serial.println(content);
      if (root->containsKey("mac")) {
        String macStr = String((*root)["mac"].as<const char*>());
        Serial.printf("Loaded mac %s\r\n", macStr.c_str());
        uint8_t mac[6];
        CMMC::convertMacStringToUint8(macStr.c_str(), mac);
        // CMMC::printMacAddress(mac);
        // Serial.println();
        memcpy(that->master_mac, mac, 6);
      }
      else {
        Serial.println("no mac field.");
      }
    }
  });
  this->configWebServer();
} 

void ESPNowModule::loop() {
  Serial.printf("looping at %lums\r\n", millis());
  u8 t = 1;
  delay(2);
  Serial.printf("sending at %lums\r\n", millis());
  espNow.send(master_mac, &t, 1, []() {
    Serial.println("espnow sending timeout.");
  }, 200);
  delay(1000);
}

void ESPNowModule::configLoop() {
  if (digitalRead(BUTTON_PIN) == 0) {
    _init_simple_pair();
    delay(1000);
  }
}
void ESPNowModule::setup() { 
  _init_espnow(); 
} 
void ESPNowModule::_init_simple_pair() {
  Serial.println("calling simple pair.");
  this->led->blink(250);
  simplePair.debug([](const char* msg) {
    Serial.println(msg);
  });
  static ESPNowModule *module = this;
  static bool *flag = &sp_flag_done;
  simplePair.begin(SLAVE_MODE, [](u8 status, u8 * sa, const u8 * data) {
    Serial.println("evt_callback.");
    if (status == 0) {
      char buf[13];
      char self_buf[13];
      Serial.printf("[CSP_EVENT_SUCCESS] STATUS: %d\r\n", status);
      Serial.printf("WITH KEY: ");
      CMMC::dump(data, 16);
      Serial.printf("WITH MAC: ");
      CMMC::dump(sa, 6);
      CMMC::macByteToString(data, buf);
      CMMC::macByteToString(module->self_mac, self_buf);
      CMMC::printMacAddress((uint8_t*)buf);
      CMMC::printMacAddress((uint8_t*)self_buf);
      module->_managerPtr->add_field("mac", buf);
      module->_managerPtr->add_field("self_mac", self_buf);
      module->_managerPtr->commit();
      Serial.println("DONE...");
      *flag = true;
    }
    else {
      Serial.printf("[CSP_EVENT_ERROR] %d: %s\r\n", status, (const char*)data);
    }
  });

  simplePair.start();
  uint32_t startMs = millis();
  while (!sp_flag_done && (millis() - startMs < 10000)) {
    Serial.println("waiting sp_flag_done ..");
    delay(1000L + (250 * sp_flag_done));
  }
  if (sp_flag_done) {
    module->led->blink(1000); 
    delay(5000);
    ESP.restart();
    Serial.println("pair done.");
  }
  else {
    Serial.println("do simple pair device not found.");
    module->led->blink(50);
  }
}

void ESPNowModule::_go_sleep(uint32_t deepSleepM) {
  Serial.printf("\r\nGo sleep for .. %lu min. \r\n", deepSleepM);
  ESP.deepSleep(deepSleepM * 60e6);
}


void ESPNowModule::_init_espnow() {
  Serial.print("Slave Mac Address: ");
  CMMC::printMacAddress(self_mac, true);
  espNow.init(NOW_MODE_SLAVE);
  espNow.enable_retries(true);
  // espNow.debug([](const char* msg) {
  //   Serial.println(msg);
  // });
  // static CMMC_LED *led = ((CMMC_Legend*) os)->getBlinker();
  // led->detach();
  espNow.on_message_sent([](uint8_t *macaddr, u8 status) {
    // led->toggle();
    Serial.printf("sent status %lu\r\n", status);
  });

  espNow.on_message_recv([](uint8_t * macaddr, uint8_t * data, uint8_t len) {
    // led.toggle();
    Serial.printf("GOT sleepTime = %lu at(%lu ms)\r\n", data[0], millis());
    // if (data[0] == 0)
    //   data[0] = DEFAULT_DEEP_SLEEP_M;
    // _go_sleep(data[0]);
  });
}