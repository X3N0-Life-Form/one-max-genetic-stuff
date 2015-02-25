#include "one-max.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "smart_mutate.h"

extern Stats stats;

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

double entropy() { // ?????
  double res = 0.0;
  for (int i = 0; i < pop_size; i++) {
    double x = (population[i]->fitness / population[i]->size);
    res += (x * log(x)) / (pop_size * log(2));
  }
  return -res;
}

void printPopulation() {
  for (unsigned int i = 0; i < pop_size; i++) {
    for (unsigned int j = 0; j < population[i]->size; j++) {
      printf(" %d", population[i]->bits[j]);
    }
    printf(" ==> %d\n", population[i]->fitness);
  }
}

char* getRecap(char* res) { // stupid c string handling
  char buffer[10];
  strcat(res, "\nRun configuration:");
  strcat(res, "\n\tSelection =\t");
  switch (selection) {
  case BEST:
    strcat(res, "best");
    break;
  case RANDOM:
    strcat(res, "random");
    break;
  case WORST_BEST:
    strcat(res, "worst x best");
    break;
  case TOURNAMENT:
    strcat(res, "tournament of ");
    sprintf(buffer, "%d", t);
    strcat(res, buffer);
    strcat(res, " individuals");
    break;
  }
  strcat(res, "\n\tCrossover =\t");
  switch (crossover) {
  case CROSS_POINT:
    strcat(res, "cross-point");
    break;
  case CROSS_UNIFORM:
    strcat(res, "cross-uniform");
    break;
  }
  strcat(res, "\n\tMutation  =\t");
  switch (mutation) {
  case BIT_FLIP:
    strcat(res, "bit-flip");
    break;
  case K_FLIP:
    strcat(res, "k-flip\t(k=");
    sprintf(buffer, "%d", k);
    strcat(res, buffer);
    strcat(res, ")");
    break;
  }
  strcat(res, "\n\tInsertion =\t");
  switch (insertion) {
  case COMPARE_WITH_PARENTS:
    strcat(res, "compare with parents");
    break;
  case AGE:
    strcat(res, "replace oldest");
    break;
  case REPLACE_WORST:
    strcat(res, "replace worst");
    break;
  }
  strcat(res, "\n\tFitness: best               = ");
  sprintf(buffer, "%d", fitnessBest());
  strcat(res, buffer);
  strcat(res, "\n\tFitness: average            = ");
  sprintf(buffer, "%d", fitnessAverage());
  strcat(res, buffer);
  strcat(res, "\n\tFitness: standard deviation = ");
  sprintf(buffer, "%d", fitnessStandardDeviation());
  strcat(res, buffer);
  strcat(res, "\n\tENTROPY = ");
  sprintf(buffer, "%f", entropy());
  strcat(res, buffer);

  strcat(res, "\n\nAlgorithm automation is ");
  if (automate) {
    strcat(res, "ON");
  } else {
    strcat(res, "OFF");
  }
  return res;
}

void printRecap() {
  char buffer[500];
  printf("%s", getRecap(buffer));
}

void printTrace(int iteration) {
  fprintf(trace_file, "%d,%d,%d,%d,%f\n",
	  iteration,
	  fitnessBest(),
	  fitnessAverage(),
	  fitnessStandardDeviation(),
	  entropy());
}

void dealWithArgs(int argc, char** argv) {
  for (int i = 0; i < argc - 1; i++) {
    if (strcmp(argv[i],  "-pop_size")) {
      pop_size = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-i")) {
      numberOfIterations = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-select")) {
      selection = selectIdentify(argv[++i]);
    } else if (strcmp(argv[i], "-t")) {
      t = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-cross")) {
      crossover = crossIdentify(argv[++i]);
    } else if (strcmp(argv[i], "-mutate")) {
      mutation = mutateIdentify(argv[++i]);
    } else if (strcmp(argv[i], "-k")) {
      k = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-insert")) {
      insertion = insertIdentify(argv[++i]);
    } else {
      printf("\nUnrecognised argument: %s", argv[i]);
    }
  }
}


char* getTraceFileName(char* name) {
  char buffer[10];
  //pop_size
  sprintf(buffer, "trace_%d_", pop_size);
  strcat(name, buffer);

  switch (selection) {
  case BEST:
    strcat(name, "b");
    break;
  case RANDOM:
    strcat(name, "r");
    break;
  case WORST_BEST:
    strcat(name, "wb");
    break;
  case TOURNAMENT:
    sprintf(buffer, "t%d", t);
    strcat(name, buffer);
    break;
  }
  strcat(name, "_");
  
  switch (crossover) {
  case CROSS_POINT:
    strcat(name, "cp");
    break;
  case CROSS_UNIFORM:
    strcat(name, "cu");
    break;
  }
  strcat(name, "_");

  switch (mutation) {
  case BIT_FLIP:
    strcat(name, "bf");
    break;
  case K_FLIP:
    sprintf(buffer, "%df", k);
    strcat(name, buffer);
    break;
  }
  strcat(name, "_");

  switch (insertion) {
  case COMPARE_WITH_PARENTS:
    strcat(name, "cwp");
    break;
  case AGE:
    strcat(name, "a");
    break;
  case REPLACE_WORST:
    strcat(name, "rw");
    break;
  }
  strcat(name, "_");

  //iterations
  sprintf(buffer, "%d", numberOfIterations);
  strcat(name, buffer);

  strcat(name, ".csv");
  return name;
}

////////////
/// Main ///
////////////

int main(int argc, char** argv) {
  //automate = 1;
  stats.bit_flips = 1;
  stats.bit_flip_gain = 1;
  stats.k_flips = 1;
  stats.k_flip_gain = 1;

  pop_size = POP_SIZE;
  selection = TOURNAMENT;
  crossover = CROSS_POINT;
  mutation = BIT_FLIP;
  insertion = REPLACE_WORST;
  numberOfIterations = DEFAULT_NUMBER_OF_ITERATIONS;
  k = DEFAULT_K_FLIP;
  t = DEFAULT_T;

  dealWithArgs(argc, argv);

  char fileName[100];
  getTraceFileName(fileName);
  trace_file = fopen(fileName,"w");
  initialize();
  srand(time(NULL));

  printf("Initialization complete\n");
  //char buffer[500];
  //fprintf(trace_file, "%s\n", getRecap(buffer));
  for (int h = 1; h <= numberOfIterations; h++) {
    if (automate) {
      mutation = customThingy();
      switch (mutation) {
      case BIT_FLIP:
	printf("Automated choice: BIT_FLIP\n");
	break;
      case K_FLIP:
	printf("Automated choice: K_FLIP\n");
	break;
      }
    }
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
    printTrace(0);
  }
  printRecap();
  fclose(trace_file);
  printf("\nTHE END\n");
}
