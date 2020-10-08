/** @file   PaperScissorsRock.h
    @author Bede Skinner-Vennell, Jack Warburton
    @date   7 October 2020
    @brief  Main Function header

    This module defines the
*/

#define PACER_RATE 500
#define MESSAGE_RATE 15

#define led_on led_set (LED1, 1)
#define led_off led_set (LED1, 0)

const pio_t rows[7];

const pio_t cols[5];

const char possible_chars[3];

int navswitch_moved(void);

void text_init(void);

void clear_display(void);

void display_message(char* message);

void display_character (char character);

void pause(uint16_t time);
