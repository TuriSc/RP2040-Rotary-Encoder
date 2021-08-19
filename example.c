#include "encoder.c"
#include "pico-button/button.c"
#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdio.h>

void onchange(rotary_encoder_t *encoder) {
  printf("Position: %d\n", encoder->position);
  printf("State: %d%d\n", encoder->state&0b10 ? 1 : 0, encoder->state&0b01);
}

void onpress(button_t *button) {
  printf("Button pressed: %s\n", button->state ? "Off" : "On");
}

int main() {
  stdio_init_all();
  rotary_encoder_t *encoder = create_encoder(2, 3, onchange);
  printf("Rotary Encoder created and it's state is %d%d\n", encoder->state&0b10 ? 1 : 0, encoder->state&0b01);
  printf("Rotary Encoder created and it's position is %d\n", encoder->position);
  button_t *button = create_button(21, onpress);
  printf("Button created and it's state is %d\n", button->state);
  while (true) tight_loop_contents();
  return 0;
}
