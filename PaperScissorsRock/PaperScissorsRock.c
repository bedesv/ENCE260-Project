#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../../fonts/font3x5_1.h"

#define PACER_RATE 500
#define MESSAGE_RATE 15

void display_init_1(void)
{
	tinygl_init(PACER_RATE);
    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
}

void display_message_once(char* message)
{
	tinygl_text(message);
	
}

 int main(void)
{
    system_init ();
	display_init_1();
	display_message_once("WELCOME TO PAPER SCISSORS ROCK");
	pacer_init(PACER_RATE);
	
	
    while (1)
    {
		pacer_wait();
		tinygl_update();

    }
}
