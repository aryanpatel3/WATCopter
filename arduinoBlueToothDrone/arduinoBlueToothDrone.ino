/*
 * This is the working code for the Stepper motors on pins 2 through 5
 * works with all 4 motors connected in parallel with the bread board
 */
#include <Servo.h>
Servo s3,s4;
int high3 = 30;
int low3 = 70;
int high4 = 10;
int low4 = 90;
char command = '0'; 

void setSpeed(int speed, Servo s)
{
  // speed is from 0 to 100 where 0 isM off and 100 is max speed
  // the following maps speed values of 0-100 to angles from 0-180
  
  int angle = map(speed, 0, 100, 0, 180);
  s.write(angle);

}

void arm()
{
//arm speed controller, modify as necessary for your ESC
//m1: 30 - 70
//m2: 10 - 90
//m3: 20 - 80
//m4: DNE
/*Serial.println("Arming S1");
setSpeed(20,s1);
delay(1000);

setSpeed(80,s1);
delay(1000);
Serial.println("Armed S1");
Serial.println("Arming S2");
setSpeed(20,s2);
delay(1000);

setSpeed(80,s2);
delay(1000);
Serial.println("Armed S2");
Serial.println("Arming S3");
setSpeed(20,s3);
delay(1000);

setSpeed(80,s3);
delay(1000);
Serial.println("Armed S3");*/
delay(5000);
Serial.println("Arming S4");
Serial.println("Arm LOW S4");
setSpeed(low4,s4);
delay(5000);
Serial.println("Arm HIGH S4");
setSpeed(high4,s4);
delay(5000);
Serial.println("Armed S4");

delay(1000);

Serial.println("Arming S3");
Serial.println("Arm LOW S3");
setSpeed(low3,s3);
delay(5000);
Serial.println("Arm HIGH S3");
setSpeed(high3,s3);
delay(5000);
Serial.println("Armed S3");

//setSpeed(30,s3);
Serial.println("Rest Phase Started");
setSpeed((high4+low4)/4,s4);
setSpeed((high3+low3)/4,s3);
delay(5000);
Serial.println("Rest Phase Complete");
}

void setup() 
{
  // initialize the serial port:
  Serial.begin(9600);
  
  /*s1.attach(6);
  s2.attach(9);
  s3.attach(10);*/
  s3.attach(9);
  s4.attach(10);
  arm();
}

void loop() {
  if(Serial.available())
  {
     Serial.println("Avalible");
     command = Serial.read();
     Serial.println(command);
     if(command == '1' || command == '!'){
        Serial.println("COMMAND RECEIVED");
        Serial.println("Stopping");
        setSpeed(0,s3);
        setSpeed(0,s4);
        delay(1000);
        /*int speed;
       
        Serial.println("Sweeping up");
        for(speed = low; speed <= high; speed+= 1)
        {
          //setSpeed(speed,s3);
          setSpeed(speed,s4);
          Serial.println(speed);
          delay(100);
        }
  
        //setSpeed(20,s3);
        setSpeed((high+low)/2,s4);
        
        delay(10000);
  
        Serial.println("Sweeping down");
        for(speed = high; speed >low; speed -=1)
        {
          //setSpeed(speed,s3);
          setSpeed(speed,s4);
          Serial.println(speed);
          delay(100);
        }
  
        Serial.println("30 halting...");
        //setSpeed(20,s3);
        setSpeed((high+low)/2,s4);
        
        delay(5000);*/
     } else if(command == '3' || command == '#'){
        Serial.println("COMMAND RECEIVED");
        Serial.println("Starting");
        setSpeed(20,s3);
        setSpeed(20,s4);
        delay(1000);
        setSpeed(30,s3);
        setSpeed(30,s4);
        delay(1000);
        setSpeed(40,s3);
        setSpeed(40,s4);
        delay(1000);
        setSpeed(50,s3);
        setSpeed(50,s4);
        delay(1000);
        setSpeed(60,s3);
        setSpeed(60,s4);
        delay(1000);
        setSpeed(70,s3);
        setSpeed(70,s4);
        delay(1000);
    }
  }
}
