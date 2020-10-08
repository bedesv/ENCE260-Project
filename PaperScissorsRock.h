#include "system.h"
#include "ScoreControl.h"


#define PACER_RATE 500
#define MESSAGE_RATE 15
#define TIMER1_PRESCALE 1024
#define CPU_F 8000000

#define led_on led_set (LED1, 1)
#define led_off led_set (LED1, 0)

const pio_t rows[7];

const pio_t cols[5];

const char possible_chars[3];

int navswitch_moved(void);

void text_init(void);

void clear_display(void);

void display_message_until_joystick_moved(char* message);

void display_character (char character);

void pause(uint16_t time);
