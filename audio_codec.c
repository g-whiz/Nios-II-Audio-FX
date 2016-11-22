#include "audio_codec.h"

#define ADDR_CONTROL		((volatile int * const) 0xFF203040)
#define ADDR_FIFOSPACE		(((volatile int * const) 0xFF203040) + 1)
#define ADDR_LEFT_DATA		(((volatile int * const) 0xFF203040) + 2)
#define ADDR_RIGHT_DATA		(((volatile int * const) 0xFF203040) + 3)

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

/* Enable read, write interrupts on the audio codec. */
void codec_enable_interrupts() {
	*ADDR_CONTROL &= 0b11;
}