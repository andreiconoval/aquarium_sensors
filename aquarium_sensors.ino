#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include "temperatureSensors.h"

#define TEMP_WIRE_BUS 4
// -----
TemperatureSensors tempSensor(TEMP_WIRE_BUS);
// ---


void setup() {
  Serial.begin(9600);
  // setupWifiManager();

}

void loop() {
  tempSensor.readTemperatures();
}
