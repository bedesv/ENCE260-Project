/** @file   PaperScissorsRock.c
    @author Bede Skinner-Vennell, Jack Warburton
    @date   7 October 2020
    @brief  Main Function header

    This module contains the main setup of the game including the games
    initialisation funtions and the main game loop.
*/

#define PACER_RATE 500
#define MESSAGE_RATE 15

#define led_on led_set (LED1, 1)
#define led_off led_set (LED1, 0)

/* Initialises the tinygl text for the menu */
void text_init(void);

/* Sets up the system components */
void game_init(void);

/* Displays a message across the screen */
void display_message(char* message);
