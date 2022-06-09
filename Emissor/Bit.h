namespace Bit {
  short soma(char caractere);
  bool impar(char caractere);
  bool paridade(char caractere);
}


short Bit::soma(char caractere) {
  short soma = 0;
  
  for (short i = 0; i < 8; i++) {
    soma += bitRead(caractere, i);
  }

  return soma;
}

bool Bit::impar(char caractere) { // Checa se a paridade(ímpar) está correta
  return soma(caractere) % 2;
}

bool Bit::paridade(char caractere) { // Calcula o bit de paridade(ímpar)
  return (soma(caractere) + 1) % 2;
}
