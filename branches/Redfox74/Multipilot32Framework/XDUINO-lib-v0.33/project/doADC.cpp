/******************************************************************
*  Copyright (C) 2009 Ram Narula <ram@pluslab.com> 
*  Filename: doADC.cpp
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
#include "doADC.h"
#include "defineName.h"
#include "doGPIO.h"

doADC::doADC() 
{
}

doADC::doADC(ADC_TypeDef* ADCn_,u8 ADC_Channelx_) : ADCn(ADCn_),ADC_Channelx(ADC_Channelx_)
{
}

void doADC::Setup(ADC_TypeDef* ADCn_)
{
  ADC_InitTypeDef  ADC_InitStructure;

  RCC_ADCCLKConfig(RCC_PCLK2_Div6); // 72MHz/6=12 MHz range must be 0.6-14MHz
  

  ADC_DeInit(ADCn_);
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; // This ADC independent from other ADC
  ADC_InitStructure.ADC_ScanConvMode = DISABLE; // Convert only specified chanel	
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; // Convert on demand only
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // Do conversion on demand
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // ADC 12 bits data into 16 bits with 0 paddings
  ADC_InitStructure.ADC_NbrOfChannel = 1; 
  ADC_Init(ADCn_, &ADC_InitStructure);	// Put all settings into structure
  ADC_Cmd(ADCn_, ENABLE);				// Start ADCn
  ADC_ResetCalibration(ADCn_);			// Reset calibration
  while(ADC_GetResetCalibrationStatus(ADCn_));
  ADC_StartCalibration(ADCn_);			// Start final calibration
  while(ADC_GetCalibrationStatus(ADCn_));
  
}



u16 doADC::Read(u8 SampleTime)
{
  //SampleTime = ADC_SampleTime_XCycles5 X=1,7,13,28,41,55,71,239
  
  defineName	myADC;
  myADC.getADCchannel(ADC_Channelx);
  
  
  if((ADC_Channelx!=16) && (ADC_Channelx!=17))	//16 & 17 no need GPIO_Mode_AIN
  {
  		doGPIO		myGPIOPin=doGPIO(myADC.GPIObank,myADC.GPIOPin,GPIO_Mode_AIN);
  }
  
  
  ADC_RegularChannelConfig(ADCn, myADC.ADC_Channel, 1, SampleTime);
  ADC_SoftwareStartConvCmd(ADCn, ENABLE);
  while(ADC_GetFlagStatus(ADCn, ADC_FLAG_EOC) == RESET);
  return ADC_GetConversionValue(ADCn);
}

void doADC::StartTemperatureSensor(void)
{
	ADC_TempSensorVrefintCmd(ENABLE); // Enable the temp sensor
}

