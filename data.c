///
/// Author: Adrien DROGUET
///

#include "data.h"

Instance* createInstance(Instance* instance) {
  Instance* copy = malloc(sizeof(Instance));
  copy->size = instance->size;
  copy->bits = malloc(copy->size * sizeof(short));
  for (unsigned int i = 0; i < copy->size; i++) {
    copy->bits[i] = instance->bits[i];
  }
  copy->fitness = instance->fitness;
  return copy;
}

int hasDuplicates(unsigned int* targets, unsigned int latestTarget) {
  for (unsigned int i = 0; i < latestTarget; i++) {
    if (targets[i] == targets[latestTarget])
      return 1;
  }
  return 0;
}

int calculateFitness(Instance* instance) {
  int total = 0;
  for (unsigned int i = 0; i < instance->size; i++) {
    total += instance->bits[i];
  }
  return total;
}
