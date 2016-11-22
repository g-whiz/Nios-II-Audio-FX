#include "sample_buf.h"

#define BUFSIZE 48000
#define MIN(L, R)	(L <= R ? L : R)

struct sample sample_buf[BUFSIZE];
struct sample_buffer sbuf_internal =
				    {.buf = (struct sample * const) sample_buf,
					 .buf_len = BUFSIZE,
					 .idx_in = 0,
					 .idx_out = 0};

struct sample_buffer * const sbuf = &sbuf_internal;

void sbuf_update_in_samples(void) {
	unsigned int num_samples = MIN(fifospace->read_l, fifospace->read_r);

	for (; num_samples > 0; num_samples--) {
		sbuf->buf[sbuf->idx_in].left = codec_data->left;
	    sbuf->buf[sbuf->idx_in].right = codec_data->right;

		sbuf->idx_in++;
		sbuf->idx_in %= sbuf->buf_len;
	}
}