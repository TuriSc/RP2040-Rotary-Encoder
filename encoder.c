#ifndef PICO_ROTARY_ENCODER_C
#define PICO_ROTARY_ENCODER_C

#include "pico-gpio-interrupt/gpio-interrupt.c"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct rotary_encoder_t {
  int pin_a, pin_b;
  int state;
  long int position;
  void (*onchange)(struct rotary_encoder_t *button);
} rotary_encoder_t;

void handle_rotation(void *pointer) {
  rotary_encoder_t *encoder = (rotary_encoder_t *)pointer;
  int state = gpio_get(encoder->pin_a)<<1 | gpio_get(encoder->pin_b);
  switch ((encoder->state)<<2 | state) {
    case 0b0001: case 0b1110: case 0b1000: case 0b0111:
      encoder->position++;
      encoder->onchange(encoder);
      break;
    case 0b0100: case 0b1011: case 0b0010: case 0b1101:
      encoder->position--;
      encoder->onchange(encoder);
      break;
  }
  encoder->state = state;
}

rotary_encoder_t *create_encoder(int pin_a, int pin_b, void (*onchange)(rotary_encoder_t *encoder)) {
  rotary_encoder_t *encoder = (rotary_encoder_t *)malloc(sizeof(rotary_encoder_t));
  encoder->pin_a = pin_a;
  encoder->pin_b = pin_b;
  encoder->state = (gpio_get(pin_a)<<1 | gpio_get(pin_b));
  encoder->position = 0;
  encoder->onchange = onchange;
  listen(pin_a, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, handle_rotation, encoder);
  listen(pin_b, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, handle_rotation, encoder);
  return encoder;
}

#endif