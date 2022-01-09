int led = 13;
void configPinLed(){ 
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void turnOnLed(){
  digitalWrite(led, HIGH);
}

void turnOffLed(){
  digitalWrite(led, LOW);
}

void blinkLed(){
  turnOnLed();
  delay(3000);
  turnOffLed();
}
