#include "system.h"


static const char possible_chars[] ;

// Returns the index of the character in possible chars structure
int index_of_char(char character);

//
void selection_changed(int* char_index);


void check_received_char(int* received_char, int* away_char, bool* char_received_success);


void send_and_receive_moves(char* character, int* received_char);



// Lets player make their decison: Paper/Scissors/Rock
void pick_move(int* moves);
