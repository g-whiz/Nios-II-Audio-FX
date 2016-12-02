#include "audio_codec.h"

#ifndef __AUDIO_MODULO_H__
#define __AUDIO_MODULO_H__

struct audio_modulo {
	unsigned int modulus;
};

void audio_modulo_init(struct audio_modulo *modulo, unsigned int modulus);

void audio_modulo_apply(struct audio_modulo *modulo, struct sample *sample);

#endif