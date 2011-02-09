/*
  Example of GPS UBLOX library.
  Code by Jordi Muï¿½oz and Jose Julio. DIYDrones.com

  Works with Ardupilot Mega Hardware (GPS on Serial Port1)
  and with standard ATMega168 and ATMega328 on Serial Port 0
*/

#include <GPS_UBLOX.h> // UBLOX GPS Library

void setup()
{
  SerialUSB.println("GPS UBLOX library test");
  GPS.Init();   // GPS Initialization
  delay(1000);
}
void loop()
{
  GPS.Read();
  if (GPS.NewData)  // New GPS data?
    {
    SerialUSB.print("GPS:");
    SerialUSB.print(" Time:");
    SerialUSB.print(GPS.Time);
    SerialUSB.print(" Fix:");
    SerialUSB.print((int)GPS.Fix);
    SerialUSB.print(" Lat:");
    SerialUSB.print(GPS.Lattitude);
    SerialUSB.print(" Lon:");
    SerialUSB.print(GPS.Longitude);
    SerialUSB.print(" Alt:");
    SerialUSB.print(GPS.Altitude/1000.0);
    SerialUSB.print(" Speed:");
    SerialUSB.print(GPS.Ground_Speed/100.0);
    SerialUSB.print(" Course:");
    SerialUSB.print(GPS.Ground_Course/100000.0);
    SerialUSB.println();
    GPS.NewData = 0; // We have readed the data
    }
  delay(20);
}

