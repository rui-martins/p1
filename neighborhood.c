#include "neighborhood.h"
#include "AI_move.h"
#include "example.h"
#include <stdio.h>

/* Function to search for nearest agent */
void nearest_agent_at (int WORLD_X, int WORLD_Y,
                       AGENT agent_grid[WORLD_X][WORLD_Y],
                       AGENT **agents_array, unsigned int i,
                       unsigned int nagents, int *nhumans) {

    COORDS position = {0, 0}; /* Var of type COORDS to verify positions. */
    int r = 1; /* Radius of verify. */
    int dx = 0; /* destination x to verify. */
    int dy = 0; /* destination y to verify. */
    int x = 0; /* receives x coord from verify_borders after offbound verify.*/
    int y = 0; /* receives y coord from verify_borders after offbound verify. */
    int FLAG; /* FLAG changes to 1 when nearest agent is found. */
    int BIGGEST_COORD; /* Used to determine when the radius search should stop */

    /* Biggest coordinate determines when the radius will stop */
    if (WORLD_X > WORLD_Y) {
        BIGGEST_COORD = WORLD_X;
    }
    else {
        BIGGEST_COORD = WORLD_Y;
    }

    FLAG = 0;
    /* If actual agent type is a Human and it isn't playable... */
    if ( (agents_array[i]->type == Human)
    && (agents_array[i]->playable == 0) ) {
        /* Print its ID along with coordinates */
        printf("\nHuman: Id:%x | X:%d Y:%d\n",
        agents_array[i]->id, agents_array[i]->x, agents_array[i]->y);

        /* For radius starting at 1 until biggest cord / 2 */
        for (r = 1; r <= (BIGGEST_COORD/2); r++) {
            if (FLAG == 1) break;
            /* Moore Neighbourhood verify - Squares surrounding the agent */
            for (dx = -r; dx <= r; dx++) {
                if (FLAG == 1) break;
                    for (dy = -r; dy <= r; dy++) {

                        /* position receives right coordinates from toroidal */
                        position = verify_borders(WORLD_X, WORLD_Y,
                        agents_array[i]->x, agents_array[i]->y, dx, dy);

                        /* x is equal to the position returned by the struct */
                        x = position.x;
                        /* y is equal to the position returned by the struct */
                        y = position.y;
                        /* If agent on x,y is a Zombie... */
                        if (agent_grid[x][y].type == Zombie) {
                            FLAG = 1;
                            /* Print its ID and coordinates */
                            printf("\nNearest Zombie: Id:%x | X:%d Y:%d\n",
                            agent_grid[x][y].id, x, y);
                            /* Call the function for the human to flee! */
                            human_flee(WORLD_X, WORLD_Y, agent_grid, agents_array, i, x, y, r);
                            break;
                        }
                    }
                }
            }
        }
    else {
        /* If actual agent is a Zombie and it isn't playable then... */
        if ( (agents_array[i]->type == Zombie)
        && (agents_array[i]->playable == 0) ) {
            /* Print its ID along with coordinates */
            printf("\nZombie: Id:%x | X:%d Y:%d\n",
            agents_array[i]->id, agents_array[i]->x, agents_array[i]->y);

            /* For radius starting at 1 until biggest cord / 2 */
            for (r = 1; r <= (BIGGEST_COORD/2); r++) {
                if (FLAG == 1) break;
                /* Moore Neighbourhood verify - Squares surrounding the agent */
                for (dx = -r; dx <= r; dx++) {
                    if (FLAG == 1) break;
                    for (dy = -r; dy <= r; dy++) {

                        /* position receives right coordinates from toroidal */
                        position = verify_borders(WORLD_X, WORLD_Y,
                            agents_array[i]->x, agents_array[i]->y, dx, dy);

                        /* x is equal to the position returned by the struct */
                        x = position.x;
                        /* y is equal to the position returned by the struct */
                        y = position.y;
                        /* If agent at x,y is a Human then... */
                        if (agent_grid[x][y].type == Human) {
                            FLAG = 1;
                            /* Print enemy's ID along with coordinates */
                            printf("\nNearest Human: Id:%x | X:%d Y:%d\n",
                            agent_grid[x][y].id, x, y);
                            /* Call the function for the zombie to chase human! */
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
