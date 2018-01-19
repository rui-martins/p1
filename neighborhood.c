#include "neighborhood.h"
#include "AI_move.h"
#include "example.h"
#include <stdio.h>

void nearest_agent_at (int WORLD_X, int WORLD_Y,
                       AGENT agent_grid[WORLD_X][WORLD_Y],
                       AGENT **agents_array, unsigned int i,
                       unsigned int nagents, int *nhumans) {

    COORDS position = {0, 0}; // Var of type COORDS to verify positions.
    int r = 1; /* Radius of verify. */
    int dx = 0; /* destination x to verify. */
    int dy = 0; // destination y to verify.
    int x = 0; // receives x coord from verify_borders after offbound verify.
    int y = 0; // receives y coord from verify_borders after offbound verify.
    int FLAG; // FLAG changes to 1 when nearest agent is found.
    int BIGGEST_COORD;

    if (WORLD_X > WORLD_Y) {
        BIGGEST_COORD = WORLD_X;
    }
    else {
        BIGGEST_COORD = WORLD_Y;
    }

    FLAG = 0;
    if ( (agents_array[i]->type == Human)
    && (agents_array[i]->playable == 0) ) {
        printf("\nHuman: Id:%x | X:%d Y:%d\n",
        agents_array[i]->id, agents_array[i]->x, agents_array[i]->y);

        for (r = 1; r <= (BIGGEST_COORD/2); r++) {
            if (FLAG == 1) break;
            for (dx = -r; dx <= r; dx++) {
                if (FLAG == 1) break;
                    for (dy = -r; dy <= r; dy++) {

                        position = verify_borders(WORLD_X, WORLD_Y,
                        agents_array[i]->x, agents_array[i]->y, dx, dy);

                        x = position.x;
                        y = position.y;
                        if (agent_grid[x][y].type == Zombie) {
                            FLAG = 1;
                            printf("\nNearest Zombie: Id:%x | X:%d Y:%d\n",
                            agent_grid[x][y].id, x, y);

                            human_flee(WORLD_X, WORLD_Y, agent_grid, agents_array, i, x, y, r);
                            break;
                        }
                    }
                }
            }
        }
    else {
        if ( (agents_array[i]->type == Zombie)
        && (agents_array[i]->playable == 0) ) {
            printf("\nZombie: Id:%x | X:%d Y:%d\n",
            agents_array[i]->id, agents_array[i]->x, agents_array[i]->y);

            for (r = 1; r <= (BIGGEST_COORD/2); r++) {
                if (FLAG == 1) break;
                for (dx = -r; dx <= r; dx++) {
                    if (FLAG == 1) break;
                    for (dy = -r; dy <= r; dy++) {

                    position = verify_borders(WORLD_X, WORLD_Y,
                    agents_array[i]->x, agents_array[i]->y, dx, dy);

                    x = position.x;
                    y = position.y;
                    if (agent_grid[x][y].type == Human) {
                        FLAG = 1;
                        printf("\nNearest Human: Id:%x | X:%d Y:%d\n",
                        agent_grid[x][y].id, x, y);

                        zombie_chase(WORLD_X, WORLD_Y, agent_grid, agents_array,
                        i, x, y, r, nagents, nhumans);

                        break;
                                                }
                    }
                }
            }
        }
    }
}
