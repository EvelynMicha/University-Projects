#include <Wire.h>
#include <LiquidCrystal.h>

const int rs = 9, en = 8, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  
  Serial.begin(9600);  // start serial for output
 
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("ROOM 1");
	
  lcd.setCursor(9, 0);
  lcd.print("ROOM 2");

void loop() {
  Wire.requestFrom(2,1);    // request 1 byte from slave device #2

  while (Wire.available()) { // slave may send less than requested
    int ResValue1 = Wire.read(); // receive a byte as character
    Serial.print(ResValue1);         // print the character
    lcd.setCursor(0, 1);
    lcd.print(ResValue1);
    lcd.print(" ");    
  }
  
  Wire.requestFrom(3,1);	// request 1 byte from slave device #3
  while (Wire.available()) { // slave may send less than requested
    byte ResValue2 = Wire.read(); // receive a byte as character
    Serial.print(ResValue2);         // print the character
    lcd.setCursor(9, 1);
    lcd.print(ResValue2);
    lcd.print(" ");

  }

  delay(500);
}
  
