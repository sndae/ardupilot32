/******************************************************************
*  Copyright (C) 2009 Ram Narula <ram@pluslab.com> 
*  Filename: doDAC.cpp
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
#include "doDAC.h"
#include "defineName.h"
#include "doGPIO.h"

doDAC::doDAC() 
{
}

doDAC::doDAC(u8 DAC_Channelx_) : DAC_Channelx(DAC_Channelx_)
{
}

void doDAC::Setup(u32 DACn_)
{

  DAC_InitTypeDef  DAC_InitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
  
  
  DAC_InitStructure.DAC_Trigger = DAC_Trigger_None; 
  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None; 
  //DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_Triangle; 
  //DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_31;
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable; 
  DAC_Init(DACn_, &DAC_InitStructure); 
  DAC_Cmd(DACn_, ENABLE); 
  DAC_DMACmd(DACn_, DISABLE); 
  DAC_SoftwareTriggerCmd(DACn_, DISABLE); 
  DAC_DualSoftwareTriggerCmd(DISABLE); 

} 


void doDAC::Write(u16 OutputData)
{

  defineName	myDAC;
  myDAC.getDACchannel(DAC_Channelx);
  
  //Set Pin to analog
  doGPIO	myGPIOPin=doGPIO(myDAC.GPIObank,myDAC.GPIOPin,GPIO_Mode_AIN);
  
  //Set output
  if(DAC_Channelx == 1) {
  		DAC_SetChannel1Data(DAC_Align_12b_R,(OutputData & 0xFFF));
  }
  if(DAC_Channelx == 2) {
  		DAC_SetChannel2Data(DAC_Align_12b_R,(OutputData & 0xFFF));
  }

}

u16 doDAC::LastWrite(void)
{
  defineName	myDAC;
  myDAC.getDACchannel(DAC_Channelx);  
  return DAC_GetDataOutputValue(myDAC.DAC_Channel);
}
