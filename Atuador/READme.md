# Relé e Mini Bomba de Agua:

## Descrição de Uso:
A mini bomba de agua será usada para a irrigacão, controlada pelo modulo rele. A mini bomba de agua tem a capacidade de elevar a agua ate 3 metros e aspirar ate 2 metros de profundidade. A quantidade de agua impulsionada e de 80 a 120 litros por hora. O modulo rele funciona 

 
<img src="/Atuador/MiniBomba.png" height="400" width="400"/>
<img src="/Atuador/ModuloRele.png" height="400" width="460"/>

## Especificações e características da mini bomba de água:
- Tensão de operação: 9 V;
- Corrente Sem Carga:	600 mA;
- Corrente Com Carga:	2 A;
- Vazão:	de até 2L/min;
- Elevação Máxima da Coluna:	3 metros;
- Medidas - Tubos de Entrada / Saída;
 - Diâmetro Externo: 7,5 mm;
 - Diâmetro Interno: 5,0 mm;

## Especificações e características do módulo relé:
- Modelo: JQC3F-C;
- Pinos: SIG/VCC/GND;
- Carga nominal: 10A 250VAC/ 10A 125VAC/ 10A 30VDC/ 10A 28VDC;
- Tensão de operação: 5VDC (VCC);
- Tensão de sinal: TTL 5VCD ;
- Saídas: Contato reversível NA (normal aberto), NF (normal fechado), C (comum);
- Corrente por canal: até 10A;
- Dimensões totais (CxLxA): 34x26x17mm;
- Peso com embalagem: 13g.

## Datasheets:

[Datasheet Mini Bomba](/Atuador/)

[Datasheet Módulo Relé](/Atuador/)

## Pinagem do Modulo Relé
| Pino | Saida | Pino ESP8266 |
| ------------- | ------------- | ------------- |
| DATA  | 1 | GPIO4 - D2  |
| VCC  | 2 | 33V  |
| GND  | 3 | GND  |

## Bibliotecas:

- Sem bibliotecas adicionais

## Codigo:

```C++
int PinoAnalogico = A0; // Define o pino 13 como Pino Analógico do sensor
int PinoDigital = 4; // Define pino D14 como Pino Digital do Sensor 

int Rele = 5; // Pino Digital D1 como Relé

int EstadoSensor = 0;
int UltimoEstSensor = 0;

int  ValAnalogIn; // Valor analógico no código

void setup() {

Serial.begin(9600); 
pinMode(Rele, OUTPUT); // Declara o Rele como Saída Digital 

pinMode(PinoDigital, INPUT);
}
void loop() {


ValAnalogIn = analogRead(PinoAnalogico);
Serial.print (ValAnalogIn);
int Porcento = map(ValAnalogIn, 1023, 0, 0, 100); // Traforma o valor analógico em porcentagem

Serial.print("Umidade: "); // Imprime o símbolo no valor
Serial.print(Porcento); // Imprime o valor em Porcentagem no monitor Serial
Serial.println("%");

if (Porcento <= 76) { // Se a porcentagem for menor ou igual à 76%.
 
Serial.println("Irrigando Planta"); // Imprime no monitor serial
digitalWrite(Rele, LOW); // Aciona Relé

}else { // Caso contrario 
 
Serial.println("Planta Irrigada"); // Imprime a no monitor serial
digitalWrite(Rele, HIGH); // Desliga Relé

delay (5000);
}
}
```
