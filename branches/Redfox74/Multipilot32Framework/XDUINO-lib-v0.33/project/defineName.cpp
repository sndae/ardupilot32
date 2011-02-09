/******************************************************************
*  Copyright (C) 2009 Ram Narula <ram@pluslab.com> 
*  Filename: definePin.cpp
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
#include "defineName.h"

void defineName::getPin(u8 Pxn)
{

	GPIObank=GPIOBANKS[((Pxn & 0xF0) >> 4)-1]; // Subtract one as there GPIOA = 0 not 1	
	GPIOPin=GPIOPINS[ (Pxn & 0x0F) ];

	GPIObankSource=GPIOBANKS_SOURCE[((Pxn & 0xF0) >> 4)-1]; // Subtract 1 as GPIOA=0
	GPIOPinSource=GPIOPINS_SOURCE[ (Pxn & 0x0F) ];

	GPIO_RCC_APBxPeriph=GPIO_RCC_APBxPERIPHS[((Pxn & 0xF0) >> 4)-1];

	EXTI_Linex=::EXTI_LINES[(Pxn & 0x0F)];
	PinNumber=(Pxn & 0x0F);
	PinBankNumber=((Pxn & 0xF0) >> 4);
}

void defineName::getADCchannel(u8 myChannel)
{

ADC_Pin=ADC_PINS[myChannel];			// pin name from channel number
getPin(ADC_Pin);						// translate pin to GPIOx and GPIO_PIN_x
ADC_Channel=ADC_CHANNELS[myChannel];	// channel name

}


void defineName::getDACchannel(u8 myChannel)
{

DAC_Pin=DAC_PINS[myChannel-1];			// pin name from 1 so subtract 1
getPin(DAC_Pin);						// translate pin to GPIOx and GPIO_PIN_x
DAC_Channel=DAC_CHANNELS[myChannel-1];	// channel name start from 1 so subtract 1 

}

void defineName::getUxART(u8 port)
{

defineName my_Pin;

my_Pin.getPin(UxART_RX_PINS[port-1]);
UxART_Rx_Pin=my_Pin.GPIOPin;
UxART_Rx_Bank=my_Pin.GPIObank;
UxART_Rx_GPIO_RCC_APBxPeriph=my_Pin.GPIO_RCC_APBxPeriph;

my_Pin.getPin(UxART_TX_PINS[port-1]);
UxART_Tx_Pin=my_Pin.GPIOPin;
UxART_Tx_Bank=my_Pin.GPIObank;
UxART_Tx_GPIO_RCC_APBxPeriph=my_Pin.GPIO_RCC_APBxPeriph;

UxARTxName=UxARTS[port-1];
UxARTx_RCC_APBxPeriph=UxARTS_RCC_APBxPERIPHS[port-1];

}



