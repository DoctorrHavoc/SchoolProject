#include <Arduino.h>
#include <SharpIR.h>
#include <Servo.h>

/* Models : 
- GP2Y0A02YK0F --> "20150"
- GP2Y0A21YK --> "1080"
- GP2Y0A710K0F --> "100500"
- GP2YA41SK0F --> "430"
*/
// Global SharpIR Assets
#define irModel 20150
int MinDistanceCM=3;
int disCM1,disCM2,disCM3;
//==================

// SharpIR #1 Assets  
#define irPin1 A0
SharpIR SharpIR1(irPin1, irModel);
int dis1;
//==================

// SharpIR #2 Assets
#define irPin2 A1
SharpIR SharpIR2(irPin2, irModel);
int dis2;
//==================

// SharpIR #3 Assets
#define irPin3 A2
SharpIR SharpIR3(irPin3, irModel);
int dis3;
//==================

// LED #1 Assets
#define Green1Pin 2
#define Red1Pin 3
//==================

// LED #2 Assets
#define Green2Pin 4
#define Red2Pin 5
//==================

// LED #3 Assets
#define Green3Pin 6
#define Red3Pin 7

//==================

// MotorDriver1 Assets
#define Motor1Delay 2500
#define Motor2Delay 2500
#define IN1 22
#define IN2 24
#define IN3 26
#define IN4 28

//==================

// MotorDriver2 Assets
#define Motor3Delay 2500
#define IN5 30
#define IN6 32
//==================

// Plate Servo Assets
Servo plateServo;
#define pServoPin 8
//==================

// Rack & Pinion Servo Assets
Servo rackServo;
#define rServoPin 9
int CutPos=180, shortPos=100;
//==================

// Functions Assets
#define StatePin 10
#define ToppingStartProcessPin 11
#define CuttingStartProcessPin 12
//==================

void setup() {
  Serial.begin(9600);
  pinMode(Green1Pin,OUTPUT);
  pinMode(Green2Pin,OUTPUT);
  pinMode(Green3Pin,OUTPUT);
  pinMode(Red1Pin,OUTPUT);
  pinMode(Red2Pin,OUTPUT);
  pinMode(Red3Pin,OUTPUT);
  for (int i = 0; i < 6; i++){ pinMode(i+1,OUTPUT );}
  digitalWrite(IN1,LOW); digitalWrite(IN2,LOW); digitalWrite(IN3,LOW); digitalWrite(IN4,LOW); digitalWrite(IN5,LOW); digitalWrite(IN6,LOW);
  plateServo.attach(pServoPin);
  rackServo.attach(rServoPin);
}

void loop() {
  disCM1=SharpIR1.distance(); // Returns the distance to the object.
  disCM2=SharpIR2.distance(); // Returns the distance to the object.
  disCM3=SharpIR3.distance(); // Returns the distance to the object.

  CheckInvetory1();
  CheckInvetory2();
  CheckInvetory3();
  if(digitalRead(ToppingStartProcessPin)==1){
    SauceMotor();
    CheeseMotor();
    if (digitalRead(StatePin)==1){ToppingsMotor();}
  }

  if(digitalRead(CuttingStartProcessPin)==1){
    StartCutting();
  }

}

void CheckInvetory1(){
  if(disCM1<=MinDistanceCM){
    digitalWrite(Red1Pin,HIGH);
    digitalWrite(Green1Pin,LOW);
  }
  else{
    digitalWrite(Red1Pin,LOW);
    digitalWrite(Green1Pin,HIGH);
  }
}

void CheckInvetory2(){
  if(disCM2<=MinDistanceCM){
    digitalWrite(Red2Pin,HIGH);
    digitalWrite(Green2Pin,LOW);
  }
  else{
    digitalWrite(Red2Pin,LOW);
    digitalWrite(Green2Pin,HIGH);
  }
}

void CheckInvetory3(){
  if(disCM3<=MinDistanceCM){
    digitalWrite(Red3Pin,HIGH);
    digitalWrite(Green3Pin,LOW);
  }
  else{
    digitalWrite(Red3Pin,LOW);
    digitalWrite(Green3Pin,HIGH);
  }
}

void SauceMotor(){
  plateServo.write(0); delay(500);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  plateServo.write(180);
  delay(Motor1Delay);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
}

void CheeseMotor(){
  plateServo.write(0); delay(500);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  plateServo.write(180);
  delay(Motor2Delay);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

void ToppingsMotor(){
  plateServo.write(0); delay(500);
  digitalWrite(IN5,HIGH);
  digitalWrite(IN6,LOW);
  plateServo.write(180);
  delay(Motor3Delay);
  digitalWrite(IN5,LOW);
  digitalWrite(IN6,LOW);
}

void StartCutting(){
  // First Cut - 2 Slices
  plateServo.write(0);
  rackServo.write(CutPos);
  rackServo.write(shortPos);
  
  // Second Cut - 4 Slices
  plateServo.write(60);
  rackServo.write(CutPos);
  rackServo.write(shortPos);

  // Second Cut - 6 Slices
  plateServo.write(120);
  rackServo.write(CutPos);
  
  rackServo.write(0);
  plateServo.write(0);
}
