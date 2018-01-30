#include "agent.h"
#include <stdlib.h>

/* Function to create a new agent */
AGENT *agent_new(AGENT_TYPE type, unsigned char playable,
                 unsigned short id, int x, int y) {

    /* Allocate size for new AGENT object */
    AGENT *ag_new = (AGENT *) malloc(sizeof(AGENT));
    /* Set AGENT information */
    ag_new->type = type;
    ag_new->playable = playable;
    ag_new->id = id;
    ag_new->x = x;
    ag_new->y = y;

    /* Return AGENT object info */
    return ag_new;
}

/* Function to destroy an AGENT object. */
void agent_destroy(AGENT *ag_new) {
    /* Free the allocated memory for ag_new */
    free(ag_new);
}

/* Function to populate the grid */
void put_agent_on_grid(
    int WORLD_X, int WORLD_Y,
    AGENT agent_grid[WORLD_X][WORLD_Y],
    CONFIG cfg, unsigned int *nagents) {

    /* Counters to prevent exceeding spawn defined in the config file */
    int counterh = 0;
    int counterz = 0;
    int counterhplayers = 0;
    int counterzplayers = 0;
    /* Random X and Y that will serve to put an agent on specific coords in grid */
    int x_rand;
    int y_rand;
    /* Variables receive values from the config file! */
    int nzombies = cfg.nzombies;
    int nhumans = cfg.nhumans;
    int nzplayers = cfg.nzplayers;
    int nhplayers = cfg.nhplayers;
    /* Initialize ag */
    AGENT ag = {None, 0, 0, 0, 0};

    /* While there are still humans or zombies to spawn, generate random
    X and Y coords until grid cell is empty. */
    while ((counterh < nhumans) || (counterz < nzombies)) {
        do {
            x_rand = rand() % WORLD_X;
            y_rand = rand() % WORLD_Y;
        }
        while (agent_grid[x_rand][y_rand].type != None);

        /* If counter hasn't reached all humans yet, spawn another one. */
        if (counterh < nhumans) {
            ag.type = Human;
            counterh++;
            /* If playable humans haven't reached the limit, spawn one more */
            if (counterhplayers < nhplayers) {
                ag.playable = 1;
                /* Increment number of playable humans */
                counterhplayers++;
            }
            /* If playable humans number is full, then human isn't playable */
            else {
            ag.playable = 0;
            }
        }
        else {
            /* Spawn zombie if there are still zombies to spawn */
            if (counterz < nzombies) {
                ag.type = Zombie;
                /* Increment number of zombies */
                counterz++;
                /* Zombie is playable if playable zombies aren't full */
                if (counterzplayers < nzplayers) {
                    ag.playable = 1;
                    /* Increment playable zombies number*/
                    counterzplayers++;
                }
                /* Otherwise Zombie isn't playable */
                else {
                    ag.playable = 0;
                }
            }
        }
        /* Assign agent ID and then increment number of agents so far. */
        ag.id = (*nagents)++;

        /* Assign agent X coordinate */
        ag.x = x_rand;

        /* Assign agent Y coordinate */
        ag.y = y_rand;

        /* Assign agent to grid at (i,j). */
        agent_grid[x_rand][y_rand] = ag;
    }
}
