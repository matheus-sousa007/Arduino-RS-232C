#include "Bit.h"
#include "Input.h"
#include "Temporizador.h"


// Pinos
#define RX  13
#define RTS 12
#define CTS 11

// Baud
#define BAUD_RATE 1
#define HALF_BAUD 1000 / (2 * BAUD_RATE)


// Variáveis globais
volatile char letra;
volatile short contador;


void setup() {
  noInterrupts();
  Serial.begin(9600);
 
  // Inicializa os pinos
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RX,  INPUT);
  pinMode(RTS, INPUT);
  pinMode(CTS, OUTPUT);

  digitalWrite(CTS, LOW);
  
  Temporizador::configura(BAUD_RATE);
  interrupts();

  Serial.println("Receptor iniciado!");
}

void loop() {
  // Espera o emissor sinalizar envio e responde
  while (digitalRead(RTS) == LOW);
  digitalWrite(CTS, HIGH);

  letra = 0;
  contador = 0;

  delay(HALF_BAUD);
  Temporizador::inicia();

  // Recebe a letra bit por bit
  while (digitalRead(RTS) == HIGH);
  Temporizador::para();

  if (contador == 8 && Bit::impar(letra)) Serial.print(Input::mascara(letra));
  else                                    Serial.print("<Erro>");

  digitalWrite(CTS, LOW);
}

ISR(TIMER1_COMPA_vect){
  if (contador == 8) return; // Todos os bits já foram lidos
  contador++;
 
  letra <<= 1;
  letra |= digitalRead(RX);
}
