/******************************************************************
*  Copyright (C) 2009 Ram Narula <ram@pluslab.com> 
*  Filename: Serial.cpp
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
#include "doSerial.h"
#include "doGPIO.h"
#include "defineName.h"


doSerial::doSerial(u8 port_,u32 Baudrate_) : 
			port(port_), Baudrate(Baudrate_)
{
	RxBufferSize=RXBUFFERSIZE;
	TxBufferSize=TXBUFFERSIZE;
	begin(Baudrate);
}

doSerial::doSerial(const u8 &port_) : port(port_)
{
	RxBufferSize=RXBUFFERSIZE;
	TxBufferSize=TXBUFFERSIZE;
}

void doSerial::begin(const u32 &Baudrate_)
{
Baudrate=Baudrate_;
	if(RxBufferSize) {
		RxBuffer = new char[RxBufferSize]; 
		RRrxbuffer = new RoundRobinData<char>(RxBuffer,RxBufferSize);
	}

	if(TxBufferSize) {
		TxBuffer = new char[TxBufferSize]; 
		RRtxbuffer = new RoundRobinData<char>(TxBuffer,TxBufferSize);
	}

	defineName myUxART;
	myUxART.getUxART(port);
	RCC_APB2PeriphClockCmd(myUxART.UxART_Rx_GPIO_RCC_APBxPeriph,ENABLE);
	RCC_APB2PeriphClockCmd(myUxART.UxART_Tx_GPIO_RCC_APBxPeriph,ENABLE);
	if(port==1) {
		RCC_APB2PeriphClockCmd(myUxART.UxARTx_RCC_APBxPeriph, ENABLE);
	} else {
		RCC_APB1PeriphClockCmd(myUxART.UxARTx_RCC_APBxPeriph, ENABLE);
	}

	doGPIO(myUxART.UxART_Rx_Bank,myUxART.UxART_Rx_Pin,GPIO_Mode_IN_FLOATING);
	doGPIO(myUxART.UxART_Tx_Bank,myUxART.UxART_Tx_Pin,GPIO_Mode_AF_PP); 
		
	UxARTx=myUxART.UxARTxName;

  	
  USART_InitTypeDef USART_InitStructure;

  // UxARTx Baudrate 8N1 no hardware flow control
  USART_InitStructure.USART_BaudRate = Baudrate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  
  USART_Init(UxARTx, &USART_InitStructure);  //finished initialization parameters

  //USART_ClockInitTypeDef USART_ClockInitStructure;

  //USART_ClockInitStructure.USART_Clock= USART_Clock_Disable;
  //USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;  
  //USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;  
  //USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
  //USART_ClockInit(USART1,&USART_ClockInitStructure); 

  USART_Cmd(UxARTx, ENABLE); // and finally start UxARTx
  
  //TX interrupt must be off , it should only be turned on by sending data
  //USART_ITConfig(UxARTx, USART_IT_TXE, ENABLE); 

  // if Rx Buffer exist then turn on Rx interrupt  
  if(RxBufferSize) 
  {
  	USART_ITConfig(UxARTx, USART_IT_RXNE, ENABLE); //set RX interrupt
  }

}



void doSerial::printNoBuffer(char c)  
{
  while (!(UxARTx->SR & USART_FLAG_TXE));
  UxARTx->DR = (c & 0x1FF); //upto 9 bits
  //return(UxARTx->DR = (c & 0x1FF)); //upto 9 bits
}

void doSerial::print(char c)  
{
  if(TxBufferSize) 
  {
  	printBuffer(c);
	//return printBuffer(c);
  } else {
 	printNoBuffer(c);
	//return printNoBuffer(c);
  }
}

void doSerial::print(char *s)
{
	while(*s)   // Check for end of string
	{
      print(*s++);
   	}
}

	

char doSerial::readNoBuffer(void)  
{
  while (!(UxARTx->SR & USART_FLAG_RXNE));
  return (UxARTx->DR & 0xFF); //upto 8 bits
}

char doSerial::read(void)
{
  if(RxBufferSize)
  {
  	return readBuffer();
  } else {
    return readNoBuffer();
  }
}

u16 doSerial::getData(void)  
{
  while (!(UxARTx->SR & USART_FLAG_RXNE));
  return ((u16)(UxARTx->DR & 0x1FF)); //upto 9 bits
}

bool doSerial::availableNoBuffer(void)  
{
  return (bool)(UxARTx->SR & USART_FLAG_RXNE);
}

bool doSerial::availableBuffer(void) 
{
	return (RRrxbuffer->notEmpty());
}

bool doSerial::available(void)  
{
	if(RxBufferSize)
	{
		return availableBuffer();
	} else {
		return availableNoBuffer();
	}
}

// Buffered operations
void doSerial::printBuffer(char c) 
{
  	//bool txbufferNotFull;

	// put data in txbuffer before setting TXE interrupt
	//txbufferNotFull=RRtxbuffer->Put(w);
	RRtxbuffer->Put(c);

	// set interrupt if not active
	if(!(UxARTx->CR1 & USART_FLAG_TXE))	UxARTx->CR1 |= USART_FLAG_TXE; 
 		
	//return txbufferNotFull;	// return 0 if txbuffer is full
}		

char doSerial::readBuffer(void) 
{
	char c;
	while(!(c=RRrxbuffer->Get()));
	return c;
}


void doSerial::flush(void)
{
	RRrxbuffer->Reset();
}

void doSerial::setRxBufferSize(u32 size)
{
	RxBufferSize=size;
}

void doSerial::setTxBufferSize(u32 size)
{
	TxBufferSize=size;
}

char doSerial::GetTxBuffer(char c)
{
	c=RRtxbuffer->Get();
	return c;
}

char doSerial::PutRxBuffer(char c)
{
	return RRtxbuffer->Put(c);
}

void doSerial::print(signed int i) {	printf("%d",i); }
void doSerial::print(unsigned int i){	printf("%u",i); }
void doSerial::print(signed long i) { printf("%lu",i); }
void doSerial::print(unsigned long i) { printf("%lu",i); }
void doSerial::print(double d) { printf("%f",d); }
void doSerial::print(const char *s) { print((char*)s); }

void doSerial::printf(char *s) { print(s); }



doSerial::~doSerial()
{
	delete [] RxBuffer;
	delete [] TxBuffer;
	delete RRrxbuffer;
	delete RRtxbuffer;

}
