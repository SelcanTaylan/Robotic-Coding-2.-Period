/* BlogKod - Analog Çıkış İşlemleri Uygulaması */
const int analogGirisPini = A0; // Potu A0 analog pine bağlayacağız
const int analogCikisPini = 3; // PWM pini olmak zorunda!
int potDegeri = 0; // Pottan gelen değeri bu değişkene atayacağız
int LEDDegeri = 0; // 0-255 arası dönüşüm değerini bu değişken tutacak



void setup() {
  Serial.begin(9600);
  pinMode(3,OUTPUT);
}

void loop() {

  potDegeri = analogRead(analogGirisPini); // A0 pininden değer okundu
  Serial.print("Pottan Okunan Deger: "); // A0'dan gelen değeri Seri porta yazıyoruz
  Serial.println(potDegeri);

  // Analog IN değerini Analog OUT değerine çevrim işlemini map() fonksiyonu ile yapıyoruz
  // map() fonskiyonu potDegerini alacak(0-1023 arası) ve 0-255 arası bir değere çevirecek

  //Çevrim işlemi yapılıyor ve bu değer LEDDegeri değişkeninde tutuluyor
  LEDDegeri = map(potDegeri, 0, 1023, 0, 255);
  Serial.print("Analog Cikis Degeri: "); //Çevrimi yapılan bu yeni değeri seri porta yazıyoruz
  Serial.println(LEDDegeri);


  // analogWrite() fonksiyonu PWM pinimize çevrimi yapılan yeni değeri gönderiyor
  // PWM pinine bağlı olan LED'imiz bu değere göre parlaklık alıyor.
  analogWrite(analogCikisPini, LEDDegeri);
}
