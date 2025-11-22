#ifndef PICO_ROTARY_ENCODER_H
#define PICO_ROTARY_ENCODER_H

#include "pico/stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @def MAX_ENCODER_EVENTS
 * @brief Maximum number of encoder events that can be queued
 */
#define MAX_ENCODER_EVENTS 16

/**
 * @struct rotary_encoder_t
 * @brief Represents a rotary encoder with its pin configuration, state, and onchange callback
 */
typedef struct rotary_encoder_t {
  /**
   * @var pin_a
   * @brief The GPIO pin number of the encoder's A channel
   */
  int pin_a;
  /**
   * @var pin_b
   * @brief The GPIO pin number of the encoder's B channel
   */
  int pin_b;
  /**
   * @var state
   * @brief The current state of the encoder (a 2-bit value representing the A and B channels)
   */
  int state;
  /**
   * @var position
   * @brief The current position of the encoder
   */
  long int position;
  /**
   * @var onchange
   * @brief The callback function to be called when the encoder's position changes
   */
  void (*onchange)(struct rotary_encoder_t *encoder);
} rotary_encoder_t;

/**
 * @struct encoder_event_t
 * @brief Represents an encoder event in the queue
 */
typedef struct {
  /**
   * @var encoder
   * @brief Pointer to the encoder that generated the event
   */
  rotary_encoder_t *encoder;
  /**
   * @var delta
   * @brief The position change delta (+1 or -1)
   */
  int delta;
} encoder_event_t;

/**
 * @brief Handles a rotary encoder interrupt
 * @param pointer The rotary encoder structure
 */
void handle_rotation(void *pointer);

/**
 * @brief Initialize the encoder system (call before creating encoders)
 */
void encoder_system_init(void);

/**
 * @brief Poll for encoder events and process callbacks (call from main loop)
 * @return Number of events processed
 */
int encoder_poll_events(void);

/**
 * @brief Poll for all events (encoder and button) and process callbacks (call from main loop)
 * @return Total number of events processed (encoder + button)
 */
int encoder_poll_all_events(void);

/**
 * @brief Creates a new rotary encoder structure
 * @param pin_a The GPIO pin number of the encoder's A channel
 * @param pin_b The GPIO pin number of the encoder's B channel
 * @param onchange The onchange callback function
 * @return The new rotary encoder structure, or NULL on failure
 */
rotary_encoder_t *create_encoder(int pin_a, int pin_b, void (*onchange)(rotary_encoder_t *encoder));

/**
 * @brief Destroy an encoder and free its resources
 * @param encoder Pointer to the encoder to destroy
 */
void destroy_encoder(rotary_encoder_t *encoder);

#ifdef __cplusplus
}
#endif

#endif
