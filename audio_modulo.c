#include "audio_modulo.h"

void audio_modulo_init(struct audio_modulo *modulo, unsigned int modulus) {
	modulo->modulus = modulus;
}

void audio_modulo_apply(struct audio_modulo *modulo, struct sample *sample){
	
	sample->left = sample->left > 0 ? sample->left % modulo->modulus : -1 * (sample->left % modulo->modulus);
	sample->right = sample->right > 0 ? sample->right % modulo->modulus : -1 * (sample->right % modulo->modulus);
	
}