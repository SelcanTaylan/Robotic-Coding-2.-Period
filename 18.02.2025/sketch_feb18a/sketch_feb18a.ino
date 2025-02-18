#define Ldr A0
void setup()
{
Serial.begin(9600);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
} 
void loop()
{
int Ldr_deger = analogRead(Ldr);
Serial.print("Analog Deger = "); 
Serial.println(Ldr_deger);
delay(250); 
if( Ldr_deger<=60&& Ldr_deger>=0){
    digitalWrite(3, 1);
   digitalWrite(4, 1);
   digitalWrite(5, 1);
  
  }

 else if( Ldr_deger<=100&& Ldr_deger>50){
    digitalWrite(3, 1);
    digitalWrite(4, 1);
    digitalWrite(5, 0);
  }
  
 else if(Ldr_deger>100){
    digitalWrite(3, 0);
    digitalWrite(4, 0);
    digitalWrite(5, 1);
  }
  
}
