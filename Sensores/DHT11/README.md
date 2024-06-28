# DHT11 - Sensor de Humidade do Ar e Temperatura Atmosferica:

## Descrição de Uso:
- O sensor DHT11 é usado no sistema da horta automatizada para que sejam captados os dados da temperatura e humidade atmosferica. Ele é posicionado no lado de fora proximo as plantas para que possa atuar de maneira eficiente.
 
<img src="/Sensores/DHT11/DHT11_PIN.png" width="400" height="400" />

## Especificações e características:
- Tensão de operação: 3,5 a 5,5VDC;
- Corrente de operação: 0,3mA;
- Resolução: 16 bits;
- Faixa de medição (umidade): 20 a 90%;
- Faixa de medição (temperatura): 0º a 50º celsius;
- Precisão (umidade): ±5%;
- Precisão (temperatura): ±2º celsius;
- Tempo de resposta: 2s.


## Datasheet:

[Datasheet DHT11](/Sensores/DHT11/DHT11.PDF)


## Pinagem
| Pino | Saida | Pino ESP8266 |
| ------------- | ------------- | ------------- |
| VCC  | 1 | 33V  |
| DATA  | 2 | GPIO5 - D1  |
| N/C  | 3 | NC |
| GND  | 4 | GND  |

## Bibliotecas:

- DHT sensor library

## Codigo:

```C++
#include <DHT.h>
#define DHT11PIN 4

dht11 DHT11;

void  setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println();

  int chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature  (C): ");
  Serial.println((float)DHT11.temperature, 2);

  delay(2000);

}
```
## Montagem

<img src="/Sensores/DHT11/Montagem DHT11.png" width="400" height="400" />
