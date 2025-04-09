
#include "TM1637.h"

const int CLK = 6;
const int DIO = 7;
TM1637 tm1637(CLK, DIO);

void setup() {
    tm1637.init();
}
void loop() {
   
    char* dogum = "30-03-2009";
    tm1637.displayStr(dogum);  
    delay(2000);
}
