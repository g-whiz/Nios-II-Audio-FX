#include "audio_codec.h"
#include "ring_modulator.h"
#include "sample_buf.h"

#define MIN(L, R) (L <= R ? L : R)

#define WAVE_HEIGHT 0xFFFF
#define WAVE_FREQUENCY 60

struct ring_modulator ringmod;

void sbuf_update_out_samples(void) {
  unsigned int num_samples = MIN((sbuf->idx_in - sbuf->idx_out),
                                 MIN(fifospace->write_l, fifospace->write_r));
  struct sample ringmod_sample;

  for (; num_samples > 0; num_samples--) {
    ringmod_sample.left = sbuf->buf[sbuf->idx_out].left;
    ringmod_sample.right = sbuf->buf[sbuf->idx_out].right;

    ring_modulator_apply(&ringmod, &ringmod_sample);

    *ADDR_LEFT_DATA = ringmod_sample.left;
    *ADDR_RIGHT_DATA = ringmod_sample.right;

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

  ring_modulator_init(&ringmod, WAVE_HEIGHT, WAVE_FREQUENCY);

  codec_enable_interrupts();
  ctl_enable_interrupts();

  while (1)
    ;
}
