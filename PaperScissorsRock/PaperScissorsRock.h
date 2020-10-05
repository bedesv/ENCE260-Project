#include <string.h>
#include <stdbool.h>

#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"
#include "pio.h"
#include "led.h"
#include "button.h"
#include "ir_uart.h"
#include "../../fonts/font3x5_1.h"
#include "ScoreControl.h"
#include "PlayerSelection.h"
#include "Display.h"

#define PACER_RATE 500
#define MESSAGE_RATE 15



void text_init(void);


void game_init(void);
