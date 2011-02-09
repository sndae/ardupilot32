/*
  Example of GPS MTK library.
  Code by Jordi Muï¿½oz and Jose Julio. DIYDrones.com

  Works with Ardupilot Mega Hardware (GPS on Serial Port1)
  and with standard ATMega168 and ATMega328 on Serial Port 0
*/

#include <GPS_MTK.h> // UBLOX GPS Library

#define T6 1000000
#define T7 10000000

void setup()
{
  SerialUSB.println("GPS MTK library test");
  GPS.Init();   // GPS Initialization
  delay(1000);
}
void loop()
{
  GPS.Read();
  if (GPS.NewData)  // New GPS data?
    {
    SerialUSB.print("GPS:");
    SerialUSB.print(" Lat:");
    SerialUSB.print((float)GPS.Lattitude/T7, DEC);
    SerialUSB.print(" Lon:");
    SerialUSB.print((float)GPS.Longitude/T7, DEC);
    SerialUSB.print(" Alt:");
    SerialUSB.print((float)GPS.Altitude/100.0, DEC);
    SerialUSB.print(" GSP:");
    SerialUSB.print((float)GPS.Ground_Speed/100.0, DEC);
    SerialUSB.print(" COG:");
    SerialUSB.print(GPS.Ground_Course/100.0, DEC);
    SerialUSB.print(" SAT:");
    SerialUSB.print((int)GPS.NumSats);
    SerialUSB.print(" FIX:");
    SerialUSB.print((int)GPS.Fix);
    SerialUSB.print(" TIM:");
    SerialUSB.print(GPS.Time);
    SerialUSB.println();
    GPS.NewData = 0; // We have readed the data
    }
  delay(20);
}

