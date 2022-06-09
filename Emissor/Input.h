namespace Input {
  String recebe();
  char mascara(char caractere);
}


String Input::recebe() {
  Serial.print("Digite a mensagem: ");
  String mensagem = "";

  while (mensagem == "") {
    mensagem = Serial.readString();
  }

  Serial.print(mensagem);
  return mensagem;
}

char Input::mascara(char caractere) { // Torna o bit mais sigificativo 0
  return caractere & 127;
}
