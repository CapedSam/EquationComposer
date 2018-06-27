#include "Arduino.h"
#include "ModuleClockAccelerator.h"
#include "defines.h"

ModuleClockAccelerator::ModuleClockAccelerator()
{


	last_state = true;
	pulse_timer = 0;
	pulse_counter = 0;
	
	/* Do I need to be initializing all of the inputs here?*/


}



uint16_t ModuleClockAccelerator::compute()
{
	// RISING EDGE DETECTOR
	// Check value at the external trigger input.  

	uint32_t trigger = this->readInput(trigger_input);

	// Want this to happen often, to read inputs for ModuleTimeMachine always, 
	// and not just at the instance of a rising edge.
	distance = this->readInput(distance_input);

	/*Serial.print("ModuleClockAccelerator trigger value: ");
	Serial.print(trigger);
	Serial.print(", and the distance value: ");
	Serial.println(distance);*/
	uint16_t new_pulse = 1;		
	//Serial.println("OK, well at least we know we're getting here quite often.");


	if ((trigger < MID_CV))
	{
		// if input is low, then we're not at a rising edge
		rising_edge = false;
		last_state = false;
	}
	else
	{ 
		if (last_state)
		{
			//if the last cycle is high, then we're not at a rising edge
			rising_edge = false;
		}
		else
		{
			// we're at a rising edge
			rising_edge = true;
		}
		// Set last_state here to indicate for the next cycle.
		last_state = true;
	}
	if (!rising_edge)  // NOT A RISING EDGE
	{
		//increment pulse timer
		pulse_timer++;

		// just so nobody gets mad when we ask for the "pulse_counter-th" 
		// entry into an array of length 'nPulses'.
		if (pulse_counter <= nPulses)
		{


			//Serial.println("Not always, right?");
			if (pulse_timer == PulseArray[pulse_counter])
			{

				
				// then we're starting a new output pulse.
				//Serial.println("Create a new trigger from the PulseArray.");

				//Serial.print("nPulses = ");
				//Serial.println(nPulses);
				//Serial.print("pulse_counter = ");
				//Serial.println(pulse_counter);

				/*
				Serial.print("pulse_timer = ");
				Serial.print(pulse_timer);
				Serial.print(" = ");
				Serial.print(PulseArray[pulse_counter]);
				Serial.println(" = PulseArray[pulse_counter]");
				*/

				pulse_counter++;
				new_pulse = MAX_CV;
				//Serial.println("But oftentimes, yes.");
			}
			else
			{
				// then we're NOT starting a new pulse.
				new_pulse = 1;
			}
		}
		else
		{
			new_pulse = 1;
		}
	}
	else  // FOUND A NEW RISING EDGE
	{
		pulse_timer		= 0;
		pulse_counter	= 0; 
		nPulses = this->readInput(pulse_count_input, 2, 512);
		acc				= this->readInput(accel_input); 

		float alpha= (float)(0.0);

		// This is sort of a "width" factor for the range of alpha.
		float gamma = (float)(1 / 2.0);

		if (acc < 2048)
		{
			// these two cases are simply point-slope form interpolating between two points in (acc, a) space.
			// the first is between the points (0, c) and (2048, 1).
			alpha = (float)((((1 - (gamma)) / 2048)*(acc)) + gamma);
		}			
		else
		{
			// the second is between the points (2048,1) and (4096, 1/c).
			alpha = (float)(((1.0 / gamma) - 1.0)*((acc - 2048.0) / (2048.0)) + 1.0);
		}
		

		// Essentially the following is because the first pulse occurs on
		// pulse_timer = 0, and we don't need to store that in the PulseArray.
		nPulses = nPulses + 1;

		// Implementing geometric progression-inspired derived formula for the "length of the longest
		// increment between pulses".
		if (alpha== 1)
		{
			increment = float(distance / nPulses);
		}
		else
		{
			increment = float(distance*(1 - (1 / alpha)) / (1 - (1 / (pow(alpha, nPulses)))));

		}

		pulse_location = 0; // Always start with a pulse immediately and build from there.
		
		float sum = (float)increment;
		for (uint8_t pulse_i = 0; pulse_i < nPulses; pulse_i++)
		{
			pulse_location = pulse_location + round(increment);
			PulseArray[pulse_i] = pulse_location;
			increment = float(increment / alpha);
			sum = sum + increment;
		}

		// start new output pulse
		new_pulse = MAX_CV;

	}
	return(new_pulse);
}
