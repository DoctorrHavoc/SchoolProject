#include <Arduino.h>

// Bluetooth Assets
char val;
//==================

// LDR Assets
#define LDRpin A0
int maxLight=800;
int LDRval;
//==================

// Laser Sensor Assets
#define LaserReciverpin 2
boolean LaserVal;
//==================

// Switch...Case Assets
boolean isToppings;
//==================



void setup() {
  pinMode(LDRpin,INPUT); // LDR Pin setup.
  pinMode(LaserReciverpin, INPUT); // Laser Reciver Pin setup.

  Serial.begin(9600);
  
}

void loop() {
  LaserVal = digitalRead(LaserReciverpin);
  LDRval=analogRead(LDRpin);

 if (Serial.available()) {
   val = Serial.read();
    switch (val) {
      case 'T':
        isToppings = true;
        Serial.println("Toppings are set to: True" );
        break;

      case 'F':
        isToppings = false;
        Serial.println("Toppings are set to: False" );
        break;

      case 'S':
      if (isSecure(LaserVal,LDRval)){
        toppingFunction();
      }
      else{Serial.println("Cant' start!");}

      break;
      
      case 's':
        break;

    }
  } 
}

// Checks if 
boolean isSecure(boolean laser, int ldrVal){
  if (laser == HIGH and ldrVal <= maxLight){
    return true;
  }
  else return false;
}

void toppingFunction(){
  Serial.println("Toppings will begin unless there's not enough supply!");
}

