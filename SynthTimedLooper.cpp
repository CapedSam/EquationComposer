#include "defines.h"
#include "SynthTimedLooper.h"

SynthTimedLooper::SynthTimedLooper(Inputs* inputs)
{

  ModuleTempo *tempo = new ModuleTempo();
  ModuleTimedLooper *timed_looper = new ModuleTimedLooper();
  ModuleFreeze *freeze = new ModuleFreeze();

  // Wire up tempo inputs
  tempo->clock_input = inputs->param2;

  // Wire up looper inputs
  timed_looper->sample_input = inputs->mod;
  timed_looper->sample_rate_input = tempo;
  timed_looper->slice_input = inputs->param3;
  timed_looper->trigger_input = inputs->gate;

  // Send the looper through a freeze effect
  freeze->audio_input = timed_looper;
  freeze->length_input = inputs->param1;

  this->last_module = freeze;
}