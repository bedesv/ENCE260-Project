#include "system.h"
#include <stdlib.h>

typedef struct scoreboard {
    int wins;
    int losses;
    int draws;
    int played;
} stats;


stats* SCORE = NULL;

// Initialise the scoreboard
void score_init(void)
{
    SCORE = malloc(sizeof(stats));
    SCORE->wins = 0;
    SCORE->losses = 0;
    SCORE->draws = 0;
    SCORE->played = 0;
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
void update_score(int home, int away)
{
    int result = 0;
    result = check_selections(home, away);
    if (result == 1) {
        SCORE->wins++;

    } else if (result == 2) {
        SCORE->losses++;
    } else {
        SCORE->draws++;

    }
    SCORE->played++;
}

//Returns the address of the scoreboard
stats* get_score(void)
{
    return SCORE;
}

//Frees the malloc (deletes scoreboard)
void free_score(void)
{
    free(SCORE);
}


