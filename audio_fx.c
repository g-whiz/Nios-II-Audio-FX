#include "audio_codec.h"

#define BUFSIZE 48000

const sample_t audio_buf[BUFSIZE];
int idx_i = 0;
int idx_o = 0;

/* 
 * Called from the ISR in <INSERT-ASM-FILENAME-HERE>. 
 * At this point, interrupts should be disabled.
 */
void on_codec_interrupt() {
	// read available samples to buf
	// write samples from buf to to available space
}

void read_available_samples() {
	
}

void write_available_

int main() {

	// TODO: Enable interrupts (link asm to do this)
	
	int nop = 0;
	while(1){
		nop += 0;
	}
}