#ifndef AGENT_H
#define AGENT_H

#include "example.h"
#include "read_from_config.h"

/**
 * Create a new `AGENT` object.
 *
 * @param type `AGENT` type (Zombie, Human or None).
 * @param playable Defines if `AGENT` is playable.
 * @param id Each `AGENT` has its own id.
 * @param x Coordinate X of the `AGENT`.
 * @param x Coordinate Y of the `AGENT`.
 * @return A new `AGENT` object.
 * */
AGENT *agent_new(AGENT_TYPE type, unsigned char playable,
                 unsigned short id, int x, int y);

/**
 * Destroy an `AGENT` object.
 *
 * @param ag_new `AGENT` object to destroy).
 * */
void agent_destroy(AGENT *ag_new);

/**
 * Fill the game grid with `AGENT` objects.
 *
 * @param WORLD_X Horizontal dimension of the simulation world (number of columns).
 * @param WORLD_Y Vertical dimension of the simulation world (number of rows).
 * @param agent_grid Array that holds `AGENT` objects.
 * @param cfg `CONFIG` object that contains values from the config.ini file.
 * @param nagents Number of AGENTS created (Zombies and Humans).
 * */
void put_agent_on_grid(
    int WORLD_X, int WORLD_Y,
    AGENT agent_grid[WORLD_X][WORLD_Y],
    CONFIG cfg, unsigned *nagents);

#endif
