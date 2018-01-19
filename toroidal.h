#ifndef TOROIDAL_H
#define TOROIDAL_H

//Struct that holds coords to return in the function verify_borders.
typedef struct {
    int x, y;
} COORDS;

//Function to verify if agent is off grid and apply toroidal.
COORDS verify_borders (
    int WORLD_X, int WORLD_Y,
    int x, int y, int dest_x, int dest_y);

#endif
