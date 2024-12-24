#ifndef PICO_ROTARY_ENCODER_H
#define PICO_ROTARY_ENCODER_H

#include "pico/stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif

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
 * @brief Handles a rotary encoder interrupt
 * @param pointer The rotary encoder structure
 */
void handle_rotation(void *pointer);

/**
 * @typedef handler
 * @brief A function pointer type for onchange callbacks
 */
typedef void (*handler)(void *argument);

/**
 * @brief Listens for a GPIO interrupt
 * @param pin The GPIO pin number
 * @param condition The interrupt condition
 * @param fn The callback function
 * @param arg The argument to be passed to the callback function
 */
extern void listen(uint pin, int condition, handler fn, void *arg);

/**
 * @brief Creates a new rotary encoder structure
 * @param pin_a The GPIO pin number of the encoder's A channel
 * @param pin_b The GPIO pin number of the encoder's B channel
 * @param onchange The onchange callback function
 * @return The new rotary encoder structure
 */
rotary_encoder_t *create_encoder(int pin_a, int pin_b, void (*onchange)(rotary_encoder_t *encoder));

#ifdef __cplusplus
}
#endif

#endif

