//Motor pinos

#define motor1A 27
#define motor1B 26
#define motor2A 23
#define motor2B 19
//motor 1 = motor esquerda = motor B
//motor 2 = motor direita = motor A

enum controlModes { MANUAL, AUTONOMOUS, COMMAND }; 
int controlMode = MANUAL;

void stopCar();
void frontCar(int milisseconds);
void backCar(int milisseconds);
void turnRightFrontCar(int milisseconds);
void turnLeftFrontCar(int milisseconds);
void turnRightBackCar();
void turnLeftBackCar();
void autonomousDrive();
void changeMode(int value);

//Prototipo de variaveis externas
extern int distancia1;
extern int distancia2;
extern int distancia3;
extern void read_sensors();
extern void read_accel_gyro();
extern void sendValues();
extern PubSubClient MQTT;

void configPinsMotor(){
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  stopCar();
}

void stopCar(){
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
}

void frontCar(int milisseconds){
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
  if(milisseconds != 0){
    delay(milisseconds);
    stopCar();
  }
}

void backCar(int milisseconds){
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
  if(milisseconds != 0){
    delay(milisseconds);
    stopCar();
  }
}

void turnRightFrontCar(int milisseconds){
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
  if(milisseconds != 0){
    delay(milisseconds);
    stopCar();
  }
}

void turnLeftFrontCar(int milisseconds){
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
  if(milisseconds != 0){
    delay(milisseconds);
    stopCar();
  }
}

void turnRightBackCar(){
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
}

void turnLeftBackCar(){
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
}

void autonomousDrive(){
  if(distancia1 > 200){
    frontCar(0);
  }else{
    stopCar();
    backCar(300);
    delay(500);
    if(distancia3 > distancia2){
      if(distancia3 > 100){
        turnLeftFrontCar(500); 
      } 
    }else{
      if(distancia2 > 100){
        turnRightFrontCar(500); 
      }   
    }
    stopCar();
    delay(500);
  }
  read_sensors();
  MQTT.loop();
  read_accel_gyro();
  sendValues();
}

void changeMode(int value){
  controlMode = value;
  stopCar();
}
