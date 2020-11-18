#include "Type4067Mux.h"
#include <SoftwareSerial.h>

SoftwareSerial blu(11, 12); // TX, RX

// Pinos       sig          s0 s1 s2 s3
Type4067Mux mux1(A0, DIGITAL, 8, 9, 10, 11);
Type4067Mux mux2(A1, DIGITAL, 12, 13, 14, 15);
Type4067Mux mux3(A2, DIGITAL, 16, 17, 18, 19);
Type4067Mux mux4(A3, DIGITAL, 20, 21, 22, 23);


// Definição movimentação  //   Imas
char frente = '1';         //  0 0 1
char direita = '2';        //  0 1 0
char esquerda = '3';       //  0 1 1
char funcao = '4';         //  1 0 0

char erroFun = '9'; // Se tiver uma peça funcao sera adicionado 9 no char
char fimMov = ';';  //  ; será adicionado para identificar fim do char
char erroIden = '0'; // Se a peça nao for reconhecida tera 0

//Array onde sera salvo os movimentos
String movimentos = "";

//Botão de play
int play = 0;  // numero porta

// Setando pinos de cada led e sensor reed swith
// Linha 1 - Sensores
// Slot 1
int slot1_1 = 15;
int slot1_2 = 14;
int slot1_3 = 13;

// Slot 2
int slot2_1 = 12;
int slot2_2 = 11;
int slot2_3 = 10;

// Slot 3
int slot3_1 = 9;
int slot3_2 = 8;
int slot3_3 = 7;

// Slot 4
int slot4_1 = 6;
int slot4_2 = 5;
int slot4_3 = 4;

// LEDs
int led1 = 0;
int led2 = 1;
int led3 = 2;
int led4 = 3;

// Linha 2 - Sensores
// Slot 5
int slot5_1 = 15;
int slot5_2 = 14;
int slot5_3 = 13;

// Slot 6
int slot6_1 = 12;
int slot6_2 = 11;
int slot6_3 = 10;

// Slot 7
int slot7_1 = 9;
int slot7_2 = 8;
int slot7_3 = 7;

// Slot 8
int slot8_1 = 6;
int slot8_2 = 5;
int slot8_3 = 4;


// Linha 3 - Sensores
// Slot 9
int slot9_1 = 15;
int slot9_2 = 14;
int slot9_3 = 13;

// Slot 10
int slot10_1 = 12;
int slot10_2 = 11;
int slot10_3 = 10;

// Slot 11
int slot11_1 = 9;
int slot11_2 = 8;
int slot11_3 = 7;

// Slot 12
int slot12_1 = 6;
int slot12_2 = 5;
int slot12_3 = 4;

// Linha 4 - Sensores
// Slot 13
int slot13_1 = 15;
int slot13_2 = 14;
int slot13_3 = 13;

// Slot 14
int slot14_1 = 12;
int slot14_2 = 11;
int slot14_3 = 10;

// Slot 15
int slot15_1 = 9;
int slot15_2 = 8;
int slot15_3 = 7;

// Slot 16
int slot16_1 = 6;
int slot16_2 = 5;
int slot16_3 = 4;




void setup() {
  Serial.begin(9600);
  blu.begin(9600);
  pinMode(play, INPUT);
  
}



char QualMovimento(bool slot1, bool slot2, bool slot3) {
  if (slot1 = LOW) { if (slot2 = LOW) { if (slot3 = HIGH) {
        return frente; ///     FRENTE 1
      }}}

  if (slot1 = LOW) { if (slot2 = HIGH) { if (slot3 = LOW) {
        return direita; ///     DIREITA 2
      }}}

  if (slot1 = LOW) { if (slot2 = HIGH) { if (slot3 = HIGH) {
        return esquerda; ///     ESQUERDA 3
      }}}

  if (slot1 = HIGH) { if (slot2 = LOW) { if (slot3 = LOW) {
        return funcao; ///     FUNCAO 4
      }}}
  return erroIden; // Erro na identificação da peça
}

void SalvaMovimento(char jogada) {
  movimentos += jogada;
}

void MovFuncao() {
  char jogada;
  //Verifica se tem peça nos slot de funçao
  if (mux1.read(slot13_1) or mux1.read(slot13_2) or mux1.read(slot13_3)) {
    jogada = QualMovimento(mux4.read(slot13_1), mux4.read(slot13_2), mux4.read(slot13_3));
    if (jogada != funcao) {
      SalvaMovimento(jogada); // Salva a ação correspondente que esta na funcao
    } else {
      SalvaMovimento(erroFun);
    }
    if (mux1.read(slot14_1) or mux1.read(slot14_2) or mux1.read(slot14_3)) {
      jogada = QualMovimento(mux4.read(slot14_1), mux4.read(slot14_2), mux4.read(slot14_3));
      if (jogada != funcao) {
        SalvaMovimento(jogada); // Salva a ação correspondente que esta na funcao
      }
      else {
        SalvaMovimento(erroFun);
      }
      if (mux1.read(slot15_1) or mux1.read(slot15_2) or mux1.read(slot15_3)) {
        jogada = QualMovimento(mux4.read(slot15_1), mux4.read(slot15_2), mux4.read(slot15_3));
        if (jogada != funcao) {
          SalvaMovimento(jogada); // Salva a ação correspondente que esta na funcao
        }
        else {
          SalvaMovimento(erroFun);
        }
        if (mux1.read(slot16_1) or mux1.read(slot16_2) or mux1.read(slot16_3)) {
          jogada = QualMovimento(mux4.read(slot16_1), mux4.read(slot16_2), mux4.read(slot16_3));
          if (jogada != funcao) {
            SalvaMovimento(jogada); // Salva a ação correspondente que esta na funcao
          }
          else {
            SalvaMovimento(erroFun);
          }
        }
      }
    }
  }
}



bool VerificaF() {           //  -1 por causa do ; no final
  for (int i = 0; i < movimentos.length() - 1; i++) {
    if (movimentos[i] == erroFun) {
      return false;
    }
  }
  return true;
}

int Movimentos() {
  char jogada;
  // Verificar se tem alguma peça no slot 1
  if (mux1.read(slot1_1) or mux1.read(slot1_2) or mux1.read(slot1_3)) {
    jogada = QualMovimento(mux1.read(slot1_1), mux1.read(slot1_2), mux1.read(slot1_3)); // Verifica peça correspondente
    if (jogada != funcao) {   // Se nao for uma peça de função
      SalvaMovimento(jogada); // Salva movimento do array
    } else {
      MovFuncao();        // Se a peça for iqual a funcao
    }
    // Verificar se tem alguma peça no slot 2
    if (mux1.read(slot2_1) or mux1.read(slot2_2) or mux1.read(slot2_3)) {
      jogada = QualMovimento(mux1.read(slot2_1), mux1.read(slot2_2), mux1.read(slot2_3)); // Verifica peça correspondente
      if (jogada != funcao) {   // Se nao for uma peça de função
        SalvaMovimento(jogada); // Salva movimento do array
      } else {
        MovFuncao();        // Se a peça for iqual a funcao
      }
      // Verificar se tem alguma peça no slot 3
      if (mux1.read(slot3_1) or mux1.read(slot3_2) or mux1.read(slot3_3)) {
        jogada = QualMovimento(mux1.read(slot3_1), mux1.read(slot3_2), mux1.read(slot3_3)); // Verifica peça correspondente
        if (jogada != funcao) {   // Se nao for uma peça de função
          SalvaMovimento(jogada); // Salva movimento do array
        } else {
          MovFuncao();        // Se a peça for iqual a funcao
        }
        // Verificar se tem alguma peça no slot 4
        if (mux1.read(slot4_1) or mux1.read(slot4_2) or mux1.read(slot4_3)) {
          jogada = QualMovimento(mux1.read(slot4_1), mux1.read(slot4_2), mux1.read(slot4_3)); // Verifica peça correspondente
          if (jogada != funcao) {   // Se nao for uma peça de função
            SalvaMovimento(jogada); // Salva movimento do array
          } else {
            MovFuncao();        // Se a peça for iqual a funcao
          }
          // Verificar se tem alguma peça no slot 8
          if (mux1.read(slot8_1) or mux1.read(slot8_2) or mux1.read(slot8_3)) {
            jogada = QualMovimento(mux2.read(slot8_3), mux2.read(slot8_2), mux2.read(slot8_1)); // Verifica peça correspondente
            if (jogada != funcao) {   // Se nao for uma peça de função
              SalvaMovimento(jogada); // Salva movimento do array
            } else {
              MovFuncao();        // Se a peça for iqual a funcao
            }
            // Verificar se tem alguma peça no slot 7
            if (mux1.read(slot7_1) or mux1.read(slot7_2) or mux1.read(slot7_3)) {
              jogada = QualMovimento(mux2.read(slot7_3), mux2.read(slot7_2), mux2.read(slot7_1)); // Verifica peça correspondente
              if (jogada != funcao) {   // Se nao for uma peça de função
                SalvaMovimento(jogada); // Salva movimento do array
              } else {
                MovFuncao();        // Se a peça for iqual a funcao
              }
              // Verificar se tem alguma peça no slot 6
              if (mux1.read(slot6_1) or mux1.read(slot6_2) or mux1.read(slot6_3)) {
                jogada = QualMovimento(mux2.read(slot6_3), mux2.read(slot6_2), mux2.read(slot6_1)); // Verifica peça correspondente
                if (jogada != funcao) {   // Se nao for uma peça de função
                  SalvaMovimento(jogada); // Salva movimento do array
                } else {
                  MovFuncao();        // Se a peça for iqual a funcao
                }
                // Verificar se tem alguma peça no slot 5
                if (mux1.read(slot5_1) or mux1.read(slot5_2) or mux1.read(slot5_3)) {
                  jogada = QualMovimento(mux2.read(slot5_3), mux2.read(slot5_2), mux2.read(slot5_1)); // Verifica peça correspondente
                  if (jogada != funcao) {   // Se nao for uma peça de função
                    SalvaMovimento(jogada); // Salva movimento do array
                  } else {
                    MovFuncao();        // Se a peça for iqual a funcao
                  }
                  // Verificar se tem alguma peça no slot 9
                  if (mux1.read(slot9_1) or mux1.read(slot9_2) or mux1.read(slot9_3)) {
                    jogada = QualMovimento(mux3.read(slot9_1), mux3.read(slot9_2), mux3.read(slot9_3)); // Verifica peça correspondente
                    if (jogada != funcao) {   // Se nao for uma peça de função
                      SalvaMovimento(jogada); // Salva movimento do array
                    } else {
                      MovFuncao();        // Se a peça for iqual a funcao
                    }
                    // Verificar se tem alguma peça no slot 10
                    if (mux1.read(slot10_1) or mux1.read(slot10_2) or mux1.read(slot10_3)) {
                      jogada = QualMovimento(mux3.read(slot10_1), mux3.read(slot10_2), mux3.read(slot10_3)); // Verifica peça correspondente
                      if (jogada != funcao) {   // Se nao for uma peça de função
                        SalvaMovimento(jogada); // Salva movimento do array
                      } else {
                        MovFuncao();        // Se a peça for iqual a funcao
                      }
                      // Verificar se tem alguma peça no slot 11
                      if (mux1.read(slot11_1) or mux1.read(slot11_2) or mux1.read(slot11_3)) {
                        jogada = QualMovimento(mux3.read(slot11_1), mux3.read(slot11_2), mux3.read(slot11_3)); // Verifica peça correspondente
                        if (jogada != funcao) {   // Se nao for uma peça de função
                          SalvaMovimento(jogada); // Salva movimento do array
                        } else {
                          MovFuncao();        // Se a peça for iqual a funcao
                        }
                        // Verificar se tem alguma peça no slot 12
                        if (mux1.read(slot12_1) or mux1.read(slot12_2) or mux1.read(slot12_3)) {
                          jogada = QualMovimento(mux3.read(slot12_1), mux3.read(slot12_2), mux3.read(slot12_3)); // Verifica peça correspondente
                          if (jogada != funcao) {   // Se nao for uma peça de função
                            SalvaMovimento(jogada); // Salva movimento do array
                          } else {
                            MovFuncao();        // Se a peça for iqual a funcao
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  movimentos += fimMov;
}


void loop() {
    if (digitalRead(play) == HIGH) {  // Botao de iniciar
    Movimentos();   // Verifica se tem peça, qual peça é e se tem função
    if (VerificaF() == true) {    
      blu.println(movimentos); // envia os movimentos para o robo
      }
      else {
        // ERROR Função dentro de Função
        Serial.println("Peça Função em posição invalida");
      }
    }

  }
