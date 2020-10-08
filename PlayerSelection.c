/** @file   PlayerSelection.c
    @author Bede Skinner-Vennell, Jack Warburton
    @date   7 October 2020
    @brief  Module for player move selection and IR transmission

    This module includes the functions used to allow the player to select
    their move and then transmits
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
#include "Visuals.h"


/* Array with the possible moves the player can select */
const char possible_chars[] = {
    'P', 'R', 'S'
};

/* Returns the index of the given character in possible chars array */
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

/* Checks if the player has changed their selection and updates
   char_index with the appropriate value */
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

/* Checks if the character received is a valid move from the other
   player rather than interference then updates the away_char integer and
   the char_received_success bool to allow the player to exit
   transmisson mode if it is */
void check_received_char(int* received_char, int* away_char, bool* char_received_success)
{
    if (*received_char != -1) {
        *away_char = *received_char;
        *char_received_success = 1;
        led_on;
    }
}

/* Checks if the player has pressed down on the joystick to send their
   character selection and sends it to the other player if so */
void send_move(char* character)
{
    if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
        ir_uart_putc(*character);
    }
}

/* Recieves an IR transmission and assigns it to the received char */
void receive_move(int* received_char)
{
    if (ir_uart_read_ready_p()) {
        char ch;
        ch = ir_uart_getc();
        *received_char = index_of_char(ch);
    }
}

/* Utilises the above functions to allow the player to pick their move
   for this round and sends it to the other player. It also receives
   the other players move and then stores both moves in an array for the
   main function to use for score keeping */
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
