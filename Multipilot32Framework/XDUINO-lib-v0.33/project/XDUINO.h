/******************************************************************
*  Copyright (C) 2009 Ram Narula <ram@pluslab.com>,<ram@xduino.com>
*  Filename: XDUINO.h
*  Version: 0.33
*  Date: 03 September 2009
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
#ifndef XDUINO_h
#define XDUINO_h

#define XDUINO_VERSION 0.33

// all UxARTs default Rx & Tx buffer size (0=direct communication without buffer)
// This setting can be changed by setting RxBufferSize variable of Serialx object
// for example for setting Rx Buffer to 5 bytes and no Tx Buffer for USART1
//     Serial1.RxBufferSize=5;
//     Serial1.TxBufferSize=0;
// Note: settings should be done before calling Serial1.begin();

#define RXBUFFERSIZE 128
#define TXBUFFERSIZE 0


// default max output string length for Serial printf function
// this has nothing todo with Rx Tx buffersize above
#define SERIAL_PRINTF_SIZE 200



/*****************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE
// UNLESS YOU KNOW WHAT YOU ARE DOING
******************************************************************/

// Include stm32 header library in C style
extern "C" {
#include "stm32f10x_lib.h"
#include "stm32f10x_dac.h"
}


// SysTick
// With SysTick_CLKSource_HCLK_Div8 9ticks=1mS 9000ticks=1uS
// eg. MCU runs at 72MHz Div8 becomes 9Ticks/microsecond
#define define_SYSTICK_CLKSOURCE_SPEED SysTick_CLKSource_HCLK_Div8
#define	define_TICKS_1uS	9
#define define_TICKS_1mS	9000
#define define_TICKS_1S		9000000
// Setting SysTick interrupt rate to 1 Second is alright setting,
// lower settings will take more processing power
// the highest possible value is 0x00FFFFFF
#define define_SYSTICK_REFRESH	define_TICKS_1S

// Arduino keyword compatibility
#define  INPUT        GPIO_Mode_IN_FLOATING
#define  OUTPUT       GPIO_Mode_Out_PP
#define  ANALOGOUTPUT  GPIO_Mode_AIN
#define  ANALOGINPUT  GPIO_Mode_AIN

#define XDUINO_ARD_COMPAT_BEGIN using namespace compatArduino;
#define XDUINO_ARD_COMPAT_END int main(){doInit();setup();for (;;)loop();return 0;}

// For digital commands
#define HIGH 1
#define LOW 0

// For interrupt commands
#define	CHANGE		   EXTI_Trigger_Rising_Falling
#define	RISING		   EXTI_Trigger_Rising
#define	FALLING		   EXTI_Trigger_Falling

// For shiftOut	command
#define LSBFIRST		0
#define MSBFIRST		1

// General function - no external variable involved
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define map(x,inMin,inMax,outMin,outMax) ((((inMax)-(inMin))>((outMax)-(outMin)))?\
					((((x)-(inMin))/(((inMax)-(inMin))/((outMax)-(outMin))))+(outMin)):\
					((((x)-(inMin))*(((outMax)-(outMin))/((inMax)-(inMin))))+(outMin))\
					)
#define constrain(x,low,high) ((((x)>=(low))&&((x)<=(high)))?(x):((x)>(high)?(high):(low)))
#define sq(x) ((x)*(x))

// Bit wise functions
#define lowByte(x) ((x)&0x00FF)
#define highByte(x) ((x)>>8)
#define bitRead(x,nbit) (((x)>>(nbit)) & 1)
#define bitWrite(x,nbit,b) (((((x)>>(nbit)) & 1) == (b))?(x):(x)^=(0x01<<(nbit)))
#define bitSet(x,nbit) ((x) |= (1<<(nbit)))
#define bitClear(x,nbit) ((x) &= ~(1<<(nbit)))
#define bit(x) (1<<(x))

//#define abs(x) ((x)<0?-(x):(x)) // can be used if not including math.h


//board has pins upto GPIOD and ADC2 if your board has more you can add more lines
#define define_RCC_APB2PERIPH_START RCC_APB2Periph_GPIOA | \
			RCC_APB2Periph_GPIOB |				   \
			RCC_APB2Periph_GPIOC |				   \
			RCC_APB2Periph_GPIOD |				   \
			RCC_APB2Periph_AFIO  |				   \
			RCC_APB2Periph_ADC1  |				   \
			RCC_APB2Periph_ADC2  				   
		


#define define_GPIOBANKS	{	   \
							GPIOA, \
							GPIOB, \
							GPIOC, \
							GPIOD, \
							GPIOE, \
							GPIOF, \
							GPIOG  \
							}
#define define_GPIOPINS	{			 \
						GPIO_Pin_0,  \
						GPIO_Pin_1,	 \
						GPIO_Pin_2,	 \
						GPIO_Pin_3,	 \
						GPIO_Pin_4,	 \
						GPIO_Pin_5,	 \
						GPIO_Pin_6,	 \
						GPIO_Pin_7,	 \
						GPIO_Pin_8,	 \
						GPIO_Pin_9,	 \
						GPIO_Pin_10, \
						GPIO_Pin_11, \
						GPIO_Pin_12, \
						GPIO_Pin_13, \
						GPIO_Pin_14, \
						GPIO_Pin_15	 \
						}

#define define_GPIOBANKS_SOURCE	{                 \
							GPIO_PortSourceGPIOA, \
							GPIO_PortSourceGPIOB, \
							GPIO_PortSourceGPIOC, \
							GPIO_PortSourceGPIOD, \
							GPIO_PortSourceGPIOE, \
							GPIO_PortSourceGPIOF, \
							GPIO_PortSourceGPIOG  \
							}

#define define_GPIOPINS_SOURCE	{         \
						GPIO_PinSource0,  \
						GPIO_PinSource1,  \
						GPIO_PinSource2,  \
						GPIO_PinSource3,  \
						GPIO_PinSource4,  \
						GPIO_PinSource5,  \
						GPIO_PinSource6,  \
						GPIO_PinSource7,  \
						GPIO_PinSource8,  \
						GPIO_PinSource9,  \
						GPIO_PinSource10, \
						GPIO_PinSource11, \
						GPIO_PinSource12, \
						GPIO_PinSource13, \
						GPIO_PinSource14, \
						GPIO_PinSource15  \
						}

#define define_GPIO_RCC_APBxPERIPHS	{         \
						RCC_APB2Periph_GPIOA, \
						RCC_APB2Periph_GPIOB, \
						RCC_APB2Periph_GPIOC, \
						RCC_APB2Periph_GPIOD, \
						RCC_APB2Periph_GPIOE, \
						RCC_APB2Periph_GPIOF, \
						RCC_APB2Periph_GPIOG  \
						}


#define define_ADC_PINS	{		\
					PA0,		\
					PA1,		\
					PA2,		\
					PA3,		\
					PA4,		\
					PA5,		\
					PA6,		\
					PA7,		\
					PB0,		\
					PB1,		\
					PC0,		\
					PC1,		\
					PC2,		\
					PC3,		\
					PC4,		\
					PC5			\
					}

#define define_ADC_CHANNELS  {      \
					ADC_Channel_0, 	\
					ADC_Channel_1, 	\
					ADC_Channel_2, 	\
					ADC_Channel_3, 	\
					ADC_Channel_4, 	\
					ADC_Channel_5, 	\
					ADC_Channel_6, 	\
					ADC_Channel_7, 	\
					ADC_Channel_8, 	\
					ADC_Channel_9, 	\
					ADC_Channel_10, \
					ADC_Channel_11, \
					ADC_Channel_12, \
					ADC_Channel_13, \
					ADC_Channel_14, \
					ADC_Channel_15, \
					ADC_Channel_16,	\
					ADC_Channel_17  \
					}

#define define_DAC_PINS {	    \
					PA4,		\
					PA5			\
					}

#define define_DAC_CHANNELS {      \
					DAC_Channel_1, \
					DAC_Channel_2  \
					}
  
#define define_UxARTS	{	\
					USART1,	\
					USART2,	\
					USART3,	\
					UART4,	\
					UART5	\
					}

#define define_UxART_RX_PINS {	\
					PA10,		\
					PA3,		\
					PB11,		\
					PC11,		\
					PD2			\
					}

#define define_UxART_TX_PINS { \
					PA9,	   \
					PA2,	   \
					PB10,	   \
					PC10, 	   \
					PC12 	   \
					}		   

#define define_UxARTS_RCC_APBxPERIPHS {      \
					RCC_APB2Periph_USART1,	 \
					RCC_APB1Periph_USART2,	 \
					RCC_APB1Periph_USART3,	 \
					RCC_APB1Periph_UART4,	 \
					RCC_APB1Periph_UART5	 \
					}

#define define_EXTI_LINES {             \
					EXTI_Line0,  \
					EXTI_Line1,  \
					EXTI_Line2,  \
					EXTI_Line3,  \
					EXTI_Line4,  \
					EXTI_Line5,  \
					EXTI_Line6,  \
					EXTI_Line7,  \
					EXTI_Line8,  \
					EXTI_Line9,  \
					EXTI_Line10, \
					EXTI_Line11, \
					EXTI_Line12, \
					EXTI_Line13, \
					EXTI_Line14, \
					EXTI_Line15, \
					EXTI_Line16, \
					EXTI_Line17, \
					EXTI_Line18  \
					}

#define define_NVC_IRQCHANNELS_n 13
#define define_NVIC_IRQCHANNELS {         \
					USART1_IRQChannel,    \
					USART2_IRQChannel,    \
					USART3_IRQChannel,    \
					UART4_IRQChannel,     \
					UART5_IRQChannel,     \
					EXTI0_IRQChannel,     \
					EXTI1_IRQChannel,     \
					EXTI2_IRQChannel,     \
					EXTI3_IRQChannel,     \
					EXTI4_IRQChannel,     \
					EXTI9_5_IRQChannel,   \
					EXTI15_10_IRQChannel \
					}

#define define_NVIC_IRQ_PREEMPTION_PRIORITY { \
					1,  \
					1,  \
					1,  \
					1,  \
					1,  \
					3,  \
					3,  \
					3,  \
					3,  \
					3,  \
					3,  \
					3,  \
					3   \
					}






#define PA0 0x10
#define PA1 0x11
#define PA2 0x12
#define PA3 0x13
#define PA4 0x14
#define PA5 0x15
#define PA6 0x16
#define PA7 0x17
#define PA8 0x18
#define PA9 0x19
#define PA10 0x1A
#define PA11 0x1B
#define PA12 0x1C
#define PA13 0x1D
#define PA14 0x1E
#define PA15 0x1F

#define PB0 0x20
#define PB1 0x21
#define PB2 0x22
#define PB3 0x23
#define PB4 0x24
#define PB5 0x25
#define PB6 0x26
#define PB7 0x27
#define PB8 0x28
#define PB9 0x29
#define PB10 0x2B
#define PB11 0x2B
#define PB12 0x2C
#define PB13 0x2D
#define PB14 0x2E
#define PB15 0x2F

#define PC0 0x30
#define PC1 0x31
#define PC2 0x32
#define PC3 0x33
#define PC4 0x34
#define PC5 0x35
#define PC6 0x36
#define PC7 0x37
#define PC8 0x38
#define PC9 0x39
#define PC10 0x3B
#define PC11 0x3B
#define PC12 0x3C
#define PC13 0x3D
#define PC14 0x3E
#define PC15 0x3F

#define PD1 0x41
#define PD2 0x42
#define PD3 0x43
#define PD4 0x44
#define PD5 0x45
#define PD6 0x46
#define PD7 0x47
#define PD8 0x48
#define PD9 0x49
#define PD10 0x4B
#define PD11 0x4B
#define PD12 0x4C
#define PD13 0x4D
#define PD14 0x4E
#define PD15 0x4F

#define PE0 0x50
#define PE1 0x51
#define PE2 0x52
#define PE3 0x53
#define PE4 0x54
#define PE5 0x55
#define PE6 0x56
#define PE7 0x57
#define PE8 0x58
#define PE9 0x59
#define PE10 0x5B
#define PE11 0x5B
#define PE12 0x5C
#define PE13 0x5D
#define PE14 0x5E
#define PE15 0x5F

#define PF0 0x60
#define PF1 0x61
#define PF2 0x62
#define PF3 0x63
#define PF4 0x64
#define PF5 0x65
#define PF6 0x66
#define PF7 0x67
#define PF8 0x68
#define PF9 0x69
#define PF10 0x6B
#define PF11 0x6B
#define PF12 0x6C
#define PF13 0x6D
#define PF14 0x6E
#define PF15 0x6F

#define PG0 0x70
#define PG1 0x71
#define PG2 0x72
#define PG3 0x73
#define PG4 0x74
#define PG5 0x75
#define PG6 0x76
#define PG7 0x77
#define PG8 0x78
#define PG9 0x79
#define PG10 0x7B
#define PG11 0x7B
#define PG12 0x7C
#define PG13 0x7D
#define PG14 0x7E
#define PG15 0x7F


extern const u16 GPIOPINS[];
extern GPIO_TypeDef* const GPIOBANKS[];
extern const u16 GPIOPINS[];
extern const u8  GPIOBANKS_SOURCE[];
extern const u8  GPIOPINS_SOURCE[];
extern const u32 GPIO_RCC_APBxPERIPHS[];
		  
extern const u8  ADC_PINS[];
extern const u8  ADC_CHANNELS[];

extern const u8  DAC_PINS[];
extern const u32 DAC_CHANNELS[];

extern USART_TypeDef* const UxARTS[];
extern const u8  UxART_RX_PINS[];
extern const u32 UxART_TX_PINS[];
extern const u32 UxARTS_RCC_APBxPERIPHS[];

extern const u32 EXTI_LINES[];

extern vu32 SystemUptime;
extern vu32 SysTick_Use_Counter;


 
#endif
