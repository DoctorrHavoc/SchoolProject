#include <Arduino.h>
#include <SharpIR.h>

// Toppings Assets
#define ToppingState 10
#define ToppingSignal 11
//==================

// Cutting Assets
#define CuttingSignal 12
//==================

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

// MotorDriver1
#define IN1 22
#define IN2 24
#define IN3 26
#define IN4 28

//==================

// MotorDriver2
#define IN5 30
#define IN6 32
//==================

void setup() {
  Serial.begin(9600);
  pinMode(Green1Pin,OUTPUT);
  pinMode(Green2Pin,OUTPUT);
  pinMode(Green3Pin,OUTPUT);
  pinMode(Red1Pin,OUTPUT);
  pinMode(Red2Pin,OUTPUT);
  pinMode(Red3Pin,OUTPUT);

}

void loop() {
  disCM1=SharpIR1.distance(); // Returns the distance to the object.
  disCM2=SharpIR2.distance(); // Returns the distance to the object.
  disCM3=SharpIR3.distance(); // Returns the distance to the object.

  CheckInvetory1();
  CheckInvetory2();
  CheckInvetory3();
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
