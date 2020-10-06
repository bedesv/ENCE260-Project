/** @file   PaperScissorsRock.h
    @author Bede Skinner-Vennell, Jack Warburton
    @date   7 October 2020
    @brief  Main Function header

    This module defines the
*/

#include "system.h"

#define PACER_RATE 500
#define MESSAGE_RATE 15
#define led_on led_set (LED1, 1)
#define led_off led_set (LED1, 0)



void text_init(void);


void game_init(void);
