/** @file   Display.c
    @author Bede Skinner-Vennell, Jack Warburton
    @date   7 October 2020
    @brief  Visuals module

    This module defines the functions to use the display for text
*/

#include <string.h>

#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "pio.h"
#include "pacer.h"

#include "PaperScissorsRock.h"

#include "../../fonts/font3x5_1.h"
#include "../../fonts/font5x7_1.h"

/* Defines the number of ways the navswitch can be moved */
#define NO_NAVSWITCH_OPTIONS 5

/* Matrix rows PIO ports */
const pio_t rows[] = {
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO,
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};

/* Matrix columns PIO ports */
const pio_t cols[] = {
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

/* Returns 1 if the navswitch has been moved since the last time
   navswitch_update has been called */
int navswitch_moved(void)
{
    int moved = 0;
    for (int i = 0; i < NO_NAVSWITCH_OPTIONS; i++) {
        if (navswitch_push_event_p(i)) {
            moved = 1;
        }
    }
    return moved;
}

/* Loops through each row and column in the display and clears them */
void clear_display(void)
{
    for (int row = 0; row < 7; row++) {
        pio_config_set(rows[row], PIO_OUTPUT_HIGH);
    }
    for (int col = 0; col < 5; col++) {
        pio_config_set(cols[col], PIO_OUTPUT_HIGH);
    }
}

/* Displays a message across the screen */
void display_message(char* message)
{
    tinygl_clear();
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

/* Displays the given character on the screen */
void display_character(char character)
{
    tinygl_font_set(&font5x7_1);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text(buffer);
}

/* Initialises the tinygl text for the welcome messages and the score
   display */
/* In this file to stop memory overflow related to loading
   fonts multiple times */
void text_init(void)
{
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
}
