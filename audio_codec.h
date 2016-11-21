#include "audio_codec.h"

#define CONTROL(ptr)	*(ptr)
#define FIFOSPACE(ptr)	*(ptr + 1)
#define LEFT_DATA(ptr) 	*(ptr + 2)
#define RIGHT_DATA(ptr) *(ptr + 3)

volatile int *audio_ptr = (int *) 0xFF203040;

void write_sample(Sample *s) {
	LEFT_DATA(audio_ptr) = s->left;
	RIGHT_DATA(audio_ptr) = s->right;
}

void read_sample(Sample *s) {
	s->left = LEFT_DATA(audio_ptr);
	s->right = RIGHT_DATA(audio_ptr);
}

void get_fifospace(Fifospace *fspace) {
	*fspace = (Fifospace) FIFOSPACE(audio_ptr);
}