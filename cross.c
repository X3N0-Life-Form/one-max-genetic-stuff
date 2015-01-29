#include "cross.h"

#include <string.h>

Crossover crossIdentify(char* arg) {
  if (strcmp(arg, "cross_point")) {
    return CROSS_POINT;
  } else if (strcmp(arg, "cross_uniform")) {
    return CROSS_UNIFORM;
  } else {
    return CROSS_UNIFORM;
  }
}

Instance** crossPoint(Instance* a, Instance* b) {
  Instance* nuA = createInstance(a);
  Instance* nuB = createInstance(b);
  unsigned int point = rand() % a->size;
  for (unsigned int i = point; i < a->size; i++) {
    nuA->bits[i] = b->bits[i];
  }
  for (unsigned int i = 0; i < point; i++) {
    nuB->bits[i] = a->bits[i];
  }
  nuA->fitness = calculateFitness(nuA);
  nuB->fitness = calculateFitness(nuB);
  Instance** res = malloc(2 * sizeof(Instance*));
  res[0] = nuA;
  res[1] = nuB;
  return res;
}

Instance** crossUniform(Instance* a, Instance* b) {
  Instance* nuA = createInstance(a);
  Instance* nuB = createInstance(b);
  for (unsigned int i = 0; i < a->size; i++) {
    if (rand() > 0.5) {
      nuA->bits[i] = a->bits[i];
      nuB->bits[i] = b->bits[i];
    } else {
      nuA->bits[i] = b->bits[i];
      nuB->bits[i] = a->bits[i];
    }
  }

  nuA->fitness = calculateFitness(nuA);
  nuB->fitness = calculateFitness(nuB);
  Instance** res = malloc(2 * sizeof(Instance*));
  res[0] = nuA;
  res[1] = nuB;
  return res;
}
