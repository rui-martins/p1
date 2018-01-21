#include "example.h"
#include "AI_move.h"
#include <stdio.h>
#include <stdlib.h>

void human_flee(int WORLD_X, int WORLD_Y, AGENT agent_grid[WORLD_X][WORLD_Y],
                AGENT **agents_array, unsigned int i,
                int enemy_x, int enemy_y, int r) {

    int ag_x = agents_array[i]->x; /* Actual agent X pos */
    int ag_y = agents_array[i]->y; /* Actual agent Y pos */
    int dx, dy = 0;
    COORDS new_pos = {0, 0};
    AGENT no_agent = {None, 0, 0, 0, 0};

    if ( abs(agents_array[i]->x - enemy_x) > r ) {
        if (agents_array[i]->x - enemy_x < 0) {
            dx = 1;
        }
        if (agents_array[i]->x - enemy_x > 0) {
            dx = -1;
        }
    }
    else {
        if (agents_array[i]->x - enemy_x < 0) {
            dx = -1;
        }
        if (agents_array[i]->x - enemy_x == 0) {
            dx = 0;
        }
        if (agents_array[i]->x - enemy_x > 0) {
            dx = 1;
        }
    }

    if ( abs(agents_array[i]->y - enemy_y) > r ) {
        if (agents_array[i]->y - enemy_y < 0) {
            dy = 1;
        }
        if (agents_array[i]->y - enemy_y > 0) {
            dy = -1;
        }
    }
    else {
        if (agents_array[i]->y - enemy_y < 0) {
            dy = -1;
        }
        if (agents_array[i]->y - enemy_y == 0) {
            dy = 0;
        }
        if (agents_array[i]->y - enemy_y > 0) {
            dy = 1;
        }
    }

    new_pos = verify_borders(WORLD_X, WORLD_Y, ag_x, ag_y, dx, dy);

    if (agent_grid[new_pos.x][new_pos.y].type == None) {
        agent_grid[new_pos.x][new_pos.y] = agent_grid[ag_x][ag_y];
        agents_array[i]->x = new_pos.x;
        agents_array[i]->y = new_pos.y;
        agent_grid[ag_x][ag_y] = no_agent;
    }
}

void zombie_chase(int WORLD_X, int WORLD_Y, AGENT agent_grid[WORLD_X][WORLD_Y],
                  AGENT **agents_array, unsigned int i,
                  int enemy_x, int enemy_y, int r,
                  unsigned int nagents, int *nhumans) {

    int ag_x = agents_array[i]->x; /* Actual agent X pos */
    int ag_y = agents_array[i]->y; /* Actual agent Y pos */
    int dx, dy = 0;
    COORDS new_pos = {0, 0};
    AGENT no_agent = {None, 0, 0, 0, 0};

    if ( abs(agents_array[i]->x - enemy_x) > r ) {
        if (agents_array[i]->x - enemy_x < 0) {
            dx = -1;
        }
        if (agents_array[i]->x - enemy_x > 0) {
            dx = 1;
        }
    }
    else {
        if (agents_array[i]->x - enemy_x < 0) {
            dx = 1;
        }
        if (agents_array[i]->x - enemy_x == 0) {
            dx = 0;
        }
        if (agents_array[i]->x - enemy_x > 0) {
            dx = -1;
        }
    }

    if ( abs(agents_array[i]->y - enemy_y) > r ) {
        if (agents_array[i]->y - enemy_y < 0) {
            dy = -1;
        }
        if (agents_array[i]->y - enemy_y > 0) {
            dy = 1;
        }
    }
    else {
        if (agents_array[i]->y - enemy_y < 0) {
            dy = 1;
        }
        if (agents_array[i]->y - enemy_y == 0) {
            dy = 0;
        }
        if (agents_array[i]->y - enemy_y > 0) {
            dy = -1;
        }
    }
    new_pos = verify_borders(WORLD_X, WORLD_Y, ag_x, ag_y, dx, dy);

    if (agent_grid[new_pos.x][new_pos.y].type == None) {
        agent_grid[new_pos.x][new_pos.y] = agent_grid[ag_x][ag_y];
        agents_array[i]->x = new_pos.x;
        agents_array[i]->y = new_pos.y;
        agent_grid[ag_x][ag_y] = no_agent;
    }
    if (agent_grid[new_pos.x][new_pos.y].type == Human) {
        agent_grid[new_pos.x][new_pos.y].type = Zombie;
        (*nhumans)--;
        if (agent_grid[new_pos.x][new_pos.y].playable == 1) {
            agent_grid[new_pos.x][new_pos.y].playable = 0;
        }

        for (unsigned int j = 0; j < nagents; j++) {
            if ((agents_array[j]->x == new_pos.x) &&
            (agents_array[j]->y == new_pos.y)) {
                agents_array[j]->type = Zombie;
                if (agents_array[j]->playable == 1) {
                    agents_array[j]->playable = 0;
                }
            }
        }
    }
}
