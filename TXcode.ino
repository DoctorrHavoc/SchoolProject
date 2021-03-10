#include <VirtualWire.h>
const int tx_pin = 2;
const int indicate_pin = 13;
int pb1pin = 3;//pb1
int pb1val = 0;
int pb2pin = 4;//pb2
int pb2val = 0;
int pb3pin = 5;//pb3
int pb3val = 0;
void setup()
{
  pinMode(pb1pin, INPUT);
  pinMode(pb2pin, INPUT);
  pinMode(pb3pin, INPUT);
  vw_set_tx_pin(tx_pin);
  pinMode(indicate_pin, OUTPUT);
  vw_setup(2000);
}

void loop()
{
  pb1val = digitalRead(pb1pin);
  pb2val = digitalRead(pb2pin);
  pb3val = digitalRead(pb3pin);
/////////////////////PB1//////////////////////
  if (pb1val == HIGH) {
    digitalWrite(indicate_pin, HIGH);
    send("a");
  }
  else {
    digitalWrite(indicate_pin, LOW);
    send("b");
  }
//////////////////////PB2////////////////////
if (pb2val == HIGH) {
    digitalWrite(indicate_pin, HIGH);
    send("c");
  }
  else {
    digitalWrite(indicate_pin, LOW);
    send("b");
  }
//////////////////////PB3////////////////////

if (pb3val == HIGH) {
    digitalWrite(indicate_pin, HIGH);
    send("d");
  }
  else {
    digitalWrite(indicate_pin, LOW);
    send("b");
  }
//////////////////////////////////////////
}//end loop

void send (char *message)
{
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx();
}

