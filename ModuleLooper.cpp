#include "Arduino.h"
#include "ModuleLooper.h"
#include "Defines.h"
#include "GlobalLoops.h"
#include "GlobalIncrements.h"

ModuleLooper::ModuleLooper()
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

uint16_t ModuleLooper::compute()
{

  // Read inputs
  uint16_t sample = this->readInput(sample_input, 0,4);  // the range here needs to match the number of samples in the forthcoming switch statement.
  uint16_t trigger = this->readInput(trigger_input);
  uint16_t frequency = this->readInput(sample_rate_input) << 1;
  uint16_t slice = this->readInput(slice_input, CONVERT_TO_4_BIT); // ranges from 0 to 16
  uint16_t sample_length;
  
  // Select sample
  switch (round(sample) - 1)
  {// the number of elements here needs to match the max value in the line above "this->readInput(sample_input, 0, XXX)"
    case 0:
		sample_length = DEVINE_BEAT2_MOD_LENGTH;
		break;
    case 1:
		sample_length = SOD_LOOP1_LENGTH;
		break;
	case 2:
		sample_length = SOD_LOOP2_LENGTH;
		break;
	case 3:
		sample_length = SOD_LOOP3_LENGTH;
		break;
  }

  // Handle trigger events

  if ((trigger >= MID_CV) && !triggered)
  {
	  triggered = true;
	  fixed_point_20_12_index = (slice * (sample_length / 16)) << 12;
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
  {// same requirement for this switch statement as the one above.
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
