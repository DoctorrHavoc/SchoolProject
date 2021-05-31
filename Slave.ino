/*
   ╔═════════════════════════╗
   ║Category: School Project ║
   ║File Name: Slave         ║
   ║Programmer: Noam Cohen   ║
   ║Date: 28/5/2021          ║
   ╚═════════════════════════╝
*/

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
#define irModel 1080
int MinDistanceCM = 19;
int disCM1, disCM2, disCM3;
//==================

// SharpIR #1 Assets
#define irPin1 A0
SharpIR SharpIR1(irPin1, irModel);
//==================

// SharpIR #2 Assets
#define irPin2 A1
SharpIR SharpIR2(irPin2, irModel);
//==================

// SharpIR #3 Assets
#define irPin3 A2
SharpIR SharpIR3(irPin3, irModel);
//==================

// State Yellow LED Assets
#define yellowPin 50
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
#define Motor1Delay 1500
#define Motor2Delay 1500
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
#define rServoPin 7
int CutPos = 180, shortPos = 100;
//==================

// Functions Assets
#define StatePin 9
#define ToppingStartProcessPin 10
#define CuttingStartProcessPin 11
//==================

void setup() {
  Serial.begin(9600); // Establish communication at 9600 'baud rate'.
  pinMode(Green1Pin, OUTPUT); // Green Led - #1 RGB Led Setup.
  pinMode(Green2Pin, OUTPUT); // Green Led - #2 RGB Led Setup.
  pinMode(Green3Pin, OUTPUT); // Green Led - #3 RGB Led Setup.
  pinMode(Red1Pin, OUTPUT); // Red Led - #1 RGB Led Setup.
  pinMode(Red2Pin, OUTPUT); // Red Led - #2 RGB Led Setup.
  pinMode(Red3Pin, OUTPUT); // Red Led - #3 RGB Led Setup.
  pinMode(yellowPin, OUTPUT);
  for (int i = 22; i < 34; i = i + 2) {
    pinMode(i + 1, OUTPUT ); // 6 Motordrivers connections Setups.
    Serial.println(i);
  }
  // Turns off all motors.
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); digitalWrite(IN3, LOW); digitalWrite(IN4, LOW); digitalWrite(IN5, LOW); digitalWrite(IN6, LOW);
  plateServo.attach(pServoPin); // Declaring the pin for the Plate Servo.
  rackServo.attach(rServoPin); // Declaring the pin for the Rack & Pinion Servo.
}

void loop() {
  disCM1 = SharpIR1.distance(); // Returns the distance to the object in container #1.
  disCM2 = SharpIR2.distance(); // Returns the distance to the object in container #2.
  disCM3 = SharpIR3.distance(); // Returns the distance to the object in container #3.

  CheckInvetory1(); // Changes the RGB LED color by deciding if it's empty or not [Container #1].
  CheckInvetory2(); // Changes the RGB LED color by deciding if it's empty or not [Container #2].
  CheckInvetory3(); // Changes the RGB LED color by deciding if it's empty or not [Container #3].

  if (digitalRead(StatePin) == 1) {
    analogWrite(yellowPin, 225);
  }
  else {
    digitalWrite(yellowPin, LOW);
  }

  // Starts the Toppings process if it gets a signal.
  if (digitalRead(ToppingStartProcessPin) == 1) {
    SauceMotor();
    CheeseMotor();
    if (digitalRead(StatePin) == 1) {
      ToppingsMotor(); // Pours toppings if the user declared to do so.
    }
  }

  // Starts the Cutting process if it gets a signal.
  if (digitalRead(CuttingStartProcessPin) == 1) {
    StartCutting();
  }
}

void CheckInvetory1() {
  if (disCM1 <= MinDistanceCM) {
    digitalWrite(Red1Pin, LOW);
    digitalWrite(Green1Pin, HIGH);

  }
  else {
    digitalWrite(Red1Pin, HIGH);
    digitalWrite(Green1Pin, LOW);
  }
}

void CheckInvetory2() {
  if (disCM2 <= MinDistanceCM) {

    digitalWrite(Red2Pin, LOW);
    digitalWrite(Green2Pin, HIGH);
  }
  else {
    digitalWrite(Red2Pin, HIGH);
    digitalWrite(Green2Pin, LOW);
  }
}

void CheckInvetory3() {
  if (disCM3 <= MinDistanceCM) {
    digitalWrite(Red3Pin, LOW);
    digitalWrite(Green3Pin, HIGH);
  }
  else {

    digitalWrite(Red3Pin, HIGH);
    digitalWrite(Green3Pin, LOW);
  }
}

void SauceMotor() {
  plateServo.write(0); delay(500);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  plateServo.write(45); delay(500);
  plateServo.write(90); delay(500);
  plateServo.write(135); delay(500);
  plateServo.write(180);
  delay(Motor1Delay);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  plateServo.write(0);
}

void CheeseMotor() {
  plateServo.write(0); delay(500);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  plateServo.write(45); delay(500);
  plateServo.write(90); delay(500);
  plateServo.write(135); delay(500);
  plateServo.write(180);
  delay(Motor2Delay);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  plateServo.write(0);
}

void ToppingsMotor() {
  plateServo.write(0); delay(500);
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
  plateServo.write(180);
  delay(Motor3Delay);
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, LOW);
}

void StartCutting() {
  // First Cut - 2 Slices
  plateServo.write(0);
  rackServo.write(CutPos);
  rackServo.write(shortPos);

  // Second Cut - 4 Slices
  plateServo.write(60);
  rackServo.write(CutPos);
  rackServo.write(shortPos);

  // Third Cut - 6 Slices
  plateServo.write(120);
  rackServo.write(CutPos);

  rackServo.write(0);
  plateServo.write(0);
}
