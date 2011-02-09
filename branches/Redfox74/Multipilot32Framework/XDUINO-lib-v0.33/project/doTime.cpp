/******************************************************************
*  Copyright (C) 2009 Ram Narula <ram@pluslab.com> 
*  Filename: doTime.h
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
#include "doTime.h"

void delay_mS(u32 milliSec)
{
 
	// SysTick_Target = SystemUptime in ticks + milliSec in ticks + (ResetCounter-SysTick_GetCounter)
	// then simplifying the above gives the followings:
	// Note that the SysTick counter count downwards
	
	SysTick_Use_Counter=0;
	const u32 SysTick_Target=(define_SYSTICK_REFRESH*(SysTick_Use_Counter+1))
							  + (milliSec * define_TICKS_1mS)
							  - SysTick_GetCounter(); 
	while((define_SYSTICK_REFRESH*(SysTick_Use_Counter+1))-SysTick_GetCounter()< SysTick_Target);
}	

void delay_uS(u32 microSec)
{
	// See the above delay() function note
	
	SysTick_Use_Counter=0;
	const u32 SysTick_Target=(define_SYSTICK_REFRESH*(SysTick_Use_Counter+1))
							  + (microSec * define_TICKS_1uS)
							  - SysTick_GetCounter(); 
	while((define_SYSTICK_REFRESH*(SysTick_Use_Counter+1))-SysTick_GetCounter()< SysTick_Target);	
	
}	

void pause_mS(u32 approxms)
{
	// pause(x) delay for APPROXIMATELY x milliseconds, works within interrupt
	volatile unsigned int i=40*approxms;
	volatile unsigned short j;
	while(i--) for(j=0;j<200;j++);
}

void pause_uS(u32 approxus)
{
	// pause(x) delay for APPROXIMATELY x microseconds, works within interrupt
	vu32 i=approxus*10;
	while(i--);
}

u32 SystemUptime_mS()
{
	// Simplification from SystemUptime + current count on SysTick_GetCounter();
	return ((define_SYSTICK_REFRESH*(SystemUptime+1))-SysTick_GetCounter())/define_TICKS_1mS;
}

u32 SystemUptime_uS()
{
	return ((define_SYSTICK_REFRESH*(SystemUptime+1))-SysTick_GetCounter())/define_TICKS_1uS;
	
}


