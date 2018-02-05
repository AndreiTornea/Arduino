#include <LiquidCrystal.h>

//Digitali:
int fan = 4;
int light = 7;
int pump = 2;
int buzzer = 9;
int ledred = 12;
int ledgreen = 8;
//Analogici:
int soulPin = A0;
int H2OPin = A1;
int brightness = A2;
float temp = A3;
//Valori:
int humidity_level;
int H2O_level;
int light_level;
int temp_level;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  pinMode(fan, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(ledgreen, OUTPUT);
  pinMode(ledred, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("hello world!");
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print(millis()/1000);
  humidity_level = analogRead(soulPin);
  H2O_level = analogRead(H2OPin);
  light_level = analogRead(brightness);
  temp_level = analogRead(temp);
  float voltage = temp_level * 5.0;
  voltage /= 1024.0; 
  float temperatureC = (voltage - 0.5) * 100 ;
  Serial.println("Gradi:");Serial.println(temperatureC);

  
  if (humidity_level < 50){
	digitalWrite(pump, HIGH);
	delay(1000);
  }
  else {
    digitalWrite(pump,LOW);
	delay(1000);
  }

  if (H2O_level < 100){
    digitalWrite(ledred, HIGH);
    digitalWrite(ledgreen,LOW);
	digitalWrite(pump,LOW);
	delay(1000);
  }
  else {
    digitalWrite(ledred,LOW);
    digitalWrite(ledgreen, HIGH);
	delay(1000);
  }

  if (light_level < 50){
    digitalWrite(light, LOW);
    delay(1000);
  }
  if (light_level > 60){
    digitalWrite(light,HIGH);
    delay(1000);
  }

  if(temperatureC > 28){
    digitalWrite(fan,HIGH);
    delay(1000);
  }
  if(temperatureC < 24){
    digitalWrite(fan,LOW);
    delay(1000);
  }
}

