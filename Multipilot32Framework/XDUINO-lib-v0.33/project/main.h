/******************************************************************
*  Copyright (C) 2009 Ram Narula <ram@pluslab.com>
*  Filename: main.h
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
#ifndef main_h
#define main_h

/*
#include "XDUINO.h"
#include "doGPIO.h"
#include "doADC.h"
#include "doDAC.h"
#include "doSerial.h"
#include "doEXTI.h"
#include "doTime.h"
#include "compatArduino.h"
  */

// The following includes must be in proper order
#include "xduinoInit.h"
#include "InterruptHandler.h"


#include "..\ap32lib\AP_ADC_ADS7844.h"


// math function ie. sin cos abs sqrt etc.
#include <math.h>

// Standard library functions also has random number functions
#include <stdlib.h>




#endif

