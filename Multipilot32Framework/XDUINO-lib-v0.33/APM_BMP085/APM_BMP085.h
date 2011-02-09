#ifndef APM_BMP085_h
#define APM_BMP085_h


class APM_BMP085_Class
{
  private:
    // State machine
    unsigned int BMP085_State;
	// Internal calibration registers
	long ac1, ac2, ac3, b1, b2, mb, mc, md;
    long ac4, ac5, ac6;  
	void Command_ReadPress();
	void Command_ReadTemp();
	void ReadPress();
	void ReadTemp();
	void Calculate();
  public:
	long RawPress;
	long RawTemp;
	int Temp;
	long Press;
	//int Altitude;
	unsigned int oss;
	//int32_t Press0;  // Pressure at sea level

	APM_BMP085_Class();  // Constructor
	void Init(int initialiseWireLib = 1);
	unsigned int Read();	
};

class APM_BMP085_HIL_Class
{
  private:
    unsigned int  BMP085_State;
  public:
	long RawPress;
	long RawTemp;
	int Temp;
	long Press;
	//int Altitude;
	unsigned int oss;
	APM_BMP085_HIL_Class();  // Constructor
	void Init(int initialiseWireLib = 1);
	unsigned int Read();	
    void setHIL(float Temp, float Press);
};

#endif
