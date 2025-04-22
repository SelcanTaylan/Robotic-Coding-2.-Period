#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  

int trigPin = 13; 
int echoPin = 12;  
long zaman;
long mesafe;
long toplamMesafe = 0;
void setup() {
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT); 
    lcd.begin(); 
    lcd.backlight(); 
    delay(1000);  // Sensörün stabil hale gelmesi için bekleme süresi
  
}



void loop() {
   // mesafe = mesafeOlc();  // Güncellenmiş ölçüm fonksiyonunu çağırıyoruz
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  
  zaman = pulseIn(echoPin, HIGH);
  toplamMesafe += (zaman / 29.1) / 2;
  delay(50);
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("MESAFE OLCER"); 
  lcd.setCursor(0, 1); 
  lcd.print(190-mesafe);  
  lcd.setCursor(4, 1); 
  lcd.print("cm");    

  delay(500);
}
