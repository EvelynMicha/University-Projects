/**
   @mainpage Obstacle Avoiding Car
   @version v1
   @author Evangelia Micha
   CreateDate 2021

*/

/** @file project8-cs171102.ino
    @brief Obstacle Avoiding Car

    @author Evangelia Micha
    @bug No known bugs.
*/

/** @defgroup   Obstacle Avoiding Car Firmware
  @{
*/

//Motor 1
const int motorLeft_Pin1  = 10;  // Pin 2 of L293
const int motorLeft_Pin2  = 11;  // Pin 7 of L293
//Motor 2
const int motorRight_Pin1  = 12; // Pin  10 of L293
const int motorRight_Pin2  = 13;  // Pin  15 of L293
//Ultrasonic Sensor
int trigPin=8; //Sensor Trip pin connected to Arduino pin 8
int echoPin=9; //Sensor Echo pin connected to Arduino pin 9
float pingTime; //time for ping to travel from sensor to target and return
float targetDistance; //Distance to Target in inches
float speedOfSound=1235; //Speed of sound in km per hour when temp is 20 degrees.


//This will run only one time.
void setup(){
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    //Set pins as outputs
    pinMode(motorLeft_Pin1, OUTPUT);
    pinMode(motorLeft_Pin2, OUTPUT);
    pinMode(motorRight_Pin1, OUTPUT);
    pinMode(motorRight_Pin2, OUTPUT);
}


void loop(){
  float distance = getDistance();
  if(distance<=40){ //if there's an obstacle near
    stopMotors(); //stop the motion on both motors
    delay(1000);
    turnRight(); //make right turn
    delay(1000);
  }else{
    moveForward(); //if there's no obstacle continue with forward movement
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

/** @brief Stop Motors
    Stops the motion of both motors
*/
void stopMotors(){
    digitalWrite(motorLeft_Pin1, LOW);
    digitalWrite(motorLeft_Pin2, LOW);
    digitalWrite(motorRight_Pin1, LOW);
    digitalWrite(motorRight_Pin2, LOW);
}

/** @brief Move Forward
   Both motors move forwardly
*/
void moveForward(){
    digitalWrite(motorLeft_Pin1, HIGH);
    digitalWrite(motorLeft_Pin2, LOW);
    digitalWrite(motorRight_Pin1, HIGH);
    digitalWrite(motorRight_Pin2, LOW);
}

/** @brief Turn Right
   Left motor moves forward while Right motor moves backward
   in order to achieve a right turn on the spot
*/
void turnRight(){
    digitalWrite(motorLeft_Pin1, HIGH);
    digitalWrite(motorLeft_Pin2, LOW);
    digitalWrite(motorRight_Pin1, LOW);
    digitalWrite(motorRight_Pin2, HIGH);
}


/** @brief Move Backward
   Both motors move backwards
   Not used in the code - made for future additions
*/
void moveBackward(){
    digitalWrite(motorLeft_Pin1, LOW);
    digitalWrite(motorLeft_Pin2, HIGH);
    digitalWrite(motorRight_Pin1, LOW);
    digitalWrite(motorRight_Pin2, HIGH);
}

