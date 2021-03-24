#include <VirtualWire.h>
byte message[VW_MAX_MESSAGE_LEN]; 
byte messageLength = VW_MAX_MESSAGE_LEN; 
const int receive_pin = 3;
const int led1pin = 7;
const int led2pin = 8;
const int led3pin = 9;
int pos = 0;
void setup()
{
pinMode(led1pin, OUTPUT);
pinMode(led2pin, OUTPUT);
pinMode(led3pin, OUTPUT);
vw_set_rx_pin(receive_pin);
Serial.begin(9600);
Serial.println("Device is ready");
vw_setup(2000); 
vw_rx_start(); 
}
void loop()
{
if (vw_get_message(message, &messageLength)) 
{
Serial.print("Received: ");
for (int i = 0; i < messageLength; i++) 
{ 
char c = message[i]; 
Serial.print(c); 
/////////////////////////////
if(c == 'a') { 
digitalWrite(led1pin, HIGH); 
//delay(100);
} 

if(c == 'b') { 
digitalWrite(led1pin, LOW);
} 
/////////////////////////////

if(c == 'c') { 
digitalWrite(led2pin, HIGH); 
//delay(100);
} 

if(c == 'b') { 
digitalWrite(led2pin, LOW);
} 
/////////////////////////////
if(c == 'd') { 
digitalWrite(led3pin, HIGH); 
//delay(100);
} 

if(c == 'b') { 
digitalWrite(led3pin, LOW);
} 

} 
Serial.println(); 
} 

}

