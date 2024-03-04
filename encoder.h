#ifndef PICO_ROTARY_ENCODER_H
#define PICO_ROTARY_ENCODER_H

#include "pico/stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct rotary_encoder_t {
  int pin_a, pin_b;
  int state;
  long int position;
  void (*onchange)(struct rotary_encoder_t *button);
} rotary_encoder_t;

void handle_rotation(void *pointer);

typedef void (*handler)(void *argument);

extern void listen(uint pin, int condition, handler fn, void *arg);

rotary_encoder_t *create_encoder(int pin_a, int pin_b, void (*onchange)(rotary_encoder_t *encoder));

#ifdef __cplusplus
}
#endif

#endif