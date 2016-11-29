#include "ring_modulator.h"

int amplitude = 0x10000;
int triangleIncrement = 0x1000;
int triangleWave = 0;

void ringModulateSample(struct sample *in_sample, struct sample *out_sample) {

  triangleWave += triangleIncrement;

  // Start incrementing triangle wave in opposite direction
  if (triangleWave >= amplitude || triangleWave <= amplitude * (-1)) {
    triangleIncrement *= -1;
  }

  out_sample->left = in_sample->left * triangleWave;
  out_sample->right = in_sample->right * triangleWave;
}

void ring_modulator_init(struct ring_modulator *ringmod,
                         unsigned short wave_height, int wave_frequency) {
  ringmod->wave = 0;
  ringmod->wave_height = wave_height;

  // given 48000 samples/sec, for a wave to have the given frequency,
  // the sample must
  ringmod->wave_increment = (2 * wave_height) / (48000 / wave_frequency)
}
