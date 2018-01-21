#ifndef AI_MOVE_H
#define AI_MOVE_H

#include "toroidal.h"

/**
 * Human `AGENT` movement.
 *
 * @param WORLD_X Horizontal dimension of the simulation world (number of columns).
 * @param WORLD_Y Vertical dimension of the simulation world (number of rows).
 * @param agent_grid Array that holds `AGENT` objects.
 * @param agents_array Array that holds pointers to `AGENT` objects of type
 Human and Zombie.
 * @param i Marks the actual position of agents_array being used.
 * @param enemy_x Nearest enemy X coordinate.
 * @param enemy_y Nearest enemy Y coordinate.
 * @param r Radius in which the enemy has been found.
 * */
void human_flee(int WORLD_X, int WORLD_Y, AGENT agent_grid[WORLD_X][WORLD_Y],
                AGENT **agents_array, unsigned int i,
                int enemy_x, int enemy_y, int r);

/**
 * Zombie `AGENT` movement.
 *
 * @param WORLD_X Horizontal dimension of the simulation world (number of columns).
 * @param WORLD_Y Vertical dimension of the simulation world (number of rows).
 * @param agent_grid Array that holds `AGENT` objects.
 * @param agents_array Array that holds pointers to `AGENT` objects of type
 Human and Zombie.
 * @param i Marks the actual position of agents_array being used.
 * @param enemy_x Nearest enemy X coordinate.
 * @param enemy_y Nearest enemy Y coordinate.
 * @param r Radius in which the enemy has been found.
 * @param nagents Number of `AGENT` object of type Zombie and Human.
 * @param nhumans Number of `AGENT` object of type Human.
 * */
void zombie_chase(int WORLD_X, int WORLD_Y, AGENT agent_grid[WORLD_X][WORLD_Y],
                  AGENT **agents_array, unsigned int i,
                  int enemy_x, int enemy_y, int r,
                  unsigned int nagents, int *nhumans);
#endif
