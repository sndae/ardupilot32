/******************************************************************
*  Copyright (C) 2009 Ram Narula <ram@pluslab.com> 
*  Filename: doDAC.h
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
#ifndef doDAC_h
#define doDAC_h

#include "XDUINO.h"

class doDAC
{
  public:
  // variables
  	//u32 DACn;

  // methods
  	doDAC(); 
  	doDAC(u8 DAC_Channelx_);
	static void Setup(u32 DACn_);
  	void Write(u16 OutputData);
  	u16 LastWrite(void);
	
  private:
  	u8 DAC_Channelx;
};

#endif

