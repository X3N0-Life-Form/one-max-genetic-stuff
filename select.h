#ifndef SELECT_H
#define SELECT_H

#include <stdlib.h>
#include "data.h"

enum e_selection {
  BEST,
  RANDOM,
  WORST_BEST,
  TOURNAMENT
};
typedef enum e_selection Selection;

unsigned int selectBest();
unsigned int selectBestWorseThan(unsigned int target);
unsigned int selectRandom();
unsigned int selectWorst();
/**
 * Selects the two best instances in a given population.
 */
unsigned int* selectTournament(unsigned int* targets, unsigned int numberOfTargets);
/**
 * Selects t targets for a tournament selection.
 */
unsigned int* selectTargetsForTournament(unsigned int t);
#endif
