/**
 * This `main` function is only an example of: a) how to use the API defined in
 * the showworld.h header (mandatory for the project); and, b) how to use the
 * concrete simple implementation of the API (provided in the
 * showworld_simple.c file).
 *
 * @return Always zero.
 * */

 #include "example.h"
 #include "agent.h"
 #include "shuffle.h"
 #include "toroidal.h"
 #include "neighborhood.h"
 #include "manual_move.h"
 #include "read_from_config.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>

/* Main can receive parameters from the console line*/
int main(int argc, char *argv[]) {

    /* Create a CONFIG object that holds all the info from config.ini */
    CONFIG cfg = read_config(argc, argv);
    /* Put all the values from config.ini in the respective vars */
    int WORLD_X = cfg.xdim;
    int WORLD_Y = cfg.ydim;
    int turns = cfg.turns;
    int nzombies = cfg.nzombies;
    int nhumans = cfg.nhumans;
    int nzplayers = cfg.nzplayers;
    int nhplayers = cfg.nhplayers;
    /* We use the FLAG to  break out of cycles when its value changes to 1 */
    int FLAG = 0;

    /* Error message if number of agents exceed number of grid slots. */
    if ((nzombies+nhumans) > (WORLD_X*WORLD_Y)) {
        fprintf(stderr, "Number of agents can't exceed number of grid slots.");
        exit (1);
    }
    /* Error message if of playable zombies exceed total zombies. */
    if (nzplayers > nzombies) {
        fprintf(stderr, "Number of playable zombies can't exceed initial zombies.");
        exit (1);
    }
    /* Error message if of playable humans exceed total humans. */
    if (nhplayers > nhumans) {
        fprintf(stderr, "Number of playable humans can't exceed initial humans.");
        exit (1);
    }

    /* An instance of a WORLD structure. */
    WORLD my_world;

    /* An instance of a SHOWWORLD world display. */
    SHOWWORLD *sw = NULL;

    /* A bidimensional array of agents, representing agents in a grid. */
    AGENT agent_grid[WORLD_X][WORLD_Y];

    /* Number of agents created so far. */
    unsigned int nagents = 0;

    /* Initialize world display. */
    sw = showworld_new(WORLD_X, WORLD_Y, example_get_ag_info);

    /* Initialize random number generator. */
    srand(time(NULL));

    /* **************************************************************** */
    /* Cycle through all cells in grid and randomly place agents in it. */
    /* **************************************************************** */
    for (int i = 0; i < WORLD_X; ++i) {
        for (int j = 0; j < WORLD_Y; ++j) {

            /* Possible agent in grid. By default we assume there is none. */
            AGENT ag = {None, 0, 0, 0, 0};

            /* Assign possible agent to grid at (i,j). */
            agent_grid[i][j] = ag;
        }
    }

    /* Call function to populate grid */
    put_agent_on_grid(WORLD_X, WORLD_Y, agent_grid, cfg, &nagents);

    /* ******************************* */
    /* Populate the my_world variable. */
    /* ******************************* */

    /* A bidimensional array of agents can be interpreted as a pointer to
           agents. */
    my_world.grid = (AGENT *) agent_grid;

    /* World size is defined by constants in this example. */
    my_world.xsize = WORLD_X;
    my_world.ysize = WORLD_Y;

    /* ********************************************************************* */
    /* Show world using the simple_show_world() function. This function can  */
    /* be used in the first part of the project.                             */
    /* ********************************************************************* */

    /* Update the world */
    showworld_update(sw, &my_world);

    /* Counter to put agents into new array of pointers to AGENT */
    int counter = 0;
    /* Array of pointers to AGENT of size nagents (total agents) */
    AGENT *agents_array[nagents];
    /* ******************************************************************** */
    /* Cycle through all cells in grid and check if agent types are != None */
    /* ******************************************************************** */
    for (int i = 0; i < WORLD_X; ++i) {
        for (int j = 0; j < WORLD_Y; ++j) {
            if (agent_grid[i][j].type != None) {
                /* If agent type is Zombie or Human then put it into new array */
                agents_array[counter] = agent_new(agent_grid[i][j].type,
                                                  agent_grid[i][j].playable,
                                                  agent_grid[i][j].id,
                                                  agent_grid[i][j].x,
                                                  agent_grid[i][j].y);
                /* Increment counter for next agent to put into the array */
                counter++;
            }
        }
    }
    /* Cycle through all the turns */
    for (int j = 0; j <= turns; j++) {
        /* If j reaches max turns and number of humans is still > 0 you win! */
        if ((j == turns) & (nhumans > 0)) {
            /* Print message of winning */
            printf("\nYou win! Humans have survived!");
            break;
        }
        /* If FLAG is 1 then break cycle */
        if (FLAG == 1) break;
        /* Call shuffle function to shuffle agents as new turn just started */
        shuffle(agents_array, nagents);
        /* Cycle through the shuffled array for play order */
        for (unsigned int i = 0; i < nagents; i++) {
            if (FLAG == 1) break;
            /* If agent at current position is playable... */
            if (agents_array[i]->playable == 1) {
                /* Print current turn */
                printf("You are currently on turn: %d\n", j+1);
                /* Call manual play function */
                manual_play(
                WORLD_X, WORLD_Y, agent_grid, agents_array, i, nagents, &nhumans);
            }
            /* If actual agent isn't playable... */
            else {
                /* Print current turn */
                printf("You are currently on turn: %d\n", j+1);
                /* Call function to look for nearest agent (Moore Neighbourhood) */
                nearest_agent_at(
                WORLD_X, WORLD_Y, agent_grid, agents_array, i, nagents, &nhumans);
                /* User has to press key to continue */
                getchar();
            }
            /* Update world grid */
            showworld_update(sw, &my_world);
            /* If number of humans have reached 0 then it is game over */
            if (nhumans == 0) {
                /*Print game over message on screen */
                printf("\nGame Over. Humans have been wiped out.");
                FLAG = 1;
                break;
            }
        }
    }

    /* Before finishing, ask user to press ENTER. */
    printf("\nPress ENTER to continue...");
    getchar();

    /* Destroy all the agents created */
    for (unsigned int i = 0; i < nagents; i++) {
        agent_destroy(agents_array[i]);
    }
    /* Destroy world display. */
    showworld_destroy(sw);

    /* Bye. */
    return 0;
}

/**
 * This function is an implementation of the ::get_agent_info_at() function
 * definition. It only works for ::AGENT and ::WORLD structures defined in this
 * example.
 *
 * It basically receives a pointer to a ::WORLD structure, obtains the AGENT
 * structure in the given coordinates, and returns the agent information in a
 * bit-packed `unsigned int`.
 *
 * @note This is an example which will probably not work in a fully functional
 * game. Students should develop their own implementation of
 * ::get_agent_info_at() and agent/world data structures.
 *
 * @param w Generic pointer to object representing the simulation world.
 * @param x Horizontal coordinate of the simulation world from where to fetch
 * the agent information.
 * @param y Vertical coordinate of the simulation world from where to fetch
 * the agent information.
 * @return An integer containing bit-packed information about an agent, as
 * follows: bits 0-1 (agent type), bit 2 (is agent playable), bits 3-18 (agent
 * ID). Bits 19-31 are available for student-defined agent extensions.
 * */
unsigned int example_get_ag_info(void *w, unsigned int x, unsigned int y) {

    /* The agent information to return. */
    unsigned int ag_info = 0;

    /* Convert generic pointer to world to a WORLD object. */
    WORLD *my_world = (WORLD *) w;

    /* Check if the given (x,y) coordinates are within bounds of the world. */
    if ((x >= my_world->xsize) || (y >= my_world->ysize)) {

        /* If we got here, then the coordinates are off bounds. As such we will
        report that the requested agent is of unknown type. No need to
        specify agent ID or playable status, since the agent is unknown. */
        ag_info = Unknown;

    } else {

        /* Given coordinates are within bounds, let's get and pack the request
        agent information. */

        /* Obtain agent at specified coordinates. */
        AGENT ag = my_world->grid[x * my_world->ysize + y];

        /* Is there an agent at (x,y)? */
        if (ag.type == None) {

            /* If there is no agent at the (x,y) coordinates, set agent type to
            None. No need to specify agent ID or playable status, since
            there is no agent here. */
            ag_info = None;

        } else {

            /* If we get here it's because there is an agent at (x,y). Bit-pack
             all the agent information as specified by the get_agent_info_at
             function pointer definition. */
            ag_info = (ag.id << 3) | (ag.playable << 2) | ag.type;

        }

    }
    /* Return the requested agent information. */
    return ag_info;
}
