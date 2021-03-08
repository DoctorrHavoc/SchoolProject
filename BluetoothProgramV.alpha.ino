boolean isToppings;
int val;
int ledF = 13;

void setup()
{
  Serial.begin(9600);
  pinMode(ledF, OUTPUT);


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

void toppingsFunction() {
  Serial.println("The toppings function has been executed!");
}

void cuttingFunction() {
  Serial.println("The cutting function has been executed!");
}
