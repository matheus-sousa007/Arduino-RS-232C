# Arduino Transmission Data Protocol

### Disciplina: SCC0142 - Redes de Computadores

## Autores
 - [Gustavo Henrique Brunelli - 11801053](https://github.com/GBrunelli)
 - [Matheus Ventura de Sousa - 11345541](https://github.com/matheus-sousa007/)
 - [Pedro Lucas de Moliner de Castro - 11795784](https://github.com/pedrolmcastro)

## Ferramentas utilizadas no projeto

Para o desenvolvimento do projeto, foi utilizada a linguagem **C++ 11** dentro das ferramentas de desenvolvimento Arduino IDE e Tinkercad Circuits para a plataforma Arduino UNO R3.

## Compilação e Execução

Caso possua 2 arduinos para testar, basta apenas baixar o repositório com o comando abaixo e abrir os arquivos `emissor.ino` e `receptor.ino` dentro da IDE do Arduino.
```
git clone https://github.com/matheus-sousa007/Arduino-RS-232C.git
```

Para a configuração dos arduinos,serão necessários 3 jumpers para conectar as portas I/O digitais 11, 12 e 13 de cada arduino. Com isso, basta apenas alimentá-lo com o cabo USB.

Após a abertura dos arquivos, basta apenas configurar as respectivas portas dos arduinos e carregar o sketch em `Sketch -> Carregar` em cada programa aberto.

Caso não possua os dois arduinos, poderá utilizar [este Tinkercad](https://www.tinkercad.com/things/2a1NkF46jcS?sharecode=aAZjLkvQorBfngIxJZ01mImUlqpqjhRwDdd5XMdHzJM). Para executar o projeto, basta apenas clicar em `Iniciar Simulação`.

## Descrição do Projeto

O projeto baseia-se em fazer dois arduinos se comunicarem usando um protocolo em comum. O protocolo utilizado foi o **RS-232C** com modificações ja que ele é usado na transmissão de caracteres na forma serial e assíncrona.

A modificação consiste em adicionar um timer tanto para o transmissor e o receptor para permitir um fluxo síncrono dos dados.

Para a transmissão do caractere, foi utilizado um bit de paridade para detectar possíveis erros de transmissão. O grupo adotou a paridade ímpar, assim, o bit de paridade estará ativo caso a soma de todos os bits ativos do caractere somarem um número par. Caso contrário, o bit de paridade permanecerá desativado.

### Comunicação entre os arduinos

Antes de iniciar a transmissão de dados, o emissor precisa ativar a RTS flag para sinalizar ao receptor que há dados a serem transmitidos.
Ao verificar que o RTS do emissor está ativo, o receptor ativará o CTS o mais rápido possível para sinalizar ao emissor que está pronto para receber os dados.

Quando os dois sinais são ativados, o timer começa a contar visto que a transmissão de dados se iniciará por meio do canal de dados. Ao terminar a transmissão, o emissor desativa a flag RTS para sinalizar que não há mais dados a serem enviados no momento. Assim, o receptor desativa o CTS para avisar que não está mais preparado para receber dados.

A comunicação entre os arduinos é feita seguindo o esquema abaixo.

![](./images/esquema.png)

## Conclusão

O grupo conseguiu executar o projeto sem grande dificuldade na implementação do protocolo proposto. Além disso, o grupo considera uma notável melhora entre o tempo de execução do Sketch no arduino físico e a o tempo de execução do Sketch no Tinkercad.

Ademais, o grupo considerou que o último caractere do input '\n' sempre será transmitido já que o receptor serve apenas como um terminal para apresentar as palavras enviadas pelo emissor. Isso pode ser visto no vídeo cujo link estará logo abaixo.


## Vídeo

O grupo possui um vídeo explicativo sobre o projeto o qual pode ser acessado por [este link](https://youtu.be/RlWI3TtgbQQ). 