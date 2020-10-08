/** @file   PlayerSelection.c
    @author Bede Skinner-Vennell, Jack Warburton
    @date   7 October 2020
    @brief  Player Selection module

    This module defines the
*/

#include "system.h"
#include "ir_uart.h"
#include "led.h"
#include "navswitch.h"
#include "tinygl.h"
#include "pio.h"
#include "pacer.h"
#include "button.h"
#include "PaperScissorsRock.h"


const char possible_chars[] = {
    'P', 'R', 'S'
};
// Returns the index of the character in possible_chars array
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

/* Checks if the player has changed their character selection and
   changes char_index appropriately */
void selection_changed(int* char_index)
{
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        if (*char_index == 2) {
            *char_index = 0;
        } else {
            *char_index = *char_index + 1;
        }
    }
    if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        if (*char_index == 0) {
            *char_index = 2;
        } else {
            *char_index = *char_index - 1;
        }
    }

}

void check_received_char(int* received_char, int* away_char, bool* char_received_success)
{
    if (*received_char != -1) {
        *away_char = *received_char;
        *char_received_success = 1;
        led_on;
    }
}

void send_move(char* character)
{
    if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
        ir_uart_putc(*character);
    }
}

void receive_move(int* received_char)
{
    if (ir_uart_read_ready_p()) {
        char ch;
        ch = ir_uart_getc();
        *received_char = index_of_char(ch);
    }
}



// Lets player make their decison: Paper/Scissors/Rock
void pick_move(int* moves)
{
    int char_index = 0;
    char character;
    int away_char = -1;
    int received_char = -1;
    bool char_received_success = 0;

    led_off;

    while (1) {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
        button_update();

        if (button_push_event_p(BUTTON1) & char_received_success) {
        led_off;
        break;
        }

        character = possible_chars[char_index];
        selection_changed(&char_index);
        send_move(&character);
        receive_move(&received_char);
        check_received_char(&received_char, &away_char, &char_received_success);

        display_character(character);
    }

    tinygl_clear();
    tinygl_update();
    moves[0] = char_index;
    moves[1] = away_char;
}
