/*
  Example of APM_BMP085 (absolute pressure sensor) library.
  Code by Jordi Muï¿½oz and Jose Julio. DIYDrones.com
*/

#include <Wire.h>
#include <APM_BMP085.h> // ArduPilot Mega BMP085 Library

APM_BMP085_Class APM_BMP085;

unsigned long timer;

void setup()
{  
  APM_BMP085.Init();   // APM ADC initialization

  SerialUSB.println("ArduPilot Mega BMP085 library test");
  delay(1000);
  timer = millis();
}

void loop()
{
  int ch;
  float tmp_float;
  float Altitude;
  
  if((millis()- timer) > 50)
    {
    timer=millis();
    APM_BMP085.Read();
    SerialUSB.print("Pressure:");
    SerialUSB.print(APM_BMP085.Press);
    SerialUSB.print(" Temperature:");
    SerialUSB.print(APM_BMP085.Temp/10.0);
    SerialUSB.print(" Altitude:");
    tmp_float = (APM_BMP085.Press/101325.0);
    tmp_float = pow(tmp_float,0.190295);
    Altitude = 44330*(1.0-tmp_float);
    SerialUSB.print(Altitude);
    SerialUSB.println();
    }
}

