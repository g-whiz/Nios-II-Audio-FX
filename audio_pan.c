#include "audio_pan.h"

void audio_pan_init(struct audio_pan *pan, unsigned int max) {
	pan->max = max;
	pan->curr = 0;
	pan->increment = 1;
}

void audio_pan_apply(struct audio_pan *pan, struct sample *sample){
	
	sample->left = sample->right / pan->max * (pan->max - pan->curr);
	sample->right = sample->left / pan->max * pan->curr;
	pan->curr += pan->increment;
	
	if (pan->curr >= pan->max || pan->curr <= 0){
		pan->increment *= -1;
	}
}