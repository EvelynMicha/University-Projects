int carRed = 10; // To assign the car lights
int carYellow = 9;
int carGreen = 8;
int pedRed = 12; // To assign the pedestrian lights
int pedGreen = 11;
int button = 2; // Tactile button pin

volatile int state = 1; // time allowed to cross
volatile int buttonState = 0; // variable for reading the pushbutton status

void setupTimer1() {
 noInterrupts();
 TCCR1A = 0; // Clear registers
 TCCR1B = 0; // Clear registers
 TCNT1 = 0; // Clear registers
 OCR1A =  15624;//1Hz (16*10^6) / (1*1024) - 1 (must be <65536)
 TCCR1B |= (1 << WGM12); // CTC
 TCCR1B |= (1 << CS12); // Prescaler 256
 TIMSK1 |= (1 << OCIE1A); // Output Compare Match A Interrupt Enable
 interrupts();
}
void setup() {
  // put your setup code here, to run once:
  pinMode(carRed, OUTPUT);
  pinMode(carYellow, OUTPUT);
  pinMode(carGreen, OUTPUT);
    
  pinMode(pedRed, OUTPUT);
  pinMode(pedGreen, OUTPUT);
    
  pinMode(button, INPUT); // button on pin 2
  setupTimer1();
  attachInterrupt(0,changeLights,RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
}
void changeLights(){
  //Για να μην πάει από το κόκκινο στο κίτρινο
  //και να μην καθυστερεί περισσότερο το κίτρινο
  if(state==1)
	state = 2;
}

ISR(TIMER1_COMPA_vect) {
  //Κατάσταση 1 - Αρχική
   if(state == 1){
   digitalWrite(carGreen,HIGH);
   digitalWrite(pedRed,HIGH); 
  //Κατάσταση 2 - Κίτρινο
   }else if(state == 2){
   digitalWrite(carGreen,LOW);
     
   digitalWrite(carYellow,HIGH);
  //Κατάσταση 3 - Κόκκινο
   }else if(state == 3){
   digitalWrite(carYellow,LOW);
   digitalWrite(pedRed,LOW);
     
   digitalWrite(carRed,HIGH);
   digitalWrite(pedGreen,HIGH);   
   //Κατάσταση 4 - Πράσινο
   }else if(state == 4){
   digitalWrite(carRed,LOW);
   digitalWrite(pedGreen,LOW);    
       
   digitalWrite(carGreen,HIGH);
   digitalWrite(pedRed,HIGH); 
     
   state = 1;  //Αρχικοποίηση 
   }
  state++; //Επόμενη Κατάσταση
}
