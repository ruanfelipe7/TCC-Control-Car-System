#include <WiFi.h> 
#include <PubSubClient.h>

//Prototipo de funções externas
extern void configPinsMotor();
extern void initMqtt();
extern void conectaWiFi();
extern void mantemConexoes();
extern void startMQTTLoop();
extern void initSensorsDistance();
extern void configPinsSensorsDistance();
extern void read_sensors();
extern void initMPU6050();
extern void read_accel_gyro();
extern void sendValues();
extern void configPinLed();
extern void blinkLed();

extern PubSubClient MQTT;

void setup() {
  // put your setup code here, to run once:
  configPinLed();
  Serial.begin(9600);
  configPinsMotor();
  conectaWiFi();
  initMqtt();
  configPinsSensorsDistance();
  initSensorsDistance();
  initMPU6050();
  blinkLed();
}

void loop() {
  mantemConexoes();
  MQTT.loop();
  read_sensors();
  read_accel_gyro();
  sendValues();
}
