#ifndef MANUAL_MOVE_H
#define MANUAL_MOVE_H

#include "example.h"

/**
 * Manual `AGENT` movement.
 *
 * @param WORLD_X Horizontal dimension of the simulation world (number of columns).
 * @param WORLD_Y Vertical dimension of the simulation world (number of rows).
 * @param agent_grid Array that holds `AGENT` objects.
 * @param agents_array Array that holds pointers to `AGENT` objects of type
 Human and Zombie.
 * @param i Marks the actual position of agents_array being used.
 * @param nagents Number of total agents.
 * @param nhumans Pointer to number of humans still alive.
 * */
void manual_play(int WORLD_X, int WORLD_Y, AGENT agent_grid[WORLD_X][WORLD_Y],
                 AGENT **agents_array, unsigned int i,
                 unsigned int nagents, int *nhumans);

#endif
