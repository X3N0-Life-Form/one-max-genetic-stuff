#include "smart_mutate.h"

#include <stdio.h>

Mutation ap_getBest() {
  if (stats.bit_flip_gain > stats.k_flip_gain) {
    return BIT_FLIP;
  } else {
    return K_FLIP;
  }
}

Mutation adaptivePursuit() {
  double alpha = (rand() % 100) / 100.0;
  if (ap_getBest() == K_FLIP) { // best action = k-flip
    ap_kfP = ap_kfP + alpha * (ap_Pmax - ap_kfP);
    ap_bfP = ap_bfP + alpha * (ap_Pmin - ap_bfP);
  } else {
    ap_bfP = ap_bfP + alpha * (ap_Pmax - ap_bfP);
    ap_kfP = ap_kfP + alpha * (ap_Pmin - ap_kfP);
  }
  ap_Pmax = 1 - (2 - 1) * ap_Pmin;

  double roll1 = (rand() % 100) / 100.0;
  double roll2 = (rand() % 100) / 100.0;
  if (ap_bfP * roll1 > ap_kfP * roll2) {
    return BIT_FLIP;
  } else {
    return K_FLIP;
  }
}

Mutation customThingy() {
  double roll = (rand() % 100) / 100.0;
  double bit_flip_value = ((double) stats.bit_flip_gain / (double) stats.bit_flips) * roll;
  roll = (rand() % 100) / 100.0;
  double k_flip_value = ((double) stats.k_flip_gain / (double) stats.k_flips) * roll;

  //printf("Stats: %d, %d || %d, %d\n", stats.bit_flip_gain, stats.bit_flips, stats.k_flip_gain, stats.k_flips);
  //printf("CUSTOM THINGY: roll=%f, %f, %f\n", roll, bit_flip_value, k_flip_value);
  if (bit_flip_value > k_flip_value) {
    return BIT_FLIP;
  } else {
    return K_FLIP;
  }
}
