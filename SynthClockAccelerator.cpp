#include "defines.h"
#include "SynthClockAccelerator.h"

SynthClockAccelerator::SynthClockAccelerator(Inputs* inputs)
{
	ModuleClockAccelerator *accel	= new ModuleClockAccelerator();
	ModuleTimeMachine *time_machine = new ModuleTimeMachine();
	ModuleTempo *tempo				= new ModuleTempo();
	ModuleSamplePlayer *player		= new ModuleSamplePlayer();

	// Incoming tempo will be calculated from param 3 through ModuleTempo.
	tempo->clock_input = inputs->param3;


	// Determine total length via time machine:
	time_machine->tempo_input = tempo;
	//time_machine->clk_multiplier_input = inputs->param2;
	time_machine->clk_multiplier_input = new ModuleConstant(1);
	time_machine->mult_clk_count_input = inputs->param1;

	// Wire up ModuleAccelerator to provide accelerated clock pulses.
	accel->pulse_count_input = inputs->sr;
	accel->accel_input = inputs->mod;
	accel->distance_input = time_machine;
	
	
	// This works well, but is just for debugging sake, tying the distance_input to Param 2.
	//accel->distance_input = inputs->param2;




	accel->trigger_input = inputs->gate;

	// Finally, use the SamplePlayer to test the ouptut
	player->sample_selection_input = inputs->param2;
	player->trigger_input = accel;
	player->sample_rate_input = new ModuleConstant(22050);

	this->last_module = player;
}