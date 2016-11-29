
#include "audio_codec.h"

#ifndef __RING_MODULATOR_H__
#define __RING_MODULATOR_H__

struct ring_modulator {
	int wave_sample;
	int wave_height;
	int wave_increment;
};

void ring_modulator_init(struct ring_modulator *ringmod,
                         unsigned short wave_height, int wave_frequency);
						 
void ring_modulator_apply(struct ring_modulator *ringmod, struct sample *sample);

#endif