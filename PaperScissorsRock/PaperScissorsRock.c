/** @file   PaperScissorsRock.c
    @author Bede Skinner-Vennell, Jack Warburton
    @date   7 October 2020
    @brief  Main Function header

    This module defines the
*/

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
#define led_on led_set (LED1, 1)
#define led_off led_set (LED1, 0)



void text_init(void)
{
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
}


void game_init(void)
{
    system_init ();
    navswitch_init();
    text_init();
    ir_uart_init();
    led_init ();
    button_init ();
    pacer_init(PACER_RATE);
}


int main(void)
{
    game_init();
    stats score;
    score_init(&score);
    display_message("WELCOME TO PAPER SCISSORS ROCK");
    pacer_wait();

    int moves[2];
    char* current_stats;
    int home_move;
    int away_move;

    while(1) {                                                // Main game loop
        clear_display();
        display_message("PICK MOVE");
        pick_move(moves);
        home_move = moves[0];
        away_move = moves[1];
        update_score(home_move, away_move, &score);
        current_stats = get_score(&score);
        if (score.wins >= score.losses) {
            led_on;
        } else {
            led_off;
        }
        display_message(current_stats);
    }
}
