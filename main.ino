/// @dir Ports/lcd_demo
/// Demo sketch for an LCD connected to I2C port via MCP23008 I/O expander.
// 2009-10-31 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php

#include <stdio.h>
#include <PortsLCD.h>

PortI2C myI2C (1);
LiquidCrystalI2C lcd (myI2C);

Port sensor(4);

#define screen_width 16
#define screen_height 2

void setup() {
  // set up the LCD's number of rows and columns: 
  lcd.begin(screen_width, screen_height);
  // Print a message to the LCD.
  lcd.print("Hello, world!");
  delay(2000);
}

char buffer[17];

void loop() {
  const unsigned value = sensor.anaRead();
  snprintf(buffer, 16, "p: %u", value);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(buffer);
  delay(200);
}
