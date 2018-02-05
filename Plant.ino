#include <LiquidCrystal.h>

//Digital:
int Fan = 4;
int Light = 7;
int Pump = 2;
int Buzzer = 9;
int LedRed = 12;
int LedGreen = 8;
//Analog:
int SoulPin = A0;
int H2OPin = A1;
int Brightness = A2;
float Temp = A3;
//Values:
int Humidity_level;
int H2O_level;
int Light_level;
int Temp_level;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  pinMode(Fan, OUTPUT);
  pinMode(Light, OUTPUT);
  pinMode(Pump, OUTPUT);
  pinMode(LedGreen, OUTPUT);
  pinMode(LedRed, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("hello world!");
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print(millis()/1000);
  Humidity_level = analogRead(SoulPin);
  H2O_level = analogRead(H2OPin);
  Light_level = analogRead(Brightness);
  Temp_level = analogRead(Temp);
  float voltage = Temp_level * 5.0;
  voltage /= 1024.0; 
  float TemperatureC = (voltage - 0.5) * 100 ;
  Serial.println("Degrees:");Serial.println(TemperatureC);

  
  if (Humidity_level < 50){
	digitalWrite(Pump, HIGH);
	delay(1000);
  }
  else {
    digitalWrite(Pump,LOW);
	delay(1000);
  }

  if (H2O_level < 100){
    digitalWrite(LedRed, HIGH);
    digitalWrite(LedGreen,LOW);
	digitalWrite(Pump,LOW);
	delay(1000);
  }
  else {
    digitalWrite(LedRed,LOW);
    digitalWrite(LedGreen, HIGH);
	delay(1000);
  }

  if (Light_level < 50){
    digitalWrite(Light, LOW);
    delay(1000);
  }
  if (Light_level > 60){
    digitalWrite(Light,HIGH);
    delay(1000);
  }

  if(TemperatureC > 28){
    digitalWrite(Fan,HIGH);
    delay(1000);
  }
  if(TemperatureC < 24){
    digitalWrite(Fan,LOW);
    delay(1000);
  }
}
