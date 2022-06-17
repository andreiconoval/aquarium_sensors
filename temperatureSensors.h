#include <OneWire.h>
#include <DallasTemperature.h>
#include "timer2Minim.h"
#include "as_structs.h"
#define TEMP_SENS_ERROR_VALUE -127

class TemperatureSensors
{
public:
  TemperatureSensors(uint8_t pin,ASTempSensor *tempSensors[]);
  void readTemperatures();
  void printAddress(DeviceAddress deviceAddress);
  float getTempC();

private:
  OneWire _oneWire;
  DallasTemperature _sensors;
  timerMinim _tempSensorTimer;
  uint8_t _tempDevices;
  DeviceAddress _wTherm;
  float _temp;
};

TemperatureSensors::TemperatureSensors(uint8_t pin, ASTempSensor *tempSensors[])
{
  _tempSensorTimer = timerMinim(5000);
  _oneWire = OneWire(pin);
  _sensors = DallasTemperature(&_oneWire);
  _temp = -127; // wrong sensor conection value;
}

void TemperatureSensors::readTemperatures()
{
  if (_tempSensorTimer.isReady())
  {
    _sensors.requestTemperatures();
    _tempDevices = _sensors.getDeviceCount();
    _temp = _sensors.getTempCByIndex(0);
     Serial.println(_temp);
    for (int i = 0; i < _tempDevices; i++)
    {
      Serial.print("Sensor ");
      Serial.print(i + 1);
      Serial.print(" : ");
      _sensors.getAddress(_wTherm, i);
      printAddress(_wTherm);
    }
  }
}

void TemperatureSensors::printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    Serial.print("0x");
    if (deviceAddress[i] < 0x10)
      Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
    if (i < 7)
      Serial.print(", ");
  }
  Serial.println("");
}

float TemperatureSensors::getTempC()
{
  return _temp;
}
