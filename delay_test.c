#include "audio_codec.h"
#include "ring_modulator.h"
#include "echo_delay.h"
#include "sample_buf.h"
#include "switches.h"

#define MIN(L, R) (L <= R ? L : R)

#define WAVE_HEIGHT_1 12000
#define WAVE_FREQUENCY_1 100

#define WAVE_HEIGHT_2 12000
#define WAVE_FREQUENCY_2 10

#define DELAY_DEPTH 12000
#define DELAY_FRAC 2

struct ring_modulator ringmod_1;
struct ring_modulator ringmod_2;
struct echo_delay delay;

void sbuf_update_out_samples(void) {
  unsigned int num_samples = MIN((sbuf->idx_in - sbuf->idx_out),
                                 MIN(fifospace->write_l, fifospace->write_r));
  struct sample sample;

  for (; num_samples > 0; num_samples--) {
    sample.left = (int) sbuf->buf[sbuf->idx_out].left;
    sample.right = (int) sbuf->buf[sbuf->idx_out].right;

    if (switch_is_on(0)){
        ring_modulator_apply(&ringmod_1, &sample);
    }
	
	if (switch_is_on(1)){
		apply_echo_delay(&delay, &sample);
	}

	if (switch_is_on(2)) {
		ring_modulator_apply(&ringmod_2, &sample);
	}
	
    *ADDR_LEFT_DATA = sample.left;
    *ADDR_RIGHT_DATA = sample.right;

    sbuf->idx_out++;
    sbuf->idx_out %= sbuf->buf_len;
  }
}

void ctl_enable_interrupts(void) {

  __asm__("movi r8, 0b01000000\n"
          "wrctl ctl3, r8\n"

          "rdctl r8, ctl0\n"
          "ori r8, r8, 0b01\n"
          "wrctl ctl0, r8\n");
  return;
}

void on_codec_interrupt(void) {
  if (read_is_pending()) {
    sbuf_update_in_samples();
  }

  if (write_is_pending()) {
    sbuf_update_out_samples();
  }
}

int main() {

  ring_modulator_init(&ringmod_1, WAVE_HEIGHT_1, WAVE_FREQUENCY_1);
  ring_modulator_init(&ringmod_2, WAVE_HEIGHT_2, WAVE_FREQUENCY_2);
  init_echo_delay(&delay, DELAY_DEPTH, DELAY_FRAC);

  codec_enable_interrupts();
  ctl_enable_interrupts();

  while (1);
}
