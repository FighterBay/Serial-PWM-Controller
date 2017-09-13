/*
 PWM output through arduino, controlled via serial interface. 


Usage:
Writes PWM to pins 9,10 taking commands from Serial @ 9600 bauds.
PWM1 through pin 9.
PWM2 through pin 10.
Syntax :

PWM1:PWM2:|

*/

#include <Servo.h>

Servo s[2];  // create servo object to control a servo

int i,pwm[2]={1000,1000}; //PWM to write to arduino.
String buf;
void setup() {
   Serial.begin(9600); // Start Serial Interface @ 9600 bauds
  s[0].attach(9);  // attaches the servo on pin 9 to the servo object
  s[1].attach(10);
  
  
}
int Occurrence(String data, char separator)
{
  int ctr = 0;
   int maxIndex = data.length()-1;
  for(int i=0; i<=maxIndex; i++)
  {
     if(data.charAt(i)==separator){
      ctr++;
     }
    }
    return ctr;
  }
 String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void loop() {
  if(Serial.available() > 0) //Check if we have something from the serial input.
  {

   
      buf = Serial.readStringUntil('|');
      buf.trim();
      if(Occurrence(buf,':') == 2)
      {
      pwm[0] = getValue(buf,':',0).toInt();
     
      pwm[1] = getValue(buf,':',1).toInt();
      }
      
  }
  for(i=0;i<2;i++)
    {
      s[i].writeMicroseconds(pwm[i]);
    }
    //Serial.println("PWM1:" + (String)pwm[0]);
    //Serial.println("PWM2:" + (String)pwm[1]);
}


