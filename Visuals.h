/** @file   Display.h
    @author Bede Skinner-Vennell, Jack Warburton
    @date   7 October 2020
    @brief  Visuals module header

    This module defines the functions to use the display for text
*/

/* defines the number of ways the navswitch can be moved */
#define NO_NAVSWITCH_OPTIONS 5

/* Defines arrays of PIO ports for the rows and colums of the matrix
   respectively - to make using the display easier */
const pio_t rows[7] ;
const pio_t cols[5] ;

/* Returns 1 if the navswitch has been moved. Uses a for-loop to check
   each movement */
int navswitch_moved(void);

/* Runs through all rows and columns of the matrix and turns them off */
void clear_display(void);

/* Displays the given string message until the navswitch is moved */
void display_message(char* message);

/* Displays a single character */
void display_character(char character);

/* Initialises tinygl with the appropriate settings */
/* In this file to stop memory overflow related to loading
  fonts multiple times */
void text_init(void);
