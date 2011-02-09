/*
	APM_BMP085.cpp - Arduino Library for BMP085 absolute pressure sensor
	Code by Jordi Muñoz and Jose Julio. DIYDrones.com

	This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

	Sensor is conected to I2C port
	Sensor End of Conversion (EOC) pin is PC7 (30)
	
	Variables:
		RawTemp : Raw temperature data
		RawPress : Raw pressure data

		Temp : Calculated temperature (in 0.1ºC units)
		Press : Calculated pressure   (in Pa units)
	
	Methods:
		Init() : Initialization of I2C and read sensor calibration data
		Read() : Read sensor data and calculate Temperature and Pressure
		         This function is optimized so the main host don´t need to wait 
				 You can call this function in your main loop
				 It returns a 1 if there are new data.
    
	Internal functions:
		Command_ReadTemp(): Send commando to read temperature
		Command_ReadPress(): Send commando to read Pressure
		ReadTemp() : Read temp register
		ReadPress() : Read press register
		Calculate() : Calculate Temperature and Pressure in real units

		
*/
extern "C" {
  // AVR LibC Includes
  
  //#include <inttypes.h>
  //#include <stdint.h>
  
	//#include <avr/interrupt.h>
  //#include "WConstants.h"
}

#include "APM_BMP085.h"
#include "..\project\compatArduino.h"
using namespace compatArduino;


#define BMP085_ADDRESS 0x77  //(0xEE >> 1)
#define BMP085_EOC 30        // End of conversion pin PC7

// Constructors ////////////////////////////////////////////////////////////////
APM_BMP085_Class::APM_BMP085_Class()
{
}

// Public Methods //////////////////////////////////////////////////////////////
void APM_BMP085_Class::Init(int initialiseWireLib)
{
  unsigned char tmp;
  char buff[22];
  int i=0;

  pinMode(BMP085_EOC,INPUT);   // End Of Conversion (PC7) input
  
  if( initialiseWireLib != 0 )
      //Wire.begin();
  oss = 3;           // Over Sampling setting 3 = High resolution
  BMP085_State = 0;     // Initial state

  // We read the calibration data registers
  //Wire.beginTransmission(BMP085_ADDRESS);
  //Wire.send(0xAA);
  //Wire.endTransmission();

  //Wire.requestFrom(BMP085_ADDRESS, 22);
  //Wire.endTransmission();
  //while(Wire.available())
  { 
    buff[i] = Wire.receive();  // receive one byte
    i++;
  }
  ac1 = ((int)buff[0] << 8) | buff[1];
  ac2 = ((int)buff[2] << 8) | buff[3];
  ac3 = ((int)buff[4] << 8) | buff[5];
  ac4 = ((int)buff[6] << 8) | buff[7];
  ac5 = ((int)buff[8] << 8) | buff[9];
  ac6 = ((int)buff[10] << 8) | buff[11];
  b1 = ((int)buff[12] << 8) | buff[13];
  b2 = ((int)buff[14] << 8) | buff[15];
  mb = ((int)buff[16] << 8) | buff[17];
  mc = ((int)buff[18] << 8) | buff[19];
  md = ((int)buff[20] << 8) | buff[21];

  //Send a command to read Temp
  Command_ReadTemp();
  BMP085_State=1;
}


// Read the sensor. This is a state machine
// We read one time Temperature (state=1) and then 4 times Pressure (states 2-5)
unsigned int APM_BMP085_Class::Read()
{
unsigned int result=0;

	if (BMP085_State==1)
	{
		//if (digitalRead(BMP085_EOC))
		//{
			ReadTemp();             // On state 1 we read temp
			BMP085_State++;
			//Command_ReadPress();
		//}
	}
	else
	{
		if (BMP085_State==5)
		{
		//	if (digitalRead(BMP085_EOC))
		//	{
				//ReadPress();
				Calculate();
				BMP085_State = 1;    // Start again from state=1
				Command_ReadTemp();  // Read Temp
				result=1;            // New pressure reading
		//	}
		}
		else
		{
			//if (digitalRead(BMP085_EOC))
			//{
				//ReadPress();
				Calculate();
				BMP085_State++;
				//Command_ReadPress();
				result=1;            // New pressure reading
			//}
		}
	}
  return(result);
}


// Send command to Read Pressure
void APM_BMP085_Class::Command_ReadPress()
{
  //Wire.beginTransmission(BMP085_ADDRESS);
  //Wire.send(0xF4);
  //Wire.send((uint8)(0x34+(oss<<6)));  //write_register(0xF4,0x34+(oversampling_setting<<6));
  //Wire.endTransmission();
}

// Read Raw Pressure values
void APM_BMP085_Class::ReadPress()
{
  byte msb;
  byte lsb;
  byte xlsb;

  //Wire.beginTransmission(BMP085_ADDRESS);
  //Wire.send(0xF6);
  //Wire.endTransmission();

  Wire.requestFrom(BMP085_ADDRESS, 3); // read a byte
  //while(!Wire.available()) {
    // waiting
  //}
  //msb = Wire.receive();
  ///while(!Wire.available()) {
    // waiting
  //}
  //lsb = Wire.receive();
  //while(!Wire.available()) {
    // waiting
  //}
  //xlsb = Wire.receive();
  RawPress = (((long)msb<<16) | ((long)lsb<<8) | ((long)xlsb)) >> (8-oss);
}

// Send Command to Read Temperature
void APM_BMP085_Class::Command_ReadTemp()
{
  //Wire.beginTransmission(BMP085_ADDRESS);
  //Wire.send(0xF4);
  //Wire.send(0x2E);
  //Wire.endTransmission();
}

// Read Raw Temperature values
void APM_BMP085_Class::ReadTemp()
{ 
  uint8 tmp;
  uint8 Rawt;
  uint8 ret;
  RawTemp=0;
  //Wire.beginTransmission(BMP085_ADDRESS);
  //Wire.send(0xF6);
  //Wire.endTransmission();

  //Wire.beginTransmission(BMP085_ADDRESS);
  
  //ret=Wire.readOneByte(BMP085_ADDRESS,&Rawt);
  if (ret==0)Serial1.println("OK");
  else
  {
	  Serial1.print("ERROR B1:");
      Serial1.println(ret);
  
  }
	  //while(!Wire.available());  // wait
  //ret=Wire.readOneByte(BMP085_ADDRESS,&tmp);
  if (ret==0)SerialUSB.println("OK");
  else
  {
	  Serial1.print("ERRORB2:");
      Serial1.println(ret);
  
  }
 
  
  /*
  Wire.requestFrom(BMP085_ADDRESS,2);
  while(!Wire.available());  // wait
  Rawt = Wire.receive();
  while(!Wire.available());  // wait
  tmp = Wire.receive();
  */
  Serial1.println((long)Rawt);
  Serial1.println((long)tmp);
  
  RawTemp = (long)(Rawt <<8 | tmp);
  //SerialUSB.println(RawTemp);
  
}

// Calculate Temperature and Pressure in real units.
void APM_BMP085_Class::Calculate()
{
  long x1, x2, x3, b3, b5, b6, p;
  unsigned long b4, b7;
  long tmp;
  
  // See Datasheet page 13 for this formulas
  // Based also on Jee Labs BMP085 example code. Thanks for share.
  // Temperature calculations
  x1 = ((long)RawTemp - ac6) * ac5 >> 15;
  x2 = ((long) mc << 11) / (x1 + md);
  b5 = x1 + x2;
  Temp = (b5 + 8) >> 4;
  //Temp=250; // era un debug che avevo messo per fare alcuni test di volo da rimettere in caso di volo
  // Pressure calculations
  b6 = b5 - 4000;
  x1 = (b2 * (b6 * b6 >> 12)) >> 11; 
  x2 = ac2 * b6 >> 11;
  x3 = x1 + x2;
  //b3 = (((int32_t) ac1 * 4 + x3)<<oss + 2) >> 2; // BAD
  //b3 = ((int32_t) ac1 * 4 + x3 + 2) >> 2;  //OK for oss=0
  tmp = ac1;
  tmp = (tmp*4 + x3)<<oss;
  b3 = (tmp+2)/4;
  x1 = ac3 * b6 >> 13;
  x2 = (b1 * (b6 * b6 >> 12)) >> 16;
  x3 = ((x1 + x2) + 2) >> 2;
  b4 = (ac4 * (unsigned long) (x3 + 32768)) >> 15;
  b7 = ((unsigned long) RawPress - b3) * (50000 >> oss);
  p = b7 < 0x80000000 ? (b7 * 2) / b4 : (b7 / b4) * 2;
  
  x1 = (p >> 8) * (p >> 8);
  x1 = (x1 * 3038) >> 16;
  x2 = (-7357 * p) >> 16;
  Press = p + ((x1 + x2 + 3791) >> 4);
}

// Constructors ////////////////////////////////////////////////////////////////
APM_BMP085_HIL_Class::APM_BMP085_HIL_Class()
{
}

// Public Methods //////////////////////////////////////////////////////////////
void APM_BMP085_HIL_Class::Init(int initialiseWireLib)
{
  BMP085_State=1;
}


// Read the sensor. This is a state machine
// We read one time Temperature (state=1) and then 4 times Pressure (states 2-5)
unsigned int APM_BMP085_HIL_Class::Read()
{
    unsigned int result=0;

	if (BMP085_State==1)
	{
        BMP085_State++;
	}
	else
	{
		if (BMP085_State==5)
		{
            BMP085_State = 1;    // Start again from state=1
            result=1;            // New pressure reading
		}
		else
		{
            BMP085_State++;
            result=1;            // New pressure reading
		}
	}
    return(result);
}

void APM_BMP085_HIL_Class::setHIL(float _Temp, float _Press)
{
    // TODO: map floats to raw
    Temp = _Temp;
    Press = _Press;
}
