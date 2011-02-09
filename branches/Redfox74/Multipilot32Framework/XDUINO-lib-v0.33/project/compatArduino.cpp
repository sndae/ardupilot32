/******************************************************************
*  Copyright (C) 2009 Ram Narula <ram@pluslab.com> 
*  Filename: compatArduino.cpp
*  Version: 0.3
*  Date: 05 August 2009
*  Information: http://www.xduino.com/    
******************************************************************/
/******************************************************************
*   This file is part of XDUINO-lib
*
*   XDUINO-lib is free software: you can redistribute it and/or modify
*   it under the terms of the GNU Lesser General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*	
*   XDUINO-lib is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU Lesser General Public License for more details.
*
*   You should have received a copy of the GNU Lesser General Public License
*   along with XDUINO-lib.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************/
#include "compatArduino.h"
#include "doGPIO.h"
#include "defineName.h"
#include "doADC.h"
#include "doDAC.h"
#include "doEXTI.h"
#include "doTime.h"
#include "stdlib.h" // for Random related functions

// ## BEGIN namespace compatArduino
namespace compatArduino {

//GPIO stuff
void pinMode(u8 Pxn,GPIOMode_TypeDef GPIOMode)
{
	defineName	myPin;
	myPin.getPin(Pxn);
	doGPIO		myGPIOPin=doGPIO(myPin.GPIObank,myPin.GPIOPin,GPIOMode);
}

void digitalWrite(u8 Pxn,bool data)
{
	
	defineName	myPin;
	myPin.getPin(Pxn);
	(data)?myPin.GPIObank->BSRR|=myPin.GPIOPin:myPin.GPIObank->BRR|=myPin.GPIOPin;
}

bool digitalRead(u8 Pxn)
{
	defineName	myPin;
	myPin.getPin(Pxn);
	return (bool)(myPin.GPIObank->IDR & myPin.GPIOPin);
}

void digitalToggle(u8 Pxn)
{
	defineName	myPin;
	myPin.getPin(Pxn);
	(myPin.GPIObank->IDR & myPin.GPIOPin)?myPin.GPIObank->BRR|=myPin.GPIOPin:myPin.GPIObank->BSRR|=myPin.GPIOPin;
}


// ADC stuff
u16 analogRead(u8 ADC_channel_number)
{
	doADC	myADC=doADC(ADC1,ADC_channel_number);
	return	myADC.Read(ADC_SampleTime_1Cycles5);
}	

// DAC stuff
void analogWrite(u8 DAC_channel_number,u16 myOutputData)
{
	doDAC	myDAC=doDAC(DAC_channel_number);
	myDAC.Write(myOutputData);
}	

u16 analogLastWrite(u8 DAC_channel_number)
{
	doDAC	myDAC=doDAC(DAC_channel_number);
	return	myDAC.LastWrite();
}

// EXTI (digital interrupt) stuff
void attachInterrupt(u8 Pxn,void(*IRQ_Function)(), EXTITrigger_TypeDef InterruptTrigger)
{
	doEXTI EXTILine=doEXTI(Pxn);
	EXTILine.setIRQHandler(IRQ_Function);
	EXTILine.setMode(EXTI_Mode_Interrupt);
	EXTILine.setTrigger(InterruptTrigger);
	EXTILine.Enable();
}

void detachInterrupt(u8 Pxn)
{
	doEXTI EXTILine=doEXTI(Pxn);
	EXTILine.Disable();	
}	

void interrupts(void)
{
	doEXTI::EnableAll();
}

void noInterrupts(void)
{
	doEXTI::DisableAll();
}


// simple SPI emulation
void shiftOut(u8 PxnDataOut,u8 PxnClock,bool BitOrder,u8 Data)
{
	digitalWrite(PxnClock,LOW);
	for(int i=0;i<=7;i++)
	{
		if(BitOrder == LSBFIRST)  
		{
			digitalWrite(PxnDataOut,((Data >> i) & 0x01)?HIGH:LOW);
		} else {
			digitalWrite(PxnDataOut,((Data >> (7-i)) & 0x01)?HIGH:LOW);			
		}
		digitalWrite(PxnClock,HIGH);
		digitalWrite(PxnClock,LOW);
	}
	digitalWrite(PxnDataOut,LOW);
}

// Function to check pulse time
u32 pulseIn(u8 Pxn,bool startState,u32 TimeOut)
{
	vu32 startTime,stopTime,PulseStartTime;
	startTime=micros();
	while(digitalRead(Pxn)!=startState && (micros()-startTime < TimeOut));
	PulseStartTime=micros();
	while((!(TimeOut) || (micros()-startTime < TimeOut)) && (digitalRead(Pxn)==startState));
	stopTime=micros();
	return ((micros()-startTime)>=TimeOut?0:stopTime-PulseStartTime);
}


// Timing related functions
u32 micros(void)
{
	return SystemUptime_uS();
}

u32 millis(void)
{
	return SystemUptime_mS();
}

void delay(u32 milliSec)
{
	delay_mS(milliSec);
}

void delayMicroseconds(u32 microSec)
{
	delay_uS(microSec);
}

void pause(u32 milliSec)
{
	pause_mS(milliSec);
}

void pauseMicroseconds(u32 microSec)
{
	pause_uS(microSec);
}

// Random number related functions
void randomSeed(u32 seed)
{
	if(seed=='\0')
	{
		srand(micros()+sq(analogRead(16))); // use uptime and temperature sensor
	} else {
		srand(seed);
	}
}

s32 random(s32 param1,s32 param2)
{
	s32 min=param1,max=param2;
	if(param2=='\0') { min=0; max=param1; }
	return map(rand(),0,RAND_MAX-1,min,max);
}

} 
// ## END namespace compatArduino
