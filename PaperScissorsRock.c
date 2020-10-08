#include "system.h"
#include <string.h>
#include <stdbool.h>
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
#include "Display.h"


#define PACER_RATE 500
#define MESSAGE_RATE 15

#define led_on led_set(LED1, 1)
#define led_off led_set(LED1, 0)


void text_init(void)
{
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
}

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

int main(void)
{
    system_init ();
    navswitch_init();
    text_init();
    ir_uart_init();
    led_init ();
    button_init ();

    stats score;
    score_init(&score);
    pacer_init(PACER_RATE);
    display_message("WELCOME TO PAPER SCISSORS ROCK");
    pacer_wait();

    int moves[2];
    char* current_stats;
    int home_move;
    int away_move;

    while(1) {
        clear_display();
        current_stats = malloc(30);
        display_message("PICK MOVE");
        pick_move(moves);
        home_move = moves[0];
        away_move = moves[1];
        update_score(home_move, away_move, &score);
        get_score(&score, current_stats);
        if (score.wins >= score.losses) {
            led_on;
        } else {
            led_off;
        }
        led_on;
        display_message(current_stats);
        free(current_stats);
    }
}
