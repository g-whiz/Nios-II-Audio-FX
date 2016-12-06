#include "echo_delay.h"

void init_echo_delay(struct echo_delay * delay, int delay_depth, int delay_frac) 
{
	delay->echo_idx = (sbuf->idx_out - delay_depth) % sbuf->buf_len;
	delay->frac = delay_frac;
}

void apply_echo_delay(struct echo_delay *delay, struct sample *sample)
{
	struct sample out_sample;
	struct sample *echo_sample = &(sbuf->buf[delay->echo_idx]);
	
	out_sample.left = echo_sample->left / delay->frac;
	out_sample.right = echo_sample->right / delay->frac;
	
	out_sample.left += sample->left / delay->frac;
	out_sample.right += sample->right / delay->frac;
	
	sample->left = out_sample.left;
	sample->right = out_sample.right;
	
	delay->echo_idx++;
	delay->echo_idx %= sbuf-> buf_len;
}