/// @dir Ports/lcd_demo
/// Demo sketch for an LCD connected to I2C port via MCP23008 I/O expander.
// 2009-10-31 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php

#include <stdio.h>
#include <math.h>
#include <JeeLib.h>
#include <PortsLCD.h>

#include "neopixel.h"

#define JEE_ID 3
#define JEE_GROUP 19
#define RADIO 1
#define REPORT_EVERY 60 // number of cycles

#define screen_width 16
#define screen_height 2

PortI2C myI2C (1);
LiquidCrystalI2C lcd (myI2C);

Port sensor(4);

char buffer[17];

const int N = 50;
unsigned prev_values[N];
int values = 0;

void setup() {
  ledsetup();
  showColor(0,0, 8);
  // set up the LCD's number of rows and columns: 
  lcd.begin(screen_width, screen_height);
  // Print a message to the LCD.
  lcd.print("Hello, world!");
  #ifdef RADIO
    rf12_initialize(JEE_ID, RF12_868MHZ, JEE_GROUP);
  #endif
  for(int i=0; i<N; ++i) prev_values[i] = 0;
}

const char* formatPayload(unsigned p) {
  static char buf[256];
  snprintf(buf, sizeof(buf)-1, "{"
    "\"water_pressure\": %u"
  "}", p);
  return buf;
}

void doReport(unsigned payload) {
    const char* msg = formatPayload(payload);

    #ifdef RADIO
      //rf12_sleep(RF12_WAKEUP);
      rf12_sendNow(0, msg, strlen(msg));
      //rf12_sendWait(RADIO_SYNC_MODE);
      //rf12_sleep(RF12_SLEEP);
    #endif
}

unsigned addValue(const unsigned value) {
  
  // shift values to the left
  if (values>1) {
    for(int i=0; i<values-1; ++i) prev_values[i] = prev_values[i+1];
    // make sure next index is valid index
    if (values>N-1) values = N-1;
  } 
  // store new value
  prev_values[values++] = value;

  unsigned total = 0;
  for(int i=0; i<values; ++i) total += prev_values[i];
  return (unsigned)roundf((float)total / (float)values);  
}

void showBar(int bar) {
  cli();
  for(int i=0; i<bar; ++i) {
    sendPixel(0,0,8);
  }
  for(int i=0; i<8-bar; ++i) {
    sendPixel(0,0,0);
  }
  show();
  sei();
}

int count_down = REPORT_EVERY;
void loop() {
  const unsigned value = sensor.anaRead();
  const unsigned average = addValue(value);
  snprintf(buffer, 16, "p: %u", average);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(buffer);
  lcd.setCursor(0, 1);
  int len = round((value - 137) * 16.0 / 600.0);
  if (len > 15) len = 15;
  for(int i=0; i<len; i++)
    lcd.print("#");

  int bar = round((value - 137) * 8.0 / 500.0);
  if (bar>7) bar=7;
  showBar(bar);

  if (!--count_down) {
    count_down = REPORT_EVERY;
    doReport(average);
  }
  delay(20);
}
