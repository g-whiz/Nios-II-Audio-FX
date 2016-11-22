#include "sample_buf.h"

#define BUFSIZE 48000

Sample sample_buf[BUFSIZE];
SampleBuffer sbuf = {.buf = &sample_buf,
					 .buf_len = BUFSIZE,
					 .idx_in = 0,
					 .idx_out = 0};

/* 
 * Returns a ptr to the next sample to output to LINE OUT and advances
 * sbuf's idx_out.
 */
Sample *sbuf_out_next(SampleBuffer *sbuf) {
	Sample *next = &(sbuf->buf[sbuf->idx_out])
}

bool sbuf_out_has_next(SampleBuffer *sbuf) {
	return sbuf->idx_out != sbuf->idx_in;
}

/* 
 * Returns a ptr to the next sample to read input from MIC to and advances
 * sbuf's idx_in.
 */
Sample *sbuf_in_next(SampleBuffer *sbuf);