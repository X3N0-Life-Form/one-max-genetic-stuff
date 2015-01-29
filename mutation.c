#include "mutation.h"

void flipBit(Instance* instance, unsigned int toFlip, Instance* origin) {
  instance->bits[toFlip] = !origin->bits[toFlip];
}

Instance** bitFlip(Instance* a, Instance* b) {
  Instance** res = malloc(2 * sizeof(Instance*));
  res[0] = createInstance(a);
  unsigned int i = rand() % a->size;
  flipBit(res[0], i, a);
  res[0]->fitness = calculateFitness(res[0]);

  res[1] = createInstance(b);
  i = rand() % b->size;
  flipBit(res[1], i, b);
  res[1]->fitness = calculateFitness(res[1]);
  return res;
}

Instance** kFlip(Instance* a, Instance* b, unsigned int k) {
  Instance** res = malloc(2 * sizeof(Instance*));
  res[0] = createInstance(a);
  res[1] = createInstance(b);
  unsigned int* targets_a = malloc(k * sizeof(unsigned int));
  unsigned int* targets_b = malloc(k * sizeof(unsigned int));
  for (int i = 0; i < k; i++) {
    targets_a[i] = rand() % a->size;
    while (hasDuplicates(targets_a, i)) {
      targets_a[i] = rand() % a->size;
    }
    targets_b[i] = rand() % b->size;
    while (hasDuplicates(targets_b, i)) {
      targets_b[i] = rand() % b->size;
    }
  }
  
  for (unsigned int i = 0; i < k; i++) {
    flipBit(res[0], targets_a[i], a);
    flipBit(res[1], targets_b[i], b);
  }
  res[0]->fitness = calculateFitness(res[0]);
  res[1]->fitness = calculateFitness(res[1]);
  
  free(targets_a);
  free(targets_b);
  return res;
}
