/******************************************************************
*  Copyright (C) 2009 Ram Narula <ram@pluslab.com> 
*  Filename: XDUINO.cpp
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
#include "XDUINO.h"

// GPIO Pin
GPIO_TypeDef* const GPIOBANKS[] = define_GPIOBANKS;
const u16 GPIOPINS[]=define_GPIOPINS;
const u8  GPIOBANKS_SOURCE[] = define_GPIOBANKS_SOURCE;
const u8  GPIOPINS_SOURCE[] = define_GPIOPINS_SOURCE;
const u32 GPIO_RCC_APBxPERIPHS[] = define_GPIO_RCC_APBxPERIPHS;

// ADC	  
const u8  ADC_PINS[] = define_ADC_PINS;	
const u8  ADC_CHANNELS[] = define_ADC_CHANNELS;

// DAC
const u8  DAC_PINS[] = define_DAC_PINS;
const u32 DAC_CHANNELS[] = define_DAC_CHANNELS;

// UxARTs
USART_TypeDef* const UxARTS[] = define_UxARTS;	
const u8  UxART_RX_PINS[] = define_UxART_RX_PINS;
const u32 UxART_TX_PINS[] = define_UxART_TX_PINS;
const u32 UxARTS_RCC_APBxPERIPHS[] = define_UxARTS_RCC_APBxPERIPHS;

// GPIO Pin interrupt
const u32 EXTI_LINES[] = define_EXTI_LINES;


