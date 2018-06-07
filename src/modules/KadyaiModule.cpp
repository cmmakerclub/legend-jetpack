#include "KadyaiModule.h"
extern int temp;

static CMMC_SENSOR_DATA_T data1;
static CMMC_SENSOR_DATA_T data2;

void KadyaiModule::config(CMMC_System *os, AsyncWebServer* server) {
  static KadyaiModule *that = this;
  sensor1 = new CMMC_BME680();
  sensor1->setup();
  sensor1->every(10);
  sensor1->onData([](void *d, size_t len) {
    memcpy(&data1, d, len);
    Serial.printf("ON SENSOR DATA.. at %lums\r\n", millis());
  });
}

enum SENSOR_TYPE { PH=1, MOISTURE };

void turnOffSensorSwitch() {
  digitalWrite(14, LOW);
  digitalWrite(15, LOW); 
}
void turnOnSensorSwitch(SENSOR_TYPE type) {
  if (type == PH) { 
    digitalWrite(14, HIGH);
    digitalWrite(15, LOW); 
  }
  else if (type == MOISTURE) {
    digitalWrite(14, HIGH);
    digitalWrite(15, HIGH);
  } 
  delay(10);
}

void KadyaiModule::_read_sensor() {
  Serial.println("READ SENSOR...");
  uint32_t moistureValue, phValue, batteryValue;
  int a0Val;
  /* battery */
  Serial.println("Reading Battery..");
  turnOffSensorSwitch(); 
  delay(10);
  batteryValue = analogRead(A0) * 0.0051724137931034f * 100;

  /* pH */
  Serial.println("Reading Ph..");
  turnOnSensorSwitch(PH);
  a0Val = analogRead(A0);
  Serial.printf("ph raw a0Val = %d\r\n", a0Val);
  phValue = map(a0Val, 0, 200, 900, 300); 
  turnOffSensorSwitch();
  delay(10); 


  /* Moisture */
  Serial.println("Reading Moisture..");
  turnOnSensorSwitch(MOISTURE); 
  a0Val = analogRead(A0);
  moistureValue = ((a0Val * 0.035f) + 1) * 100; 
  Serial.printf("battery=%lu, moisture=%lu, pH=%lu\r\n", batteryValue, moistureValue, phValue);

  //turn off
  delay(10);
  turnOffSensorSwitch();
  data2.battery = batteryValue;

  data2.field1 = data1.field1; /* temp */
  data2.field2 = data1.field2; /* humid */
  data2.field3 = phValue;
  data2.field4 =  moistureValue;
  data2.field5 = data1.field3; /* pressure */
  data2.ms = millis();
  // data2.sum = CMMC::checksum((uint8_t*) &data2, sizeof(data2) - sizeof(data2.sum)); 
  // strcpy(data2.sensorName, data1.sensorName);
  // data2.nameLen = strlen(data2.sensorName); 
}

void KadyaiModule::configLoop() { 
  yield(); 
}

void KadyaiModule::setup() {
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT); 
  sensor1->read();
  _read_sensor();
}

void KadyaiModule::loop() { 
  yield();
}
