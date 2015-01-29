#ifndef INSERT_H
#define INSERT_H

#include <stdlib.h>
#include <stdio.h>
#include "data.h"

enum e_insertion {
  COMPARE_WITH_PARENTS,
  AGE,
  REPLACE_WORST
};
typedef enum e_insertion Insertion;

/**
 * Used by insertAge, keeps track of where we are.
 * Must always be < pop_size.
 */
extern unsigned int age_index;

/**
 * Defaults to AGE.
 */
Insertion insertIdentify(char* arg);

/**
 * Compares an offspring with its parents and keep whoever is best.
 * Note: assumes that offspring has a size of 2.
 */
void insertCompareWithParents(Instance** offspring, unsigned int target_1, unsigned int target_2);
void insertAge(Instance** offspring);
void insertReplaceWorst(Instance** offspring);


#endif
