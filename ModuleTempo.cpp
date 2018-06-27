#include "Arduino.h"
#include "ModuleTempo.h"
#include "defines.h"


ModuleTempo::ModuleTempo()
{
  // 'counter' (IS NOT NEEDED?)
  //this->counter = 0;  

  // 'last_state_high' records the status (high = true, low = false) of the external clock input from the last cycle
	last_state_high = true;

  // Boolean to indicate if we are currently looking at a rising edge
  //rising_edge = false;

  // 'ext_clock_counter' is used to measure the time between external rising edges
  ext_clock_counter = 0;

}


uint16_t ModuleTempo::compute()
{
	// Check value at the external clock input.  
	uint32_t clock = this->readInput(clock_input);

	// if input is low, then we're not at a rising edge
	if ((clock < MID_CV))
	{
		rising_edge = false;
		last_state_high = false;
	}
	// otherwise, the input is high, so it's possible we're at a rising edge, but only if the last state was low.
	else
	{
		if (last_state_high)
		{
			//if the last cycle is high, then we're not at a rising edge
			rising_edge = false;
		}
		else
		{
			// we're at a rising edge
			rising_edge = true;
		}
		last_state_high = true;
	}

	if (!rising_edge)
	{
		//increment counter
		ext_clock_counter++;
	    //return existing bpm
	}
	else
	{
		//return the appropriate number of samples corresponding to the bpm.
		calculated_bpm = ext_clock_counter;
		ext_clock_counter = 0;
	}
  return(calculated_bpm);
}
