/* 
 * Interface with the audio codec.
 */

#ifndef __AUDIO_CODEC_H__
#define __AUDIO_CODEC_H__

#define ADDR_CONTROL		((volatile int * const) 0xFF203040)
#define ADDR_FIFOSPACE		(((volatile int * const) 0xFF203040) + 1)
#define ADDR_LEFT_DATA		(((volatile int * const) 0xFF203040) + 2)
#define ADDR_RIGHT_DATA		(((volatile int * const) 0xFF203040) + 3)

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

extern volatile struct fifospace * const 	fifospace;

/* Convenience functions for checking whether read/write interrupts are pending
 * on the audio codec. */
int read_is_pending(void);
int write_is_pending(void);

/* Enable read, write interrupts on the audio codec. */
void codec_enable_interrupts();

#endif /* __AUDIO_CODEC_H__ */