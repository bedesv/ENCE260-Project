#include "system.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct scoreboard {
    int wins;
    int losses;
    int draws;
    int played;
} stats;


// Initialise the scoreboard
void score_init(stats* score)
{
    score->wins = 0;
    score->losses = 0;
    score->draws = 0;
    score->played = 0;
}

/*Checks who won the round
 * Actions:
 * P R S = 0 1 2
 *
 * Result:
 * 0 = draw
 * 1 = win
 * 2 = loss
 */
int check_selections(int home, int away)
{
    uint16_t result;
    //Tie
    if (home == away) {
        result = 0;

    } else if (home < away) {
        if ((away-home) == 1) {
            result = 1;
        } else {
            result = 2;
        }
    } else {
        if ((home-away) == 1) {
            result = 2;
        } else {
            result = 1;
        }
    }
    return result;
}

//Checks current round and updates scoreboard
void update_score(int home, int away, stats* score)
{
    int result = -1;
    result = check_selections(home, away);
    if (result == 1) {
        score->wins++;
    }
    if (result == 2) {
        score->losses++;
    }
    if (result == 0) {
        score->draws++;
    }
    score->played++;
}

//Returns the address of the scoreboard
char* get_score(stats* score)
{
    char* return_string = "";
    sprintf(return_string, "W%d L%d D%d P%d", score->wins, score->losses, score->draws, score->played);
    return return_string;
}
