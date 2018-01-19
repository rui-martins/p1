#include "toroidal.h"
#include "example.h"
#include <stdio.h>
#include <stdlib.h>

/* Function to verify if agent is off grid and apply toroidal. */
COORDS verify_borders (
    int WORLD_X, int WORLD_Y,
    int x, int y, int dest_x, int dest_y) {

    /* Struct to hold position to return. */
    COORDS position;

    /* X and Y are never offgrid. */
    position.x = (x + dest_x + WORLD_X) % WORLD_X;
    position.y = (y + dest_y + WORLD_Y) % WORLD_Y;

    /* Returns value of x,y. */
    return position;
}
