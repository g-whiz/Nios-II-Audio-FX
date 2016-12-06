#include "sample_buf.h"

#ifndef __ECHO_PAN_H__
#define __ECHO_PAN_H__

#define ECHO_PAN_RIGHT 0
#define ECHO_PAN_LEFT 1

struct echo_pan {
	int echo_idx;
	int echo_channel;
	int period;
	int count;
};

/*
	delay_depth: depth of the delay in number of samples
*/
void init_echo_pan(struct echo_pan * delay, int delay_depth, int period);

void apply_echo_pan(struct echo_pan *delay, struct sample *sample);

#endif