#include "example.h"
#include "AI_move.h"
#include <stdio.h>
#include <stdlib.h>

/* Function that makes humans run from zombies */
void human_flee(int WORLD_X, int WORLD_Y, AGENT agent_grid[WORLD_X][WORLD_Y],
                AGENT **agents_array, unsigned int i,
                int enemy_x, int enemy_y, int r) {

    int ag_x = agents_array[i]->x; /* Actual agent X pos */
    int ag_y = agents_array[i]->y; /* Actual agent Y pos */
    int dx, dy = 0; /* Destination X and Y */
    COORDS new_pos = {0, 0}; /* Initialize new COORDS object */
    AGENT no_agent = {None, 0, 0, 0, 0}; /* Initialize empty AGENT object */

    /* If distance of actual agent X to enemy > radius then */
    if ( abs(agents_array[i]->x - enemy_x) > r ) {
        /* It the result is < 0 then destination X is 1 */
        if (agents_array[i]->x - enemy_x < 0) {
            dx = 1;
        /* It the result is > 0 then destination X is -1 */
        }
        if (agents_array[i]->x - enemy_x > 0) {
            dx = -1;
        }
    }
    /* If distance of actual agent X to enemy < radius then */
    else {
        /* It the result is < 0 then destination X is -1 */
        if (agents_array[i]->x - enemy_x < 0) {
            dx = -1;
        }
        /* It the result is == 0 then destination X is 0 */
        if (agents_array[i]->x - enemy_x == 0) {
            dx = 0;
        }
        /* It the result is > 0 then destination X is 1 */
        if (agents_array[i]->x - enemy_x > 0) {
            dx = 1;
        }
    }
    /* If distance of actual agent Y to enemy > radius then */
    if ( abs(agents_array[i]->y - enemy_y) > r ) {
        /* It the result is < 0 then destination Y is 1 */
        if (agents_array[i]->y - enemy_y < 0) {
            dy = 1;
        /* It the result is > 0 then destination Y is -1 */
        }
        if (agents_array[i]->y - enemy_y > 0) {
            dy = -1;
        }
    }
    /* If distance of actual agent Y to enemy < radius then */
    else {
        /* It the result is < 0 then destination Y is -1 */
        if (agents_array[i]->y - enemy_y < 0) {
            dy = -1;
        }
        /* It the result is == 0 then destination Y is 0 */
        if (agents_array[i]->y - enemy_y == 0) {
            dy = 0;
        }
        /* It the result is > 0 then destination Y is 1 */
        if (agents_array[i]->y - enemy_y > 0) {
            dy = 1;
        }
    }

    /* new_pos receives correct coordinates that aren't offgrid */
    new_pos = verify_borders(WORLD_X, WORLD_Y, ag_x, ag_y, dx, dy);

    /* If agent where we want to move is None then we move there*/
    if (agent_grid[new_pos.x][new_pos.y].type == None) {
        /* New position receives agent info from actual position */
        agent_grid[new_pos.x][new_pos.y] = agent_grid[ag_x][ag_y];
        /* Positions also change in the array of pointers (to shuffle) */
        agents_array[i]->x = new_pos.x;
        agents_array[i]->y = new_pos.y;
        /* Old position receives a "None" agent which equals empty. */
        agent_grid[ag_x][ag_y] = no_agent;
    }
}

/* Function that makes zombies chase humans */
void zombie_chase(int WORLD_X, int WORLD_Y, AGENT agent_grid[WORLD_X][WORLD_Y],
                  AGENT **agents_array, unsigned int i,
                  int enemy_x, int enemy_y, int r,
                  unsigned int nagents, int *nhumans) {

    int ag_x = agents_array[i]->x; /* Actual agent X pos */
    int ag_y = agents_array[i]->y; /* Actual agent Y pos */
    int dx, dy = 0; /* Destination X and Y */
    COORDS new_pos = {0, 0}; /* Initialize new COORDS object */
    AGENT no_agent = {None, 0, 0, 0, 0}; /* Initialize empty AGENT object */

    /* If distance of actual agent X to enemy > radius then */
    if ( abs(agents_array[i]->x - enemy_x) > r ) {
        /* It the result is < 0 then destination X is -1 */
        if (agents_array[i]->x - enemy_x < 0) {
            dx = -1;
        }
        /* It the result is > 0 then destination X is 1 */
        if (agents_array[i]->x - enemy_x > 0) {
            dx = 1;
        }
    }
    /* If distance of actual agent X to enemy < radius then */
    else {
        /* It the result is < 0 then destination X is 1 */
        if (agents_array[i]->x - enemy_x < 0) {
            dx = 1;
        }
        /* It the result is == 0 then destination X is 0 */
        if (agents_array[i]->x - enemy_x == 0) {
            dx = 0;
        }
        /* It the result is > 0 then destination X is -1 */
        if (agents_array[i]->x - enemy_x > 0) {
            dx = -1;
        }
    }
    /* If distance of actual agent Y to enemy > radius then */
    if ( abs(agents_array[i]->y - enemy_y) > r ) {
        /* It the result is < 0 then destination Y is -1 */
        if (agents_array[i]->y - enemy_y < 0) {
            dy = -1;
        }
        /* It the result is > 0 then destination Y is 1 */
        if (agents_array[i]->y - enemy_y > 0) {
            dy = 1;
        }
    }
    /* If distance of actual agent Y to enemy < radius then */
    else {
        /* It the result is < 0 then destination Y is 1 */
        if (agents_array[i]->y - enemy_y < 0) {
            dy = 1;
        }
        /* It the result is == 0 then destination Y is 0 */
        if (agents_array[i]->y - enemy_y == 0) {
            dy = 0;
        }
        /* It the result is > 0 then destination Y is -1 */
        if (agents_array[i]->y - enemy_y > 0) {
            dy = -1;
        }
    }
    /* new_pos receives correct coordinates that aren't offgrid */
    new_pos = verify_borders(WORLD_X, WORLD_Y, ag_x, ag_y, dx, dy);

    /* If position where we want to move is empty (None) then we move */
    if (agent_grid[new_pos.x][new_pos.y].type == None) {
        /* New position receives AGENT from actual position */
        agent_grid[new_pos.x][new_pos.y] = agent_grid[ag_x][ag_y];
        /* Coordinates are also changed in the array of pointers (to shuffle) */
        agents_array[i]->x = new_pos.x;
        agents_array[i]->y = new_pos.y;
        /* Old position receives a "None" agent (Empty space) */
        agent_grid[ag_x][ag_y] = no_agent;
    }
    /* If position where we want to move is occupied by a human */
    if (agent_grid[new_pos.x][new_pos.y].type == Human) {
        /* Then human turns into a zombie */
        agent_grid[new_pos.x][new_pos.y].type = Zombie;
        /* Counter of humans decrease */
        (*nhumans)--;
        /* Also, if human was a playable agent, then it isn't anymore */
        if (agent_grid[new_pos.x][new_pos.y].playable == 1) {
            agent_grid[new_pos.x][new_pos.y].playable = 0;
        }
        /* Cycle through the array used for shuffle */
        for (unsigned int j = 0; j < nagents; j++) {
            /* If we find a match of the agent at new X, Y */
            if ((agents_array[j]->x == new_pos.x) &&
            (agents_array[j]->y == new_pos.y)) {
                /* Then we also change its type to Zombie on the array */
                agents_array[j]->type = Zombie;
                /* And change it to non playable if it was before */
                if (agents_array[j]->playable == 1) {
                    agents_array[j]->playable = 0;
                }
            }
        }
    }
}
