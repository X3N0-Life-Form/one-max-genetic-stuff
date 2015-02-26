///
/// Author: Adrien DROGUET
///

#include "insert.h"

#include <string.h>
#include "select.h"


Insertion insertIdentify(char* arg) {
  if (!strcmp(arg, "compare_with_parents")) {
    return COMPARE_WITH_PARENTS;
  } else if (!strcmp(arg, "age")) {
    return AGE;
  } else if (!strcmp(arg, "replace_worst")) {
    return REPLACE_WORST;
  } else {
    return AGE;
  }
}

void insertCompareWithParents(Instance** offspring, unsigned int target_1, unsigned int target_2) {
  Instance** allOfThem = malloc(4 * sizeof(Instance*));
  allOfThem[0] = offspring[0];
  allOfThem[1] = offspring[1];
  allOfThem[2] = population[target_1];
  allOfThem[3] = population[target_2];
  Instance* best = allOfThem[0];
  Instance* secondBest = NULL;
  int bestFitness = best->fitness;
  int secondBestFitness = 0;
  for (int i = 1; i < 4; i++) {
    if (allOfThem[i]->fitness > bestFitness) {
      best = allOfThem[i];
      bestFitness = best->fitness;
    } else if (allOfThem[i]->fitness >= secondBestFitness) {
      secondBest = allOfThem[i];
      secondBestFitness = secondBest->fitness;
    }
  }
  // check if everything went smoothly
  if (secondBest == NULL || best == secondBest) {
    printf("\nInsertion error #1\n");
  }
  *population[target_1] = *best;
  *population[target_2] = *secondBest;
  free(allOfThem);
}

void insertAge(Instance** offspring) {
  free(population[age_index]);
  population[age_index] = offspring[0];
  age_index = (age_index + 1) % pop_size;
  free(population[age_index]);
  population[age_index] = offspring[1];
}

void insertReplaceWorst(Instance** offspring) {
  unsigned int britta = selectWorst();
  free(population[britta]);
  population[britta] = offspring[0];
  britta = selectWorst();
  free(population[britta]);
  population[britta] = offspring[1];
}
