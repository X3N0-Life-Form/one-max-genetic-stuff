///
/// Author: Adrien DROGUET
///

#ifndef SMART_MUTATE_H
#define SMART_MUTATE_H

#include "mutation.h"

extern Stats stats;
double ap_Pmax;
double ap_Pmin;
double ap_bfP;
double ap_kfP;

Mutation ap_getBest();

Mutation proportionalRoulette();
Mutation adaptivePursuit();
Mutation UCB();
Mutation uniformRoulette();

Mutation customThingy();

#endif
