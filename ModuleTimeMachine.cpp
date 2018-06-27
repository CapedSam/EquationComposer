#include "Arduino.h"
#include "ModuleTimeMachine.h"
#include "defines.h"


ModuleTimeMachine::ModuleTimeMachine()
{

// No known initilization needed in the constructor.

}


uint16_t ModuleTimeMachine::compute()
{
	uint16_t tmp = this->readInput(tempo_input);
	
	//Serial.println("tmp = ");
	//Serial.println(tmp);

	uint16_t cm = this->readInput(clk_multiplier_input);
	
	//Serial.print("cm = ");
	//Serial.println(cm);

	// The "tempo div by clock multiplier" quantity, (tmp/cm) can 
	// be thought of as the "sub beat" that the distance will be 
	// measured by.  For instance, if the input tempo is based on 
	// quarter notes, and cm = 2, then (tmp/cm) will represent 
	// eighth notes.

	// The "mcc" or "multiplyer for clock count" will represent 
	// the number of (tmp/cm) beats to use for the total time travel distance.

	uint16_t mcc = this->readInput(mult_clk_count_input, 1, 32);

	Serial.print("mcc = ");
	Serial.println(mcc);

	full_time_travel_distance = mcc*(tmp / cm);

	/*
	Serial.print("mcc = ");
	Serial.println(mcc);
	Serial.print("tmp = ");
	Serial.println(tmp);
	Serial.print("full_time_travel_distance = ");
	Serial.println(full_time_travel_distance);
	*/

	return(full_time_travel_distance);
}
