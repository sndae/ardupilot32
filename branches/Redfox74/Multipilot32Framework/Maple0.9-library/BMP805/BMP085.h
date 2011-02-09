/****************************************************************************
* BMP085.h - BMP085/I2C (Digital Pressure Sensor) library for Arduino				*
* Copyright 2010 Filipe Vieira 																							*
* 																																					*
* This file	is part of BMP085 Arduino library.															*
*																																						*
* This library is free software: you can redistribute it and/or modify			*
* it under the terms of the GNU Lesser General Public License as published	*
* by the Free Software Foundation, either version 3 of the License, or			*
* (at your option) any later version.																				*
*																																						*
* This program is distributed in the hope that it will be useful,						*
* but WITHOUT ANY WARRANTY; without even the implied warranty of						*
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the							*
* GNU Lesser General Public License for more details.												*
*																																						*
* You should have received a copy of the GNU Lesser General Public License	*
* along with this program.  If not, see <http://www.gnu.org/licenses/>.			*
****************************************************************************/
/****************************************************************************
*	Tested on Arduino Mega with BMP085 Breakout																*
*	SDA 		-> pin 20			(no pull up resistors)															*
*	SCL 		-> pin 21			(no pull up resistors)															*
*	XCLR 		-> not connected																									*
*	EOC 		-> not connected 																									*
*	GND 		-> pin GND																												*
*	VCC			-> pin 3.3V 																											*
* NOTE: SCL and SDA needs pull-up resistors for each I2C bus. 							*
*		2.2kOhm..10kOhm, typ. 4.7kOhm																						*
*****************************************************************************/
#ifndef BMP085_h
#define BMP085_h

#include "WProgram.h"

#define BMP085_DEFAULT_ADDR				0x77   	//0x77 default I2C address
#define BUFFER_SIZE								3

#define AUTO_UPDATE_TEMPERATURE 	true		//default is true
				// when true, temperature is measured everytime pressure is measured (Auto).
				// when false, user chooses when to measure temperature (just call calcTrueTemperature()).
				// used for dynamic measurement to increase sample rate (see BMP085 modes below).
				
/* ---- Registers ---- */
#define CAL_AC1					0xAA  // R   Calibration data (16 bits)
#define CAL_AC2					0xAC  // R   Calibration data (16 bits)
#define CAL_AC3					0xAE  // R   Calibration data (16 bits)  	
#define CAL_AC4					0xB0  // R   Calibration data (16 bits)
#define CAL_AC5					0xB2  // R   Calibration data (16 bits)
#define CAL_AC6					0xB4  // R   Calibration data (16 bits)
#define CAL_B1					0xB6  // R   Calibration data (16 bits)
#define CAL_B2					0xB8  // R   Calibration data (16 bits)
#define CAL_MB					0xBA  // R   Calibration data (16 bits)
#define CAL_MC					0xBC  // R   Calibration data (16 bits)
#define CAL_MD					0xBE  // R   Calibration data (16 bits)
#define CONTROL					0xF4  // W   Control registor 
#define CONTROL_OUTPUT	0xF6  // R   Output registers 0xF6=MSB, 0xF7=LSB, 0xF8=XLSB

/************************************/
/*		REGISTERS PARAMETERS					*/
/************************************/
// BMP085 Modes
#define MODE_ULTRA_LOW_POWER		0 //oversampling=0, internalsamples=1, maxconvtimepressure=4.5ms, avgcurrent=3uA, RMSnoise_hPA=0.06, RMSnoise_m=0.5
#define MODE_STANDARD						1 //oversampling=1, internalsamples=2, maxconvtimepressure=7.5ms, avgcurrent=5uA, RMSnoise_hPA=0.05, RMSnoise_m=0.4
#define MODE_HIGHRES						2 //oversampling=2, internalsamples=4, maxconvtimepressure=13.5ms, avgcurrent=7uA, RMSnoise_hPA=0.04, RMSnoise_m=0.3
#define MODE_ULTRA_HIGHRES			3 //oversampling=3, internalsamples=8, maxconvtimepressure=25.5ms, avgcurrent=12uA, RMSnoise_hPA=0.03, RMSnoise_m=0.25
									// "Sampling rate can be increased to 128 samples per second (standard mode) for
									// dynamic measurement.In this case it is sufficient to measure temperature only 
									// once per second and to use this value for all pressure measurements during period."
									// (from BMP085 datasheet Rev1.2 page 10).
									// To use dynamic measurement set AUTO_UPDATE_TEMPERATURE to false and
                  // call calcTrueTemperature() from your code. 
// Control register
#define READ_TEMPERATURE				0x2E 
#define READ_PRESSURE						0x34 

//Other
#define MSLP										1013.25	        // Mean Sea Level Pressure = 1013.25 hPA



class BMP085 {
public:	
	BMP085();
	
	// BMP initialization
	void init();    															            // sets current elevation above ground level to 0 meters
	void init(byte _BMPMode, float _initVal, bool _meters);		// sets a reference datum
                                                            // if _meters=false _initVal is hPa

	// Who Am I
	byte getDevAddr();
	
	// BMP mode	
	byte getMode();				
	void setMode(byte _BMPMode); 									// BMP085 mode
	
	// initialization
	void setLocalPressure(float _hPa);  					// set known barometric pressure as reference Ex. QNH
	void setLocalAbsAlt(float _meters);						// set known altitude as reference
	void setAltOffset(float _meters);							// altitude offset
	void sethPaOffset(float _hPa);								// pressure offset
	void zeroCal(float _hPa, float _meters);				// zero Calibrate output to a specific hPa/altitude 
	
	// BMP Sensors
	void getPressure(float *_hPa);								// pressure in hPa + offset	
	void getAltitude(float *_meters);  						// altitude in meters + offset	
	void getTemperature(float *_Temperature);			// temperature in C� 
	
	void calcTrueTemperature();										// calc temperature data b5 (only needed if AUTO_UPDATE_TEMPERATURE is false)	
	void calcTruePressure(long *_TruePressure);		// calc Pressure in Pa 
		
	// dummy stuff
	void dumpRegisters();													// debug only
	void dumpCalData();														// debug only

private:
	int ac1,ac2,ac3,b1,b2,mb,mc,md;								// cal data	
	unsigned int ac4,ac5,ac6;											// cal data
	long b5;																			// temperature data
	
	int _dev_address;
	byte _buff[BUFFER_SIZE]; 											// buffer  MSB LSB XLSB
	byte _oss;																		// OverSamplingSetting
	int _pressure_waittime[4];										// Max. Conversion Time Pressure is ms for each mode
	
	float _meter_Offset, _hPa_Offset;
	float _param_datum, _param_meters;

	void getCalData();				
	
	void writemem(byte _addr, byte _val);
	void readmem(byte _addr, int _nbytes, byte __buff[]);
};
/* dummy stuff */
void print_bits(byte val);
//void print_unit16(uint16_t val);
#endif