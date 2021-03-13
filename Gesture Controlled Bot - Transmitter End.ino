#include <VirtualWire.h>
int xPin=A0;
int yPin=A1;
int ledPin=13;
int xinit;
int yinit;
void send(char *message)//send function definition
{
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
}
void setup() { 
  Serial.begin(9600); // Initialize serial communication at 9600 bits per second
   // Set pins as outputs
   vw_setup(2000);//Bits per second
  pinMode(ledPin,OUTPUT);
pinMode(xPin, INPUT);
pinMode(yPin, INPUT);
xinit=analogRead(xPin);
yinit=analogRead(yPin);
vw_set_tx_pin(7);
} 

void loop() { 
int xfin=analogRead(xPin);
int yfin=analogRead(yPin);
int xval=xfin-xinit;
int yval=yfin-yinit;
Serial.print("x= ");
Serial.println(xval);
Serial.print("y= ");
Serial.println(yval);
if( (yval>40)&& (xval<40 && xval>-40))
{ // Forward
  
digitalWrite(ledPin, HIGH);
Serial.println("Forward------------------------");
send("f");
}
if((xval>-40 && xval<40) && (yval<-40)){ // Reverse
    
digitalWrite(ledPin, HIGH);
Serial.println("backward----------------");
send("a"); 
} 
if((xval<-40 ) && (yval>-40 && yval<40)){ // Right
    //Serial.println(state);
digitalWrite(ledPin, HIGH);
Serial.println("right--------------");
send("r");
}
if((xval>40)&&(yval>-40 && yval<40)){ // Left
    
digitalWrite(ledPin, HIGH);
Serial.println("left----------");
send("l");
} 
if((xval>-40 && xval<40) && (yval>-40 && yval<40)){ // Stop
    
digitalWrite(ledPin, LOW);
Serial.println("stop-------");
send("s");
}
}
