#include "smart_mutate.h"

#include <stdio.h>

Mutation customThingy() {
  double roll = (rand() % 100) / 100.0;
  double bit_flip_value = ((double) stats.bit_flip_gain / (double) stats.bit_flips) * roll;
  double k_flip_value = ((double) stats.k_flip_gain / (double) stats.k_flips) * roll;

  //printf("Stats: %d, %d || %d, %d\n", stats.bit_flip_gain, stats.bit_flips, stats.k_flip_gain, stats.k_flips);
  //printf("CUSTOM THINGY: roll=%f, %f, %f\n", roll, bit_flip_value, k_flip_value);
  if (bit_flip_value > k_flip_value) {
    return BIT_FLIP;
  } else {
    return K_FLIP;
  }
}
