/******************************************************************
*  Copyright (C) 2009 Ram Narula <ram@pluslab.com> 
*  Filename: Serial.h
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
#ifndef doSerial_h
#define doSerial_h

#include "XDUINO.h"
#include "roundrobinData.h"
#include "stdio.h"

// Serial communication via USART/UART defaults to USART1
class doSerial
{
  public:
  // variables
  	const u8 port;
	u32 Baudrate;
	u32 RxBufferSize;
	u32 TxBufferSize;
	

  // methods
	doSerial(u8 port_,u32 Baudrate_);
	doSerial(const u8 &port_);					//Arduino style (called from generalInit.h)
    void begin(const u32 &Baudrate_);			//Arduino style, assign baudrate later
	
	
	void printNoBuffer(char c);			//Actual output UxARTx
	void printBuffer (char c);			//Output to UxARTx TX buffer for Interrupt handler
	

	
	
	void print(char c);					//Final print
	void print(char *s);
	void print(signed int i);
	void print(unsigned int i);
	void print(signed long i);
	void print(unsigned long i);
	void print(double d);
	
	void print(const char *s);

	template<typename T> 
	void println(T data) { print(data);print("\r\n"); }
	
	char read(void);					//Read rx
	char readNoBuffer(void);			//Actual reading from UxARTx
	char readBuffer(void);				//Actual reading from buffer of UxARTx
	
	
	char PutRxBuffer(char c);			//put into RxBuffer for interrupt call
	char GetTxBuffer(char c);			//get TxBuffer data for interrupt call	

	u16 getData(void);					//read 9 bits from UxARTx no interrupt
	
	bool available(void);  				//Check rx for data
	bool availableNoBuffer(void);		//Actual checking from UxARTx
	bool availableBuffer(void);			//Actual checking from buffer of UxARTx

	void setRxBufferSize(u32 size);		// Set Rx/Tx buffer size 0 for no buffer
	void setTxBufferSize(u32 size);		//
	
	
	void flush(void);	  				//Flush receive buffer of UxARTx

	// using Round-Robin class for the buffer
	RoundRobinData<char> * RRrxbuffer;		//RRrxbuffer public access for interrupt
	RoundRobinData<char> * RRtxbuffer;		//RRtxbuffer public access for interrupt

	void printf(char *fmt);

	template<typename T1> 
	void printf(char *fmt,T1 data1)
	{
		printf(fmt,data1,0,0,0,0);
	}

	template<typename T1, typename T2> 
	void printf(char *fmt,T1 data1,T2 data2)
	{
		printf(fmt,data1,data2,0,0,0);
	}
		
	template<typename T1, typename T2,typename T3>
	void printf(char *fmt,T1 data1,T2 data2,T3 data3)
	{
		printf(fmt,data1,data2,data3,0,0);
	}

	template<typename T1, typename T2,typename T3,typename T4>
	void printf(char *fmt,T1 data1,T2 data2,T3 data3,T4 data4)
	{
		printf(fmt,data1,data2,data3,data4,0);
	}
	
	template<typename T1, typename T2,typename T3,typename T4,typename T5>
	void printf(char *fmt,T1 data1,T2 data2,T3 data3,T4 data4,T5 data5)
	{
		char buffer[SERIAL_PRINTF_SIZE] = {};
		snprintf(buffer,SERIAL_PRINTF_SIZE,fmt,data1,data2,data3,data4,data5);
		print(buffer);
	}
		


	~doSerial();

	
  private:
  	//pointers only will allocate if XxBuffer > 0
	char * RxBuffer;					//RxBuffer string
	char * TxBuffer;					//TxBuffer string
	USART_TypeDef* UxARTx;
  	
};



#endif


