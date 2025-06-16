#include <Arduino.h>
#include "ui.h"

#include "U8g2lib.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 18, /* data=*/ 23); 
uint8_t brightness = 255; // Default brightness value

listItem item1("Item 1");
Page home;
Page settings; // Create a settings page
listItem Setting1("Setting 1", &brightness); // Create a setting item
listItem Setting2("Setting 2"); // Create another setting item
UI ui(u8g2); // Create an instance of UI with the u8g2 object


void setup() {
  Serial.begin(115200);
  
  home.addItem(&item1); // Add item1 to the home page
  settings.addItem(&Setting1); // Add Setting1 to the settings page
  settings.addItem(&Setting2); // Add Setting2 to the settings page
  ui.currentPage = settings; // Set the current page to settings
  ui.begin(); // Initialize the UI
  pinMode(16, INPUT_PULLUP); // Set pin 18 as output for I2C clock
  pinMode(17, INPUT_PULLUP); // Set pin 19 as output for I2C data

  
}

void loop() {
  // put your main code here, to run repeatedly:
  ui.draw(); // Draw the UI on the display
  
  
  delay(10);
}

