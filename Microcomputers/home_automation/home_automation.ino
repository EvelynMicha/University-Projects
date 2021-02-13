/**
   @mainpage Home Automation
   @version v1
   @author Evangelia Micha
   CreateDate 2021

*/

/** @file project9-cs171102.ino
    @brief Home Automation

    @author Evangelia Micha
    @bug No known bugs.
*/

/** @defgroup   Home Automation Firmware
  @{
*/

int celsius = 0; //TMP
int dcSpeed = 0; //DC MOTOR
int sensorState = 0; //PIR

int trigPin=8; //Sensor Trip pin connected to Arduino pin 8
int echoPin=9; //Sensor Echo pin connected to Arduino pin 9
float pingTime; //time for ping to travel from sensor to target and return
float targetDistance; //Distance to Target in inches
float speedOfSound=1235; //Speed of sound in km per hour when temp is 20 degrees.


void setup()
{
  pinMode(13, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  DoorControl();
  LightControl();
  TemperatureControl();

}

/** @brief Temperature Control
    Open the fun if temperature is above 20 celsius
*/
void TemperatureControl(){
  celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1024, -40, 125);
  Serial.print(celsius);
  Serial.println(" C, ");
  
  if(celsius > 20){
     Serial.println("Opening fun");  
     for (dcSpeed = 0; dcSpeed <= 255; dcSpeed += 5) {
     analogWrite(10,dcSpeed);
     delay(30); 
     }
  }else{
     Serial.println("Closed fun");
  }              
}

/** @brief Light Control
    Open the lights(led) if motion is detected
*/
void LightControl(){
   // read the state of the sensor/digital input
   sensorState = digitalRead(2);
   // check if sensor pin is HIGH. if it is, set the LED on.
   if (sensorState == HIGH) {
   digitalWrite(13, HIGH);
   Serial.println("Sensor activated!");
   } else {
   digitalWrite(13, LOW);
   Serial.println("Sensor deactivated!");   
   }
   delay(10); // Delay a little bit to improve simulation performance

}

/** @brief Door Control
    Open the door if someone is at distance less than 40cm 
    check again keep open for 2 seconds or close door
*/
void DoorControl(){
  float distance = getDistance();
  Serial.println(distance);
  if(distance<=40){
  Serial.println("Open Door");
    if(distance<=40)
      delay(2000);
  }else{
    Serial.println("Closed Door");
  }
}

 
/** @brief Calculate Distance from Ultrasonic Sensor
    Returns the current distance
*/

float getDistance(){
  digitalWrite(trigPin, LOW); //Set trigger pin low
  delayMicroseconds(2000); //Let signal settle
  digitalWrite(trigPin, HIGH); //Set trigPin high
  delayMicroseconds(10); //Delay in high state
  digitalWrite(trigPin, LOW); //ping has now been sent
  delayMicroseconds(10); //Delay in high state

  pingTime = pulseIn(echoPin, HIGH); //pingTime is presented in microceconds
  pingTime=pingTime/1000000; //convert pingTime to seconds by dividing by 1000000 (microseconds in a second)
  pingTime=pingTime/3600; //convert pingtime to hours by dividing by 3600 (seconds in an hour)
  targetDistance= speedOfSound * pingTime; //This will be in km, since speed of sound was km per hour
  targetDistance= targetDistance/2; //Remember ping travels to target and back from target, so you must divide by 2 for actual target distance.
  targetDistance= targetDistance*100000; //Convert km to cm by multipling by 100000 (1km to cm)
  
  Serial.print(targetDistance); //Print measured distance
  Serial.println(" cm"); //Print your units.
  delay(250); //pause to let things settle
  return targetDistance;
}

