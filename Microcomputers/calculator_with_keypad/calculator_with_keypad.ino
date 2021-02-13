#include <Keypad.h>
#include <LiquidCrystal.h>

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'.', '0', '=', '/'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

float Number1 = 0, Number2 = 0, Res;
char Op, key;
boolean ready = false, isfloat = false;
int count, first = 0;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.clear(); //clean lcd screen
}

void loop() {

  char key = keypad.getKey();
  //if key is pressed
  if (key) {
    //if key isn't operator - key is number
    if (key != '+' && key != '-' && key != '*' && key != '/' && key != '=') {
      //if Op has no value - not an operator chosen - We are Number1
      if (Op == NO_KEY) {
        //if we want decimal then isfloat becomes true
        if (key == '.') {
          Serial.print(". pressed"); //debugging
          isfloat = true;
          count = 1; //initialise counter for the decimal position
        }

        key = key - 48;

        //if we are the first input and not in the decimals then Number1 value equals the input
        if (Number1 == 0 && (key + 48) != '.' && isfloat == false) {
          Number1 = key; 
        //if we are not the first number and not in the decimals 
        //then Number1 value is 10 times its previous value + the value of the key  
        } else if ((key + 48) != '.' && isfloat == false) {
          Number1 = (Number1 * 10) + key; 
        //if we are in the decimals 
        //then Number1 equals (Number1 * position in decimals + key)/position in decimals  
        } else if ((key + 48) != '.' && isfloat == true) {
          count = count * 10;
          Number1 = (Number1 * count + key) / count;
        }

        Serial.println("First number: "); //debugging
        Serial.println(Number1); //debugging
        lcd.setCursor(0, 0);
        lcd.print(" "); //clear screen before the next number
        lcd.print(Number1); //print Number1 on screen
        

      } else { //Op has a value - We are Number2
        //if it's the first time then isfloat should be false
        if (first == 0)
          isfloat = false;
        first++;

        //if we want decimal then isfloat becomes true
        if (key == '.') {
          Serial.print(". pressed"); //debugging
          isfloat = true;
          count = 1; //initialise counter for the decimal position
        }

        key = key - 48;

        //if we are the first input and not in the decimals then Number2 value equals the input
        if (Number2 == 0 && (key + 48) != '.' && isfloat == false) {
          Number2 = key; 
        //if we are not the first number and not in the decimals 
        //then Number2 value is 10 times its previous value + the value of the key  
        } else if ((key + 48) != '.' && isfloat == false) {
          Number2 = (Number2 * 10) + key; 
        //if we are in the decimals 
        //then Number2 equals (Number2 * position in decimals + key)/position in decimals  
        } else if ((key + 48) != '.' && isfloat == true) {
          count = count * 10;
          Number2 = (Number2 * count + key) / count;
        }
        
        Serial.println("Second number: "); //debugging
        Serial.println(Number2); //debugging
        lcd.setCursor(8, 0); 
        lcd.print(" "); //clear screen before the next number
        lcd.print(Number2); //print Number2 on screen
 
      }
    //if '=' is pressed then we have the required inputs and flag ready becomes true  
    } else if (key == '=') { 
      Serial.print("Ready for results: ");
      Serial.print(key);
      Serial.print("\n");
      lcd.print(key); //print '=' on screen 
      ready = true;
    //if key is operator 
    } else {
      //if we have a value for Number1
      if (Number1 != 0) {
        Op = key;
        Serial.print("Operator: "); //debugging
        Serial.println(Op); //debugging
        lcd.setCursor(7, 0);
        lcd.print(Op); //print operator on screen
        //if there is no input for Number1 then warn user 
      } else {
        Serial.println("No number pressed"); //debugging
        lcd.print("No number given"); //display warning on screen
        delay(1000); //wait
        lcd.clear(); //clear screen 
      }
    }
    //if we are ready for results
    if (ready == true) {
      //calculation based on the operator chosen
      switch (Op) {
        case '+':
          Res = Number1 + Number2; //addition
          Serial.print("Result: "); //debugging
          Serial.println(Res); //debugging
          lcd.setCursor(1, 1);
          lcd.print(Res); //print result on screen
          break;
        case '-':
          Res = Number1 - Number2; //subtraction
          Serial.print("Result: "); //debugging
          Serial.println(Res); //debugging
          lcd.setCursor(1, 1);
          lcd.print(Res); //print result on screen
          break;
        case '*':
          Res = Number1 * Number2; //multiplication
          Serial.print("Result: "); //debugging
          Serial.println(Res); //debugging
          lcd.setCursor(1, 1);
          lcd.print(Res); //print result on screen
          break;
        case '/':
          Res = Number1 / Number2; //division
          Serial.print("Result: "); //debugging
          Serial.println(Res); //debugging
          lcd.setCursor(1, 1);
          lcd.print(Res); //print result on screen
          break;
      }
    }

  }


}
