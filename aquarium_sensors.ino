#include <WiFiManager.h>
// https://github.com/tzapu/WiFiManager
#include "temperatureSensors.h"
#define TEMP_WIRE_BUS 4
// -----
TemperatureSensors tempSensor(TEMP_WIRE_BUS);
// ---

#include "ssd1306.h"
#include "nano_engine.h"
/**
 *  Default ESP8266: connect LCD to D1(D/C), D2(CS), RX(RES), D7(DIN), D5(CLK)
 */
SAppMenu menu;
const char *menuItems[] =
    {
        "show temperatures",
        "text examples"};

static void textDemo()
{
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  ssd1306_clearScreen8();
  ssd1306_setColor(RGB_COLOR8(255, 255, 0));
  ssd1306_printFixed8(0, 8, "Normal text", STYLE_NORMAL);
  ssd1306_setColor(RGB_COLOR8(0, 255, 0));
  ssd1306_printFixed8(0, 16, "bold text?", STYLE_BOLD);
  ssd1306_setColor(RGB_COLOR8(0, 255, 255));
  ssd1306_printFixed8(0, 24, "Italic text?", STYLE_ITALIC);
  ssd1306_negativeMode();
  ssd1306_setColor(RGB_COLOR8(255, 255, 255));
  ssd1306_printFixed8(0, 32, "Inverted bold?", STYLE_BOLD);
  ssd1306_positiveMode();
  delay(3000);
}

static void showTemperature()
{
  char result[8];                               // Buffer big enough for 7-character float
  dtostrf(tempSensor.getTempC(), 6, 2, result); // Leave room for too large numbers!
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  ssd1306_clearScreen8();
  ssd1306_setColor(RGB_COLOR8(255, 255, 0));
  ssd1306_printFixed8(0, 8, result, STYLE_NORMAL);
  delay(3000);
}


void setup()
{
  Serial.begin(9600);
  // setupWifiManager();

  // Set up display
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  // D2(4) , D1(5) RX(3)
  // D6(12)
  st7735_128x160_spi_init(3, 12, 5);
  // RGB functions do not work in default SSD1306 compatible mode
  ssd1306_setMode(LCD_MODE_NORMAL);
  ssd1306_clearScreen8();
  ssd1306_createMenu(&menu, menuItems, sizeof(menuItems) / sizeof(char *));
  ssd1306_showMenu8(&menu);
}

void loop()
{
  tempSensor.readTemperatures();
  delay(1000);
  switch (ssd1306_menuSelection(&menu))
  {
  case 0:
    showTemperature();
    break;
  case 1:
    textDemo();
    break;
  default:
    break;
  }

  ssd1306_clearScreen8();
  ssd1306_setColor(RGB_COLOR16(255, 255, 255));
  ssd1306_showMenu8(&menu);
  delay(500);
  ssd1306_menuDown(&menu);
  ssd1306_updateMenu8(&menu);
}
