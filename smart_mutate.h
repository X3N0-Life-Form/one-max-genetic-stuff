#ifndef SMART_MUTATE_H
#define SMART_MUTATE_H

#include "mutation.h"

extern Stats stats;

Mutation proportionalRoulette();
Mutation adaptivePursuit();
Mutation UCB();
Mutation uniformRoulette();

Mutation customThingy();

#endif
