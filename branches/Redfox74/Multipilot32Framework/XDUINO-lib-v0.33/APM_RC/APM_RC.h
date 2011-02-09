#ifndef APM_RC_h
#define APM_RC_h

#define NUM_CHANNELS 8
#define MIN_PULSEWIDTH 900
#define MAX_PULSEWIDTH 2100

#define MOTORID1 0		
#define MOTORID2 1		
#define MOTORID3 2		
#define MOTORID4 3		
#define MOTORID5 4		
#define MOTORID6 5		

//#define MINTHROTTLE 1300 // for Turnigy Plush ESCs 10A
#define MINTHROTTLE 1120 // for Super Simple ESCs 10A

//#define SERIAL_SUM_PPM  // for specific receiver with only one PPM sum signal, on digital PIN 2
#define PPM_ORDER         PITCH,YAW,THROTTLE,ROLL,MODE,AUX1,AUX2,AUX3 //For Graupner/Spektrum



// *************************
// motor and servo functions
// *************************

#define MINCOMMAND 1000
#define MAXCOMMAND 1850


//PIN assignment
#define THROTTLEPIN 2
#define ROLLPIN 4
#define PITCHPIN 5
#define YAWPIN 6
#define AUX1PIN 7

//PIN for TRICOPTER and QUAD+   //QUADX equivalency 
#define REARMOTORPIN 9          //REAR_RIGHT_MOTORPIN
#define RIGHTMOTORPIN 10        //FRONT_RIGHT_MOTORPIN
#define LEFTMOTORPIN 11         //REAR_LEFT_MOTORPIN
#define FRONTMOTORPIN 3         //FRONT_LEFT_MOTORPIN

#define LEDPIN 13
#define POWERPIN 12

// alias for TRI and QUAD+      //QUADX equivalency
#define REAR 0                  //REAR_R
#define RIGHT 1                 //FRONT_R
#define LEFT 2                  //REAR_L
#define FRONT 3                 //FRONT_L

// alias QUADX equivalency
#define REAR_R REAR
#define FRONT_R RIGHT
#define REAR_L LEFT
#define FRONT_L FRONT


// alias for RC
#define ROLL 4
#define PITCH 2
#define YAW 3
#define THROTTLE 1
#define MODE 5
#define AUX1 6
#define AUX2 7
#define AUX3 8


// These constants won't change.  They're used to give names
// to the pins used:
//int analogOutPin[12];

#include <inttypes.h>

class APM_RC_Class
{
  private:
  public:
	APM_RC_Class();
	void Init();
	void OutputCh(unsigned char ch, uint16_t pwm);
	uint16_t InputCh(unsigned char ch);
	unsigned char GetState();
	void Force_Out0_Out1(void);
	void Force_Out2_Out3(void);
	void Force_Out6_Out7(void);
};

extern APM_RC_Class APM_RC;

#endif
