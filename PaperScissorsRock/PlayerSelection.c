#include "system.h"
#include "ir_uart.h"
#include "led.h"
#include "navswitch.h"
#include "tinygl.h"
#include "pio.h"
#include "PaperScissorsRock.h"

// contains the possible characters in the game
static const char possible_chars[] = {
    'P', 'R', 'S'
};

// Returns the index of the character in possible chars structure
int index_of_char(char character)
{
    int index = -1;
    if (character == possible_chars[0]) {
        index = 0;
    } else if (character == possible_chars[1]) {
        index = 1;
    } else if (character == possible_chars[2]) {
        index = 2;
    }
    return index;
}


// Lets player make their decison: Paper/Scissors/Rock
void pick_move(int* moves)
{
    int char_index = 0;
    char character;
    int away_char = -1;
    char received_char = -1;

    bool char_received_success = 0;                     // ?
    led_set (LED1, 0);

    while (1) {
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
        }
        if (received_char != -1) {
            away_char = received_char;
            char_received_success = 1;
            led_set (LED1, 1);
        }
        display_character(character);
    }

    tinygl_clear();
    tinygl_update();
    moves[0] = char_index;
    moves[1] = away_char;
}
