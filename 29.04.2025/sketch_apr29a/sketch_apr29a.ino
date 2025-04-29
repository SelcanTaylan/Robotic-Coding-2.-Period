void setup() {
 Serial.begin(9600);
 pinMode(6,OUTPUT);
 pinMode(7,INPUT); 
}

void loop() {
 digitalWrite(6,1); delay(1);
 digitalWrite(6,0);
 int sure=pulseIn(7,1);
 int mesafe=(sure/2)/28.97 ;
 Serial.print("Olculen Mesafe: ");
Serial.println(mesafe);
delay(1); 
}
