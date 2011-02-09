/*
  Example of GPS IMU library.
  Code by Jordi Munoz, Jose Julio and, Jason Short . DIYDrones.com

  Works with Ardupilot Mega Hardware (GPS on Serial Port1)
  and with standard ATMega168 and ATMega328 on Serial Port 0
*/

#include <GPS_IMU.h> // GPS Library

void setup()
{
 // SerialUSB.begin(38400);
  SerialUSB.println("GPS IMU library test");
  GPS.Init();   // GPS Initialization
  delay(1000);
}
void loop()
{
  GPS.Read();
  if (1){  // New GPS data?

    SerialUSB.print("GPS:");
    SerialUSB.print(" Lat:");
    SerialUSB.print(GPS.Lattitude);
    SerialUSB.print(" Lon:");
    SerialUSB.print(GPS.Longitude);
    SerialUSB.print(" Alt:");
    SerialUSB.print((float)GPS.Altitude/100.0);
    SerialUSB.print(" GSP:");
    SerialUSB.print((float)GPS.Ground_Speed/100.0);
    SerialUSB.print(" COG:");
    SerialUSB.print(GPS.Ground_Course/1000000);
    SerialUSB.print(" SAT:");
    SerialUSB.print((int)GPS.NumSats);
    SerialUSB.print(" FIX:");
    SerialUSB.print((int)GPS.Fix);
    SerialUSB.print(" TIM:");
    SerialUSB.print(GPS.Time);
    SerialUSB.println();
    GPS.NewData = 0; // We have read the data
    }
  delay(20);
}
