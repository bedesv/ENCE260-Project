/** @file   ScoreControl.c
    @author Bede Skinner-Vennell, Jack Warburton
    @date   7 October 2020
    @brief  Score functions module

    This module defines the functions to manage the score on each board
*/

#include "system.h"
#include <stdlib.h>
#include <stdio.h>

/* The structure of the scoreboard */
typedef struct scoreboard {
    int wins;
    int losses;
    int draws;
    int played;
} stats;

/* Initialise the scoreboard */
void score_init(stats* score)
{
    score->wins = 0;
    score->losses = 0;
    score->draws = 0;
    score->played = 0;
}

/*Checks who won the round
 * Actions:
 * P R S = 0 1 2 -possible_chars list in PlayerSelection.c
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

/* Checks the current round and updates scoreboard */
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

/* Stores the games current score in a provided space */
void get_score(stats* score, char* current_stats)
{
    sprintf(current_stats, "W%d L%d D%d P%d", score->wins, score->losses, score->draws, score->played);
}
