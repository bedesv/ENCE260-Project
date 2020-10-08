/** @file   PlayerSelection.h
    @author Bede Skinner-Vennell, Jack Warburton
    @date   7 October 2020
    @brief  Module for player move selection and IR transmission

    This module defines the
*/

/* Array with the possible moves the player can select */
const char possible_chars[3];

/* Returns the index of the given character in possible chars array */
int index_of_char(char character);

/* Checks if the player has changed their selection and updates
   char_index with the appropriate value */
void selection_changed(int* char_index);

/* Checks if the character received is a valid move from the other
   player rather than interference then updates the away_char integer and
   the char_received_success bool to allow the player to exit
   transmisson mode if it is */
void check_received_char(int* received_char, int* away_char, bool* char_received_success);

/* Checks if the player has pressed down on the joystick to send their
   character selection and sends it to the other player if so */
void send_move(char* character);

/* Recieves an IR transmission and assigns it to the received char */
void receive_move (int* received_char);

/* Utilises the above functions to allow the player to pick their move
   for this round and sends it to the other player. It also receives
   the other players move and then stores both moves in an array for the
   main function to use for score keeping */
void pick_move(int* moves);
