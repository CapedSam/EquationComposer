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

// making generic loop names so that swapping is trivial
#define CUSTOM_LOOP_1_LENGTH 58800
#define CUSTOM_LOOP_2_LENGTH 58800
#define CUSTOM_LOOP_3_LENGTH 58800
#define CUSTOM_LOOP_4_LENGTH 58800
extern const uint8_t CUSTOM_LOOP_1[];
extern const uint8_t CUSTOM_LOOP_2[];
extern const uint8_t CUSTOM_LOOP_3[];
extern const uint8_t CUSTOM_LOOP_4[];


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