#include "Arduino.h"

#ifndef GOBAL_LOOPS
#define GOBAL_LOOPS

// Loops by Richard Devine

#define DEVINE_BEAT1_LENGTH 29669
#define DEVINE_BEAT2_LENGTH 29730
#define SIGNS_SONG5_BEAT1_LENGTH  47676

// actual number should be 65554
#define DEVINE_BEAT2_MOD_LENGTH 64969
#define SOD_LOOP1_LENGTH 64969
#define SOD_LOOP2_LENGTH 64969
#define SOD_LOOP3_LENGTH 64969

#define TRUCHAN_BEAT1_LENGTH 36873

extern const uint8_t DEVINE_BEAT1[]; 
extern const uint8_t DEVINE_BEAT2[];
extern const uint8_t SIGNS_SONG5_BEAT1[];


extern const uint8_t DEVINE_BEAT2_MOD[];
extern const uint8_t SOD_LOOP1[];
extern const uint8_t SOD_LOOP2[];
extern const uint8_t SOD_LOOP3[];


extern const uint8_t TRUCHAN_BEAT1[];

#endif