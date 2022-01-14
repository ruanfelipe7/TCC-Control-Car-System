//WiFi
const char* SSID = "SSID";                // SSID / nome da rede WiFi que deseja se conectar
const char* PASSWORD = "PASSWORD";                 //Senha da rede WiFi que deseja se conectar
WiFiClient wifiClient;

//MQTT
const char* BROKER_MQTT = "broker.mqtt-dashboard.com";   // seu endereço IP  //  "broker.hivemq.com - funcionou"; // "broker.mqtt-dashboard.com - funcionou";  //"192.168.1.19"; "iot-eclipse.org"    //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883;                      // Porta do Broker MQTT

#define ID_MQTT  "CARRO1"            //Informe um ID unico e seu. Caso sejam usados IDs repetidos a ultima conexão irá sobrepor a anterior. 

//topicos
#define TOPIC_SUBSCRIBE "4361fd9a-0c1e-420c-b858-27ad478288e6/controlCar"

#define TOPIC_PUBLISH_DISTANCE_SENSOR "4361fd9a-0c1e-420c-b858-27ad478288e6/distanceSensor"
#define TOPIC_PUBLISH_ACCELEROMETER "4361fd9a-0c1e-420c-b858-27ad478288e6/accelerometer"
#define TOPIC_PUBLISH_GYROSCOPE "4361fd9a-0c1e-420c-b858-27ad478288e6/gyroscope"

char data[40];

PubSubClient MQTT(wifiClient);        // Instancia o Cliente MQTT passando o objeto espClient

//Declaração das Funções
void mantemConexoes();  //Garante que as conexoes com WiFi e MQTT Broker se mantenham ativas
void conectaWiFi();     //Faz conexão com WiFi
void conectaMQTT();     //Faz conexão com Broker MQTT
void enviaPacote();     //Envia pacote
void recebePacote(char* topic, byte* payload, unsigned int length); //Recebe pacote
void sendValues();
void sendDistanceMeasure();
void sendAcceleration();
void sendGyro();

//Prototipo de funções externas
extern void stopCar();
extern void frontCar(int milisseconds);
extern void backCar(int milisseconds);
extern void turnRightFrontCar(int milisseconds);
extern void turnLeftFrontCar(int milisseconds);
extern void turnRightBackCar();
extern void turnLeftBackCar();
extern void changeMode(int value);

//Prototipo de variaveis externas
extern int controlMode;

extern int distancia1;
extern int distancia2;
extern int distancia3;

extern float ax;
extern float ay;
extern float az;
extern float gx;
extern float gy;
extern float gz;

void initMqtt() {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  MQTT.setCallback(recebePacote);
}

void startMQTTLoop(){
  MQTT.loop();
}

void mantemConexoes() {
  if (!MQTT.connected()) {
    conectaMQTT();
  }

  conectaWiFi(); //se não há conexão com o WiFI, a conexão é refeita
}

void conectaWiFi() {

  if (WiFi.status() == WL_CONNECTED) {
    return;
  }

  Serial.print("Conectando-se na rede: ");
  Serial.print(SSID);
  Serial.println("  Aguarde!");
  WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Conectado com sucesso, na rede: ");
  Serial.print(SSID);
  Serial.print("  IP obtido: ");
  Serial.println(WiFi.localIP());
}

void conectaMQTT() {
  while (!MQTT.connected()) {
    Serial.print("Conectando ao Broker MQTT: ");
    Serial.println(BROKER_MQTT);
    if (MQTT.connect(ID_MQTT)) {
      Serial.println("Conectado ao Broker com sucesso!");
      MQTT.subscribe(TOPIC_SUBSCRIBE);
    }
    else {
      Serial.println("Nao foi possivel se conectar ao broker.");
      Serial.println("Nova tentativa de conexao em 10s");
      delay(10000);
    }
  }
}

void recebePacote(char* topic, byte* payload, unsigned int length) {
  String msg;

  //obtem a string do payload recebido
  for (int i = 0; i < length; i++)
  {
    char c = (char)payload[i];
    msg += c;
  }

  Serial.println(msg);
  if (msg == "A") {
    changeMode(AUTONOMOUS);
  }else if(msg == "M"){
    changeMode(MANUAL);
  }else if(msg == "C"){
    changeMode(COMMAND);
  }
  
  if(controlMode == MANUAL){
    Serial.println("MANUAL");
    if (msg == "000") {
      stopCar();
    } else if (msg == "101") {
      frontCar(0);
    } else if (msg == "111") {
      backCar(0);
    } else if (msg == "001") {
      turnRightFrontCar(0);
    } else if (msg == "100") {
      turnLeftFrontCar(0);
    } else if (msg == "011") {
      turnRightBackCar();
    } else if (msg == "110") {
      turnLeftBackCar();
    }  
  }else if(controlMode == AUTONOMOUS){
    Serial.println("AUTO");
    do {
      autonomousDrive();
    } while(controlMode == AUTONOMOUS);
  }else if(controlMode == COMMAND){
    Serial.println("COMMAND");
    if(msg == "111"){
      frontCar(1000);
    }else if(msg == "010"){
      backCar(1000);
    }else if(msg == "100"){
      turnLeftFrontCar(700);  
    }else if(msg == "110"){
      turnLeftFrontCar(1200);  
    }else if(msg == "001"){
      turnRightFrontCar(700);  
    }else if(msg == "011"){
      turnRightFrontCar(1200);
    }
  }
}

void sendDistanceMeasure(){
  snprintf(data, sizeof(data), "1:%d | 2:%d | 3:%d", distancia1, distancia2, distancia3);          
  MQTT.publish(TOPIC_PUBLISH_DISTANCE_SENSOR, data);  
}

void sendAcceleration(){
  snprintf(data, sizeof(data), "x:%.2f | y:%.2f", ax, ay);          
  MQTT.publish(TOPIC_PUBLISH_ACCELEROMETER, data);  
}

void sendGyro(){
  snprintf(data, sizeof(data), "z:%.2f", gz);          
  MQTT.publish(TOPIC_PUBLISH_GYROSCOPE, data);  
}

void sendValues(){
  sendDistanceMeasure();
  sendAcceleration();
  sendGyro();
}
