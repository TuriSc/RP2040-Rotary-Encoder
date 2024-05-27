#include "encoder.h"
#include "button.h" // From https://github.com/TuriSc/RP2040-Button, expected in lib/
#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdio.h>

#define ENCODER_DT_PIN   0 // Data
#define ENCODER_CLK_PIN  1 // Clock
#define ENCODER_SW_PIN   2 // Switch

// Function to call on a change event
void onchange(rotary_encoder_t *encoder) {
  printf("Position: %d\n", encoder->position);
  printf("State: %d%d\n", encoder->state & 0b10 ? 1 : 0, encoder->state & 0b01);
}

// Function to call on a press event
void onpress(button_t *button) {
  printf("Button pressed: %s\n", button->state ? "Released" : "Pressed");
}

int main() {
  stdio_init_all();

  // Wait for serial connection
  sleep_ms(2000);

  rotary_encoder_t *encoder = create_encoder(ENCODER_DT_PIN, ENCODER_CLK_PIN, onchange);
  printf("Rotary Encoder created, its state is %d%d\n", encoder->state & 0b10 ? 1 : 0, encoder->state & 0b01);
  printf("Rotary Encoder created, its position is %d\n", encoder->position);
  button_t *button = create_button(ENCODER_SW_PIN, onpress);
  printf("Button created, its state is %d\n", button->state);

  while (true) {
    tight_loop_contents();
  }
  return 0;
}
