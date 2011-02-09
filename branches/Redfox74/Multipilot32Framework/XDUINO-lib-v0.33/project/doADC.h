/******************************************************************
*  Copyright (C) 2009 Ram Narula <ram@pluslab.com> 
*  Filename: doADC.h
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
// load this library only once
#ifndef doADC_h
#define doADC_h

#include "XDUINO.h"


class doADC {

	public:
		// variables
		ADC_TypeDef* ADCn;
		u8 ADC_Channelx;
		// constructors
		doADC();
		doADC(ADC_TypeDef* ADCn_,u8 ADC_Channelx_);
		static void Setup(ADC_TypeDef* ADCn_);
		static void StartTemperatureSensor(void);
		u16 Read(u8 SampleTime);
		
	private:
		
};
				 



#endif


