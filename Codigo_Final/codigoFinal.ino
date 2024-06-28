#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "DHT.h"

#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define FC28PIN 0

#define FC37PIN 16

#define RELEPIN 4

#define HUMVAL 30
#define RAINVAL 1
#define TEMPVAL 30
#define SENSOR_MIN_VALUE 0
#define SENSOR_MAX_VALUE 1023

#define WLAN_SSID "your_ssid"
#define WLAN_PASS "your_pass"

#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883
#define AIO_USERNAME "your_user"
#define AIO_KEY "your_key"

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish dht11_Temp = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "your_feed_path");
Adafruit_MQTT_Publish dht11_Hum = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "your_feed_path");
Adafruit_MQTT_Publish fc28_Hum = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "your_feed_path");
Adafruit_MQTT_Publish fc37_Rain = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "your_feed_path");

Adafruit_MQTT_Subscribe setSoilHumidity = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "your_feed_path");
Adafruit_MQTT_Subscribe setTemperature = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "your_feed_path");
Adafruit_MQTT_Subscribe manualActuator = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "your_feed_path");

float temperatureParam;
float pumpActivateParam;

void MQTT_connect();
void data_Publish(float Air_Humity_Dt, float Temperature_Dt, float Soil_Humidity_Dt, float Rain_Dt);
void pump_Actuator(float Soil_Humidity_Dt, float rainSensor_Dt, float temperature_Dt);
void manualPump_Actuator();
void fetch_data();

void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.begin(WLAN_SSID, WLAN_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  mqtt.subscribe(&setSoilHumidity);
  mqtt.subscribe(&setTemperature);
  mqtt.subscribe(&manualActuator);
  dht.begin();

  pinMode(DHTPIN, INPUT);
  pinMode(FC28PIN, INPUT);
  pinMode(FC37PIN, INPUT);
  pinMode(RELEPIN, OUTPUT);
}

void loop() {
  MQTT_connect();

  fetch_data();

  float dht11AirHumity = dht.readHumidity();
  float dht11Temperature = dht.readTemperature();
  float fc28SoilHumidity = analogRead(FC28PIN);
  float fc37Rain = digitalRead(FC37PIN);

  int fc28SoilHumidityPercent = map(fc28SoilHumidity, 1023, 0, 0, 100);

  data_Publish(dht11AirHumity, dht11Temperature, fc28SoilHumidityPercent, fc37Rain);
  pump_Actuator(fc28SoilHumidityPercent, fc37Rain, dht11Temperature);
}

void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) {
    return;
  }

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {
    mqtt.disconnect();
    delay(5000);
    retries--;
    if (retries == 0) {
      while (1);
    }
  }
}

void data_Publish(float Air_Humity_Dt, float Temperature_Dt, float Soil_Humidity_Dt, float Rain_Dt) {
  delay(3000);
  dht11_Hum.publish(Air_Humity_Dt);
  delay(3000);
  dht11_Temp.publish(Temperature_Dt);
  delay(3000);
  fc28_Hum.publish(Soil_Humidity_Dt);
  delay(3000);
  fc37_Rain.publish(Rain_Dt);
  return;
}

void pump_Actuator(float Soil_Humidity_Dt, float rainSensor_Dt, float temperature_Dt) {
  if (rainSensor_Dt != RAINVAL) {
    return;
  }

  if (pumpActivateParam == 0) {
    pumpActivateParam = HUMVAL;
  }

  if (temperatureParam == 0){
    temperatureParam = TEMPVAL;
  }

  if (temperature_Dt >= temperatureParam) {
    if (Soil_Humidity_Dt <= pumpActivateParam + 10) {
      digitalWrite(RELEPIN, HIGH);
      delay(3000);
      digitalWrite(RELEPIN, LOW);
    }
  } else {
    if (Soil_Humidity_Dt <= pumpActivateParam) {
      digitalWrite(RELEPIN, HIGH);
      delay(3000);
      digitalWrite(RELEPIN, LOW);
    }
  }

  return;
}

void manualPump_Actuator() {
  digitalWrite(RELEPIN, HIGH);
  delay(3000);
  digitalWrite(RELEPIN, LOW);

  return;
};

void fetch_data() {
  Adafruit_MQTT_Subscribe *subscription;
  pumpActivateParam = atoi((char *)setSoilHumidity.lastread);

  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &setSoilHumidity) {
      pumpActivateParam = atoi((char *)setSoilHumidity.lastread);
    }

    if (subscription == &setTemperature) {
      temperatureParam = atoi((char *)setTemperature.lastread);
    }

    if (subscription == &manualActuator) {
      int value = atoi((char *)manualActuator.lastread);
      if (value) {
        manualPump_Actuator();
      }
    }
  }
  return;
}