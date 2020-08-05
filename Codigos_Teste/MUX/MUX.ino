#include "Type4067Mux.h"
Type4067Mux mux(8, DIGITAL, 9, 10, 11, 12);
int liga = 15;
void setup() {
Serial.begin(9600);
pinMode(liga, OUTPUT);

}

void loop() {
mux.write(HIGH, liga);
if(mux.read(liga) == HIGH)
Serial.println("LED LIGADO");
if(mux.read(liga) == LOW)
Serial.println("LED DESLIGADO");
delay(1000);
mux.write(LOW, liga);
if(mux.read(liga) == HIGH)
Serial.println("LED LIGADO");
if(mux.read(liga) == LOW)
Serial.println("LED DESLIGADO");
delay(1000);
}
