/******************************************************************
*  Copyright (C) 2009 Ram Narula <ram@pluslab.com> 
*  Filename: main.cpp
*  Version: 0.31
*  Date: 06 August 2009
*  Early Information: http://www.xduino.com/
*  Date  09 February 2011
*  Info and support : www.virtualrobotix.com
*    
******************************************************************/
/******************************************************************
*   This file is part of Xduino
*
*   Xduino is free software: you can redistribute it and/or modify
*   it under the terms of the GNU Lesser General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*	
*   Xduino is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU Lesser General Public License for more details.
*
*   You should have received a copy of the GNU Lesser General Public License
*   along with Xduino.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************/
/* Xduino v0.34 */
/* Vrduino v0.1 */

#include "main.h"

using namespace compatArduino;

int main(void)
{

	doInit(); 				//Initialize Xduino components, this line is required

    setup();   				//Arduino Setup

	while(1)loop();			//

} //## END main()


#include "..\APM_RC\APM_RC.h"

void setup(void)
{
	APM_RC.Init();	 // APM Radio initialization
	Serial1.begin(115200);
	Serial1.print("ArduPilot Mega RC library test\n\r");
	delay(1000);
}

void loop(void)
{
	// New radio frame? (we could use also if((millis()- timer) > 20)
	if (APM_RC.GetState() == 1){
		Serial1.print("CH:");
		for(int i = 0; i < 8; i++){
			Serial1.print(APM_RC.InputCh(i));	// Print channel values
			Serial1.print(",");
			APM_RC.OutputCh(i, APM_RC.InputCh(i)); // Copy input to Servos
		}
		Serial1.print("\n");
	}
}

