#include "effect.h"

void apply_effect(struct effect *effect, struct sample *sample) {
  switch (effect->type) {
  case TYPE_RING_MODULATOR:
    ring_modulator_apply(&(effect->state.ringmod), sample);
    return;

    // case TYPE_ECHO_DELAY:
  }
}
