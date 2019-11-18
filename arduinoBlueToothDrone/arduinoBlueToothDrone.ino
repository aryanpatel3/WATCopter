/*
 * This is the working code for the Stepper motors on pins 2 through 5
 * works with all 4 motors connected in parallel with the bread board
 */
#include <Servo.h>
Servo s3,s4;

char command = '0';

void setSpeed(int speed, Servo s)
{
  // speed is from 0 to 100 where 0 is off and 100 is max speed
  // the following maps speed values of 0-100 to angles from 0-180
  
  int angle = map(speed, 0, 100, 0, 180);
  s.write(angle);

}

void arm()
{
//arm speed controller, modify as necessary for your ESC

Serial.println("Arming S3");
//m1: 30 - 70
//m2: 
//m3: 20 - 80
//m4: 
setSpeed(20,s3);
delay(1000);

setSpeed(80,s3);
delay(1000);
Serial.println("Armed S3");
Serial.println("Arming S4");

setSpeed(30,s4);
delay(1000);

setSpeed(80,s4);
delay(1000);

Serial.println("Armed S4");
setSpeed(30,s3);
setSpeed(24,s4);
delay(5000);
Serial.println("Rest Phase");
}

void setup() 
{
  // initialize the serial port:
  Serial.begin(9600);
  s3.attach(9);
  s4.attach(10);
  arm();
}

void loop() {
  //if(Serial.available())
  //{
     // command = Serial.read();
     // Serial.print(command);
     //if(command == '1'){
      int speed;
     
      Serial.println("Sweeping up");
      for(speed = 20; speed <= 40; speed+= 1)
      {
        setSpeed(speed,s3);
        setSpeed(speed,s4);
        Serial.println(speed);
        delay(1000);
      }

      setSpeed(20,s3);
      setSpeed(20,s4);
      
      delay(1000);

      Serial.println("Sweeping down");
      for(speed = 45; speed >20; speed -=1)
      {
        setSpeed(speed,s3);
        setSpeed(speed,s4);
        Serial.println(speed);
        delay(100);
      }

      Serial.println("30 halting...");
      setSpeed(20,s3);
      setSpeed(20,s4);
      
      delay(5000);
     // }
 // }
}
