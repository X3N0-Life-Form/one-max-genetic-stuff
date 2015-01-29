#include "select.h"

#include <string.h>

Selection selectIdentify(char* arg) {
  if (strcmp(arg, "best")) {
    return BEST;
  } else if (strcmp(arg, "random")) {
    return RANDOM;
  } else if (strcmp(arg, "worst_best")) {
    return WORST_BEST;
  } else if (strcmp(arg, "tournament")) {
    return TOURNAMENT;
  } else {
    return RANDOM;
  }
}

unsigned int selectBest() {
  int best = 0;
  unsigned int bestTarget = 0;
  for (unsigned int i = 0; i < pop_size; i++) {
    int score = population[i]->fitness;
    if (score >= best) {
      best = score;
      bestTarget = i;
    }
  }
  return bestTarget;
}

unsigned int selectWorst() {
  unsigned int target = 0;
  int worst = population[target]->fitness;
  for (unsigned int i = 0; i < pop_size; i++) {
    int score = population[i]->fitness;
    if (score < worst) {
      worst = score;
      target = i;
    }
  }
  return target;
}

unsigned int selectBestWorseThan(unsigned int target) {
  int targetScore = population[target]->fitness;
  int best = 0;
  unsigned int bestTarget = 0;
  for (unsigned int i = 0; i < pop_size; i++) {
    int score = population[i]->fitness;
    if (score >= best && score < targetScore && i != target) {
      best = score;
      bestTarget = i;
    }
  }
  return bestTarget;
}

unsigned int selectRandom() {
  return rand() % pop_size;
}

unsigned int* selectTournament(unsigned int* targets, unsigned int numberOfTargets) {
  unsigned int best = targets[0], secondBest = targets[0];
  int bestScore = population[targets[0]]->fitness, secondBestScore = 0;
  // select best
  for (unsigned int i = 1; i < numberOfTargets; i++) {
    Instance* instance = population[targets[i]];
    int score = instance->fitness;
    if (score >= bestScore) {
      bestScore = score;
      best = targets[i];
    }
  }

  // select second best
  for (unsigned int i = 0; i < numberOfTargets; i++) {
    Instance* instance = population[targets[i]];
    int score = instance->fitness;
    if (targets[i] != best && score > secondBestScore) {
      secondBestScore = score;
      secondBest = targets[i];
    }
  }

  // all done, prep the output array and go home
  unsigned int* ret = malloc(2 * sizeof(unsigned int));
  ret[0] = best;
  ret[1] = secondBest;
  return ret;
}

unsigned int* selectTargetsForTournament(unsigned int t) {
  unsigned int* res = malloc(t * sizeof(unsigned int));
  unsigned int count = 0;
  int getAnother = 0;
  while (count < t) {
    unsigned int selection = rand() % pop_size;
    // has it already been selected
    for (unsigned int i = 0; i < count; i++) {
      getAnother = 0;
      if (res[i] == selection) {
	getAnother = 1;
	break;
      }
    }
    // if not, select it
    if (!getAnother) {
      res[count] = selection;
      count++;
    }
  }

  return res;
}
