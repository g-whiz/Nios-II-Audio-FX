#include <stdio.h>

#include "audio_codec.h"
#include "sample_buf.h"

#define MIN(L, R)	(L <= R ? L : R)

void sbuf_update_out_samples(void) {
	unsigned int num_samples = MIN((sbuf->idx_in - sbuf->idx_out),
								   MIN(fifospace->write_l, fifospace->write_r));

	for (; num_samples > 0; num_samples--) {
		*ADDR_LEFT_DATA = sbuf->buf[sbuf->idx_out].left;
		*ADDR_RIGHT_DATA = sbuf->buf[sbuf->idx_out].right;

		sbuf->idx_out++;
		sbuf->idx_out %= sbuf->buf_len;
	}
}

void ctl_enable_interrupts(void) {
	
	__asm__ (
		"movi r8, 0b01000000\n"
		"wrctl ctl3, r8\n"
		
		"rdctl r8, ctl0\n"
		"ori r8, r8, 0b01\n"
		"wrctl ctl0, r8\n"
	);
	return;
	
}

void on_codec_interrupt(void) {
	if (read_is_pending()) {
		sbuf_update_in_samples();
	}
	
	if (write_is_pending()) {
		sbuf_update_out_samples();
	}
}

int main() {
	printf("sbuf: %p", sbuf);
	
	codec_enable_interrupts();
	ctl_enable_interrupts();

	while(1) {}
}