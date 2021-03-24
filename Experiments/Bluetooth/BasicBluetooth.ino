int val;
int ledF = 13;

void setup(){
  Serial.begin(9600);
  pinMode(ledF, OUTPUT);
}

void loop()
{
  if (Serial.available())
  {
    val = Serial.read();
    if (val == '1') {digitalWrite(ledF, HIGH);}
    if ( val == '0'){digitalWrite(ledF, LOW);}
    }
}

