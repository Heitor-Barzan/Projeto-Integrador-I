# FC37 - Sensor de Chuva:

## Descrição de Uso:
- O sensor FC37 é usado no sistema da horta automatizada para que sejam captados os dados relativos a prenseça de chuva. Ele é posicionado no exterior do prototipo para que com base na leitura dos dados ele permita a ativação do atuador.
 
<img src="/Sensores/FC37/FC37_PinOut.png"  />

## Especificações e características:
- Tensão de operação: 3.3V–5V;
- Dois modos de output: analogico and digital;
- Medida da PCB: 30x15mm
- Medida do Sensor: 54x39mm
- Sensibilidade ajustavel por potenciomentro;

## Datasheet:

[Datasheet FC37](/Sensores/)


## Pinagem
| Pino | Saida | Pino ESP8266 |
| ------------- | ------------- | ------------- |
| Analog Data  | 1 | N/C |
| Digital Data | 2 | GPIO16 - D0 |
| GND  | 4 | GND  |
| VCC  | 3 | 33V  |

## Bibliotecas:

- Sem bibliotecas adicionais

## Codigo:

```C++
int rainPin = A0;
// you can adjust the threshold value
int thresholdValue = 500;

void setup(){
  pinMode(rainPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(rainPin);
  Serial.print(sensorValue);
  if(sensorValue < thresholdValue){
    Serial.println(" - It's wet");
  }
  else {
    Serial.println(" - It's dry");
  }
  delay(500);
}

```
## Montagem:

<img src="/Sensores/FC37/Montagem FC37.png"  />
