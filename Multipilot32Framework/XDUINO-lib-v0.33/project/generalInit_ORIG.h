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
#ifndef generalInit_h
#define generalInit_h

#include "STMicro.h"


// function prototype
void doInit(void);
void NVIC_Init_Interrupt(void);
void SysTick_Init(void);

// SERIAL PORTs Arduino style
doSerial Serial1=doSerial(1);
doSerial Serial2=doSerial(2);
doSerial Serial3=doSerial(3);
doSerial Serial4=doSerial(4);
doSerial Serial5=doSerial(5);
// END SERIAL PORTs

// END SERIAL PORTs

void doInit(void)
{




	// General initialization
	RCC_Configuration();   
	NVIC_Configuration();
	
	// Start different clocks
	RCC_APB2PeriphClockCmd(define_RCC_APB2PERIPH_START, ENABLE);
	
	// Enable interrupts 
	NVIC_Init_Interrupt();

	// Enable SysTick for timing functions
 	SysTick_Init();

	// Enable ADC1 (for Arduino style of no init for analogRead() 
  	RCC_ADCCLKConfig(RCC_PCLK2_Div6);		// 72MHz/6=12 MHz range must be 0.6-14MHz
	doADC::Setup(ADC1);
	doADC::StartTemperatureSensor();	// start built in temperature sensor (analog channel 16)

	// Enable DAC channel 1&2 (for Arduino style of no init for analogWrite()
	DAC_DeInit();
	doDAC::Setup(DAC_Channel_1);
	doDAC::Setup(DAC_Channel_2);

	// Serial Buffer assignment, default RxBufferSize=128 TxBufferSize=0 (no buffer)
	Serial1.RxBufferSize=RXBUFFERSIZE;
	Serial1.TxBufferSize=TXBUFFERSIZE;
}

void NVIC_Init_Interrupt(void)
{

	NVIC_InitTypeDef NVIC_InitStructure;

	const u8 NVIC_IRQCHANNELS[] = define_NVIC_IRQCHANNELS;
	const u8 NVIC_IRQ_PREEMPTION_PRIORITY[] = define_NVIC_IRQ_PREEMPTION_PRIORITY; 
 	
	// Set Priority grouping 3 bits for pre-emption and 1 bit for subpriority
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);

	for(int i=0;i<define_NVC_IRQCHANNELS_n;i++)
	{
	NVIC_InitStructure.NVIC_IRQChannel = NVIC_IRQCHANNELS[i];
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQ_PREEMPTION_PRIORITY[i];
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	}
	
}

void SysTick_Init(void)
{
	SysTick_CLKSourceConfig(define_SYSTICK_CLKSOURCE_SPEED);
	SysTick_SetReload(define_SYSTICK_REFRESH);		// Interrupting every SYSTICK_REFRESH
	SysTick_ITConfig(ENABLE);						// Enable Interrupt
	SysTick_CounterCmd(SysTick_Counter_Enable); 	// Start SysTick
}


#endif

