#include <stdio.h>
#include "ir_uart.h"
#include "boing.h"
#include "led.h"
#include "ball.h"

void sending(uint8_t inPlay, boing_dir_t direction, uint8_t location);

boing_dir_t select_dir(uint8_t direction_sum);

uint8_t select_loc(uint8_t location_sum);

ball_state_t receiving(uint8_t c);
