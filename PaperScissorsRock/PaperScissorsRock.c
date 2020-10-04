#include "system.h"
#include <string.h>
#include <stdbool.h>
#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"
#include "timer.h"
#include "navswitch.c"
#include "led.h"
#include "button.h"
#include "ir_uart.h"
#include "../../fonts/font3x5_1.h"
#include "../../fonts/font5x7_1.h"

#include "ScoreControl.h"

#define PACER_RATE 500
#define MESSAGE_RATE 15
#define TIMER1_PRESCALE 1024
#define CPU_F 8000000
#define LED_PIO PIO_DEFINE(PORT_C, 2)

static const pio_t rows[] = {
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO,
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};

static const pio_t cols[] = {
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

static const char possible_chars[] = {
    'P', 'R', 'S'
};


int navswitch_moved(void)
{
    int moved = 0;
    for (int i = 0; i < 5; i++) {


        if (navswitch_push_event_p (i)) {
            moved = 1;
        }
    }
    return moved;
}

void text_init(void)
{
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
}

void clear_display(void)
{
    for (int row = 0; row < 7; row++) {
        pio_config_set(rows[row], PIO_OUTPUT_HIGH);
    }

    for (int col = 0; col < 5; col++) {
        pio_config_set(cols[col], PIO_OUTPUT_HIGH);
    }
}

void display_message_until_joystick_moved(char* message)
{
    tinygl_font_set(&font3x5_1);
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

void display_character (char character)
{
    tinygl_font_set(&font5x7_1);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text(buffer);
}

void pause(uint16_t time)
{
    uint16_t tick = 0;
    while (tick < time) {
        tick++;
        pacer_wait();
    }
}

int index_of_char(char character)
{
    int index = 0;
    if (character == possible_chars[0]) {
        index = 0;
    } else if (character == possible_chars[1]) {
        index = 1;
    } else if (character == possible_chars[2]) {
        index = 2;
    }
    return index;
}

void wait(uint16_t count)
{
    TCNT1 = 0;
    while (TCNT1 < count) {
        continue;
    }
}

void pick_move(int* moves)
{

    clear_display();
    display_message_until_joystick_moved("PICK MOVE");

    int char_index = 0;
    char character;
    int away_char = -1;
    char received_char;
    bool char_received_success = 0;


    while (1)
    {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
        button_update();

        if (button_push_event_p(BUTTON1) & char_received_success) {
            led_set (LED1, 0);
            break;
        }


        character = possible_chars[char_index];

        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            if (char_index == 2) {
                char_index = 0;
            } else {
                char_index ++;
            }
        }
        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            if (char_index == 0) {
                char_index = 2;
            } else {
                char_index--;
            }
        }

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            ir_uart_putc(character);

        }


        if (ir_uart_read_ready_p()) {
            char ch;
            ch = ir_uart_getc();
            received_char = index_of_char(ch);
            away_char = received_char;

        }
        if (away_char != -1) {
            char_received_success = 1;
            led_set (LED1, 1);

        } else {
            led_set(LED1, 0);
        }

        display_character (character);

    }

    tinygl_clear();
    tinygl_update();
    int home_char = char_index;
    moves[0] = home_char;
    moves[1] = away_char;
}


int main(void)
{
    system_init ();
    navswitch_init();
    text_init();
    timer_init();
    ir_uart_init();
    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCCR1C = 0x00;
    led_init ();
    button_init ();

    score_init();
    pacer_init(PACER_RATE);
    display_message_until_joystick_moved("WELCOME TO PAPER SCISSORS ROCK");
    pacer_wait();
    int moves[2];
    stats* current_stats;




    pick_move(moves);
    int home_move = moves[0];
    int away_move = moves[1];
    update_score(home_move, away_move);
    current_stats = get_score();

    char stats_array[] = {current_stats->wins + 48, current_stats->losses + 48,
        current_stats->draws + 48, current_stats->played + 48};


    int stats_index = 0;


    while (1) {
        pacer_wait();
        navswitch_update();
        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            if (stats_index == 3) {
                stats_index = 0;
            } else {
                stats_index++;
            }

        }

        display_character(stats_array[stats_index]);
        tinygl_update();



        //update_score(home_move, away_move);

    }
}
