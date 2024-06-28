# Adafruit.IO:

## Feeds e Dashboards:
- Feeds
  - Armazenamento de Dados: Os feeds em Adafruit IO são fundamentais para armazenar e organizar dados enviados pelos seus dispositivos IoT.
  - Fluxo de Dados: Facilitam o fluxo de informações entre sensores, atuadores e a plataforma, permitindo a captura e o registro de dados em tempo real.
  - Integração: Permitem a integração com diversos serviços e dispositivos, centralizando dados para fácil acesso e análise.

- Dashboards
  - Visualização de Dados: Dashboards fornecem uma interface visual para monitorar os dados armazenados nos feeds. Isso ajuda a identificar tendências e anomalias rapidamente.
  - Interatividade: Permitem a criação de controles interativos, como botões e sliders, para enviar comandos aos dispositivos, melhorando a interação com o sistema IoT.
  - Personalização: Dashboards podem ser customizados para atender às necessidades específicas de um projeto, proporcionando uma visão clara e organizada dos dados mais relevantes.

## Criar feeds:
1 - Acesse sua conta Adafruit.io
- Visite Adafruit.io.
- Faça login com seu email e senha.
  
2- Navegue até a Dashboard
- No painel de controle, clique em "Feeds" no menu lateral esquerdo.
- Clique em "Actions" e selecione "Create a New Feed".
  
3- Criação do Feed
- Na janela de criação do feed, insira um nome para seu feed (por exemplo, "Temperatura").
- Adicione uma descrição opcional para ajudar a identificar o propósito do feed.
- Clique em "Create" para finalizar.


### Exemplo feeds criados no projeto:

<img src="/Adafruit/feeds.png"/>

### Valores armazenados nos feeds a partir da leitura dos sensores:

- Grafico:

<img src="/Adafruit/feedsGraphic.png"/>

- Dados:

<img src="/Adafruit/feedsResults.png"/>

## Criar Dashboards:
1- Acesse sua conta Adafruit.io
- Visite Adafruit.io.
- Faça login com seu email e senha.

2- Navegue até Dashboards
- No painel de controle, clique em "Dashboards" no menu lateral esquerdo.
- Clique em "Actions" e selecione "Create a New Dashboard".

3- Configuração do Dashboard
- Na janela de criação do dashboard, insira um nome para seu dashboard (por exemplo, "Monitoramento de Sensores").
- Adicione uma descrição opcional para detalhar o propósito do dashboard.
- Clique em "Create" para finalizar.

4- Adicionar Blocos ao Dashboard
- Após criar o dashboard, clique no nome do dashboard para abri-lo.
- Clique em "+" para adicionar um novo bloco.
- Selecione o tipo de bloco (como gráficos, indicadores, ou controles) que deseja adicionar.
- Configure o bloco selecionando o feed apropriado e ajustando as opções de exibição.
- Clique em "Create Block" para adicionar o bloco ao seu dashboard.

### Exemplo Dashboards criados no projeto:

<img src="/Adafruit/dashboards.png"/>

### Blocos de Controle na Dashboard:

<img src="/Adafruit/dashboardControle.png"/>

## Código para Integração com a plataforma:


   
### Codigo de  Configuração:
- Certifique-se de estar utilizando as bibliotecas;
- Preencha corretamente seus dados de rede;
- Crie uma variavel tipo 'Adafruit_MQTT_Publish' com o nome de sua feed e altere o "/feeds/NomeDeSuaFeed";
- Crie uma variavel tipo 'Adafruit_MQTT_Subscribe' com o nome de sua feed e altere o "/feeds/NomeDeSuaFeed";

```C++
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "...your SSID..."
#define WLAN_PASS       "...your password..."

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "...your AIO username (see https://accounts.adafruit.com)..."
#define AIO_KEY         "...your AIO key..."

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiClientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/photocell");

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/onoff");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();
```



### Código de inicialização em setup():
- Dentro da função setup(), copie o código que configurará o ESP32 com as configurações de rede;

```C++
void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&onoffbutton);

}
```

### Código de conexão MQQT - função MQTT_connect():
- Copie a função MQTT_connect() que conectará o ESP32 ao adafruit;

```C++
void MQTT_connect() {

  int8_t ret;
  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {  // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1)
        ;
    }
  }
  Serial.println("MQTT Connected!");
}
```

### Código de execução em loop():
- Copie o código abaixo que manterá o ESP32 e o adafruit conectados e enviará os dados coletados pelos sensores ao adafruit;
- Certifique-se de colocar o nome de sua feed corretamente observadno o exemplo abaixo;

```C++
void loop() {
 // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &onoffbutton) {
      Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton.lastread);
    }
  }

  // Now we can publish stuff!
  Serial.print(F("\nSending photocell val "));
  Serial.print(x);
  Serial.print("...");
  if (! photocell.publish(x++)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }

  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  /*
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
  */
}

```
