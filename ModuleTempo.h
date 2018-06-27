/*
 *  +----------------------+
 *  | ModuleTempo          |
 *  |----------------------|
 *  > clock_input          |
 *  |               output >
 *  +----------------------+
 *
 *  ------------------------------------------------------------------------------
 *  When an external clock signal is present at clock_input, that signal
 *  is passed through to the output, and the internal clock generator is suspended.  
 *  This module is great for creating synths that can run off of either an 
 *  internally generated clock or externally supplied clock signal.
 *  ------------------------------------------------------------------------------
 *
 *  The ext clock module produces a square wave with a 50% duty cycle starting low.
 *           _____       _____
 *          |     |     |     |
 *     _____|     |_____|     |  etc...
 *
 *  The clock speed is controlled via a BPM (beats per minute) value supplied during
 *  instantiation, like: 
 * 
 *    ModuleTempo *ext_clock = new ModuleTempo(120);
 *    ext_clock->clock_input = inputs->gate;
 *    drum_sequencer->clock_input = ext_clock; 
 *
 *
 *  The output is 96 pulses per quarter note.  A second parameter can be supplied
 *  in the constructor to act as a clock divider.  To have the clock output
 *  quarter note pulses, we divide the 96 pulses-per-quarter-note by 96:
 *
 *    ModuleTempo *ext_clock = new ModuleTempo(120,96);
 *    ext_clock->clock_input = inputs->gate;
 *    drum_sequencer->clock_input = ext_clock; 
 *
 *  Helpful clock divisions have been defined in defines.h.  
 *
 * 
 *  ModuleTempo *module_ext_clock = new ModuleTempo(120, 48);                          // produce 1/8th note gates at 120 BPM
 *  ModuleTempo *module_ext_clock = new ModuleTempo(120, EIGHTH_NOTE_CLOCK_DIVISION);  // produce 1/8th note gates at 120 BPM
 *  ModuleTempo *module_ext_clock = new ModuleTempo(100, QUARTER_NOTE_CLOCK_DIVISION); // produce 1/4th note gates at 100 BPM
 *  ModuleTempo *module_ext_clock = new ModuleTempo(100, WHOLE_NOTE_CLOCK_DIVISION);   // produce whole note gates at 100 BPM
 *
 */
 
#ifndef ModuleTempo_h
#define ModuleTempo_h

#include "Arduino.h"
#include "Module.h"

class ModuleTempo : public Module
{
  public:
    //ModuleTempo(uint16_t clock_division);
	  ModuleTempo();
    uint16_t compute();

    // Inputs
	// The input to this module should be a periodic clock pulse. 
	// The rising edges will be 'observed' by this module, and a number will be returned that indicates
	// the duration of one 'beat' in terms of number of samples TIMES the clock division input.
    Module *clock_input;  


  private:
    //uint32_t rate;
    //uint32_t counter;
    //uint8_t bpm;
    //uint16_t bpm_ppqn[255];
    //uint16_t bpm_half_ppqn[255];
    //boolean ext_clocked;    


	boolean last_state_high;
	boolean rising_edge;
	uint16_t calculated_bpm; // just give some initial value for this.
    uint32_t ext_clock_counter;
};

#endif
