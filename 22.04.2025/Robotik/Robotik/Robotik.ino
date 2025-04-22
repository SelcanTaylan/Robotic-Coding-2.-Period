#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  

int trigPin = 13; 
int echoPin = 12;  
long zaman;
long mesafe;
const int sensorYukseklik = 190; // Sensörün konumlandığı yükseklik

void setup() {
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT); 
    lcd.begin(); 
    lcd.backlight(); 
    delay(1000);  // Sensörün stabil hale gelmesi için bekleme süresi
}

long mesafeOlc() {
    long toplamMesafe = 0;
    int olcumSayisi = 5;
    
    for (int i = 0; i < olcumSayisi; i++) {
        digitalWrite(trigPin, LOW); 
        delayMicroseconds(5);
        digitalWrite(trigPin, HIGH); 
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);  
        zaman = pulseIn(echoPin, HIGH);
        toplamMesafe += (zaman / 29.1) / 2;
        delay(50);  // Ölçümler arasında küçük bir gecikme ekleyelim
    }

    mesafe = toplamMesafe / olcumSayisi; // Ortalama değer alıyoruz

    if (mesafe < 4) mesafe = 4;
    else if (mesafe > 100) mesafe = 100;

    return mesafe;
}

void loop() {
    mesafe = mesafeOlc();  // Güncellenmiş ölçüm fonksiyonunu çağırıyoruz
    long boy = sensorYukseklik - mesafe;  // Boy hesaplaması

    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("BOY OLCER"); 
    lcd.setCursor(0, 1); 
    lcd.print(boy);  
    lcd.setCursor(5, 1); 
    lcd.print("cm");    

    delay(500);
}
