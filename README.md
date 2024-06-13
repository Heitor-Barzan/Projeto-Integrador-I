# Sistema de Automatização para Horta Medicinal
 ##  Introdução

 Este projeto foi desenvolvido como proposta de trabalho para a matéria Projeto Integrador I na UFSC, o qual propõe um sistema de automatização para uma Horta Medicinal, visando reduzir o processo de cuidados tornando-os menos cansativos, e mais eficientes, tornando o processo de regagem automático, necessitando apenas de uma etapa de configuração por parte do usuário, o qual precisará apenas verificar o funcionamento do sistema.

##  Lista de Hardware 

Nesta sessão teremos a lista de materiais que serão utilizados durante o procedimento de montagem do projeto, teremos alguns sensores que são vitais para o funcionamento remoto da horta conectados à um ESP que enviará os dados recebidos para um banco de dados em uma nuvem.

### Materiais
- ESP8266: Microcontrolador que será utilizado como núcleo para o funcionamento dos sensores, como também para o envio de dados para o banco de dados.
- DHT11: Sensor utilizado para medir a temperatura e umidade do ar.
- 9SS19(FC28): Sensor utilizado para medir a umidade do solo.
- 9SS18(FC37): Sensor utilizado para detectar condições climáticas(chuva, neve).
- RS385 (12v): Bomba d'água que será utilizada para irrigação da horta.
- Cabo Micro USB: Cabo de conexão utilizado para alimentacao e transmissão de dados.
- 

## Esquema de Conexão

## Instalação
 - Para que o sistema funcione é preciso configurar seu ambiente
   - Requisitos de Software:
      - Arduino IDE: A Arduino IDE é uma plataforma de código aberto que facilita a escrita e upload de código para placas Arduino. Siga os passos abaixo para instalá-la.
      - Conta na plataforma IoT Adafruit.io: Adafruit.io é uma plataforma para monitoramento e controle de dispositivos IoT. Você precisará criar uma conta para utilizar suas funcionalidades.
   - Bibliotecas de Software:
      - DHT sensor library;
      - Adafruit Unified Sensor;
      - Adafruit SleepyDog Library;
      - Adafruit MQTT Library;
      - Adafruit FONA Library;
      - Adafruit BusIO;
     Estas bibliotecas são essenciais para o funcionamento do nosso projeto IoT. Vamos instalar todas elas na Arduino IDE.
   - Instalação dos Componentes:
      - Download e Instalação da Arduino IDE:
      - Acesse o site oficial da Arduino (https://www.arduino.cc/en/software).
      - Selecione o seu sistema operacional (Windows, Mac OS, Linux) e clique no botão correspondente para fazer o download.
      - Após o download, abra o instalador e siga as instruções na tela para concluir a instalação.
  
 
 
 
