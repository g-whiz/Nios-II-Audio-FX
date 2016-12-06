#include "echo_pan.h"

void init_echo_pan(struct echo_pan * delay, int delay_depth, int period) 
{
	delay->echo_idx = (sbuf->idx_out - delay_depth) % sbuf->buf_len;
	delay->echo_channel = ECHO_PAN_RIGHT;
	delay->period = period;
	delay->count = 0;
}

void apply_echo_pan(struct echo_pan *delay, struct sample *sample)
{
	struct sample *echo_sample = &(sbuf->buf[delay->echo_idx]);
	
	sample->left = delay->echo_channel == ECHO_PAN_LEFT ? echo_sample->left : sample->left;
	sample->right = delay->echo_channel == ECHO_PAN_RIGHT ? echo_sample->right : sample->right;
	
	delay->echo_idx++;
	delay->echo_idx %= sbuf-> buf_len;
	
	delay->count++;
	if (delay->count == delay->period) {
		delay->count = 0;
		delay->echo_channel = delay->echo_channel ^ 1;
	}
}