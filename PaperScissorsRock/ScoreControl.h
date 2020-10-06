/** @file   ScoreControl.h
    @author Bede Skinner-Vennell, Jack Warburton
    @date   7 October 2020
    @brief  Score functions header

    Simple scorekeeping system
*/

#include "system.h"

//Scoreboard structure
typedef struct scoreboard {
    int wins;
    int losses;
    int draws;
    int played;
} stats;

// Initialise the scoreboard
void score_init(stats* score);

/*Checks who won the round
 * Actions:
 * P R S = 0 1 2 (respectively)
 *
 * Result:
 * 0 = draw
 * 1 = win
 * 2 = loss
 */
int check_selections(int home, int away);

//Checks current round and updates scoreboard
void update_score(int home, int away, stats* score);

//Returns the address of the scoreboard
char* get_score(stats* score);
