#include <stdio.h>
#include <stdlib.h>

int amplitude = 100;
int triangleIncrement = 5;
int triangleWave = 0;

typedef struct {
	int right;
	int left;
} sample_t;

void ringModulateSample(sample_t sample, sample_t* newSample){

	triangleWave += triangleIncrement;

	// Start incrementing triangle wave in opposite direction
	if (triangleWave >= amplitude || triangleWave <= amplitude*-1){
		triangleIncrement *= -1;
	}

    newSample->left =  sample.left * triangleWave;
    newSample->right = sample.right * triangleWave;
}
