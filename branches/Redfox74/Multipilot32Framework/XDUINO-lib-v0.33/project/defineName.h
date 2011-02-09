/******************************************************************
*  Copyright (C) 2009 Ram Narula <ram@pluslab.com> 
*  Filename: definePin.cpp
*  Version: 0.11
*  Date: 16 July 2009
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
// load this library only once
#ifndef	defineName_h
#define	defineName_h

#include "XDUINO.h"

class defineName
{
  public:
  // variables
	u8	PinNumber;
	u8	PinBankNumber;
  	GPIO_TypeDef* GPIObank;
	u16 GPIOPin;
	u8  ADC_Pin;
	u8  ADC_Channel;
	u8  DAC_Pin;
	u32 DAC_Channel;
	u8	GPIObankSource;
	u8	GPIOPinSource;
	u32				GPIO_RCC_APBxPeriph;
	u16				UxART_Rx_Pin;
	GPIO_TypeDef*	UxART_Rx_Bank;
	u32				UxART_Rx_GPIO_RCC_APBxPeriph;
	u16				UxART_Tx_Pin;
	GPIO_TypeDef*	UxART_Tx_Bank;
	u32				UxART_Tx_GPIO_RCC_APBxPeriph;
	USART_TypeDef*	UxARTxName;
	u32				UxARTx_RCC_APBxPeriph;
	u32				EXTI_Linex;
	

  // methods
	void getPin(u8 Pxn);
	void getADCchannel(u8 myChannel);
	void getDACchannel(u8 myChannel);
	void getUxART(u8 port);
	//void getEXTI_Line(u8 line);

  private:

};

#endif
