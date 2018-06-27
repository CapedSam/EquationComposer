/*
 *  +----------------------+
 *  | ModuleTimeMachine    |
 *  |----------------------|
 *  > tempo                |
 *  > clock_multiplier     |
 *  > mult_clock_count     |
 *  |               output >
 *  +----------------------+
 *
 *  ------------------------------------------------------------------------------
 *  This module takes a tempo, in terms of number of samples per beat, and outputs a new 
 *  tempo, which has been divided in length by the "clock multiplier" input, and which has 
 *  been multiplied in length by the "mult_clock_count" input.
 *
 *
 */
 
#ifndef ModuleTimeMachine_h
#define ModuleTimeMachine_h

#include "Arduino.h"
#include "Module.h"

class ModuleTimeMachine : public Module
{
  public:
    ModuleTimeMachine();
    uint16_t compute();

    // Inputs
	// The input to this module should be a periodic clock pulse. 
	// The rising edges will be 'observed' by this module, and a number will be returned that indicates
	// the duration of one 'beat' in terms of number of samples TIMES the clock division input.
	Module *tempo_input;
	Module *clk_multiplier_input;
	Module *mult_clk_count_input;

private:
	uint32_t full_time_travel_distance = 44100;
};

#endif
