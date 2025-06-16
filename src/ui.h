#pragma once
#include "U8g2lib.h"
#include "Arduino.h"



class listItem  {
    public:
        String listTitle;
        uint8_t *listValue;

        listItem(String title,uint8_t *listValue = 0)  {
            this->listTitle = title; // Assign the title to the listItem
            this->listValue = listValue; // Assign the value to the listItem
        }
        String getTitle() {
            return listTitle;
        }

        void setTitle(String title) {
            listTitle = title; // Set the title of the listItem
        }

        uint8_t getValue() {
            return *listValue;
        }

        void setValue(uint8_t value) {
            if (listValue != nullptr) {
                *listValue = value; // Set the value of the listItem
            } else {
                Serial.println("Error: listValue is null!"); // Handle case when listValue is null
            }
        }
};

#define MAX_ITEMS 10 // Define the maximum number of items in the list

class Page {
    public:
        listItem *items[MAX_ITEMS];
        uint8_t itemCount = 0; // Keep track of the number of items in the page
        uint8_t itemSelected = 0; // listItem selected item index
        Page(){
            for (int i = 0; i < MAX_ITEMS; i++) {
                items[i] = nullptr; // Initialize all items to nullptr
            }
        }

        void addItem(listItem *item) {
            if (itemCount < MAX_ITEMS) {
                items[itemCount++] = item; // Add the item to the page and increment the count
            } else {
                Serial.println("Maximum number of items reached!"); // Handle case when max items reached
            }
        }

        String getItemTitle(uint8_t index) {
            if (index < itemCount && items[index] != nullptr) {
                return items[index]->getTitle(); // Return the title of the item at the specified index
            } else {
                return "Invalid Index"; // Handle case when index is out of bounds
            }
        }


        
    
};

// U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 18, /* data=*/ 23); 

class UI {
    public:
        Page currentPage; // Current page of the UI
        U8G2 u8g2; // Reference to the U8G2 object for display handling

        UI(U8G2 u8g2){
            this->u8g2 = u8g2; // Initialize the U8G2 object
        }

        void begin() {
            this->u8g2.begin(); // Initialize the display
            this->u8g2.setFont(u8g2_font_ncenB08_tr); // Set the default font for the display
            this->u8g2.clearBuffer(); // Clear the display buffer
        }

        void draw() {
            this->u8g2.clearBuffer(); // Clear the display buffer
            this->u8g2.setFont(u8g2_font_ncenB08_tr); // Set the font for the display
            for (uint8_t i = 0; i < currentPage.itemCount; i++) {
                this->u8g2.drawStr(0, 10 + (i * 10), currentPage.getItemTitle(i).c_str()); // Draw each item title on the display
                this->u8g2.drawStr(100, 10 + (i * 10), String(currentPage.items[i]->getValue()).c_str()); // Draw the value of each item on the display
            }
            this->u8g2.sendBuffer(); // Send the buffer to the display
        }
};

