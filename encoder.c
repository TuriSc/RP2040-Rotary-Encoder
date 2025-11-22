#include "pico/stdlib.h"
#include "encoder.h"
#include "button.h"
#include <stdlib.h>
#include <stdio.h>
#include "hardware/gpio.h"

/**
 * @def MAX_ENCODER_EVENTS
 * @brief Maximum number of encoder events that can be queued
 */
#define MAX_ENCODER_EVENTS 16

/**
 * @var encoder_event_queue
 * @brief Event queue for encoder events
 */
static encoder_event_t encoder_event_queue[MAX_ENCODER_EVENTS];

/**
 * @var encoder_queue_head
 * @brief Head pointer for event queue
 */
static volatile uint8_t encoder_queue_head = 0;

/**
 * @var encoder_queue_tail
 * @brief Tail pointer for event queue
 */
static volatile uint8_t encoder_queue_tail = 0;

/**
 * @brief Queue an encoder event
 * @param encoder The encoder structure
 * @param delta The position change delta (+1 or -1)
 */
static void queue_encoder_event(rotary_encoder_t *encoder, int delta) {
  if (!encoder) return;
  
  uint8_t next_head = (encoder_queue_head + 1) % MAX_ENCODER_EVENTS;
  if (next_head != encoder_queue_tail) {
    encoder_event_queue[encoder_queue_head].encoder = encoder;
    encoder_event_queue[encoder_queue_head].delta = delta;
    encoder_queue_head = next_head;
  }
}

/**
 * @brief Handles a rotary encoder interrupt
 * @param pointer The rotary encoder structure
 */
void handle_rotation(void *pointer) {
  if (!pointer) return;
  
  rotary_encoder_t *encoder = (rotary_encoder_t *)pointer;
  if (!encoder) return;
  
  int state = gpio_get(encoder->pin_a)<<1 | gpio_get(encoder->pin_b);
  int delta = 0;
  
  switch ((encoder->state)<<2 | state) {
    case 0b0001: case 0b1110: case 0b1000: case 0b0111:
      encoder->position++;
      delta = 1;
      break;
    case 0b0100: case 0b1011: case 0b0010: case 0b1101:
      encoder->position--;
      delta = -1;
      break;
  }
  
  encoder->state = state;
  
  // Queue event instead of calling callback directly (prevents interrupt context execution)
  if (delta != 0) {
    queue_encoder_event(encoder, delta);
  }
}

/**
 * @brief Initialize the encoder system (call before creating encoders)
 */
void encoder_system_init(void) {
  encoder_queue_head = 0;
  encoder_queue_tail = 0;
}

/**
 * @brief Poll for encoder events and process callbacks (call from main loop)
 * @return Number of events processed
 */
int encoder_poll_events(void) {
  int count = 0;
  while (encoder_queue_tail != encoder_queue_head) {
    encoder_event_t *event = &encoder_event_queue[encoder_queue_tail];
    if (event->encoder && event->encoder->onchange) {
      event->encoder->onchange(event->encoder);
    }
    encoder_queue_tail = (encoder_queue_tail + 1) % MAX_ENCODER_EVENTS;
    count++;
  }
  return count;
}

/**
 * @brief Poll for all events (encoder and button) and process callbacks (call from main loop)
 * @return Total number of events processed (encoder + button)
 */
int encoder_poll_all_events(void) {
  int encoder_count = encoder_poll_events();
  int button_count = button_poll_events();
  return encoder_count + button_count;
}

/**
 * @brief Destroy an encoder and free its resources
 * @param encoder Pointer to the encoder to destroy
 */
void destroy_encoder(rotary_encoder_t *encoder) {
  if (!encoder) return;
  
  // Disable GPIO interrupts for both pins
  gpio_set_irq_enabled(encoder->pin_a, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, false);
  gpio_set_irq_enabled(encoder->pin_b, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, false);
  
  // Note: We don't clear handlers[pin] here because that's managed by button library's listen()
  // The button library's handlers array will be cleared when needed by button_destroy() or
  // when listen() is called again for those pins
  
  // Free allocated encoder memory
  free(encoder);
}

/**
 * @brief Creates a new rotary encoder structure
 * @param pin_a The GPIO pin number of the encoder's A channel
 * @param pin_b The GPIO pin number of the encoder's B channel
 * @param onchange The onchange callback function
 * @return The new rotary encoder structure, or NULL on failure
 */
rotary_encoder_t *create_encoder(int pin_a, int pin_b, void (*onchange)(rotary_encoder_t *encoder)) {
  // Validate parameters
  if (pin_a < 0 || pin_a >= 28 || pin_b < 0 || pin_b >= 28) return NULL;
  if (pin_a == pin_b) return NULL;  // Pins must be different
  if (!onchange) return NULL;
  
  gpio_init(pin_a);
  gpio_init(pin_b);
  gpio_pull_up(pin_a);
  gpio_pull_up(pin_b);
  
  rotary_encoder_t *encoder = (rotary_encoder_t *)malloc(sizeof(rotary_encoder_t));
  if (!encoder) return NULL;
  
  encoder->pin_a = pin_a;
  encoder->pin_b = pin_b;
  encoder->state = (gpio_get(pin_a)<<1 | gpio_get(pin_b));
  encoder->position = 0;
  encoder->onchange = onchange;
  
  // Use button library's listen() function - it handles GPIO IRQ callback registration
  listen(pin_a, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, handle_rotation, encoder);
  listen(pin_b, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, handle_rotation, encoder);
  
  return encoder;
}

