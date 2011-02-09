/******************************************************************
*  Copyright (C) 2009 Ram Narula <ram@pluslab.com> 
*  Filename: InterruptHandler.h
*  Version: 0.3
*  Date: 04 August 2009
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
#ifndef interrupthandler_h
#define interrupthandler_h

/* All interrupt functions prototype must be in C declaration   */
extern "C" {
	// SysTick interrupt handler
	void SysTick_IRQ_Function(void);

	// UxART1-5 interrupt handler
	void USART1_IRQ_Function(void);		
	void USART2_IRQ_Function(void);
	void USART3_IRQ_Function(void);
	void UART4_IRQ_Function(void);
	void UART5_IRQ_Function(void);

	// EXTI IRQ Handler
	void EXTI_ALL_IRQ_Function();	
}

// ###BEGIN Global interrupt related variable declaration###
// System uptime counter used by SysTick interrupt handler and time related functions
vu32 SystemUptime=0;
vu32 SysTick_Use_Counter=0;

// Function pointers for EXTI interrupt handler
typedef void(*Function_Pointer_Array)(void);
Function_Pointer_Array EXTI_Function_Pointer[19]={};
// ###END Global interrupt related variable declaration###



// ###BEGIN INTERRUPT HANDLER###

// #SysTick handler
void SysTick_IRQ_Function(void){ SystemUptime++; SysTick_Use_Counter++;}

// #UxARTs handler
// prototype for interrupt of UxUARTx functions
void UxARTx_IRQ_Function(USART_TypeDef* UxARTx,doSerial * SerialObject);

// UxARTx interrupt calls
void USART1_IRQ_Function (void) { UxARTx_IRQ_Function(USART1,&Serial1); } 
void USART2_IRQ_Function (void) { UxARTx_IRQ_Function(USART2,&Serial2); } 
void USART3_IRQ_Function (void) { UxARTx_IRQ_Function(USART3,&Serial3); } 
void UART4_IRQ_Function (void) { UxARTx_IRQ_Function(UART4,&Serial4); } 
void UART5_IRQ_Function (void) { UxARTx_IRQ_Function(UART5,&Serial5); } 

  	
inline void UxARTx_IRQ_Function(USART_TypeDef* UxARTx,doSerial * SerialObject)
{
	vu32 USARTstat=UxARTx->SR;  //interupt handler store current status

	// RXNE interrupt call
    if (USARTstat & USART_FLAG_RXNE) 
	{  		
			UxARTx->SR &= ~USART_FLAG_RXNE;			// clear RXNE status
			SerialObject->RRrxbuffer->Put(UxARTx->DR & 0x1FF); 	// put data in roundrobin rxbuffer
	}
	
	// Check if TXE interrupt is active with FLAG_TXE	
    if ((USARTstat & USART_FLAG_TXE) && (UxARTx->CR1 & USART_FLAG_TXE)) 
	{
	  if(Serial1.RRtxbuffer->notEmpty())  						//txbuffer is not empty
	  {
	 		UxARTx->DR = (Serial1.RRtxbuffer->Get() & 0x1FF);	//send data, clear TXE flag
	  } else {
	  		UxARTx->CR1 &= ~USART_FLAG_TXE; 					//no txbuffer so disable interrupt 
	  }		
	}
}



// #EXTIs handler
// Initialize function pointers for Interrupt settings 
// of custom function names, there are total 19 EXTI Lines

void EXTI_ALL_IRQ_Function(void)
{
 	// Check Interrupt setting and Interrupt request
	// Note that we put EXTI_ClearITPendingBit at bottom 
	// as we want to receive the same interrupt only after the current
	// interrupt process has been completed so we clear the flag at last line
	// If need to receive interrupt while interrupt is executing then
	// EXTI_ClearITPendingBit can be at the top.
	//
	// Only working with GPIO general interrupts 0-15
	
	for(int iEXTILine=0;iEXTILine<=15;iEXTILine++)
	{
		//if(EXTI-> PR & EXTI_LINES[iEXTILine]) 		// could use EXTI_GetITStatus()
		if(EXTI_GetITStatus(EXTI_LINES[iEXTILine]))
		{ 	
				(*EXTI_Function_Pointer[iEXTILine])();
				EXTI_ClearITPendingBit(EXTI_LINES[iEXTILine]);
		}
	}
}


// ###END INTERRUPT HANDLER###

#endif

