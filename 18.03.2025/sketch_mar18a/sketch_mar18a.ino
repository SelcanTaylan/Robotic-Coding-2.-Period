void setup() {
  pinMode(2, OUTPUT);
}

void loop() {
  // Ambulans sireni için artan ve azalan frekansları kullanıyoruz.
  
  // Yüksek frekansla başla
  tone(2, 1000);  // 1000 Hz frekans
  delay(200);     // 200ms süre
  
  // Frekansı biraz daha düşük yap
  tone(2, 1500);  // 1500 Hz frekans
  delay(200);     // 200ms süre
  
  // Frekansı biraz daha düşür
  tone(2, 500);  
}
