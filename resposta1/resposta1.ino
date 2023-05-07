#include <Wire.h>
#include "rgb_lcd.h"
#include <FlashStorage.h>

rgb_lcd lcd;
const int pushButton = 4;
int estadoPush = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode(pushButton, INPUT);

  lcd.begin(16, 2); // set up the LCD's number of columns and rows
  lcd.setCursor(0, 0); // set the cursor to column 0, line 0
  lcd.print("Estado do pushB"); // Print a message to the LCD.

}

void loop() {

}
