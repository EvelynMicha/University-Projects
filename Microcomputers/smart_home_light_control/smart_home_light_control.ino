#include <Servo.h>

//Constants
#define Vin 5 // V power voltage

const int PhR1 = A0; //Outside
const int PhR2 = A1; //Inside

//Variables
int valuePR1,valuePR2;
Servo myservo;
int pos = 0;
int PrevPos = 0;
int ResValue,ResValue2;
int AchValue;

void setup() {
  pinMode(PhR1,INPUT);
  pinMode(PhR2,INPUT);
  Serial.begin(9600);

  myservo.attach(9);
}

int sensorRawToRes(int sensorValue){
  // Conversion 
  float Vout = float(sensorValue) * (Vin / float(1023));// Conversion analog to voltage
  //Serial.print("Voltage= ");
  //Serial.println(Vout); 
  float RLDR = (Vin - Vout) / (Vout / 1000); // Conversion voltage to resistance
  return RLDR;
  
}

void loop() {
  
  valuePR1 = analogRead(PhR1);
  valuePR2 = analogRead(PhR2);
  
  ResValue = sensorRawToRes(valuePR1);
  ResValue2 = sensorRawToRes(valuePR2);
  delay(15);  

  //Serial Print for debugging
  Serial.print("Raw value from sensor = ");
  Serial.println(valuePR1); 
  Serial.print("Physical value from outside sensor = ");
  Serial.print(ResValue); 
  Serial.print("Physical value from inside sensor = ");
  Serial.print(ResValue2); 
 
  if(ResValue > 600){ // NIGHT
  for (pos = PrevPos; pos >= 0; pos -= 1) { // goes from 90 to 0 degrees
       myservo.write(pos); // go to position in variable 'pos'
       delay(15); // waits 15ms
  }
  PrevPos = pos;  
    
  }else if(ResValue > 90){ //DAWN AND SUNRISE
    for (pos = PrevPos; pos <= 90; pos += 1) { // goes from 0 to 90 degrees
       myservo.write(pos); // go to position in variable 'pos'
       delay(15); // waits 15ms
    }
  PrevPos = pos; 
    
  }else{ //NOON
    AchValue = 70/100 * ResValue2 + ResValue2; 
    pos = 0;
    while (ResValue >= AchValue){
      pos++;
      myservo.write(pos);
      delay(15);
      if(pos>=90)
        break;
    }
    PrevPos = pos; 
  }

  delay(1000);

}
