/** @file   PaperScissorsRock.c
    @author Bede Skinner-Vennell, Jack Warburton
    @date   7 October 2020
    @brief  Main Function header

    This module contains the main setup of the game including the games
    initialisation funtions and the main game loop.
*/

#include <string.h>
#include <stdlib.h>
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
#include "../../fonts/font5x7_1.h"

#include "ScoreControl.h"
#include "PlayerSelection.h"
#include "Visuals.h"


#define PACER_RATE 500
#define MESSAGE_RATE 15
#define MAX_SCORE_LENGTH 50

#define led_on led_set(LED1, 1)
#define led_off led_set(LED1, 0)


/* Initialises the tinygl text for the menu */
void text_init(void)
{
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
}

/* Sets up the system components */
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

/* Displays a message across the screen */
void display_message(char* message)
{
    tinygl_font_set(&font3x5_1);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text(message);
    int moved = 0;
    while (moved != 1) {
        pacer_wait();
        tinygl_update();
        navswitch_update();
        moved = navswitch_moved();
    }
    clear_display();

}

/* Gets the game ready and loops the gameplay an infinte number of times */
int main(void)
{
    game_init();
    stats score;
    score_init(&score);
    display_message("WELCOME TO PAPER SCISSORS ROCK");
    pacer_wait();
    int moves[2];
    char* current_stats = malloc(MAX_SCORE_LENGTH);
    int home_move;
    int away_move;
    while(1) {                                      // Main game loop
        clear_display();
        display_message("PICK MOVE");
        pick_move(moves);
        home_move = moves[0];
        away_move = moves[1];
        update_score(home_move, away_move, &score);
        get_score(&score, current_stats);
        if (score.wins >= score.losses) {          // Turns LED on if draw or winning
            led_on;
        } else {
            led_off;
        }
        display_message(current_stats);
    }
    free(current_stats);                           // Not likely used but good practice
}
