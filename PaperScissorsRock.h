#include "system.h"
#include "ScoreControl.h"

static const pio_t rows[];

static const pio_t cols[];

static const char possible_chars[];

int navswitch_moved(void);

void text_init(void);

void clear_display(void);

void display_message_until_joystick_moved(char* message);

void display_character (char character);

void pause(uint16_t time);
