#include <Wire.h>

//Constants
#define Vin 5 // V power voltage

const int PhR = A0; //Outside

//Variables
int valuePR;
int ResValue;
int AchValue;
int percentValueP;
int percentValue;


void setup() {
  // put your setup code here, to run once:
  Wire.begin(2);
  Wire.onRequest(requestEvent);
  
  pinMode(PhR,INPUT);
  Serial.begin(9600);
}

int sensorRawToRes(int sensorValue){
  // Conversion 
  float Vout = float(sensorValue) * (Vin / float(1023));// Conversion analog to voltage 
  float RLDR = (Vin - Vout) / (Vout / 1000); // Conversion voltage to resistance
  return RLDR;
  
}

void loop() {

  //Serial Print for debugging
  Serial.print("Raw value from sensor = ");
  Serial.println(valuePR); 
  ResValue = sensorRawToRes(valuePR);
  Serial.print("Physical value from sensor = ");
  Serial.print(ResValue);
  Serial.print("Raw percentage = ");	
  percentValue = (valuePR-54)*100L/(974-54);	
  Serial.print(percentValue);
  Serial.print("Physical percentage = ");	
  percentValueP = (ResValue-600)*100L/(90-600);	
  Serial.print(percentValueP);
  delay(100);

}

void requestEvent() {
  valuePR = analogRead(PhR);
  ResValue = sensorRawToRes(valuePR);
  
  if(ResValue<=600 && ResValue>=90){
  	percentValueP = (ResValue-600)*100L/(90-600);
  }else if (ResValue>600){
 	 percentValueP = 0;
  }else if (ResValue<90){
 	 percentValueP = 100;  
  }
  
  delay(15);
  Wire.write(percentValueP);

}
 
