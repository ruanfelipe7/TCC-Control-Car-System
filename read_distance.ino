#include "Adafruit_VL53L0X.h"

// address we will assign if dual sensor is present
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32

// set the pins to shutdown
#define SHT_LOX1 4
#define SHT_LOX2 16
#define SHT_LOX3 17

// objects for the vl53l0x
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();

// this holds the measurement
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;

int distancia1 = 0;
int distancia2 = 0;
int distancia3 = 0;
/*
    Reset all sensors by setting all of their XSHUT pins low for delay(10), then set all XSHUT high to bring out of reset
    Keep sensor #1 awake by keeping XSHUT pin high
    Put all other sensors into shutdown by pulling XSHUT pins low
    Initialize sensor #1 with lox.begin(new_i2c_address) Pick any number but 0x29 and it must be under 0x7F. Going with 0x30 to 0x3F is probably OK.
    Keep sensor #1 awake, and now bring sensor #2 out of reset by setting its XSHUT pin high.
    Initialize sensor #2 with lox.begin(new_i2c_address) Pick any number but 0x29 and whatever you set the first sensor to
 */
void initSensorsDistance() {
  // all reset
  digitalWrite(SHT_LOX1, LOW);    
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  delay(10);
  // all unreset
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);

  // activating LOX1 and reseting LOX2, L0X3
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);

  // initing LOX1
  while(!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    delay(1000);  
  }
  delay(10);

  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  digitalWrite(SHT_LOX3, LOW);
  delay(10);

  //initing LOX2
  while(!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    delay(1000); 
  }

  delay(10);
  // activating LOX3
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);

  //initing LOX3
  while(!lox3.begin(LOX3_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    delay(1000);
  }
}

void read_sensors() {
  
  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
  lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!
  lox3.rangingTest(&measure3, false); // pass in 'true' to get debug data printout!

  // print sensor one reading
  Serial.print(F("1: "));
  if(measure1.RangeStatus != 4) {     // if not out of range
    distancia1 = measure1.RangeMilliMeter;
    Serial.print(measure1.RangeMilliMeter);
  } else {
    distancia1 = 8091;
    Serial.print(F("Out of range"));
  }
  
  Serial.print(F(" "));

  // print sensor two reading
  Serial.print(F("2: "));
  if(measure2.RangeStatus != 4) {
    distancia2 = measure2.RangeMilliMeter;
    Serial.print(measure2.RangeMilliMeter);
  } else {
    distancia2 = 8091;
    Serial.print(F("Out of range"));
  }

  Serial.print(F(" "));

  // print sensor two reading
  Serial.print(F("3: "));
  if(measure3.RangeStatus != 4) {
    distancia3 = measure3.RangeMilliMeter;
    Serial.print(measure3.RangeMilliMeter);
  } else {
    distancia3 = 8091;
    Serial.print(F("Out of range"));
  }
  
  Serial.println();
}

void configPinsSensorsDistance(){
  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);
  pinMode(SHT_LOX3, OUTPUT);

  Serial.println(F("Shutdown pins inited..."));

  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);

  Serial.println(F("Both in reset mode...(pins are low)"));
  
  
  Serial.println(F("Starting..."));
}

/////////////////////////////////////////////////////////////////////////////////////*****************************************************************************

//#include "Adafruit_VL53L0X.h"
////
////// address we will assign if dual sensor is present
//#define LOX1_ADDRESS 0x30
//
////// objects for the vl53l0x
//Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
//
////// this holds the measurement
//VL53L0X_RangingMeasurementData_t measure1;
////
//int distancia1 = 0;
//
//void initSensorsDistance() {
//
////  //initing LOX1
//  while(!lox1.begin(LOX1_ADDRESS)) {
//    Serial.println(F("Failed to boot first VL53L0X"));
//    delay(1000);  
//  }
//  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
//}
//
//void read_sensors() {
//
//  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
//
//  Serial.print(F("1: "));
//  if(measure1.RangeStatus != 4) {     // if not out of range
//    distancia1 = measure1.RangeMilliMeter;
//    Serial.print(measure1.RangeMilliMeter);
//  } else {
//    distancia1 = 8091;
//    Serial.print(F("Out of range"));
//  }
//
//}
//
//void configPinsSensorsDistance(){
//}
