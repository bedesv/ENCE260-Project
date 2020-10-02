#include "system.h"
#include <string.h>
#include <stdbool.h>
#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"
#include "timer.h"
#include "navswitch.c"
#include "../../fonts/font3x5_1.h"
#include "../../fonts/font5x7_1.h"

#define PACER_RATE 500
#define MESSAGE_RATE 15
#define TIMER1_PRESCALE 1024
#define CPU_F 8000000

static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO,
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};

static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

static const char possible_chars[] =
{
    'R', 'P', 'S'
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
    tinygl_text(message);
    int moved = 0;
    while (moved != 1)
    {
        pacer_wait();
        tinygl_update();
        navswitch_update();
        moved = navswitch_moved();
    }
    clear_display();

}

void wait_x_ms(uint16_t ms)
{

    uint16_t ticks = (ms * (CPU_F / TIMER1_PRESCALE) / 1000);
    TCNT1 = 0;
    while (TCNT1 < ticks)
    {
        continue;
    }
}

void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text(buffer);
}

 int main(void)
{
    system_init ();
    navswitch_init();
    text_init();
    timer_init();

    pacer_init(PACER_RATE);
    display_message_until_joystick_moved("WELCOME TO PAPER SCISSORS ROCK");
    pacer_wait();
    display_message_until_joystick_moved("PICK MOVE");
    int char_index = 0;
    tinygl_font_set(&font5x7_1);


    while (1)
    {
        pacer_wait();
        tinygl_update();
        navswitch_update();

        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            if (char_index == 2) {
                char_index = 0;
            } else {
                char_index ++;
            }
        } else if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            if (char_index == 0) {
                char_index = 2;
            } else {
                char_index--;
            }
        } else if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
          break;
        }

        display_character(possible_chars[char_index]);

    }
}
