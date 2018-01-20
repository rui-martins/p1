#include "agent.h"
#include <stdlib.h>

AGENT *agent_new(AGENT_TYPE type, unsigned char playable,
                 unsigned short id, int x, int y) {

    AGENT *ag_new = (AGENT *) malloc(sizeof(AGENT));
    ag_new->type = type;
    ag_new->playable = playable;
    ag_new->id = id;
    ag_new->x = x;
    ag_new->y = y;

    return ag_new;
}

void agent_destroy(AGENT *ag_new) {
    free(ag_new);
}

void put_agent_on_grid(
    int WORLD_X, int WORLD_Y,
    AGENT agent_grid[WORLD_X][WORLD_Y],
    CONFIG cfg, unsigned int *nagents) {

    int counterh = 0;
    int counterz = 0;
    int counterhplayers = 0;
    int counterzplayers = 0;
    int x_rand;
    int y_rand;
    int nzombies = cfg.nzombies;
    int nhumans = cfg.nhumans;
    int nzplayers = cfg.nzplayers;
    int nhplayers = cfg.nhplayers;
    AGENT ag = {None, 0, 0, 0, 0};

    while ((counterh < nhumans) || (counterz < nzombies)) {
        do {
            x_rand = rand() % WORLD_X;
            y_rand = rand() % WORLD_Y;
        }
        while (agent_grid[x_rand][y_rand].type != None);

        if (counterh < nhumans) {
            ag.type = Human;
            counterh++;
            if (counterhplayers < nhplayers) {
                ag.playable = 1;
                counterhplayers++;
            }
            else {
            ag.playable = 0;
            }
        }
        else {
            if (counterz < nzombies) {
                ag.type = Zombie;
                counterz++;
                if (counterzplayers < nzplayers) {
                    ag.playable = 1;
                    counterzplayers++;
                }
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
