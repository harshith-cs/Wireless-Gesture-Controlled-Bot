//Connect the Receiver data pin to Arduino pin 11

#include <VirtualWire.h>
const int trigPin = 6;
const int echoPin = 7;
long duration;
int distance;
byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message
const int datain = 11;
int motorB2 = 3; // Pin  2 of L293 left backward
int motorA2 = 5; // Pin  7 of L293 LEFT FOR
int motorA1 = 9; // Pin 10 of L293 right BACK
int motorB1 = 10; // Pin 14 of L293 RIGHT forward
int ledPin=13;//led on pin 13 is ON except when bot is stationary
int state = '0'; // Initialise Motors
void setup() { 
Serial.begin(9600); // Initialize serial communication at 9600 bits per second
   // Set pins as outputs
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT);
pinMode(motorA1, OUTPUT);
pinMode(motorA2, OUTPUT);
pinMode(motorB1, OUTPUT);
pinMode(motorB2, OUTPUT);

 vw_setup(2000); // Bits per sec
 vw_set_rx_pin(datain);
 vw_rx_start(); // Start the receiver
} 

void loop() { 
  digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 
 digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);

distance= duration*0.034/2;
Serial.print("Distance: ");
Serial.println(distance);

  uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
  int i;

  Serial.print("Got: ");//debugging
  
  for (i = 0; i < buflen; i++)
  {
     // Serial.print(buf[i],HEX);//You may also use integer values debugging
      //Serial.print(' ');// debugging

          if (distance<15 || buf[i]==0x73)//Stationary
          { 
            digitalWrite(motorA1, LOW); 
            digitalWrite(motorA2, LOW); 
            digitalWrite(motorB1, LOW); 
            digitalWrite(motorB2, LOW);
            digitalWrite(ledPin,LOW); 
            Serial.println("stop------------------------");
          }
          else
          {
            if(buf[i]==0x66)//Forward
            {
    
              digitalWrite(motorA1, LOW); 
              digitalWrite(motorA2, HIGH); 
              digitalWrite(motorB1, HIGH); 
              digitalWrite(motorB2, LOW);
              digitalWrite(ledPin,HIGH);
              Serial.println("forward----------------");  
            } 
            if (buf[i]==0x61)//Backward
            {
              digitalWrite(motorA1, HIGH); 
              digitalWrite(motorA2, LOW); 
              digitalWrite(motorB1, LOW); 
              digitalWrite(motorB2, HIGH); 
              digitalWrite(ledPin,HIGH);
              Serial.println("backward--------------");
            }
              if (buf[i]==0x72)//Right 
                          {
                  
              digitalWrite(motorA1, HIGH); 
              digitalWrite(motorA2, HIGH);
              digitalWrite(motorB1, LOW);
              digitalWrite(motorB2, LOW); 
              digitalWrite(ledPin,HIGH);
              Serial.println("right----------");
              } 
              if (buf[i]==0x6C)//Left 
              {    
              digitalWrite(motorA1, LOW); 
              digitalWrite(motorA2, LOW); 
              digitalWrite(motorB1, HIGH); 
              digitalWrite(motorB2, HIGH); 
              digitalWrite(ledPin,HIGH);
              Serial.println("left-------");
              }
          }
  }
  //Serial.print("\n");// debugging
    }
}
