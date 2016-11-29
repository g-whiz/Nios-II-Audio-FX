#include "sample_buf.h"

#ifndef __ECHO_DELAY_H__
#define __ECHO_DELAY_H__

struct echo_delay {
	int echo_idx;
	int frac;
};

/*
	delay_depth: depth of the delay in number of samples
	delay_frac:  1 delay_frac'th of output is echo
*/
void init_echo_delay(struct echo_delay * delay, int delay_depth, int delay_frac);

void apply_echo_delay(struct echo_delay *delay, struct sample *sample);

#endif