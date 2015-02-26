///
/// Author: Adrien DROGUET
///

#ifndef CROSS_H
#define CROSS_H

#include <stdlib.h>
#include <stdio.h>
#include "data.h"

enum e_crossover {
  CROSS_POINT,
  CROSS_UNIFORM
};
typedef enum e_crossover Crossover;

/**
 * Defaults to CROSS_UNIFORM.
 */
Crossover crossIdentify(char* arg);

/**
 * Cross cuts at a random point.
 */
Instance** crossPoint(Instance* a, Instance* b);
Instance** crossUniform(Instance* a, Instance* b);

#endif
