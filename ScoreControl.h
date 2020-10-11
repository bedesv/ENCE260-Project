/** @file   ScoreControl.c
    @author Bede Skinner-Vennell, Jack Warburton
    @date   7 October 2020
    @brief  Score functions module

    This module defines the functions to manage the score on each board
*/

/* The structure of the scoreboard */
typedef struct scoreboard {
    int wins;
    int losses;
    int draws;
    int played;
} stats;

/* Initialise the scoreboard */
void score_init(stats* score);

/*Checks who won the round
 * Actions:
 * P R S = 0 1 2 -possible_chars list in PlayerSelection.c
 *
 * Result:
 * 0 = draw
 * 1 = win
 * 2 = loss
 */
int check_selections(int home, int away);

/* Checks the current round and updates scoreboard */
void update_score(int home, int away, stats* score);

/* Stores the games current score in a provided space */
void get_score(stats* score, char* current_stats);
