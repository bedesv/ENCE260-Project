#include "system.h"
#include "PaperScissorsRock.h"

#define WINS = 0
#define LOST = 0
#define DRAWS = 0
#definr PLAYED = 0

/* P R S = 0 1 2
 *
 * Result:
 * 0 = draw
 * 1 = win
 * 2 = loss
 */
int check_selections(int home int away)
{
    u_int16_t result;
    //Tie
    if (home == away) {
        result = 0;
    }

    if (home < away) {
       if ((b-a) = 1) {
           result = 1;
       } else {
           result = 2;
       }
    } else {
        if ((a-b) = 1) {
           result = 2;
       } else {
           result = 1;
       }
    }
    return result;
}

void update_score(int home int away)
{
    int result = check_solutions(int home int away);
    if (result = 1) {
        WINS++;
    }
    if (result = 2) {
        LOST++;
    }
    PLAYED++;
}

int* get_score()
{
    int* stats[] = {WINS, LOST, DRAW, PLAYED}
    return stats;
}


int main(void)
{

}
