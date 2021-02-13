#include <avr/interrupt.h>

const byte interruptLeft = 5;
const byte interruptRight = 3;

const byte RELAY_LEFT = 8;
const byte RELAY_RIGHT = 9;

volatile byte state_left = LOW;
volatile byte state_right = LOW;

volatile int value = 0;

void setup() {

  cli();
  //RELAY
  pinMode(RELAY_LEFT, OUTPUT);
  pinMode(RELAY_RIGHT, OUTPUT);  

  pinMode(interruptLeft, INPUT_PULLUP);
  pinMode(interruptRight, INPUT_PULLUP);
  
  pinMode(A0, INPUT_PULLUP);
  PCICR = B00000010; // enable PCIE1 group
  PCIFR = B00000000; // clear all interrupt flags
  PCMSK1 = B00000001; //enable PCINT8
  //EXTERNAL INTERRUPTS
  attachInterrupt(digitalPinToInterrupt(2),leftIncline,RISING); 
  attachInterrupt(digitalPinToInterrupt(3),RightIncline,RISING); 
  
  Serial.begin(9600);  
  
  sei();

}

void loop() {
  digitalWrite(RELAY_RIGHT, state_right);
  digitalWrite(RELAY_LEFT, state_left);
}

void leftIncline(){
  	//Μεγαλύτερο βάρος στα αριστερά άρα ανοίγουμε τη δεξιά αντλία
	state_right = HIGH;
    Serial.print("Go right\n");
}

void RightIncline(){
    //Μεγαλύτερο βάρος στα δεξιά άρα ανοίγουμε την αριστερή αντλία
	state_left = HIGH;
 	Serial.print("Go left\n");
}

ISR(PCINT1_vect)
{
  value++;
  if(value==1){ //Αγνόηση του πρώτου σημείου ηρεμίας
  	Serial.print("Ignore");
  }
  else{
    //Σταματάει τις αντλίες
  	state_right = LOW; 
  	state_left = LOW;
  	Serial.print("Balanced\n");
  }

}

