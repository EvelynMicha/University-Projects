#include <Servo.h> //including the library of servo motor

Servo sHour,sDecl; //initializing a variable for servo named sg90
int decl_position = 90; //Declaring the initial position at 90
int hour_position = 90;

int LDR1 = A0; //Pin at which LDR is connected
int LDR2 = A1; //Pin at which LDR is connected
int LDR3 = A2; //Pin at which LDR is connected
int LDR4 = A3; //Pin at which LDR is connected

int error = 5; //initializing variable for error
int servopin1=8;
int servopin2=9;
void setup()
{
 sHour.attach(servopin1); // attaches the servo on pin 9
 sDecl.attach(servopin2); // attaches the servo on pin 8
 pinMode(LDR1, INPUT); //Making the LDR pin as input
 pinMode(LDR2, INPUT);
 pinMode(LDR3, INPUT); 
 pinMode(LDR4, INPUT);
 sHour.write(hour_position); //Move servo at 90 degree
 sDecl.write(decl_position); //Move servo at 90 degree 
 delay(2000); // giving a delay of 2 seconds
 Serial.begin(9600);
}

void loop()
{
 int R1 = analogRead(LDR1); // reading value from LDR 1
 int R2 = analogRead(LDR2); // reading value from LDR 2
 int R3 = analogRead(LDR3); // reading value from LDR 3
 int R4 = analogRead(LDR4); // reading value from LDR 4
  
// Calculating the difference between the LDR's
 int diff1= abs(R1 - R2);
 int diff2= abs(R2 - R3);
 int diff3= abs(R3 - R4); 

 if((diff1 <= error) || (diff2 <= error || (diff3<=error))) {
 //if the difference is under the error then do nothing
 Serial.println("Difference: ");
 Serial.println(diff1);
 Serial.println(diff2);
 Serial.println(diff3);  
 } else {
 if((R1 > R3 && R1 > R4) || (R2 > R3 && R2 > R4))
 {
 //Move the servo towards 0 degree
 decl_position = --decl_position;
 Serial.println(R1);
 Serial.println(R2);
 Serial.println(R3);
 Serial.println(R4);   
 }
 if((R1 < R3 && R1 < R4) || (R2 < R3 && R2 < R4))
 {
 //Move the servo towards 180 degree
 decl_position = ++decl_position;
 Serial.println(R1);
 Serial.println(R2);
 Serial.println(R3);
 Serial.println(R4);   
 }
 if((R1 > R2 && R1 > R4) || (R3 > R2 && R3 > R4))
 {
 //Move the servo towards 0 degree
 hour_position = --hour_position;
 Serial.println(R1);
 Serial.println(R2);
 Serial.println(R3);
 Serial.println(R4);   
 }
 if((R1 < R2 && R1 < R4) || (R3 < R2 && R3 < R4))
 {
 //Move the servo towards 180 degree
 hour_position = ++hour_position;
 Serial.println(R1);
 Serial.println(R2);
 Serial.println(R3);
 Serial.println(R4);   
 }
 if(R1 < 70 && R2 < 70 && R3 < 70 && R4 < 70) //Night
 {
 sDecl.write(90);
 sHour.write(90);
 Serial.println(R1);
 Serial.println(R2);
 Serial.println(R3);
 Serial.println(R4);   
 }   
 }
 sDecl.write(decl_position); // write the position to servo
 sHour.write(hour_position); // write the position to servo
 delay(100);

}
