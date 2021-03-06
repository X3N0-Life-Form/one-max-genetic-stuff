///
/// Author: Adrien DROGUET
///

#include "mutation.h"

#include <string.h>

Mutation mutateIdentify(char* arg) {
  if (!strcmp(arg, "bit_flip")) {
    return BIT_FLIP;
  } else if (!strcmp(arg, "k_flip")) {
    return K_FLIP;
  } else {
    return K_FLIP;
  }
}

void flipBit(Instance* instance, unsigned int toFlip, Instance* origin) {
  instance->bits[toFlip] = !origin->bits[toFlip];
}

Instance** bitFlip(Instance* a, Instance* b) {
  Instance** res = malloc(2 * sizeof(Instance*));
  res[0] = createInstance(a);
  int chance = (1 / (float) a->size) * 100;
  int flips = 0;
  for (unsigned int i = 0; i < a->size; i++) {
    int proba = rand() % 100;
    if (proba <= chance) {
      flipBit(res[0], i, a);
      flips++;
    }
  }
  int prev_fitness = res[0]->fitness;
  res[0]->fitness = calculateFitness(res[0]);
  int gain = prev_fitness - res[0]->fitness;

  res[1] = createInstance(b);
  for (unsigned int i = 0; i < a->size; i++) {
    float proba = rand();
    if (proba <= chance) {
      flipBit(res[1], i, b);
      flips++;
    }
  }
  prev_fitness = res[1]->fitness;
  res[1]->fitness = calculateFitness(res[1]);
  gain += prev_fitness - res[1]->fitness;

  stats.bit_flip_gain += gain;
  stats.bit_flips += flips;
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
  int gain = 0;
  int prev_fitness = res[0]->fitness;
  res[0]->fitness = calculateFitness(res[0]);
  gain += prev_fitness - res[0]->fitness;
  prev_fitness = res[1]->fitness;
  res[1]->fitness = calculateFitness(res[1]);
  gain += prev_fitness - res[1]->fitness;
  
  stats.k_flip_gain += gain;
  stats.k_flips += k * 2;
  free(targets_a);
  free(targets_b);
  return res;
}
