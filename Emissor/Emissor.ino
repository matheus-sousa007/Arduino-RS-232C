#include "Bit.h"
#include "Input.h"
#include "Temporizador.h"


// Pinos
#define TX  13
#define RTS 12
#define CTS 11

// Baud
#define BAUD_RATE 1
#define HALF_BAUD 1000 / (2 * BAUD_RATE)


// Variáveis globais
volatile char letra;
volatile short indice;


void envia(bool enviado) {
  Serial.println(enviado);
  digitalWrite(TX, enviado);
}


void setup(){
  noInterrupts();
  Serial.begin(9600);
 
  // Inicializa os pinos
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TX,  OUTPUT);
  pinMode(RTS, OUTPUT);
  pinMode(CTS, INPUT);

  digitalWrite(TX,  LOW);
  digitalWrite(RTS, LOW);
  
  Temporizador::configura(BAUD_RATE);
  interrupts();

  Serial.println("Emissor iniciado!");
}

void loop() {
  String mensagem = Input::recebe();
  while (digitalRead(CTS) == HIGH); // Espera o receptor ficar pronto

  for (unsigned i = 0; i < mensagem.length(); i++) {
    // Sinaliza o início do envio e espera
    digitalWrite(RTS, HIGH);
    while (digitalRead(CTS) == LOW);

    letra = Input::mascara(mensagem[i]);
    indice = 7;

    // Envia a letra bit por bit
    Temporizador::inicia();
    while (digitalRead(RTS) == HIGH);

    Temporizador::para();
    Serial.println("");
  }
}

ISR(TIMER1_COMPA_vect){
  if (indice == -1) { // Finaliza o envio
    digitalWrite(RTS, LOW);
    return;
  }

  if (indice == 7) { // Envia o bit de paridade primeiro
    envia(Bit::paridade(letra));
    indice--;
    return;
  }

  envia(bitRead(letra, indice--));
}
