#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "pio.h"
#include "pacer.h"
#include "../../fonts/font3x5_1.h"
#include "../../fonts/font5x7_1.h"



static const pio_t rows[] = {
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO,
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};

static const pio_t cols[] = {
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};



// Returns 1 if navswitch has been moved in any direction
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


// makes the display blank
void clear_display(void)
{
    for (int row = 0; row < 7; row++) {
        pio_config_set(rows[row], PIO_OUTPUT_HIGH);
    }

    for (int col = 0; col < 5; col++) {
        pio_config_set(cols[col], PIO_OUTPUT_HIGH);
    }
}


// Displays the given string message until the navswitch is moved
void display_message(char* message)
{
    int moved = 0;
    tinygl_font_set(&font3x5_1);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text(message);
    while (moved != 1) {
        pacer_wait();
        tinygl_update();
        navswitch_update();
        moved = navswitch_moved();
    }
    clear_display();
}


// Displays a single char
void display_character(char character)
{
    tinygl_font_set(&font5x7_1);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text(buffer);
}
