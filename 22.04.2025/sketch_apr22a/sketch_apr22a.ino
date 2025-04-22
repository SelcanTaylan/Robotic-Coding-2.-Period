int trig=13;
int echo=12;
int sure;
int mesafe;
void setup() {
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  Serial.begin(9600);
}

void loop() {
 digitalWrite(trig,1);
 delayMicroseconds(1000);
 digitalWrite(trig,0);
 sure=pulseIn(echo,1);
 mesafe=(sure/2)/29.1;
 Serial.println(mesafe);
}
