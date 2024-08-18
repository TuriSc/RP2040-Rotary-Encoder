# RP2040-rotary-encoder
## Efficiently read rotary encoder signals with a Raspberry Pi Pico

This C library reads rotation data and switch presses from rotary encoders. It supports mechanical encoders like KY-040 (HW-040), or EC11.

It listens to GPIO_IRQ events and does not rely on continous polling.

Multiple encoders can be controlled simultaneously.


### Requirements
- [TuriSc/RP2040-Button](https://github.com/TuriSc/RP2040-Button)

Run `git submodule update --init` if you intend to compile the example.


### Usage
An example program is included. Please see [example/example.c](/example/example.c).


### Credits
This library is a fork of [jkroso/pico-rotary-encoder.c](https://github.com/jkroso/pico-rotary-encoder.c), including code from [jkroso/pico-button.c](https://github.com/jkroso/pico-button.c) and [jkroso/pico-gpio-interrupt.c](https://github.com/jkroso/pico-gpio-interrupt.c), all by Jake Rosoman. MIT license.


### Version history
- 2024-08-18 - Bug fix
- 2024-03-04 - First release
