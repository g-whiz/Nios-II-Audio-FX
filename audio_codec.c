#include "audio_codec.h"

volatile int * const audio_ptr = (int *) 0xFF203040;

volatile struct sample * const codec_data = 
	(volatile struct sample * const) ADDR_LEFT_DATA;
volatile struct fifospace * const fifospace = 
	(volatile struct fifospace * const) ADDR_FIFOSPACE;


int read_is_pending(void) {
	// return the 8th bit of the audio codec's control register
	return (1 << 8) & *ADDR_CONTROL;
}

int write_is_pending(void) {
	return (1 << 9) & *ADDR_CONTROL;
}

void codec_enable_interrupts() {
	*ADDR_CONTROL |= 0b11;
}