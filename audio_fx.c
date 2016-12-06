#include "audio_codec.h"
#include "ring_modulator.h"
#include "saw_modulator.h"
#include "echo_delay.h"
#include "audio_pan.h"
#include "echo_pan.h"
#include "audio_modulo.h"
#include "sample_buf.h"
#include "switches.h"

#define MIN(L, R) (L <= R ? L : R)

#define WAVE_HEIGHT_1 12000
#define WAVE_FREQUENCY_1 100

#define WAVE_HEIGHT_2 12000
#define WAVE_FREQUENCY_2 25

#define DELAY_DEPTH1 40000
#define DELAY_DEPTH2 30000
#define DELAY_FRAC 2

#define PAN_MAX 30000

#define MODULUS 800000000

#define ECHOPAN_PERIOD 1

struct ring_modulator ringmod_1;
struct ring_modulator ringmod_2;
struct echo_delay delay1;
struct echo_delay delay2;
struct audio_pan pan;
struct audio_modulo modulo;
struct saw_modulator sawmod1;
struct saw_modulator sawmod2;
struct echo_pan echopan;

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
		apply_echo_delay(&delay1, &sample);
	}
	
	if (switch_is_on(2)){
		apply_echo_delay(&delay2, &sample);
	}

	if (switch_is_on(3)){
		ring_modulator_apply(&ringmod_2, &sample);
	}
	
	if (switch_is_on(4)){
		audio_pan_apply(&pan, &sample);
	}
	
	if (switch_is_on(5)){
		audio_modulo_apply(&modulo, &sample);
	}
	
	if (switch_is_on(6)){
		saw_modulator_apply(&sawmod1, &sample);
	}
	
	if (switch_is_on(7)){
		saw_modulator_apply(&sawmod2, &sample);
	}
	
	if (switch_is_on(8)) {
		apply_echo_pan(&echopan, &sample);
	}

    if (switch_is_on(9)){
        ring_modulator_apply(&ringmod_1, &sample);
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
  init_echo_delay(&delay1, DELAY_DEPTH1, DELAY_FRAC);
  init_echo_delay(&delay2, DELAY_DEPTH2, DELAY_FRAC);
  audio_pan_init(&pan, PAN_MAX);
  audio_modulo_init(&modulo, MODULUS);
  saw_modulator_init(&sawmod1, SAW_MOD_DOWN, WAVE_HEIGHT_1, WAVE_FREQUENCY_1);
  saw_modulator_init(&sawmod2, SAW_MOD_UP, WAVE_HEIGHT_1, WAVE_FREQUENCY_2);
  init_echo_pan(&echopan, DELAY_DEPTH1, ECHOPAN_PERIOD);

  codec_enable_interrupts();
  ctl_enable_interrupts();

  while (1);
}