#include "system.h"
#include <string.h>
#include <stdbool.h>
#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"
#include "navswitch.c"
#include "../../fonts/font3x5_1.h"

#define PACER_RATE 500
#define MESSAGE_RATE 15

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
	for (int row = 0; row < 7; row++) {
		pio_config_set(rows[row], PIO_OUTPUT_HIGH);
	}
	
	for (int col = 0; col < 5; col++) {
		pio_config_set(cols[col], PIO_OUTPUT_HIGH);
	}
	
}

 int main(void)
{
    system_init ();
    navswitch_init();
	text_init();
	
	pacer_init(PACER_RATE);
	display_message_until_joystick_moved("WELCOME TO PAPER SCISSORS ROCK");
	display_message_until_joystick_moved("SELECT");
	
	
    while (1)
    {
		pacer_wait();

    }
}
