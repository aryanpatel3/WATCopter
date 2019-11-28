/*
 * This is the working code for the Stepper motors on pins 2 through 5
 * works with all 4 motors connected in parallel with the bread board
 */
#include <Servo.h>
#include <Wire.h>

long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;
int speedSet = 0;

Servo s1,s2,s3,s4;

int high1 = 45;
int low1 = 10;

int high2 = 90;
int low2 = 10;

int high3 = 90;
int low3 = 10;

int high4 = 90;
int low4 = 10;
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
//ARMING 4
delay(5000);
Serial.println("Arming S4");
Serial.println("Arm LOW S4");
setSpeed(high4,s4);
delay(5000);
Serial.println("Arm HIGH S4");
setSpeed(low4,s4);
delay(5000);
Serial.println("Armed S4");

delay(1000);

//ARMING 3
Serial.println("Arming S3");
Serial.println("Arm LOW S3");
setSpeed(high3,s3);
delay(5000);
Serial.println("Arm HIGH S3");
setSpeed(low3,s3);
delay(5000);
Serial.println("Armed S3");

//ARMING 2
delay(5000);
Serial.println("Arming S2");
Serial.println("Arm LOW S2");
setSpeed(high2,s2);
delay(5000);
Serial.println("Arm HIGH S2");
setSpeed(low2,s2);
delay(5000);
Serial.println("Armed S2");

//ARMING 1
delay(1000);
Serial.println("Arming S1");
Serial.println("Arm LOW S1");
setSpeed(high1,s1);
delay(5000);
Serial.println("Arm HIGH S1");
setSpeed(low1,s1);
delay(5000);
Serial.println("Armed S1");

Serial.println("Rest Phase Started");
setSpeed((high4+low4)/4,s4);
setSpeed(35,s3);
setSpeed((high2+low2)/2,s2);
setSpeed((high1+low1)/2,s1);
delay(5000);
Serial.println("Rest Phase Complete");
}


void setupMPU(){
  Wire.beginTransmission(0b1101000); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B); //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0b00000000); //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission();  
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1B); //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4) 
  Wire.write(0x00000000); //Setting the gyro to full scale +/- 250deg./s 
  Wire.endTransmission(); 
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1C); //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5) 
  Wire.write(0b00000000); //Setting the accel to +/- 2g
  Wire.endTransmission(); 
}

void recordAccelRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x3B); //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Accel Registers (3B - 40)
  while(Wire.available() < 6);
  accelX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  accelY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  accelZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  processAccelData();
}

void processAccelData(){
  gForceX = accelX / 16384.0;
  gForceY = accelY / 16384.0; 
  gForceZ = accelZ / 16384.0;
}

void recordGyroRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Gyro Registers (43 - 48)
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  gyroY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  gyroZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  processGyroData();
}

void processGyroData() {
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0; 
  rotZ = gyroZ / 131.0;
}

void printData() {
  Serial.print("Gyro (deg)");
  Serial.print(" X=");
  Serial.print(rotX);
  Serial.print(" Y=");
  Serial.print(rotY);
  Serial.print(" Z=");
  Serial.print(rotZ);
  Serial.print(" Accel (g)");
  Serial.print(" X=");
  Serial.print(gForceX);
  Serial.print(" Y=");
  Serial.print(gForceY);
  Serial.print(" Z=");
  Serial.println(gForceZ);
  //delay(1500);
}

void setup() 
{
  // initialize the serial port:
  Serial.begin(9600);
  Wire.begin();
  setupMPU();
  s1.attach(6);
  s2.attach(9);
  s3.attach(10);
  //s4.attach(11);
  arm();
}

void loop() {
  recordAccelRegisters();
  recordGyroRegisters();
  //printData();
  if(Serial.available())
  {
     Serial.println("Avalible");
     command = Serial.read();
     Serial.println(command);
     if(command == '5'){
       Serial.println("COMMAND RECEIVED");
        Serial.println("Starting");
        
        setSpeed(speedSet,s1);
        setSpeed(speedSet,s2);
        setSpeed(speedSet,s3);
        setSpeed(speedSet,s4);
        speedSet += 3;
        delay(1000);
     } else if(command == '6'){
        Serial.println("COMMAND RECEIVED");
        Serial.println("Stopping");
        speedSet -= 10;
        setSpeed(speedSet,s1);
        setSpeed(speedSet,s2);
        setSpeed(speedSet,s3);
        setSpeed(speedSet,s4);
        delay(1000);
    }
  }
}
