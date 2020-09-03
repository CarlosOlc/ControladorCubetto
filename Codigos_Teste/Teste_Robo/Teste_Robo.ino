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

int fun;
String comandos;

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

  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;
  if (mfrc522.PICC_IsNewCardPresent()) {
    if (mfrc522.PICC_ReadCardSerial()) {
      Serial.println(F("**Card Detected:**"));
      //-------------------------------------------

      //  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card

      //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

      //-------------------------------------------

      Serial.print(F("Name: "));

      byte buffer1[18];

      block = 4;
      len = 18;

      //------------------------------------------- GET FIRST NAME
      status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
      if (status != MFRC522::STATUS_OK) {
        Serial.print(F("Authentication failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }

      status = mfrc522.MIFARE_Read(block, buffer1, &len);
      if (status != MFRC522::STATUS_OK) {
        Serial.print(F("Reading failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }

      //PRINT FIRST NAME
      for (uint8_t i = 0; i < 16; i++)
      {
        if (buffer1[i] != 32)
        {
          Serial.write(buffer1[i]);
        }
      }
      Serial.print(" ");

      //---------------------------------------- GET LAST NAME

      byte buffer2[18];
      block = 1;

      status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid)); //line 834
      if (status != MFRC522::STATUS_OK) {
        Serial.print(F("Authentication failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }

      status = mfrc522.MIFARE_Read(block, buffer2, &len);
      if (status != MFRC522::STATUS_OK) {
        Serial.print(F("Reading failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }

      //PRINT LAST NAME
      for (uint8_t i = 0; i < 16; i++) {
        Serial.write(buffer2[i] );
      }


      //----------------------------------------

      Serial.println(F("\n**End Reading**\n"));

      delay(1000); //change value if you want to read cards faster

      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1();
    }
  }

  while (blu.available()) {
    comandos = "";
    fun = -1;
    while (fun != Start) {
      fun = blu.read();
      salvaCom();
      //      Serial.println(fun);
    }
    Serial.println(comandos);
  }

int incomandos = 0;
int i = 0;
String a;
while(incomandos != Start){
  Serial.println(comandos);
  a = comandos[i];
  incomandos = a.toInt();
  if (incomandos != 0)
  Serial.println(a);
//  Serial.println(incomandos);
  i++;
}

  if (fun == Frente) {
    moverFrente();
    Serial.println("Frente");
    fun = 0;
    delay(1000);
  }

  if (fun == Esquerda) {
    moverEsquerda();
    Serial.println("Esquerda");
    fun = 0;
    delay(1000);
  }

  if (fun == Direita) {
    moverDireita();
    Serial.println("Direita");
    fun = 0;
    delay(1000);
  }

  if (fun == Re) {
    moverRe();
    Serial.println("Re");
    fun = 0;
    delay(1000);
  }

  if (fun == 0) {
    naoMove();
  }

  //  if (Serial.available()) {
  //    blu.write(Serial.read());
  //  }


}
void salvaCom() {
  if (fun > 0)
    comandos += fun;
}

void moverFrente() {
  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);

}
void moverRe() {
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, speed);
  analogWrite(BIB, 0);
}
void moverDireita() {
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);

}
void moverEsquerda() {

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
