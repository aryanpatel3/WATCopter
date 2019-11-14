#include <Servo.h>

Servo myservo;
char command = '0';

void arm()
{
//arm speed controller, modify as necessary for your ESC

Serial.println("Arming");
setSpeed(50);
delay(2000);

setSpeed(90);
delay(2000);

Serial.println("Armed");
setSpeed(50);
delay(2000);

}

void setSpeed(int speed)
{
// speed is from 0 to 100 where 0 is off and 100 is max speed
// the following maps speed values of 0-100 to angles from 0-180

int angle = map(speed, 0, 100, 0, 180);
myservo.write(angle);

}

void setup()
{

Serial.begin(9600);
Serial.println("Began");
//myservo.attach(9);
//arm();

}     

void loop()
{
  //Serial.print(command);
  Serial.print(Serial.available());
  if (Serial.available()) {

    command = Serial.read();
    Serial.print(command);

    /*if(command == '1'){
      int speed;

      Serial.println("Sweeping up");
      for(speed = 57; speed <= 90; speed+= 1)
      {
        setSpeed(speed);
        Serial.println(speed);
        delay(100);
      }

      setSpeed(70);
      delay(1000);

      Serial.println("Sweeping down");
      for(speed = 90; speed >57; speed -=1)
      {
        setSpeed(speed);
        Serial.println(speed);
        delay(100);
      }

      Serial.println("30 halting...");
      setSpeed(70);
      delay(5000);
      }*/
    
  }
/*int speed;

Serial.println("Sweeping up");
for(speed = 57; speed <= 90; speed+= 1)
{
 
  setSpeed(speed);
  Serial.println(speed);
  delay(100);
 
}

setSpeed(70);
delay(1000);

Serial.println("Sweeping down");
for(speed = 90; speed >57; speed -=1)
{
 
  setSpeed(speed);
  Serial.println(speed);
  delay(100);
 
}

Serial.println("30 halting...");
setSpeed(70);
delay(5000);*/



}
