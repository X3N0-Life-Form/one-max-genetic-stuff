#include "one-max.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>

void initialize() {
  population = malloc(pop_size * sizeof(Instance*));
  for (unsigned int i = 0; i < pop_size; i++) {
    population[i] = malloc(sizeof(Instance));
    population[i]->size = DEFAULT_SIZE;
    population[i]->bits = malloc(population[i]->size * sizeof(short));
    for (unsigned int j = 0; j < population[i]->size; j++) {
      population[i]->bits[j] = 0;
    }
    population[i]->fitness = 0;
  }
}


int fitnessBest() {
  int best = 0;
  for (unsigned int i = 0; i < pop_size; i++) {
    if (population[i]->fitness > best)
      best = population[i]->fitness;
  }
  return best;
}

int fitnessAverage() {
  int hjvo = 0;
  for (unsigned int i = 0; i < pop_size; i++) {
    hjvo += population[i]->fitness;
  }
  return hjvo / pop_size;
}

int fitnessStandardDeviation() {
  int average = fitnessAverage();
  int hjvo = 0;
  for (unsigned int i = 0; i < pop_size; i++) {
    hjvo += pow(population[i]->fitness - average, 2.0);
  }
  if (average == 0)
    return 0;
  else
    return sqrt(hjvo / average);
}

double entropy() {
  printf("\nNOT IMPLEMENTED");
  return 0.0;
}

void printPopulation() {
  for (unsigned int i = 0; i < pop_size; i++) {
    for (unsigned int j = 0; j < population[i]->size; j++) {
      printf(" %d", population[i]->bits[j]);
    }
    printf(" ==> %d\n", population[i]->fitness);
  }
}

void printRecap() {
  printf("\nRun configuration:");
  printf("\n\tSelection =\t");
  switch (selection) {
  case BEST:
    printf("best");
    break;
  case RANDOM:
    printf("random");
    break;
  case WORST_BEST:
    printf("worst x best");
    break;
  case TOURNAMENT:
    printf("tournament of %d individuals", t);
    break;
  }
  printf("\n\tCrossover =\t");
  switch (crossover) {
  case CROSS_POINT:
    printf("cross-point");
    break;
  case CROSS_UNIFORM:
    printf("cross-uniform");
    break;
  }
  printf("\n\tMutation  =\t");
  switch (mutation) {
  case BIT_FLIP:
    printf("bit-flip");
    break;
  case K_FLIP:
    printf("k-flip\t(k=%d)", k);
    break;
  }
  printf("\n\tInsertion =\t");
  switch (insertion) {
  case COMPARE_WITH_PARENTS:
    printf("compare with parents");
    break;
  case AGE:
    printf("replace oldest");
    break;
  case REPLACE_WORST:
    printf("replace worst");
    break;
  }
  printf("\n\tFitness: best               = %d", fitnessBest());
  printf("\n\tFitness: average            = %d", fitnessAverage());
  printf("\n\tFitness: standard deviation = %d", fitnessStandardDeviation());
  printf("\n\tENTROPY = %f", entropy());
}

void printTrace(int iteration) {
  fprintf(trace_file, "%d,%d,%d,%d,%f\n",
	  iteration,
	  fitnessBest(),
	  fitnessAverage(),
	  fitnessStandardDeviation(),
	  entropy());
}





int main() {
  pop_size = POP_SIZE;
  selection = TOURNAMENT;
  crossover = CROSS_POINT;
  mutation = K_FLIP;
  insertion = REPLACE_WORST;
  numberOfIterations = DEFAULT_NUMBER_OF_ITERATIONS;
  k = DEFAULT_K_FLIP;
  t = DEFAULT_T;

  trace_file = fopen("trace.csv","w");
  initialize();
  srand(time(NULL));

  printf("Initialization complete\n");
  for (int h = 1; h <= numberOfIterations; h++) {
    //printf("#%d: Beginning target selection...\n", h);
    unsigned int target_1, target_2;
    // select
    switch (selection) {
    case BEST:
      target_1 = selectBest();
      target_2 = selectBestWorseThan(target_1);
      break;
    case RANDOM:
      target_1 = selectRandom();
      target_2 = selectRandom();
      while (target_2 == target_1) target_2 = selectRandom();
      break;
    case WORST_BEST:
      target_1 = selectWorst();
      target_2 = selectBest();
      break;
    case TOURNAMENT:{
      unsigned int* targets = selectTargetsForTournament(t);
      unsigned int* selectedTargets = selectTournament(targets, t);
      target_1 = selectedTargets[0];
      target_2 = selectedTargets[1];
      free(targets);
      free(selectedTargets);
      break;}
    }
    //printf("\tselected %d and %d\n", target_1, target_2);

    // crossover
    Instance** offspring;
    switch(crossover) {
    case CROSS_POINT:
      offspring = crossPoint(population[target_1], population[target_2]);
      break;
    case CROSS_UNIFORM:
      offspring = crossUniform(population[target_1], population[target_2]);
      break;    
    }

    // mutate
    switch (mutation) {
    case BIT_FLIP:
      offspring = bitFlip(population[target_1], population[target_2]);
      break;
    case K_FLIP:
      offspring = kFlip(population[target_1], population[target_2], k);
      break;
    }

    // insert
    switch (insertion) {
    case COMPARE_WITH_PARENTS:
      insertCompareWithParents(offspring, target_1, target_2);
      break;
    case AGE:
      insertAge(offspring);
      break;
    case REPLACE_WORST:
      insertReplaceWorst(offspring);
      break;
    }

    // end of loop recap
    printf("#%d population status:\n", h);
    printPopulation();
    printf("outputting to trace file\n");
    printTrace();
  }
  printRecap();
  fclose(trace_file);
  printf("\nTHE END\n");
}
