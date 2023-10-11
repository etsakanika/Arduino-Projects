#include <LiquidCrystal.h>

const int ultrasensor_PingPin = 12;
const int temp_Sensor = A0;
int ledPin_Red = 11;
int ledPin_Blue = 10;
int buzzer = 9;
const int button_Pin = 8;

int temperature = 0; 
float thres_min = 12.0;
float thres_max = 32.0;
int celsius;

int bhits = 0;
int buttonState = 0;
int prevbuttonState = 0;

LiquidCrystal lcd(2,3,4,5,6,7);


void setup() {

  Serial.begin(9600);  

  
  pinMode(ultrasensor_PingPin, INPUT);
  pinMode(temp_Sensor, INPUT);
  pinMode(button_Pin, INPUT);
  pinMode(ledPin_Red, OUTPUT);
  pinMode(ledPin_Blue, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.clear() ;
  lcd.setCursor(0, 0);  
  lcd.print("Hello!");
  lcd.setCursor(0, 1);
  lcd.print("How are you ?");
  
  
  lcd.display();
  delay(1000);
  
}


void loop() {

  
  /*Block of code for ultrasonic sensor detection*/
  long duration, inches, cm;

  pinMode(ultrasensor_PingPin, OUTPUT);
  digitalWrite(ultrasensor_PingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasensor_PingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(ultrasensor_PingPin, LOW);

  pinMode(ultrasensor_PingPin, INPUT);
  duration = pulseIn(ultrasensor_PingPin, HIGH);
  cm = microsecondsToCentimeters(duration);

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);

  /*Block of code in which the signal from the temp sensor is 
  ceing converted into celsius degrees */
  celsius = map(((analogRead(A0) - 20) * 3.04), 
                0, 1023, -40, 125); //FIND CELCIUS 

  //int temp_Signal= analogRead(temp_Sensor);
  //float voltage = temp_Signal * (5000 / 1024.0);
  //temperature = voltage / 10;
  Serial.print("The temperature is: ");
  Serial.print(celsius);
  Serial.print("\xB0");
  Serial.println("C");
  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print("The temp is:");
  lcd.setCursor(0, 1);
  lcd.print(celsius);
  lcd.print("C");
  lcd.display();
  delay(1000);

  if(celsius > thres_max){
    
     digitalWrite(ledPin_Red, HIGH);
     digitalWrite(ledPin_Blue, LOW);
     tone(buzzer, 700);
     Serial.println("High Temperature detected!");
     lcd.clear();
     lcd.setCursor(0, 0);  
     lcd.print("High Temperature");
     lcd.setCursor(0, 1);
     lcd.print("detected!");
     lcd.display();
     delay(1000);
    }
  else if(celsius < thres_min){

     digitalWrite(ledPin_Red, LOW);
     digitalWrite(ledPin_Blue, HIGH);
     tone(buzzer, 700);
     Serial.println("Low Temperature detected!");
     lcd.clear();
     lcd.setCursor(0, 0);  
     lcd.print("Low Temperature");
     lcd.setCursor(0, 1);
     lcd.print("detected!");
     lcd.display();
     delay(1000);
  }
  else{
    
     digitalWrite(ledPin_Red, LOW);
     digitalWrite(ledPin_Blue, LOW);
     noTone(buzzer);
     Serial.println("Normal Temperature");
     lcd.clear();
     lcd.setCursor(0, 0);  
     lcd.print("Normal");
     lcd.setCursor(0, 1);
     lcd.print("Temperature");
     lcd.display();
     delay(1000);
    
     if (buttonState == HIGH) {
        Serial.println("Button is not pressed");
     }
     else {
        Serial.println("Button is pressed");
     }
     delay(100);
  }


  /*Block of code for button switch in lcd screen*/
  buttonState = digitalRead(8);

  bhits = bhits + 1;
  
  if(buttonState > prevbuttonState){
  
     lcd.clear() ;
     lcd.setCursor(0, 0);  
     lcd.print("Hello!");
     lcd.setCursor(0, 1);
     lcd.print("How are you?");
     lcd.display();
     delay(1000);
     //Serial.println("Button up");
  }
  else{
     Serial.println("The button is not clicked twice");
  }
     
    
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
