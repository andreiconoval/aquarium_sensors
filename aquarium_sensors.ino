#include "timer2Minim.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

#define TEMP_WIRE_BUS 4
#define RELAY_PIN 5
#define TEMP_SENS_ERROR_VALUE -127

// -----
OneWire oneWire(TEMP_WIRE_BUS);
DallasTemperature sensors(&oneWire);
timerMinim tempSensorTimer(5000);
// -----
float aquaTempC = -127; // wrong sensor conection value;
// ---

void setup() {
    pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(9600);
  // setupWifiManager();
  // Start up the library
  sensors.begin();
}


void readTemperatures() {
  if (tempSensorTimer.isReady()) {
    Serial.print(" Requesting temperatures...");
    sensors.requestTemperatures();
    Serial.println("DONE");
    Serial.print("Temperature is: ");
    aquaTempC = sensors.getTempCByIndex(0);//get temp for first index

    Serial.print(aquaTempC);
    if (aquaTempC > 29) {
      digitalWrite(RELAY_PIN, LOW);
      Serial.print("LOW");
    } else {
      Serial.println("HIGH");
      digitalWrite(RELAY_PIN, HIGH);
    }
  }
}




void loop() {
  readTemperatures();
}
