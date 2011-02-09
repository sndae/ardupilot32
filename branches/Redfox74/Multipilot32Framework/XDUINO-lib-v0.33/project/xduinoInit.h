/******************************************************************
*  Copyright (C) 2009 Ram Narula <ram@pluslab.com> 
*  Filename: generalInit.h
*  Version: 0.31
*  Date: 06 August 2009
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
#ifndef xduinoInit_h
#define xduinoInit_h

#include "XDUINO.h"
#include "doGPIO.h"
#include "doADC.h"
#include "doDAC.h"
#include "doSerial.h"
#include "doEXTI.h"
#include "doTime.h"
#include "compatArduino.h"

typedef unsigned char           byte;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef signed char int8;
typedef short int16;
typedef int int32;
typedef long long int64;
typedef char boolean;

typedef void (*voidFuncPtr)(void);
typedef int8 int8_t;
typedef uint8 uint8_t;

// ADD .h LIB HERE

#include "..\Wire\wire.h"



#define __io volatile

#define ALWAYS_INLINE inline __attribute__((always_inline))

#ifndef NULL
#define NULL 0
#endif


using namespace compatArduino;


// function prototype
void doInit(void);
void NVIC_Init_Interrupt(void);
void SysTick_Init(void);

// SERIAL PORTs Arduino style
extern doSerial Serial1;
extern doSerial Serial2;
extern doSerial Serial3;
extern doSerial Serial4;
extern doSerial Serial5;
// END SERIAL PORTs
// I2C Port
extern TwoWire Wire;

#endif
