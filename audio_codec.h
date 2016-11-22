/* 
 * Interface with the audio codec.
 */

#ifndef __AUDIO_CODEC_H__
#define __AUDIO_CODEC_H__


/* The left and right channel values of a single sample. */
struct sample {
	int left;
	int right;
} __attribute__ ((packed));

/* Convenience struct for accessing the components of the fifospace register. */
struct fifospace {
	unsigned char read_r;
	unsigned char read_l;
	unsigned char write_r;
	unsigned char write_l;
} __attribute__ ((packed));

/* Convenience struct for accessing the data registers of the audio codec. */
extern volatile struct sample * const 		codec_data;
extern volatile struct fifospace * const 	fifospace;

/* Convenience functions for checking whether read/write interrupts are pending
 * on the audio codec. */
int read_is_pending(void);
int write_is_pending(void);


#endif /* __AUDIO_CODEC_H__ */