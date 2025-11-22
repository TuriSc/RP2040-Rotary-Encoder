# RP2040-rotary-encoder
## Efficiently read rotary encoder signals with a Raspberry Pi Pico

This C library reads rotation data and switch presses from rotary encoders. It supports mechanical encoders like KY-040 (HW-040), or EC11.

It uses GPIO_IRQ interrupts for automatic event detection - no continuous polling of GPIO pins is required. However, you must call `encoder_poll_events()` regularly in your main loop to process queued events and invoke callbacks.

Multiple encoders can be controlled simultaneously.

## Requirements

- Raspberry Pi Pico SDK
- [TuriSc/RP2040-Button](https://github.com/TuriSc/RP2040-Button)

Run `git submodule update --init` if you intend to compile the example.

## Usage

An example program is included. Please see [example/example.c](/example/example.c).

### Important Notes

- GPIO interrupts are detected automatically - no polling of GPIO pins needed
- You must call `encoder_poll_all_events()` (or `encoder_poll_events()` and `button_poll_events()` separately) regularly in your main loop to process events

## Credits
This library is a fork of [jkroso/pico-rotary-encoder.c](https://github.com/jkroso/pico-rotary-encoder.c), including code from [jkroso/pico-button.c](https://github.com/jkroso/pico-button.c) and [jkroso/pico-gpio-interrupt.c](https://github.com/jkroso/pico-gpio-interrupt.c), all by Jake Rosoman. MIT license.

## Version history

- 2025-11-22 - (Breaking changes) Add error handling, cleanup function; Implement listen() function with shared GPIO IRQ handler
- 2024-08-18 - Bug fix
- 2024-03-04 - First release
