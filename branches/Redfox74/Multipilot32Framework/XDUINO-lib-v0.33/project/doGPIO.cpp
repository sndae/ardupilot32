/******************************************************************
*  Copyright (C) 2009 Ram Narula <ram@pluslab.com> 
*  Filename: doGPIO.cpp
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
#include "doGPIO.h"
#include "defineName.h"

doGPIO::doGPIO(u8 Pxn, GPIOMode_TypeDef GPIOMode_) :
	GPIOMode(GPIOMode_)
{
  defineName myPin;
  myPin.getPin(Pxn);
  doGPIO(myPin.GPIObank, myPin.GPIOPin, GPIOMode);
}



doGPIO::doGPIO(GPIO_TypeDef* GPIObank_, u16 GPIOPin_,GPIOMode_TypeDef GPIOMode_) :
	GPIObank(GPIObank_), GPIOPin(GPIOPin_), GPIOMode(GPIOMode_)
{

  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIOMode;
  GPIO_InitStructure.GPIO_Pin = GPIOPin;
  GPIO_Init(GPIObank, &GPIO_InitStructure); 

}

void doGPIO::High(void)
{
GPIObank->BSRR |= GPIOPin;
} 

void doGPIO::Low(void)
{
GPIObank->BRR |= GPIOPin;
} 

void doGPIO::Toggle(void)
{
	(GPIObank->IDR & GPIOPin)?GPIObank->BRR|=GPIOPin:GPIObank->BSRR|=GPIOPin;
}

bool doGPIO::Read(void)
{
	 return (bool)(GPIObank->IDR & GPIOPin);
}

