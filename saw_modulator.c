#include "saw_modulator.h"

#define DIVISOR 10;

void saw_modulator_init(struct saw_modulator *sawmod, int direction,
                         unsigned short wave_height, int wave_frequency) {
  sawmod->wave_sample = 0;
  sawmod->wave_height = wave_height;
  sawmod->direction = direction;

  // given 48000 samples/sec, for a wave to have the given frequency,
  // the sample must
  sawmod->wave_increment = (4 * wave_height) / (48000 / wave_frequency);
  if (direction == SAW_MOD_DOWN) {
	  sawmod->wave_increment *= -1;
  }
}

void saw_modulator_apply(struct saw_modulator *sawmod, struct sample *sample) {
	int wave_sample = sawmod->wave_sample;
	int wave_height = sawmod->wave_height;
	
	sample->left /= wave_height;
	sample->right /= wave_height;
	
	sample->left *= wave_sample;
	sample->right *= wave_sample;
	
	sawmod->wave_sample += sawmod->wave_increment;
	if (sawmod->wave_sample >= sawmod->wave_height && sawmod->direction == SAW_MOD_UP) {
		sawmod->wave_sample = -1 * sawmod->wave_height;
		return;
	}
		
	if (sawmod->wave_sample <= -1 * sawmod->wave_height && sawmod->direction == SAW_MOD_DOWN) {
		sawmod->wave_sample = sawmod->wave_height;
	}
}
