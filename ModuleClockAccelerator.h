/*
 *  +----------------------+
 *  | ModuleClockAccelerator       |
 *  |----------------------|
 *  > clock_input          |
 *  |               output >
 *  +----------------------+
 *
 *
 */
 
#ifndef ModuleClockAccelerator_h
#define ModuleClockAccelerator_h

#include "Arduino.h"
#include "Module.h"

class ModuleClockAccelerator : public Module
{
  public:
    ModuleClockAccelerator();
    uint16_t compute();

    // Inputs
	Module *pulse_count_input;
	Module *accel_input;
	Module *distance_input;
	Module *trigger_input;
	
  private:
	uint8_t nPulses;
	uint32_t acc;
	uint32_t distance;
	uint32_t trigger;

	//uint32_t increment;
	float increment;
	uint32_t pulse_location;
	uint16_t pulse_timer;
	uint16_t pulse_counter;
	uint16_t new_pulse;
	  
	boolean last_state;
	boolean rising_edge;

    uint16_t PulseArray[512];

};

#endif
