/*
    L3G4200D Triple Axis Gyroscope: Pitch, Roll and Yaw.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-l3g4200d.html
    GIT: https://github.com/jarzebski/Arduino-L3G4200D
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <L3G4200D.h>

L3G4200D gyroscope;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;
enum command {COMMAND_REQUEST_PITCH_YAW = 0};

void setup() 
{
  Serial.begin(115200);

  // Initialize L3G4200D
  Serial.println("Initialize L3G4200D");

  // Set scale 2000 dps and 400HZ Output data rate (cut-off 50)
  while(!gyroscope.begin(L3G4200D_SCALE_2000DPS, L3G4200D_DATARATE_400HZ_50))
  {
    Serial.println("Could not find a valid L3G4200D sensor, check wiring!");
    delay(500);
  }
 
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  gyroscope.calibrate(100);
}
int ok = 1, timer2;
char tmp;
void calculation()
{
    //goto back;
    timer = millis();
  
    // Read normalized values
    Vector norm = gyroscope.readNormalize();
  
    if ( 0.2 < abs(norm.YAxis*timeStep))
    // Calculate Pitch, Roll and Yaw
        pitch = pitch + norm.YAxis * timeStep;
  
    if ( 0.2 < abs(norm.XAxis*timeStep) ) 
       roll = roll + norm.XAxis * timeStep;
       
    if ( 0.2 < abs(norm.ZAxis*timeStep))
      yaw = yaw + norm.ZAxis * timeStep;
  
    // Output raw
    //Serial.print(" Pitch = ");
    Serial.print(pitch);
    //Serial.print(" Roll = ");
    //Serial.print(roll);  
    //Serial.print(" Yaw = ");
    Serial.println(yaw);
  
    // Wait to full timeStep period
    delay((timeStep*1000) - (millis() - timer));
  
}
String str_tmp;
void loop()
{
  
   if (Serial.available() > 0)
  {
     tmp = Serial.read()-'0';
    // str_tmp = Serial.readString();
      //Serial.println(str_tmp);
    //  tmp = COMMAND_REQUEST_PITCH_YAW;
      switch (tmp) 
      {
        case COMMAND_REQUEST_PITCH_YAW:
           calculation();
         
          //Serial.println("request pitch yaw");
          break;
        default:
          
          Serial.println("incorrect request command");
          break;  
      }
  }
 
}
