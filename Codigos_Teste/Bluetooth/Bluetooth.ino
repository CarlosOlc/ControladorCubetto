#include <SoftwareSerial.h>

SoftwareSerial blu(11, 12); // TX, RX

String nome;
char c;

void setup() {
Serial.begin(9600);
blu.begin(9600);
}

void loop() {
while(blu.available() > 0){
c = blu.read();
nome+=c;
}
if(nome == "Carlos"){
Serial.println(nome);
nome="";
}
if(nome == "1010"){
Serial.println(nome);
nome="";
blu.println("0101");
}

if(Serial.available()){
blu.write(Serial.read());
}

}
