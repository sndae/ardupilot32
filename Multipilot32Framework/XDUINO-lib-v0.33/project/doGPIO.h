/******************************************************************
*  Copyright (C) 2009 Ram Narula <ram@pluslab.com> 
*  Filename: doGPIO.h
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
#ifndef doGPIO_h
#define doGPIO_h

#include "XDUINO.h"
  
// GPIO interfacing creation and manipulation of GPIO Pin objects
class doGPIO
{
  public:
  // variables
    int error;
	GPIO_TypeDef* GPIObank;	
	u16 GPIOPin; 
	GPIOMode_TypeDef GPIOMode;

  // methods
    doGPIO(GPIO_TypeDef* GPIObank_, u16 GPIOPin_, GPIOMode_TypeDef GPIOMode_);
	doGPIO(u8 Pxn, GPIOMode_TypeDef GPIOMode_);
    void High(void);
    void Low(void);
	void Toggle(void);
	bool Read(void);

  private:					   
  // variables
  	GPIO_InitTypeDef GPIO_InitStructure;
};

#endif


