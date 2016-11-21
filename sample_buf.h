#include "audio_codec.h"

typedef int bool;

typedef struct {
	Sample *buf;
	unsigned int 	buf_len, 	// length of buf
					idx_in, 	// idx of the next free spot to read a sample
					idx_out;	// idx of the next sample to output
} SampleBuffer;

extern SampleBuffer sbuf;

/* 
 * Returns a ptr to the next sample to output to LINE OUT and advances
 * sbuf's idx_out.
 */
Sample *sbuf_out_next(SampleBuffer *sbuf);

/* 
 * Returns a ptr to the next sample to read input from MIC to and advances
 * sbuf's idx_in.
 */
Sample *sbuf_in_next(SampleBuffer *sbuf);

