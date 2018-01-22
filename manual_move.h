#ifndef MANUAL_MOVE_H
#define MANUAL_MOVE_H

#include "example.h"

void manual_play(int WORLD_X, int WORLD_Y, AGENT agent_grid[WORLD_X][WORLD_Y],
                 AGENT **agents_array, unsigned int i,
                 unsigned int nagents, int *nhumans);

#endif
