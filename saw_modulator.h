
#include "audio_codec.h"

#ifndef __SAW_MODULATOR_H__
#define __SAW_MODULATOR_H__

#define SAW_MOD_UP 0
#define SAW_MOD_DOWN 1

struct saw_modulator {
	int wave_sample;
	int wave_height;
	int wave_increment;
	int direction;
};

void saw_modulator_init(struct saw_modulator *sawmod, int direction,
                         unsigned short wave_height, int wave_frequency);
						 
void saw_modulator_apply(struct saw_modulator *sawmod, struct sample *sample);

#endif