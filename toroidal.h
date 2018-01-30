#ifndef TOROIDAL_H
#define TOROIDAL_H

/**
 * Structure defining Coordinates.
 *
 * @note x and y are set inside a struct so we can return both Coordinates
 * through a function.
 * */
typedef struct {
    int x, y;
} COORDS;

/**
 * Verify borders function.
 *
 * @param WORLD_X Horizontal dimension of the simulation world (number of columns).
 * @param WORLD_Y Vertical dimension of the simulation world (number of rows).
 * @param x Actual agent X coordinate.
 * @param y Actual agent Y coordinate.
 * @param dest_x Destination to verify X coordinate.
 * @param dest_y Destination to verify Y coordinate.
 * */
COORDS verify_borders (int WORLD_X, int WORLD_Y,
                       int x, int y,
                       int dest_x, int dest_y);

#endif
