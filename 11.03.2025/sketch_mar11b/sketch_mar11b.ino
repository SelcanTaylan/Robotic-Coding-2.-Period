int kled = 11;
int yled = 10;
int mled = 9;
void setup() {
pinMode(kled, OUTPUT);
pinMode(yled, OUTPUT);
pinMode(mled, OUTPUT);
}

void loop() 
{
   for(int i=0;i<=255;i++)
  {
    analogWrite(kled, i);
    analogWrite(yled, 255);
    analogWrite(mled, 255);

     delay(50);
  
  }
    for(int i=0;i<=255;i++)
  {
    analogWrite(kled, 255);
    analogWrite(yled, i);
    analogWrite(mled, 255);

     delay(50);
  
  }
    for(int i=0;i<=255;i++)
  {
    analogWrite(kled, 255);
    analogWrite(yled, 255);
    analogWrite(mled, i);

     delay(50);
  
  }
 

}
