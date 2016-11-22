#include "audio_codec.h"

#ifndef __SAMPLE_BUF_H__
#define __SAMPLE_BUF_H__


struct sample_buffer {
	struct sample * const buf;
	unsigned int 	buf_len, 	// length of buf
					idx_in, 	// idx of the next free spot to read a sample
					idx_out;	// idx of the next sample to output
};

extern struct sample_buffer * const sbuf;

/* Reads all available samples in from the audio codec. */
void sbuf_update_in_samples(void);


#endif /* __SAMPLE_BUF_H__ */
