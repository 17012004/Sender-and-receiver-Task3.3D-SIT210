#include <ArduinoMqttClient.h>
#if defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_AVR_UNO_WIFI_REV2)
#include <WiFiNINA.h>
#elif defined(ARDUINO_SAMD_MKR1000)
#include <WiFi101.h>
#elif defined(ARDUINO_ARCH_ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#endif

// #include "arduino_secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "Veekay";    // your network SSID (name)
char pass[] = "12345678";    // your network password (use for WPA, or use as key for WEP)

int light = 2;


WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "mqtt-dashboard.com";
int        port     = 1883;
const char topic[]  = "Vansh's wave/pat";
bool iswave = true;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  pinMode(light, OUTPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // attempt to connect to WiFi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();


  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  Serial.print("Subscribing to topic: ");
  Serial.println(topic);
  Serial.println();

  // subscribe to a topic
  mqttClient.subscribe(topic);


  Serial.print("Waiting for messages on topic: ");
  Serial.println(topic);
  Serial.println();
}

void loop() {
  int messageSize = mqttClient.parseMessage();
  if (messageSize) {
    // we received a message, print out the topic and contents
    Serial.print("Received a message with topic '");
    Serial.print(mqttClient.messageTopic());
    Serial.print("', length ");
    Serial.print(messageSize);
    Serial.println(" bytes:");

    // use the Stream interface to print the contents
    while (mqttClient.available()) {
      Serial.print((char)mqttClient.read());
    }
    if(iswave = true) // for continous blinking
    {
    Serial.println();
    digitalWrite(light, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(700);                       // wait for a second
    digitalWrite(light, LOW);    // turn the LED off by making the voltage LOW
    delay(800);
    digitalWrite(light, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(700);                       // wait for a second
    digitalWrite(light, LOW);    // turn the LED off by making the voltage LOW
    delay(800);
    digitalWrite(light, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(700);                       // wait for a second
    digitalWrite(light, LOW);    // turn the LED off by making the voltage LOW
    delay(800);
    }
    // for Patting the light once
    else{
    digitalWrite(light, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(700);                       // wait for a second
    digitalWrite(light, LOW);    // turn the LED off by making the voltage LOW
    delay(800);
    }
    Serial.println();
  }
}
