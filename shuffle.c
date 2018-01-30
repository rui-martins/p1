#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shuffle.h"

/* Function to shuffle agents before each turn */
void shuffle(AGENT **agents_to_shuffle, unsigned int nagents) {
    /* Print message to warn of shuffle */
    printf("%s\n\n", "---- Agents shuffled. New turn starting ----\n");

    unsigned int i = 0; /* Var to pass value to j */
    unsigned int j = 0; /* Var to receive value from temp */
    AGENT *temp; /* Pointer to AGENT that receives a temporary value */

    /* FISHER YATES Shuffle */
    for (i = nagents - 1; i > 0; i--) {
        j = rand() % (i + 1);
        temp = agents_to_shuffle[i];
        agents_to_shuffle[i] = agents_to_shuffle[j];
        agents_to_shuffle[j] = temp;
    }
}
