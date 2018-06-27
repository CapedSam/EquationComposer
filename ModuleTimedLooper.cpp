#include "Arduino.h"
#include "ModuleTimedLooper.h"
#include "Defines.h"
#include "GlobalLoops.h"
#include "GlobalIncrements.h"

ModuleTimedLooper::ModuleTimedLooper()
{
  t = 0;  // Sample index
  w = 0;  // Final output
  fixed_point_20_12_index = 0;
  triggered = false; 

  // Initialize all inputs  
  this->sample_input = NULL;
  this->trigger_input = NULL;  
  this->sample_rate_input = NULL; 
  this->slice_input = NULL;    
}

uint16_t ModuleTimedLooper::compute()
{

  // Read inputs
  uint16_t sample = this->readInput(sample_input, 0, 4);
  uint16_t trigger = this->readInput(trigger_input);
  uint16_t frequency = this->readInput(sample_rate_input);
  uint16_t sample_length;
  uint16_t loop_length; //in terms of number of 16th notes.

  // Select sample


  switch(round(sample)-1)
  {
    case 0:
		sample_length = DEVINE_BEAT2_MOD_LENGTH;
		loop_length = 22;
		break;
    case 1:
		sample_length = SOD_LOOP1_LENGTH;
		loop_length = 22;
		break;
	case 2:
		sample_length = SOD_LOOP2_LENGTH;
		loop_length = 22;
		break;
	case 3:
		sample_length = SOD_LOOP3_LENGTH;
		loop_length = 22;
		break;
  }

 // Serial.print("Timed Looper:  ");
  //Serial.print("Incoming frequency = ");
  //Serial.print(frequency);


  //frequency = ((sample_length) / (loop_length)) *(4096 / frequency);


  frequency = (float)(4096 * (sample_length / loop_length) / frequency);
  
  //Serial.print(", Outgoing frequency = ");
//Serial.println(frequency);

  // Adjust the slice based on the number of eighth notes in the particular sample.
  uint16_t slice = this->readInput(slice_input, 1, 18); 


  // Handle trigger events

  if ((trigger >= MID_CV) && !triggered)
  {
	  triggered = true;
	  // this line was edited from the original ModuleLooper
	  fixed_point_20_12_index = (slice * (sample_length / loop_length)) << 12;  
  }

  if ((trigger < MID_CV) && triggered)
  {
	  triggered = false;
  }

  // Playback selected sample

  t = fixed_point_20_12_index >> 12;

  if (t >= sample_length)
  {
	  t = t - sample_length;
	  fixed_point_20_12_index = t << 12;
  }

  switch(sample)
  {
    case 0:
		w = DEVINE_BEAT2_MOD[t];
      break;

	case 1:
		w = SOD_LOOP1[t];
		break;
	case 2:
		w = SOD_LOOP2[t];
		break;

	case 3:
		w = SOD_LOOP3[t];
		break;
  }
  

  fixed_point_20_12_index += frequency;


  return(w<<4);
}
