#include <QTRSensors.h> // QTR v4.0 kütüphanesini dahil et (Sensör kontrolü için)

// ==== MOTOR VE SENSÖR TANIMLAMALARI ====
#define AIN1 4   // Sağ motor ileri sürüş pini
#define AIN2 3   // Sağ motor geri sürüş pini
#define ENA 5    // Sağ motor PWM hız kontrolü

#define ENB 6    // Sol motor PWM hız kontrolü
#define BIN1 7   // Sol motor ileri sürüş pini
#define BIN2 8   // Sol motor geri sürüş pini
#define STBY 9   // Motor sürücüsünü aktif/pasif yapma pini

// ==== SENSÖR VE PD KONTROL AYARLARI ====
#define sensorSayisi 8   // Kullanılan sensör sayısı (QTR-8A)
#define sensorOrnekSayisi 4   // Kalibrasyon sırasında alınan örnek sayısı
#define emiterPini 11   // Sensörlerin emiter pini (IR ışık verici)
#define LED 13   // Kalibrasyon için gösterge LED'i

int maxHiz = 70;  // Motor PWM ayarı (0 - 255 arasında)
float KP = 0.03, KD = 0.5; // Oransal (KP) ve türev (KD) katsayıları
unsigned int pozisyon = 3500;  // Çizginin merkezi konumu

int hata = 0, turev = 0; // PD kontrolünde kullanılan hata değerleri
int fark = 0; // Motorlara uygulanacak hız farkı
int sonHata; // Önceki hata değeri (Türev hesaplamaları için)
int hedef = 3500; // Sensörlerden gelen 0 - 7000 arasındaki değerin orta noktası

QTRSensors qtr;  // QTR nesnesi oluşturuldu
unsigned int sensor[sensorSayisi];  // Sensör verilerini tutan dizi

// ========================
// **KURULUM (Setup)**
// ========================
void setup() {
    Serial.begin(9600);  // Seri haberleşmeyi başlat

    // Sensörleri yapılandır
    qtr.setTypeAnalog();  // Analog sensör türünü seç
    qtr.setSensorPins((const uint8_t[]) {A0, A1, A2, A3, A4, A5, A6, A7}, 8); // Sensör pinlerini belirle
    
    // Motor ve LED pinlerini çıkış olarak ayarla
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(LED, OUTPUT);
    pinMode(STBY, OUTPUT);

    delay(1000);  // Araca enerji verildiğinde 1 saniye beklet
    kalibrasyon(1);  // 1 = otomatik kalibrasyon, 0 = manuel kalibrasyon
}

// ========================
// **ANA DÖNGÜ (Loop)**
// ========================
void loop() {
    sensorOku();  // Sensörleri oku ve hata hesapla
    pd();  // PD kontrol fonksiyonunu çalıştır
}

// ========================
// **Sensör Verilerini Okuma**
// ========================
void sensorOku() {
    pozisyon = qtr.readLineWhite(sensor);  // Çizginin pozisyonunu belirle (0 - 7000)
    hata = pozisyon - hedef;  // Merkez ile farkı hesapla
    qtr.read(sensor);  // Tüm sensörlerin ham verilerini oku
}

// ========================
// **PD KONTROL FONKSİYONU**
// ========================
void pd() {
    turev = hata - sonHata;  // Türevsel hata hesapla
    sonHata = hata;  // Önceki hata değerini güncelle

    fark = (hata * KP) + (turev * KD);  // Motorlara uygulanacak hız farkını hesapla
    constrain(fark, -maxHiz, maxHiz);  // Maksimum farkı sınırlandır

    // Motor hızlarını ayarla
    if (fark < 0) {
        motor(maxHiz, maxHiz + fark);  // Sağ motorun hızını düşür
    } else {
        motor(maxHiz - fark, maxHiz);  // Sol motorun hızını düşür
    }
}

// ========================
// **Motor Kontrol Fonksiyonu**
// ========================
void motor(int solMotorPWM, int sagMotorPWM) {
    digitalWrite(STBY, HIGH);  // Motor sürücüsünü aktif hale getir

    // Sol motoru kontrol et
    if (solMotorPWM >= 0) {
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);
    } else {
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, HIGH);
        solMotorPWM *= -1;  // Geri hareket için negatif değeri pozitife çevir
    }
    analogWrite(ENB, solMotorPWM);

    // Sağ motoru kontrol et
    if (sagMotorPWM >= 0) {
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
    } else {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
        sagMotorPWM *= -1;  // Geri hareket için negatif değeri pozitife çevir
    }
    analogWrite(ENA, sagMotorPWM);
}

// ========================
// **Kalibrasyon Fonksiyonu**
// ========================
void kalibrasyon(bool secim) {
    if (secim) {  // Eğer otomatik kalibrasyon seçildiyse
        byte hiz = 40;  // Aracın kafa sallama hızı
        for (byte i = 0; i < 3; i++) {  // Kafa sallama hareketi
            while (sensor[7] < 300) {
                motor(hiz, -hiz);
                qtr.calibrate();
                sensorOku();
            }
            while (sensor[7] > 700) {
                motor(hiz, -hiz);
                qtr.calibrate();
                sensorOku();
            }
            while (sensor[0] < 300) {
                motor(-hiz, hiz);
                qtr.calibrate();
                sensorOku();
            }
            while (sensor[0] > 700) {
                motor(-hiz, hiz);
                qtr.calibrate();
                sensorOku();
            }
            while (sensor[3] > 500) {
                motor(hiz, -hiz);
                qtr.calibrate();
                sensorOku();
            }
        }
    } else {  // Eğer manuel kalibrasyon seçildiyse
        for (byte i = 0; i < 70; i++) {
            digitalWrite(LED, HIGH);
            delay(20);
            qtr.calibrate();
            digitalWrite(LED, LOW);
            delay(20);
            qtr.calibrate();
        }
    }
    motor(0, 0);
    delay(2000);  // Kalibrasyondan sonra 2 saniye bekle
}
