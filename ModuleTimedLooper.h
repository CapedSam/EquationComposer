/*
 *  +------------------------+
 *  | ModuleTimedLooper           |
 *  |------------------------|
 *  > sample_input           |
 *  > sample_rate_input      |
 *  > slice_input            |
 *  > trigger_input          |
 *  |                 output >
 *  +------------------------+
 *
 */
// =============================================================================
// 
//

#ifndef ModuleTimedLooper_h
#define ModuleTimedLooper_h

#include "Arduino.h"
#include "Module.h"

class ModuleTimedLooper : public Module
{
  
  public:
    ModuleTimedLooper();
    uint16_t compute();

    // Inputs
    Module *sample_input;
    Module *sample_rate_input;    
    Module *slice_input;
    Module *trigger_input;

  private:
    boolean triggered;
    boolean playing;
    
    uint32_t t;  // Accumulator used in equations 
    uint32_t w;  // The final output
    
    uint32_t fixed_point_20_12_index;

    void stop_playback();
};

#endif
