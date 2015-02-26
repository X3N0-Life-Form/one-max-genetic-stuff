///
/// Author: Adrien DROGUET
///

#ifndef DATA_H
#define DATA_H

#include <stdlib.h>

struct t_instance {
  unsigned int size;
  short* bits;
  int fitness;
};
typedef struct t_instance Instance;

Instance** population;
unsigned int pop_size;

Instance* createInstance(Instance* instance);
int hasDuplicates(unsigned int* targets, unsigned int latestTarget);
int calculateFitness(Instance* instance);

#endif
