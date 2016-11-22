#include "ringModulator.h"

int amplitude = 0x10000;
int triangleIncrement = 0x1000;
int triangleWave = 0;

void ringModulateSample(struct sample *in_sample, struct sample *out_sample){

	triangleWave += triangleIncrement;

	// Start incrementing triangle wave in opposite direction
	if (triangleWave >= amplitude || triangleWave <= amplitude*(-1)){
		triangleIncrement *= -1;
	}

    out_sample->left =  in_sample->left * triangleWave;
    out_sample->right = in_sample->right * triangleWave;
}
