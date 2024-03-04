#include "encoder.h"
#include "button.h"
#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdio.h>

// Function to call on a change event
void onchange(rotary_encoder_t *encoder) {
  printf("Position: %d\n", encoder->position);
  printf("State: %d%d\n", encoder->state & 0b10 ? 1 : 0, encoder->state & 0b01);
}

// Function to call on a press event
void onpress(button_t *button) {
  printf("Button pressed: %s\n", button->state ? "Off" : "On");
}

int main() {
  stdio_init_all();

  // Wait for serial connection
  sleep_ms(2000);

  rotary_encoder_t *encoder = create_encoder(0, 1, onchange);
  printf("Rotary Encoder created and its state is %d%d\n", encoder->state & 0b10 ? 1 : 0, encoder->state & 0b01);
  printf("Rotary Encoder created and its position is %d\n", encoder->position);
  button_t *button = create_button(2, onpress);
  printf("Button created and its state is %d\n", button->state);

  while (true) {
    tight_loop_contents();
  }
  return 0;
}
