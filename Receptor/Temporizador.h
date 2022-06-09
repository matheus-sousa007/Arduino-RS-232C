namespace Temporizador {
  void configura(int boud_rate);
  void inicia();
  void para();
}


void Temporizador::configura(int baud_rate){
  int frequencia =  constrain(baud_rate,1,1500);

  // Define a interrupção do timer
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0; // Contador em 0

  OCR1A = ((16 * pow(10,6)) / (1024 * frequencia)) - 1;
  
  TCCR1B |= (1 << WGM12); // Liga o modo CTC (clear time on compare)
  TCCR1B &= 0xF8;         // Desliga o T1

  // Desativa interrupções
  TIMSK1 = 0;
  TIFR1 = 0;
}

void Temporizador::inicia() {  
  TCNT1 = 0; // Contador em 0
  TIFR1 = 0;

  TIMSK1 |= (1 << OCIE1A);             // Aciona comparação de interrupção no timer
  TCCR1B |= (1 << CS12) | (1 << CS10); // Coloca CS10 e CS12 em 1024 prescaler
}

void Temporizador::para() {
  TCCR1B &= 0xF8;
  TIMSK1 = 0;
}
