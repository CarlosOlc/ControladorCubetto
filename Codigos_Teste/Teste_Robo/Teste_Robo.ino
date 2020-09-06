#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>

constexpr uint8_t RST_PIN = 9;          // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = 10;         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

SoftwareSerial blu(6, 3); // TX, RX

//Constantes que definem os pinos da ponte H que sao conectadas no Arduino
const int AIA = 4;
const int AIB = 5;
const int BIA = 2;
const int BIB = 7;

// Valores para direção
int Frente = 50;
int Direita = 51;
int Esquerda = 49;
int Re = 52;
int Start = 53;

int i = 0;
int fun = 0;
int comandos[12];

byte speed = 255;

void setup() {
  Serial.begin(9600);
  blu.begin(9600);
  SPI.begin();  // Init SPI bus
  mfrc522.PCD_Init();

  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);

}

void loop() {
  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  MFRC522::StatusCode status;

  //  Se detectar rfid
  if (mfrc522.PICC_IsNewCardPresent()) {
    if (mfrc522.PICC_ReadCardSerial()) {
      Serial.println(F("**Card Detected:**"));

      naoMove();

      delay(3000); //change value if you want to read cards faster
      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1();
    }
  }

  while (blu.available()) {
    fun = 0;

    while (fun != Start) {
      fun = blu.read();
      if (fun > 0) {
        comandos[i] = fun;
        i++;
      }

    }
    i = 0;

  }

  if (fun == Start) {

    int incom;
    while (comandos[i] != Start) {
      incom = comandos[i];
      if (incom == Frente) {
        Serial.println("Frente");
        while (!mfrc522.PICC_IsNewCardPresent()) {
          
//            Serial.println(F("**Card Detected:**"));
            moverFrente();
          
        }
        blu.println(F("**Card Detected:**"));

        naoMove();
        delay(2000);

      }

      if (incom == Esquerda) {
        moverEsquerda();
        Serial.println("Esquerda");
        delay(500);
      }

      if (incom == Direita) {
        moverDireita();
        Serial.println("Direita");
        delay(500);
      }

      if (incom == Re) {
        moverRe();
        Serial.println("Re");
        delay(500);
      }


      i++;
    }
    i = 0;
    fun = 0;
  }




  if (fun == 0) {
    naoMove();
  }

  //  if (Serial.available()) {
  //    blu.write(Serial.read());
  //  }


}


void moverRe() {
  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);

}
void moverFrente() {
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, speed);
  analogWrite(BIB, 0);
}
void moverEsquerda() {
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);

}
void moverDireita() {

  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
  analogWrite(BIA, speed);
  analogWrite(BIB, 0);
}
void naoMove() {
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);
}
