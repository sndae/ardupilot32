/******************************************************************
*  Copyright (C) 2009 Ram Narula <ram@pluslab.com> 
*  Filename: doEXTI.cpp
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
#include "doEXTI.h"
#include "defineName.h"

// Initialize the static variable
u32 doEXTI::EXTI_Enabled_Lines;


doEXTI::doEXTI(u8 Pxn_) : Pxn(Pxn_)
{
} 

void doEXTI::setMode(EXTIMode_TypeDef mode_)
{
	//mode=mode_;
	EXTI_InitStructure.EXTI_Mode=mode_;
}

void doEXTI::setTrigger(EXTITrigger_TypeDef trigger_)
{
	//trigger=trigger_;
	EXTI_InitStructure.EXTI_Trigger=trigger_;
}

void doEXTI::setIRQHandler(void(*IRQ_Function)())
{
	defineName myPin;
	myPin.getPin(Pxn);
	EXTI_Function_Pointer[myPin.PinNumber]=IRQ_Function;
}

void doEXTI::Enable(void)
{
	defineName myPin;
	myPin.getPin(Pxn);
	GPIO_EXTILineConfig(myPin.GPIObankSource, myPin.GPIOPinSource);
	EXTI_InitStructure.EXTI_Line=myPin.EXTI_Linex;
	//EXTI_InitStructure.EXTI_Mode=mode;
	//EXTI_InitStructure.EXTI_Trigger=trigger;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	// Save current Lines state
	EXTI_Enabled_Lines|=myPin.EXTI_Linex;
}

void doEXTI::Disable(void)
{
	//EXTI_InitStructure.EXTI_LineCmd=DISABLE;
	//EXTI_Init(&EXTI_InitStructure);
	defineName myPin;
	myPin.getPin(Pxn);
	EXTI->IMR &= ~((0x00000001) << myPin.PinNumber);

	// Save current Lines state
	EXTI_Enabled_Lines|=myPin.EXTI_Linex;

}


// Static members
void doEXTI::EnableAll(void)
{
	// Enable saved Lines state
	EXTI->IMR |= EXTI_Enabled_Lines;
}
void doEXTI::DisableAll(void)
{
	EXTI_Enabled_Lines=EXTI-> IMR;	// Save Lines state before disabling
	EXTI->IMR &= ~(0x0000FFFF);		// Disable all interrupts
	EXTI->PR   =   0x0000FFFF;		// Clear all pending interrupt flags
}



