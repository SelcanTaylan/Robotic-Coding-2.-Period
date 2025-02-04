/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  delay(1);        // delay in between reads for stability
  if(sensorValue>=0 && sensorValue<=300){
       digitalWrite(3, 1);
       digitalWrite(4, 0);
       digitalWrite(5, 0);
       delay(300);
    }
   else if(sensorValue>=301 && sensorValue<=700){
       digitalWrite(3, 1);
       digitalWrite(4, 1);
        digitalWrite(5, 0);
       delay(300);
    } 
    else if(sensorValue>=701 && sensorValue<=1023){
       digitalWrite(3, 1);
       digitalWrite(4, 1);
       digitalWrite(5, 1);
       delay(300);
    } 

   
    
  
}
