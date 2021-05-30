/*
   ╔═════════════════════════╗
   ║Category: School Project ║
   ║File Name: Master        ║
   ║Programmer: Noam Cohen   ║
   ║Date: 27/5/2021          ║
   ╚═════════════════════════╝
*/

#include <Arduino.h>

// Bluetooth Assets
char val;
//==================

// LDR Assets
#define LDRpin A0
int maxLight = 500;
int LDRval;
//==================

// Laser Sensor Assets
#define LaserReciverpin 13
boolean LaserVal;
//==================

// Buzzer Assets
#define BuzzerPin 2
int BuzzerTone = 500;
short BuzzerDelay = 20;
//==================

// Switch...Case Assets
boolean isToppings;
#define StatePin 9
#define ToppingStartProcessPin 10
#define CuttingStartProcessPin 11
//==================

// This function checks if the LDR is blocked and that there's nothing in the way to make sure that it's safe to start.
boolean isSecure(boolean laser, int ldrVal) {
  if (laser == HIGH and ldrVal <= maxLight) {
    return true;
  }
  else return false;
}

// This function turns on and off the Buzzer for a short moment.
void Beep() {
  tone(BuzzerPin, BuzzerTone);
  delay(BuzzerDelay);
  noTone(BuzzerPin);
}


void setup() {
  pinMode(LDRpin, INPUT); // LDR Pin setup.
  pinMode(LaserReciverpin, INPUT); // Laser Reciver Pin setup.
  pinMode(BuzzerPin, OUTPUT); // Buzzer Pin setup.
  pinMode(12, OUTPUT); digitalWrite(12, HIGH);

  Serial.begin(9600); // Establish communication at 9600 'baud rate'.

}

void loop() {
  LaserVal = digitalRead(LaserReciverpin); // Checks if the laser is blocked or not.

  LDRval = analogRead(LDRpin); // Reads the LDR sensor value.
  Serial.println(LDRval ); delay(500);
  if (Serial.available()) { // Waits for Input.
    val = Serial.read(); // Reads the data that was sent.
    switch (val) { // Takes the data and runs it through statments.
      case 'T': // Sets the toppings options to true.
        Beep();
        isToppings = true;
        digitalWrite(StatePin, isToppings);
        Serial.println("Toppings are set to: True");
        break;

      case 'F': // Sets the toppings options to false.
        Beep();
        isToppings = false;
        digitalWrite(StatePin, isToppings);
        Serial.println("Toppings are set to: False" );
        break;

      case 'S': // Starts the toppings process.
        Beep();
        if (isSecure(LaserVal, LDRval)) {
          digitalWrite(ToppingStartProcessPin, HIGH); // Sends Signal
          delay(10); // short delay
          digitalWrite(ToppingStartProcessPin, LOW); // Turns of the Signal
          Serial.println("Topping Process has started!");
        }
        else {
          Serial.println("Can't start! \n - Make sure that the Dough is on the plate \n - Make sure that the way is clear.");
        }
        break;

      case 's': // Starts the cutting process.
        Beep();
        if (isSecure(LaserVal, LDRval)) {
          digitalWrite(CuttingStartProcessPin, HIGH);
          delay(10); // short delay
          digitalWrite(CuttingStartProcessPin, LOW);
          Serial.println("Cutting Process has started!");

        }
        else {
          Serial.println("Can't start! \n - Make sure that the Pizza is on the plate \n - Make sure that the way is clear.");
        }
        break;

      default:
        Serial.println("Unavailable option");
        break;
    }
  }
}
