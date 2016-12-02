#include "audio_codec.h"

#ifndef __AUDIO_PAN_H__
#define __AUDIO_PAN_H__

struct audio_pan {
	unsigned int max;
	unsigned int curr;
	signed int increment;
};

void audio_pan_init(struct audio_pan *pan, unsigned int max);

void audio_pan_apply(struct audio_pan *pan, struct sample *sample);

#endif