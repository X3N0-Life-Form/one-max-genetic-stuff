#ifndef FLIP_H
#define FLIP_H

#include <stdlib.h>
#include "data.h"

enum e_mutation {
  BIT_FLIP,
  K_FLIP
};
typedef enum e_mutation Mutation;

/**
 * Mutation's statistics structure.
 */
struct s_stats {
  int bit_flips;
  int bit_flip_gain;
  int k_flips;
  int k_flip_gain;
};
typedef struct s_stats Stats;
Stats stats;

/**
 * Defaults to K_FLIP.
 */
Mutation mutateIdentify(char* arg);

Instance** bitFlip(Instance* a, Instance* b);
void flipBit(Instance* flipped, unsigned int toFlip, Instance* origin);
/**
 * Because fuck you.
 */
Instance** kFlip(Instance* a, Instance* b, unsigned int k);

#endif
