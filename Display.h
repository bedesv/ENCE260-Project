/** @file   Display.h
    @author Bede Skinner-Vennell, Jack Warburton
    @date   7 October 2020
    @brief  Display module header

    This module defines the
*/

#include "system.h"

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
//void display_message(char* message);

/* Displays a single character */
void display_character(char character);
