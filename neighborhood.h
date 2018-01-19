#ifndef NEIGHBORHOOD_H
#define NEIGHBORHOOD_H

#include "example.h"
#include "toroidal.h"

//Function to search for nearest zombie in grid.
void nearest_agent_at (int WORLD_X, int WORLD_Y,
                       AGENT agent_grid[WORLD_X][WORLD_Y],
                       AGENT **agents_array, unsigned int i,
                       unsigned int nagents, int *nhumans);
#endif
