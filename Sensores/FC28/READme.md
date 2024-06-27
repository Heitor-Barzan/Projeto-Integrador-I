# FC28 - Sensor de Humidade do Solo:

## Descrição de Uso:
- O sensor FC28 é usado no sistema da horta automatizada para que sejam captados os dados da humidade do solo. Ele é posicionado no solo junto as plantas para que com base no resultado da humidade ele permita a ativação do atuador.
 
<img src="/Sensores/FC28/FC28_PinOut.png"  />

## Especificações e características:
- Tensão de operação: 3,5 a 5,5V DC;
- Corrente de operação: 15mA;
- Output Digital – 0V to 5V;
- Output Analog – 0V to 5V;
- LEDs de indicação de output e nivel de potencia;
- Tamanho da PCB: 3.2cm x 1.4cm;
- Design baseado no LM393;


## Datasheet:

[Datasheet FC28](/Sensores/)


## Pinagem
| Pino | Saida | Pino ESP8266 |
| ------------- | ------------- | ------------- |
| Analog Data  | 1 | ADC0 - A0 |
| Digital Data | 2 | N/C |
| GND  | 4 | GND  |
| VCC  | 3 | 33V  |

## Bibliotecas:

- Sem bibliotecas adicionais

## Codigo:

```C++
void setup(){
 Serial.begin(9600);
 pinMode(2, OUTPUT);
}
void loop(){
 //analog output
 if(analogRead(0)<300) Serial.println("Heavy Rain");
 else if(analogRead(0)<500) Serial.println("Moderate Rain");
 else Serial.println("No Rain");

// //digital output
// if(digitalRead(2) == HIGH) Serial.println("No Rain
// Detected");
// else Serial.println("Rain Detected");

 delay(250);
}

```
