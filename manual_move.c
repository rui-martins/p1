#include "manual_move.h"
#include "toroidal.h"
#include "neighborhood.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void manual_play(int WORLD_X, int WORLD_Y, AGENT agent_grid[WORLD_X][WORLD_Y],
                 AGENT **agents_array, unsigned int i,
                 unsigned int nagents, int *nhumans) {

    char move[50];
    int ag_x = agents_array[i]->x;
    int ag_y = agents_array[i]->y;
    int dx;
    int dy;
    COORDS new_pos = {0, 0};
    AGENT no_agent = {None, 0, 0, 0, 0};

    printf("\nYour agent's Id:%x | X:%d Y:%d\n",
        agents_array[i]->id, agents_array[i]->x, agents_array[i]->y);
    printf("Choose direction.\n\n");
    printf("  1  2  3\n   \\ | /\n8 ── © ── 4\n   / | \\\n  7  6  5\n");


    do {
        printf("Input must be from 1 to 8:\n");
        fgets(move, sizeof(move), stdin);
    } while (strcmp(move, "1\n") != 0 && strcmp(move, "2\n") != 0 &&

    strcmp(move, "3\n") != 0 && strcmp(move, "4\n") != 0 &&
    strcmp(move, "5\n") != 0 && strcmp(move, "6\n") != 0 &&
    strcmp(move, "7\n") != 0 && strcmp(move, "8\n") != 0);

    if (strcmp(move, "1\n") == 0)  {
        dx = -1;
        dy = -1;
    }
    else if (strcmp(move, "2\n") == 0) {
        dx = 0;
        dy = -1;
    }
    else if (strcmp(move, "3\n") == 0) {
        dx = 1;
        dy = -1;
    }
    else if (strcmp(move, "4\n") == 0) {
        dx = 1;
        dy = 0;
    }
    else if (strcmp(move, "5\n") == 0) {
        dx = 1;
        dy = 1;
    }
    else if (strcmp(move, "6\n") == 0) {
        dx = 0;
        dy = 1;
    }
    else if (strcmp(move, "7\n") == 0) {
        dx = -1;
        dy = 1;
    }
    else if (strcmp(move, "8\n") == 0) {
        dx = -1;
        dy = 0;
    }
    new_pos = verify_borders(WORLD_X, WORLD_Y, ag_x, ag_y, dx, dy);

    if (agent_grid[new_pos.x][new_pos.y].type == None) {
        agent_grid[new_pos.x][new_pos.y] = agent_grid[ag_x][ag_y];
        agents_array[i]->x = new_pos.x;
        agents_array[i]->y = new_pos.y;
        agent_grid[ag_x][ag_y] = no_agent;
    }
    else if ( (agent_grid[ag_x][ag_y].type == Zombie) &&
    (agent_grid[new_pos.x][new_pos.y].type == Human) ) {

        agent_grid[new_pos.x][new_pos.y].type = Zombie;
        (*nhumans)--;

        for (unsigned int j = 0; j < nagents; j++) {
            if ((agents_array[j]->x == new_pos.x) &&
            (agents_array[j]->y == new_pos.y)) {
                agents_array[j]->type = Zombie;
            }
        }
    }
}
