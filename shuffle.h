#ifndef SHUFFLE_H
#define SHUFFLE_H

#include "example.h"

/**
 * Shuffle Function.
 * @param agents_array Array that holds pointers to `AGENT` objects of type
 Human and Zombie.
 * @param nagents Number of total agents.
 * */
void shuffle(AGENT **agents_to_shuffle, unsigned int nagents);

#endif
