#include <Servo.h>
#define Time 1000

boolean isToppings;
int val;
int G1 = 0;
int ledF = 13;

Servo Sservo;
Servo Lservo;
void setup() {
  Serial.begin(9600);
  pinMode(ledF, OUTPUT);

  Sservo.attach(6);
  Lservo.attach(5);

  Sservo.write(0);
  Lservo.write(0);


}
void loop()
{
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
        toppingsFunction();
        break;
      case 's':
        cuttingFunction();
        break;
    }
  }
}
// servo name.write(angle);
// Serial.print("*T"+String("25")+"*");
void toppingsFunction() {
  Serial.println("The toppings function has been executed!");
  Sservo.write(180);
  Serial.print("*T" + String("25") + "*");
  delay(Time);

  Sservo.write(135);
  Serial.print("*T" + String("50") + "*");
  delay(Time);

  Sservo.write(90);
  Serial.print("*T" + String("75") + "*");
  delay(Time);

  Sservo.write(45);
  Serial.print("*T" + String("100") + "*");
  delay(Time);

  Serial.println("The toppings function has finished!");
  Serial.print("*T" + String("0") + "*");
  Sservo.write(0);
}

void cuttingFunction() {
  Serial.println("The cutting function has been executed!");
  Lservo.write(180);
  Serial.print("*R" + String("25") + "*");
  delay(Time);

  Lservo.write(135);
  Serial.print("*R" + String("50") + "*");
  delay(Time);

  Lservo.write(90);
  Serial.print("*R" + String("75") + "*");
  delay(Time);

  Lservo.write(45);
  Serial.print("*R" + String("100") + "*");
  delay(Time);

  Serial.println("The cutting function has finished!");
  Serial.print("*R" + String("0") + "*");
  Lservo.write(0);
}
