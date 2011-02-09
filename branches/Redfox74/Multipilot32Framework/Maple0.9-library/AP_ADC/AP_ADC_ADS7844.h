#ifndef AP_ADC_ADS7844_H
#define AP_ADC_ADS7844_H

#define bit_set(p,m)   ((p) |= ( 1<<m))
#define bit_clear(p,m) ((p) &= ~(1<<m))

// We use Serial Port 2 in SPI Mode
#define ADC_DATAOUT     51    // MOSI
#define ADC_DATAIN      50    // MISO
#define ADC_SPICLOCK    52    // SCK
#define ADC_CHIP_SELECT 33    // PC4   9 // PH6  Puerto:0x08 Bit mask : 0x40

#include "AP_ADC.h"

class AP_ADC_ADS7844 : public AP_ADC
{
  public:
	AP_ADC_ADS7844();  // Constructor
	void Init();
	void Update();
	int Ch(unsigned char ch_num);     
  private:
};

#endif
