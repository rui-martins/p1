#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shuffle.h"

void shuffle(AGENT **agents_to_shuffle, unsigned int nagents) {
    printf("%s\n\n", "---- Agents shuffled. New turn starting ----\n");

    unsigned int i;
    unsigned int j = 0;
    AGENT *temp;

    for (i = nagents - 1; i > 0; i--) {
        j = rand() % (i + 1);
        temp = agents_to_shuffle[i];
        agents_to_shuffle[i] = agents_to_shuffle[j];
        agents_to_shuffle[j] = temp;
    }
}
