#include "manual_move.h"
#include "toroidal.h"
#include "neighborhood.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function of playable agents */
void manual_play(int WORLD_X, int WORLD_Y, AGENT agent_grid[WORLD_X][WORLD_Y],
                 AGENT **agents_array, unsigned int i,
                 unsigned int nagents, int *nhumans) {

    char move[50]; /* String that holds input from user */
    int ag_x = agents_array[i]->x; /* Actual agent X coordinate*/
    int ag_y = agents_array[i]->y; /* Actual agent Y coordinate*/
    int dx; /* Destination x coordinate */
    int dy; /* Destination y coordinate */
    COORDS new_pos = {0, 0}; /* New COORDS object initialized */
    AGENT no_agent = {None, 0, 0, 0, 0}; /* New AGENT object initialized */

    /* Print agent ID of the agent you're controlling along with its positions */
    printf("\nYour agent's Id:%x | X:%d Y:%d\n",
        agents_array[i]->id, agents_array[i]->x, agents_array[i]->y);
        /* Print figure that shows possible ways to move the agent */
    printf("Choose direction.\n\n");
    printf("  1  2  3\n   \\ | /\n8 ── © ── 4\n   / | \\\n  7  6  5\n");

    /* Repeat cycle while input is different from 1 to 8. */
    do {
        printf("Input must be from 1 to 8:\n");
        /* Receive user input from console */
        fgets(move, sizeof(move), stdin);
    } while (strcmp(move, "1\n") != 0 && strcmp(move, "2\n") != 0 &&
             strcmp(move, "3\n") != 0 && strcmp(move, "4\n") != 0 &&
             strcmp(move, "5\n") != 0 && strcmp(move, "6\n") != 0 &&
             strcmp(move, "7\n") != 0 && strcmp(move, "8\n") != 0);

    /* If compare of our string and number is == 0 it means it is equal */

    /* If comparation is verified then destination x and y get new coordinates */
    if (strcmp(move, "1\n") == 0)  {
        dx = -1;
        dy = -1;
    }
    /* If comparation is verified then destination x and y get new coordinates */
    else if (strcmp(move, "2\n") == 0) {
        dx = 0;
        dy = -1;
    }
    /* If comparation is verified then destination x and y get new coordinates */
    else if (strcmp(move, "3\n") == 0) {
        dx = 1;
        dy = -1;
    }
    /* If comparation is verified then destination x and y get new coordinates */
    else if (strcmp(move, "4\n") == 0) {
        dx = 1;
        dy = 0;
    }
    /* If comparation is verified then destination x and y get new coordinates */
    else if (strcmp(move, "5\n") == 0) {
        dx = 1;
        dy = 1;
    }
    /* If comparation is verified then destination x and y get new coordinates */
    else if (strcmp(move, "6\n") == 0) {
        dx = 0;
        dy = 1;
    }
    /* If comparation is verified then destination x and y get new coordinates */
    else if (strcmp(move, "7\n") == 0) {
        dx = -1;
        dy = 1;
    }
    /* If comparation is verified then destination x and y get new coordinates */
    else if (strcmp(move, "8\n") == 0) {
        dx = -1;
        dy = 0;
    }
    /* new_pos receive coordinates from verify_borders that are never offgrid */
    new_pos = verify_borders(WORLD_X, WORLD_Y, ag_x, ag_y, dx, dy);

    /* If position where we want to move is empty then... */
    if (agent_grid[new_pos.x][new_pos.y].type == None) {
        /* New position gets actual agent */
        agent_grid[new_pos.x][new_pos.y] = agent_grid[ag_x][ag_y];
        /* Positions are also changed in the array of pointers */
        agents_array[i]->x = new_pos.x;
        agents_array[i]->y = new_pos.y;
        /* Old position is empty now */
        agent_grid[ag_x][ag_y] = no_agent;
    }
    /* If actual agent is a Zombie and agent at new position is of type Human */
    else if ( (agent_grid[ag_x][ag_y].type == Zombie) &&
    (agent_grid[new_pos.x][new_pos.y].type == Human) ) {
        /* Then agent at new position turns into a Zombie */
        agent_grid[new_pos.x][new_pos.y].type = Zombie;
        /* Number of humans decrease */
        (*nhumans)--;
        /* Cycle through the array used for shuffle */
        for (unsigned int j = 0; j < nagents; j++) {
            /* If we find our agent at new position in the array of shuffle... */
            if ((agents_array[j]->x == new_pos.x) &&
            (agents_array[j]->y == new_pos.y)) {
                /* Then he also becomes of Zombie there */
                agents_array[j]->type = Zombie;
            }
        }
    }
}
