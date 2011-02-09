/*
	APM_RC.cpp - Radio Control Library for Ardupilot Mega. Arduino
	Roberto Navoni. virtualrobotix.com DIYDrones.com

	This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

	RC Input : PPM signal on IC4 pin
	RC Output : 11 Servo outputs (standard 20ms frame)

	Methods:
		Init() : Initialization of interrupts an Timers
		OutpuCh(ch,pwm) : Output value to servos (range : 900-2100us) ch=0..10
		InputCh(ch) : Read a channel input value.  ch=0..7
		GetState() : Returns the state of the input. 1 => New radio frame to process
		             Automatically resets when we call InputCh to read channels
		
*/
#include "APM_RC.h"

#include "..\project\xduinoInit.h"

volatile unsigned char radio_status_rc=0;
volatile unsigned char sync=0;
static int analogOutPin[12];
volatile unsigned int currentChannel = 0;
static unsigned int last = 0;


//void rxInt(void);

// ******************
// rc functions
// ******************
#define MINCHECK 1100
#define MAXCHECK 1900

static uint8_t pinRcChannel[5] = {ROLLPIN, PITCHPIN, YAWPIN, THROTTLEPIN, AUX1PIN};
volatile uint16_t rcPinValue[12] = {0,0,1000,0,1500,1500,1500,1000,0,0,0,0};; // interval [1000;2000]
static uint16_t rcData[12] ; // interval [1000;2000]
static int16_t rcCommand[12] = {0,0,0,0,0}; // interval [-500;+500]
static int16_t rcHysteresis[12] ;
static int16_t rcData4Values[12][4];

static float rcRate;
static float rcExpo;

// ***PPM SUM SIGNAL***
static uint8_t rcChannel[12] = {PPM_ORDER};
volatile uint16_t rcValue[12] = {1500,1500,1500,1500,1500,1500,1500,1500,1500,1500,1500,1500}; // interval [1000;2000]


void rxInt(void) {
volatile unsigned int now;
volatile unsigned int diff;
int i;

//Serial.print("."); 
  now = micros();
  diff = now - last;
  last = now;
  //Serial.println(diff);
  //diff=diff*4; // Se si usa il timer0 come pwm in uscita e quindi con un altro coefficiente di equivalenza  che e' di 4* se si usa micros e penso /4 con delay per avere lo stesso valore.
  //Serial.println(diff);
  if(diff>4000  &&  diff<21000) // Sincro del frame 
      {
      currentChannel = 0;
	  radio_status_rc=0;
	  rcValue[currentChannel] = diff;
      currentChannel++;
	  sync=1;
      }
  else 
  	 //if(diff<=2200 && diff>=900) 
     if (sync==1) 
     {
          rcValue[currentChannel] = diff;
          currentChannel++;
		  if(diff<=2200 && diff>=900)radio_status_rc++;
	}
	 if (currentChannel>8)
	 {
		 //currentChannel=0;	
		 sync=0;
		 radio_status_rc=0;
	 }
}


// Constructors ////////////////////////////////////////////////////////////////

APM_RC_Class::APM_RC_Class()
{
}

// Public Methods //////////////////////////////////////////////////////////////
void APM_RC_Class::Init(void)
{
  analogOutPin[MOTORID1] = 0; // Connected to PPM output1 // TIMER2
  analogOutPin[MOTORID2] = 1; // Connected to PPM output2 // TIMER2
  analogOutPin[MOTORID3] = 2; //  Connected to PPM output3 // TIMER1
  analogOutPin[MOTORID4] = 3; //  Connected to PPM output4 // TIMER1

  
  pinMode(analogOutPin[MOTORID1],OUTPUT); // DEVO VEDERE COME GESTIRE L'USCITA COME PWM
  pinMode(analogOutPin[MOTORID2],OUTPUT); // PER ORA LO SETTO COME OUTPUT
  pinMode(analogOutPin[MOTORID3],OUTPUT); //
  pinMode(analogOutPin[MOTORID4],OUTPUT); //

// Configure Interrupt 2 J8 as pin for radio reciver

  pinMode(6,INPUT);
  attachInterrupt(6, rxInt, RISING);
}

void APM_RC_Class::OutputCh(unsigned char ch, uint16_t pwm)
{

  pwm=map(pwm, 1000, 2000, 32000, 64000);
  analogWrite(analogOutPin[ch], pwm);
}

uint16_t APM_RC_Class::InputCh(unsigned char ch)
{
  uint16_t data;
  data = rcValue[rcChannel[ch]]; 
  return data; // We return the value correctly copied when the IRQ's where disabled
}

unsigned char APM_RC_Class::GetState(void)
{
  return(radio_status_rc);
}

// InstantPWM implementation
// This function forces the PWM output (reset PWM) on Out0 and Out1 (Timer5). For quadcopters use
void APM_RC_Class::Force_Out0_Out1(void)
{
}
// This function forces the PWM output (reset PWM) on Out2 and Out3 (Timer1). For quadcopters use
void APM_RC_Class::Force_Out2_Out3(void)
{
}
// This function forces the PWM output (reset PWM) on Out6 and Out7 (Timer3). For quadcopters use
void APM_RC_Class::Force_Out6_Out7(void)
{
}

// make one instance for the user to use
APM_RC_Class APM_RC;
