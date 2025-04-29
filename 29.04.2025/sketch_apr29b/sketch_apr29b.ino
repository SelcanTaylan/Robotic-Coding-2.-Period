void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT); // Ultrasonik sensörün tetikleme pini
  pinMode(9, INPUT);  // Ultrasonik sensörün echo pini
  pinMode(7, OUTPUT); // Buzzer pini
  pinMode(1, OUTPUT); // 1. LED
  pinMode(2, OUTPUT); // 2. LED
  pinMode(3, OUTPUT); // 3. LED
}

void loop() {
  // Ultrasonik sensörden mesafe ölçümü
  digitalWrite(8, HIGH);
  delayMicroseconds(10);
  digitalWrite(8, LOW);

  int sure = pulseIn(9, HIGH); // Echo piniyle zamanı ölç
  int mesafe = (sure / 2) / 28.97; // Mesafeyi hesapla (cm)

  Serial.print("Ölçülen Mesafe: ");
  Serial.println(mesafe);

  // Buzzer kontrolü
  if (mesafe >= 0 && mesafe < 10) {
    // Sürekli ses çıkar
    digitalWrite(7, HIGH);
    digitalWrite(1, HIGH); // 1. LED
    digitalWrite(2, HIGH); // 2. LED
    digitalWrite(3, HIGH); // 3. LED
  } 
  else if (mesafe >= 10 && mesafe < 30) {
    // Kesik kesik ses çıkar
    digitalWrite(7, HIGH);
    delay(200); // 200 ms açık
    digitalWrite(7, LOW);
    delay(200); // 200 ms kapalı
    digitalWrite(1, HIGH); // 1. LED
    digitalWrite(2, HIGH); // 2. LED
    digitalWrite(3, LOW);  // 3. LED kapalı
  } 
  else if (mesafe >= 30 && mesafe < 50) {
    // Çok kesik kesik ses çıkar
    digitalWrite(7, HIGH);
    delay(500); // 500 ms açık
    digitalWrite(7, LOW);
    delay(500); // 500 ms kapalı
    digitalWrite(1, HIGH); // 1. LED
    digitalWrite(2, LOW);  // 2. LED kapalı
    digitalWrite(3, LOW);  // 3. LED kapalı
  } 
  else {
    // Hiç ses çıkarma
    digitalWrite(7, LOW);
     digitalWrite(1, LOW); // Tüm LED'ler kapalı
     digitalWrite(2, LOW);
     digitalWrite(3, LOW);
  }


}
