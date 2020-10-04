#include "system.h"
#include <stdlib.h>

typedef struct scoreboard {
    int wins;
    int losses;
    int draws;
    int played;
} stats;

// Initialise the scoreboard
void score_init(void);

/*Checks who won the round
 * Actions:
 * P R S = 0 1 2
 *
 * Result:
 * 0 = draw
 * 1 = win
 * 2 = loss
 */
int check_selections(int home, int away);

//Checks current round and updates scoreboard
void update_score(int home, int away);

//Returns the address of the scoreboard
stats* get_score(void);

//Frees the malloc (deletes scoreboard)
void free_score(void);


