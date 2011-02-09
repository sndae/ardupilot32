/******************************************************************
*  Copyright (C) 2009 Ram Narula <ram@pluslab.com>,<ram@xduino.com> 
*  Filename: compatArduino.h
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
#ifndef compatArduino_h
#define compatArduino_h

#include "XDUINO.h"

namespace compatArduino {

// General function protypes
// pin mode
void pinMode(u8 Pxn,GPIOMode_TypeDef GPIOMode);

// digital commands
void digitalWrite(u8 Pxn,bool data);
bool digitalRead(u8 Pxn);
void digitalToggle(u8 Pxn);

// ADC
u16 analogRead(u8 ADC_channel_number);

// DAC
void analogWrite(u8 DAC_channel_number,u16 myOutputData);
u16 analogLastWrite(u8 DAC_channel_number);

// GPIO Pin high/low interrupt
void attachInterrupt(u8 Pxn,void(*IRQ_Function)(), EXTITrigger_TypeDef InterruptTrigger);
void detachInterrupt(u8 Pxn);
void interrupts(void);
void noInterrupts(void);

// simple SPI functionality emulation output only, without latch
void shiftOut(u8 PxnDataOut,u8 PxnClock,bool BitOrder,u8 Data);

// simple function to retrieve time when Pxn changes state 
u32 pulseIn(u8 Pxn,bool startState,u32 TimeOut=0);


// timing related function
u32 micros(void);
u32 millis(void);
void delay(u32 milliSec);
void delayMicroseconds(u32 microSec);
// pause can be used in interrupt and does approximate delay
void pause(u32 milliSec);
void pauseMicroseconds(u32 microSec);



// Random number
void randomSeed(u32 seed='\0');
s32 random(s32 param1,s32 param2='\0');

// map() and constrain() is in define macro of XDuino.h
}


#endif

