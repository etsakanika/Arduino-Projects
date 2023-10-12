//Arduino Code Snipet


//Declaration of constant variables
#define gasSensor A0
#define buzzer 0
#define greenLed 10
#define redLed 11
#define HIGH 600


void setup() {

   Serial.begin(9600);
   
   pinMode(gasSensor, INPUT);
   pinMode(buzzer, OUTPUT);
   pinMode(greenLed, OUTPUT);
   pinMode(redLed, OUTPUT);
  
}


void loop() {
  
  int gasValue = analogRead(gasSensor);


  //check data from sensor if there is smoke, if will execute otherwise else will execute
  if(gasValue > HIGH){
    
     tone(buzzer,1000,500);
     digitalWrite(redLed, HIGH);
     digitalWrite(greenLed,LOW);
  }else{
    
     noTone(buzzer);
     digitalWrite(greenLed,HIGH);
     digitalWrite(redLed, LOW);
  }

  delay(200);
  
}
