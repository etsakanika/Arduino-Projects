//Arduino Code Snipet


//Declaration of variables
int smokeSensor = A0;
int greenLed = 10;
int redLed = 11;
int buzzer = 12;
int smokeReading = 0;  // store the value which the smoke sensor reads
int celsius;
int green1;
int green2;
int green3;


void setup()
{  
  
  Serial.begin(9600);
  
  pinMode(smokeSensor, INPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
}


void loop()
{

  smokeReading = analogRead(smokeSensor); 
  Serial.print("Air Quality in PPM = ");
  Serial.print(smokeReading);    
  
  if(smokeReading <= 100){
    
     Serial.print("Fresh Air");
     digitalWrite(greenLed, HIGH);
     digitalWrite(redLed, LOW);
    
  }else{
      
     Serial.print("Poor Air.Be careful!");
     digitalWrite(redLed, HIGH);
     digitalWrite(greenLed, LOW);
  }
  
  delay(100);
}
