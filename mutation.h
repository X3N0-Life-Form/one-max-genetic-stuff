#ifndef FLIP_H
#define FLIP_H

#include <stdlib.h>
#include "data.h"

enum e_mutation {
  BIT_FLIP,
  K_FLIP
};
typedef enum e_mutation Mutation;

Instance** bitFlip(Instance* a, Instance* b);
void flipBit(Instance* flipped, unsigned int toFlip, Instance* origin);
/**
 * Because fuck you.
 */
Instance** kFlip(Instance* a, Instance* b, unsigned int k);

#endif
