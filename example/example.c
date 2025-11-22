#include "encoder.h"
#include "button.h" // From https://github.com/TuriSc/RP2040-Button
#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdio.h>

#define ENCODER_DT_PIN   0 // Data
#define ENCODER_CLK_PIN  1 // Clock
#define ENCODER_SW_PIN   2 // Switch

/**
 * @brief Function to call on a rotary encoder change event
 * @param encoder The rotary encoder structure
 */
void onchange(rotary_encoder_t *encoder) {
  printf("Position: %d\n", encoder->position);
  printf("State: %d%d\n", encoder->state & 0b10 ? 1 : 0, encoder->state & 0b01);
}

/**
 * @brief Function to call on a button press event
 * @param button The button structure
 */
void onpress(button_t *button) {
  printf("Button pressed: %s\n", button->state ? "Released" : "Pressed");
}

int main() {
  stdio_init_all();

  // Wait for serial connection
  sleep_ms(2000);

  // Initialize systems
  button_system_init();
  encoder_system_init();

  rotary_encoder_t *encoder = create_encoder(ENCODER_DT_PIN, ENCODER_CLK_PIN, onchange);
  if (!encoder) {
    printf("Failed to create encoder\n");
    return 1;
  }
  
  printf("Rotary Encoder created, its state is %d%d\n", encoder->state & 0b10 ? 1 : 0, encoder->state & 0b01);
  printf("Rotary Encoder created, its position is %d\n", encoder->position);
  
  button_t *button = create_button(ENCODER_SW_PIN, onpress);
  if (!button) {
    printf("Failed to create button\n");
    destroy_encoder(encoder);
    return 1;
  }
  printf("Button created, its state is %d\n", button->state);

  while (true) {
    // Process all events (encoder and button) - callbacks run in main loop context
    encoder_poll_all_events();
    // Throttle loop to reduce CPU usage - interrupts will still fire and queue events
    sleep_ms(10);
  }
  
  // Clean up (never reached in this example, but shown for completeness)
  destroy_encoder(encoder);
  button_destroy(button);
  return 0;
}
