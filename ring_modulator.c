#include "ring_modulator.h"

#define DIVISOR 10;

void ring_modulator_init(struct ring_modulator *ringmod,
                         unsigned short wave_height, int wave_frequency) {
  ringmod->wave_sample = 0;
  ringmod->wave_height = wave_height;

  // given 48000 samples/sec, for a wave to have the given frequency,
  // the sample must
  ringmod->wave_increment = (4 * wave_height) / (48000 / wave_frequency);
}

void ring_modulator_apply(struct ring_modulator *ringmod, struct sample *sample) {
	int wave_sample = ringmod->wave_sample;
	int wave_height = ringmod->wave_height;
	
	sample->left /= wave_height;
	sample->right /= wave_height;
	
	sample->left *= wave_sample;
	sample->right *= wave_sample;
	
	ringmod->wave_sample += ringmod->wave_increment;
	if (ringmod->wave_sample >= ringmod->wave_height
		|| ringmod->wave_sample <= -1 * ringmod->wave_height) {
		ringmod->wave_increment *= -1;
	}
}
