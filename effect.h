#include "audio_codec.h"
#include "ring_modulator.h"

#ifndef __EFFECT_H__
#define __EFFECT_H__

#define TYPE_RING_MODULATOR 0
// #define TYPE_ECHO_DELAY 1

struct effect {
  int type;
  union effect_state state;
};

union effect_state {
  struct ring_modulator ringmod;
};

void apply_effect(struct effect *effect, struct sample *sample);

#endif
