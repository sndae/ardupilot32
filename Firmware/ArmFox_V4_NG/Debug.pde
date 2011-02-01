/*
 www.ArduCopter.com - www.DIYDrones.com
 Copyright (c) 2010.  All rights reserved.
 An Open Source Arduino based multicopter.
 
 File     : Debug.pde
 Version  : v1.0, Aug 27, 2010
 Author(s): ArduCopter Team
             Ted Carancho (aeroquad), Jose Julio, Jordi Muñoz,
             Jani Hirvinen, Ken McEwans, Roberto Navoni,          
             Sandro Benigno, Chris Anderson
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.

* ************************************************************** *
ChangeLog:


* ************************************************************** *
TODO:


* ************************************************************** */


#if DEBUG_SUBSYSTEM == 1
void debug_subsystem()
{
	SerialUSB.println("Begin Debug: Radio Subsystem ");
	while(1){
		delay(20);
		// Filters radio input - adjust filters in the radio.pde file
		// ----------------------------------------------------------
		read_radio();
		SerialUSB.print("Radio in ch1: ");
		SerialUSB.print(radio_in[CH_ROLL], DEC);
		SerialUSB.print("\tch2: ");
		SerialUSB.print(radio_in[CH_PITCH], DEC);
		SerialUSB.print("\tch3: ");
		SerialUSB.print(radio_in[CH_THROTTLE], DEC);
		SerialUSB.print("\tch4: ");
		SerialUSB.print(radio_in[CH_RUDDER], DEC);
		SerialUSB.print("\tch5: ");
		SerialUSB.print(radio_in[4], DEC);
		SerialUSB.print("\tch6: ");
		SerialUSB.print(radio_in[5], DEC);
		SerialUSB.print("\tch7: ");
		SerialUSB.print(radio_in[6], DEC);
		SerialUSB.print("\tch8: ");
		SerialUSB.println(radio_in[7], DEC);
	}
}
#endif

#if DEBUG_SUBSYSTEM == 2
void debug_subsystem()
{
	SerialUSB.println("Begin Debug: Servo Subsystem ");
	SerialUSB.print("Reverse ROLL - CH1: ");
	SerialUSB.println(reverse_roll, DEC);
	SerialUSB.print("Reverse PITCH - CH2: ");
	SerialUSB.println(reverse_pitch, DEC);
	SerialUSB.print("Reverse THROTTLE - CH3: ");
	SerialUSB.println(REVERSE_THROTTLE, DEC);
	SerialUSB.print("Reverse RUDDER - CH4: ");
	SerialUSB.println(reverse_rudder, DEC);

	// read the radio to set trims
	// ---------------------------
	trim_radio();

	radio_max[0]				 = 	CH1_MAX;
	radio_max[1]				 = 	CH2_MAX;
	radio_max[2]				 = 	CH3_MAX;
	radio_max[3]				 = 	CH4_MAX;
	radio_max[4]				 = 	CH5_MAX;
	radio_max[5]				 = 	CH6_MAX;
	radio_max[6]				 = 	CH7_MAX;
	radio_max[7]				 = 	CH8_MAX;
	radio_min[0]				 = 	CH1_MIN;
	radio_min[1]				 = 	CH2_MIN;
	radio_min[2]				 = 	CH3_MIN;
	radio_min[3]				 = 	CH4_MIN;
	radio_min[4]				 = 	CH5_MIN;
	radio_min[5]				 = 	CH6_MIN;
	radio_min[6]				 = 	CH7_MIN;
	radio_min[7]				 = 	CH8_MIN;

	while(1){
		delay(20);
		// Filters radio input - adjust filters in the radio.pde file
		// ----------------------------------------------------------
		read_radio();
		update_servo_switches();

		servo_out[CH_ROLL]	= ((radio_in[CH_ROLL]	- radio_trim[CH_ROLL])	* 45.0f	* reverse_roll) / 500;
		servo_out[CH_PITCH] = ((radio_in[CH_PITCH] - radio_trim[CH_PITCH]) * 45.0f	* reverse_roll) / 500;
		servo_out[CH_RUDDER] = ((radio_in[CH_RUDDER] - radio_trim[CH_RUDDER]) * 45.0f	* reverse_rudder) / 500;

		// write out the servo PWM values
		// ------------------------------
		set_servos_4();
		
		
		for(int y = 4; y < 8; y++) { 
			radio_out[y] = constrain(radio_in[y], 	radio_min[y], 	radio_max[y]);	
			APM_RC.OutputCh(y, radio_out[y]); // send to Servos
		}

		/*
		SerialUSB.print("Servo_out ch1: ");
		SerialUSB.print(servo_out[CH_ROLL], DEC);
		SerialUSB.print("\tch2: ");
		SerialUSB.print(servo_out[CH_PITCH], DEC);
		SerialUSB.print("\tch3: ");
		SerialUSB.print(servo_out[CH_THROTTLE], DEC);
		SerialUSB.print("\tch4: ");
		SerialUSB.print(servo_out[CH_RUDDER], DEC);
		*/
		///*
		SerialUSB.print("ch1: ");
		SerialUSB.print(radio_out[CH_ROLL], DEC);
		SerialUSB.print("\tch2: ");
		SerialUSB.print(radio_out[CH_PITCH], DEC);
		SerialUSB.print("\tch3: ");
		SerialUSB.print(radio_out[CH_THROTTLE], DEC);
		SerialUSB.print("\tch4: ");
		SerialUSB.print(radio_out[CH_RUDDER], DEC);
		SerialUSB.print("\tch5: ");
		SerialUSB.print(radio_out[4], DEC);
		SerialUSB.print("\tch6: ");
		SerialUSB.print(radio_out[5], DEC);
		SerialUSB.print("\tch7: ");
		SerialUSB.print(radio_out[6], DEC);
		SerialUSB.print("\tch8: ");
		SerialUSB.println(radio_out[7], DEC);
		
		//*/
	}
}
#endif


#if DEBUG_SUBSYSTEM == 3
void debug_subsystem()
{
	SerialUSB.println("Begin Debug: Analog Sensor Subsystem ");
	
	SerialUSB.print("AirSpeed sensor enabled: ");
	SerialUSB.println(AIRSPEED_SENSOR, DEC);
		
	SerialUSB.print("Enable Battery: ");
	SerialUSB.println(BATTERY_EVENT, DEC);
	zero_airspeed();
	
	SerialUSB.print("Air pressure offset:");
	SerialUSB.println(airpressure_offset, DEC);

	while(1){
		delay(20);
		read_z_sensor();
		read_XY_sensors();
		read_battery();
		
		SerialUSB.print("Analog IN:");
		SerialUSB.print("  0:");
		SerialUSB.print(analog0, DEC);
		SerialUSB.print(", 1: ");
		SerialUSB.print(analog1, DEC);
		SerialUSB.print(", 2: ");
		SerialUSB.print(analog2, DEC);
		SerialUSB.print(", 3: ");
		SerialUSB.print(airpressure_raw, DEC);
		
		SerialUSB.print("\t\tSensors:");
		SerialUSB.print("  airSpeed:");
		SerialUSB.print(airspeed, DEC);
		SerialUSB.print("m \tbattV:");
		SerialUSB.print(battery_voltage, DEC);
		SerialUSB.println("volts ");
	}
}
#endif

#if DEBUG_SUBSYSTEM == 4
void debug_subsystem()
{
	SerialUSB.println("Begin Debug: GPS Subsystem ");
	
	while(1){
		delay(333);

		// Blink GPS LED if we don't have a fix
		// ------------------------------------
		//update_GPS_light();
		
		GPS.Read();
		
		if (GPS.NewData){
			SerialUSB.print("Lat:");
			SerialUSB.print(GPS.Lattitude, DEC);
			SerialUSB.print(" Lon:");
			SerialUSB.print(GPS.Longitude, DEC);
			SerialUSB.print(" Alt:");
			SerialUSB.print(GPS.Altitude / 100, DEC);
			SerialUSB.print("m, gs: ");
			SerialUSB.print(GPS.Ground_Speed / 100, DEC);
			SerialUSB.print(" COG:");
			SerialUSB.print(GPS.Ground_Course / 1000l);
			SerialUSB.print(" SAT:");
			SerialUSB.print(GPS.NumSats, DEC);
			SerialUSB.print(" FIX:");
			SerialUSB.print(GPS.Fix, DEC);
			SerialUSB.print(" TIM:");
			SerialUSB.print(GPS.Time);
			SerialUSB.println();
		}
	}
}
#endif

#if DEBUG_SUBSYSTEM == 5
void debug_subsystem()
{
	SerialUSB.println("Begin Debug: GPS Subsystem, RAW OUTPUT");
	
	while(1){
		if(Serial1.available() > 0)	// Ok, let me see, the buffer is empty?
		{
			
			delay(60);	// wait for it all
			while(Serial1.available() > 0){
				byte incoming = Serial1.read();
				//SerialUSB.print(incoming,DEC);
				SerialUSB.print(incoming, HEX); // will output Hex values
				SerialUSB.print(",");
			}
			SerialUSB.println(" ");
		}

	}
}
#endif

#if DEBUG_SUBSYSTEM == 6
void debug_subsystem()
{
	SerialUSB.println("Begin Debug: IMU Subsystem ");
	startup_IMU_ground();
	
	while(1){
		delay(20);
		read_AHRS();
		
		// We are using the IMU
		// ---------------------
		SerialUSB.print("  roll:");
		SerialUSB.print(roll_sensor / 100, DEC);	
		SerialUSB.print("  pitch:");
		SerialUSB.print(pitch_sensor / 100, DEC);
		SerialUSB.print("  yaw:");
		SerialUSB.println(yaw_sensor / 100, DEC);
		
	}
}
#endif

#if DEBUG_SUBSYSTEM == 7
void debug_subsystem()
{
	SerialUSB.println("Begin Debug: Control Switch Test");
	
	while(1){
		delay(20);
		byte switchPosition = readSwitch();
		if (oldSwitchPosition != switchPosition){
			
			switch(switchPosition)
			{
				case 1: // First position
				SerialUSB.println("Position 1");

				break;
		
				case 2: // middle position
				SerialUSB.println("Position 2");
				break;
		
				case 3: // last position
				SerialUSB.println("Position 3");
				break;

				case 4: // last position
				SerialUSB.println("Position 4");
				break;

				case 5: // last position
				SerialUSB.println("Position 5 - Software Manual");
				break;

				case 6: // last position
				SerialUSB.println("Position 6 - Hardware MUX, Manual");
				break;

			}
	
			oldSwitchPosition = switchPosition;
		}
	}
}
#endif

#if DEBUG_SUBSYSTEM == 8
void debug_subsystem()
{
	SerialUSB.println("Begin Debug: Control Switch Test");
	
	while(1){
		delay(20);
		update_servo_switches();
		if (mix_mode == 0) {
			SerialUSB.print("Mix:standard ");
			SerialUSB.print("\t reverse_roll: ");
			SerialUSB.print(reverse_roll, DEC);
			SerialUSB.print("\t reverse_pitch: ");
			SerialUSB.print(reverse_pitch, DEC);
			SerialUSB.print("\t reverse_rudder: ");
			SerialUSB.println(reverse_rudder, DEC);
		} else {
			SerialUSB.print("Mix:elevons ");
			SerialUSB.print("\t reverse_elevons: ");
			SerialUSB.print(reverse_elevons, DEC);
			SerialUSB.print("\t reverse_ch1_elevon: ");
			SerialUSB.print(reverse_ch1_elevon, DEC);
			SerialUSB.print("\t reverse_ch2_elevon: ");
			SerialUSB.println(reverse_ch2_elevon, DEC);
		}
	}
}
#endif


#if DEBUG_SUBSYSTEM == 9
void debug_subsystem()
{
	SerialUSB.println("Begin Debug: Relay");
	pinMode(RELAY_PIN, OUTPUT);
	
	while(1){
		delay(3000);
	
		SerialUSB.println("Relay Position A");
		PORTL |= B00000100;
		delay(3000);
	
		SerialUSB.println("Relay Position B");
		PORTL ^= B00000100;		
	}
}
#endif

#if DEBUG_SUBSYSTEM == 10
void debug_subsystem()
{
	SerialUSB.println("Begin Debug: Magnatometer");
	
	while(1){
		delay(3000);
	}
}
#endif

#if DEBUG_SUBSYSTEM == 11
void debug_subsystem()
{
	ground_alt = 0;
	SerialUSB.println("Begin Debug: Absolute Airpressure");	
	while(1){
		delay(20);
		read_airpressure();
		SerialUSB.print("Air Pressure Altitude: ");
		SerialUSB.print(press_alt / 100, DEC);
		SerialUSB.println("meters");
	}
}
#endif

#if DEBUG_SUBSYSTEM == 12
void debug_subsystem()
{
	ground_alt = 0;
	SerialUSB.println("Begin Debug: Display Waypoints");	
	delay(500);

	eeprom_busy_wait();
	uint8_t options 	= eeprom_read_byte((uint8_t *) EE_CONFIG);

	eeprom_busy_wait();
	int32_t hold = eeprom_read_dword((uint32_t *) EE_ALT_HOLD_HOME);

	// save the alitude above home option
	if(options & HOLD_ALT_ABOVE_HOME){
		SerialUSB.print("Hold this altitude over home: ");
		SerialUSB.print(hold / 100, DEC);
		SerialUSB.println(" meters");
	}else{
		SerialUSB.println("Maintain current altitude ");
	}
	
	SerialUSB.print("Number of Waypoints: ");
	SerialUSB.println(wp_total, DEC);

	SerialUSB.print("Hit radius for Waypoints: ");
	SerialUSB.println(wp_radius, DEC);

	SerialUSB.print("Loiter radius around Waypoints: ");
	SerialUSB.println(loiter_radius, DEC);
	SerialUSB.println(" ");
	
	for(byte i = 0; i < wp_total; i++){
		struct Location temp = get_wp_with_index(i);
		print_waypoint(&temp, i);
	}
	
	while(1){
	}

}
#endif



#if DEBUG_SUBSYSTEM == 13
void debug_subsystem()
{
	SerialUSB.println("Begin Debug: Throttle Subsystem ");
	read_radio();
	
	uint16_t low_pwm = radio_in[CH_THROTTLE];
	uint16_t high_pwm = radio_in[CH_THROTTLE];
	
	while(1){
		delay(20);
		// Filters radio input - adjust filters in the radio.pde file
		// ----------------------------------------------------------
		read_radio();
		//update_throttle();
		set_servos_4();
		low_pwm = min(low_pwm, radio_in[CH_THROTTLE]);
		high_pwm = max(high_pwm, radio_in[CH_THROTTLE]);
		
		SerialUSB.print("Radio_in: ");
		SerialUSB.print(radio_in[CH_THROTTLE], DEC);
		SerialUSB.print("\tPWM output: ");
		SerialUSB.print(radio_out[CH_THROTTLE], DEC);
		SerialUSB.print("\tThrottle: ");
		SerialUSB.print(servo_out[CH_THROTTLE], DEC);
		SerialUSB.print("\tPWM Min: ");
		SerialUSB.print(low_pwm, DEC);
		SerialUSB.print("\tPWM Max: ");
		SerialUSB.println(high_pwm, DEC);
	}
}
#endif


#if DEBUG_SUBSYSTEM == 14
void debug_subsystem()
{
	SerialUSB.println("Begin Debug: Radio Min Max ");
	uint16_t low_pwm[8];
	uint16_t high_pwm[8];
	uint8_t i;
	
	for(i = 0; i < 100; i++){
		delay(20);
		read_radio();
	}
	
	for(i = 0; i < 8; i++){
		radio_min[i] = 0;
		radio_max[i] = 2400;
	 	low_pwm[i]	= radio_in[i];
 		high_pwm[i]	= radio_in[i];
	}
	
	while(1){
		delay(100);
		// Filters radio input - adjust filters in the radio.pde file
		// ----------------------------------------------------------
		read_radio();
		for(i = 0; i < 8; i++){
			low_pwm[i] = min(low_pwm[i], radio_in[i]);
			high_pwm[i] = max(high_pwm[i], radio_in[i]);
		}

		for(i = 0; i < 8; i++){
			SerialUSB.print("CH");
			SerialUSB.print(i + 1, DEC);
			SerialUSB.print(": ");
			low_pwm[i] = min(low_pwm[i], radio_in[i]);
			SerialUSB.print(low_pwm[i], DEC);
			SerialUSB.print("|");
			high_pwm[i] = max(high_pwm[i], radio_in[i]);
			SerialUSB.print(high_pwm[i], DEC);
			SerialUSB.print("   ");
		}
		SerialUSB.println(" ");
	}
}
#endif


#if DEBUG_SUBSYSTEM == 15
void debug_subsystem()
{
	SerialUSB.println("Begin Debug: EEPROM Dump ");
	uint16_t temp;
	for(int n = 0; n < 512; n++){
		for(int i = 0; i < 4; i++){
			temp = eeprom_read_word((uint16_t *) mem);
			mem += 2;
			SerialUSB.print(temp, HEX);
			SerialUSB.print("  ");
		}
		SerialUSB.print("  ");
		for(int i = 0; i < 4; i++){
			temp = eeprom_read_word((uint16_t *) mem);
			mem += 2;
			SerialUSB.print(temp, HEX);
			SerialUSB.print("  ");
		}
	}
}
#endif
