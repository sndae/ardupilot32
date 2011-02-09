/******************************************************************
*  Copyright (C) 2009 Ram Narula <ram@pluslab.com> 
*  Filename: doEXTI.h
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
#ifndef	doEXTI_h
#define	doEXTI_h

#include "XDUINO.h"

typedef void(*Function_Pointer_Array)(void);
extern Function_Pointer_Array EXTI_Function_Pointer[];

class doEXTI
{
  public:
  // variables
	static u32 EXTI_Enabled_Lines;
  	u8  Pxn;
	

  // methods
  	doEXTI(u8 Pxn_); 
	void setMode(EXTIMode_TypeDef mode_);
	void setTrigger(EXTITrigger_TypeDef trigger_);
	void setIRQHandler(void(*IRQ_Function)());
	void Enable(void);
	void Disable(void);
	static void EnableAll(void);
	static void DisableAll(void);

	
  private:
  	EXTI_InitTypeDef EXTI_InitStructure;
	//EXTIMode_TypeDef mode;
	//EXTITrigger_TypeDef trigger;

};

#endif


