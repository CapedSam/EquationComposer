/*
 *  +----------------------+
 *  | ModuleDrumSequencer  |
 *  |----------------------|
 *  > clock_input          |
 *  |                      |
 *  > kick_pattern_input   |
 *  > snare_pattern_input  |
 *  > hat_pattern_input    |
 *  |                      |
 *  |          kick_output >
 *  |         snare_output >
 *  |           hat_output >
 *  +----------------------+
 *
 */
// =============================================================================
// 
// ModuleDrumSequencer is a simple gate sequencer for drums.  It contains three 
// different pattern generators, one for kick, snare, and hihat.
//
// TODO: create example
//

#ifndef ModuleDrumSequencer32_h
#define ModuleDrumSequencer32_h

#include "Arduino.h"
#include "Module.h"
#include "ModuleOutput.h"


class ModuleDrumSequencer32 : public Module
{
  
  public:
    ModuleDrumSequencer32();
    uint16_t compute();
    
    // Inputs
    Module *clock_input;
    Module *kick_pattern_input;
    Module *snare_pattern_input;
    Module *hihat_pattern_input;
    
    // Outputs
    ModuleOutput *kick_output;
    ModuleOutput *snare_output;
    ModuleOutput *hihat_output;    

  private:
    uint8_t step;
    boolean clocked;

    uint32_t patterns[3][16] = {
        { 
          // Bank #0 = kick patterns         
          2147516416,    // 10000000 00000000 10000000 00000000
          2147518496,    // 10000000 00000000 10001000 00100000
          2282227720,    // 10001000 00001000 00001000 00001000
          2315813384,    // 10001010 00001000 10000010 00001000
          2281736192,    // 10001000 00000000 10001000 00000000
          2282227712,    // 10001000 00001000 00001000 00000000
          2147616776,    // 10000000 00000010 00001000 00001000
          2181071360,    // 10000010 00000000 10000010 00000000
        
          2147524640,    // 10000000 00000000 10100000 00100000
          2147518466,    // 10000000 00000000 10001000 00000010
          2149580930,    // 10000000 00100000 00000000 10000010
          2149581314,    // 10000000 00100000 00000010 00000010
           169869314,    // 00001010 00100000 00000000 00000010
          2283806722,    // 10001000 00100000 00100000 00000010
          2151680008,    // 10000000 01000000 00001000 00001000
          2181073409     // 10000010 00000000 10001010 00000001          
        },
        {
          // Bank #1 = snare patterns
             8388736,    // 00000000 10000000 00000000 10000000
             8528514,    // 00000000 10000010 00100010 10000010
             8421544,    // 00000000 10000000 10000000 10101000
             8388738,    // 00000000 10000000 00000000 10000010
               32768,    // 00000000 00000000 10000000 00000000
            41943040,    // 00000010 10000000 00000000 00000000
            41943168,    // 00000010 10000000 00000000 10000000
             8423976,    // 00000000 10000000 10001010 00101000

             8392704,    // 00000000 10000000 00010000 00000000
           142746242,    // 00001000 10000010 00100010 10000010 
             8421512,    // 00000000 10000000 10000000 10001000
             8388738,    // 00000000 10000000 00000000 10000010
           268468224,    // 00010000 00000000 10000000 00000000
            37748736,    // 00000010 10000000 00010000 00000000
            41947136,    // 00000010 10000000 10111111 10000000
             8388848     // 00000000 10000000 00000000 11110000
        },
        {
          // Bank #2 = hihat patterns
          2863311530,    // 10101010 10101010 10101010 10101010
          2290649224,    // 10001000 10001000 10001000 10001000
          2318043690,    // 10001010 00101010 10001010 00101010
          2318051496,    // 10001010 00101010 10101000 10101000
          2282228394,    // 10001000 00001000 00001010 10101010
          2149581312,    // 10000000 00100000 00000010 00000000
          2148050984,    // 10000000 00001000 10101000 00101000
           572662314,    // 00100010 00100010 00100010 00101010

          4294967295,    // 11111111 11111111 11111111 11111111
          4008636142,    // 11101110 11101110 11101110 11101110
          2401931051,    // 10001111 00101010 10001111 00101011
          2318051496,    // 10001010 00101010 10101000 10101000
          2282228399,    // 10001000 00001000 00001010 10101111
          2153775616,    // 10000000 01100000 00000010 00000000
          2164828200,    // 10000001 00001000 10101000 00101000
          1646404394     // 01100010 00100010 00100011 00101010
        }    
    };

};

#endif
