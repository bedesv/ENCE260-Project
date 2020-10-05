#include "system.h"


static const pio_t rows[] ;

static const pio_t cols[] ;


// returns 1 if navswitch has been moved in any direction
int navswitch_moved(void);

// makes the display blank
void clear_display(void);

// Displays the given string message until the navswitch is moved
void display_message(char* message);

// Displays a single char
void display_character(char character);
