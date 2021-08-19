# pico-rotary-encoder.c

## Installation

Install with [clib(1)](https://github.com/clibs/clib):

```sh
$ clib install jkroso/pico-rotary-encoder.c
```

## Api

`create_button(pin, onchange)`: It will set the pin to pull up. It returns a `button_t` struct

```c
typedef struct button_t {
  uint8_t pin;
  bool state;
  void (*onchange)(struct button_t *button);
} button_t;
```

## Example

```c
#include "pico-rotary-encoder/encoder.c"

void onchange(rotary_encoder_t *encoder) {
  printf("Position: %d\n", encoder->position);
}

int main() {
  stdio_init_all();
  rotary_encoder_t *encoder = create_encoder(2, 3, onchange);
  while (true) tight_loop_contents();
  return 0;
}
```
