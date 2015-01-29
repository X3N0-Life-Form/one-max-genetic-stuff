#ifndef ONE_MAX_H
#define ONE_MAX_H

#include <stdio.h>

#include "select.h"
#include "cross.h"
#include "mutation.h"
#include "insert.h"

#define POP_SIZE 20
#define DEFAULT_SIZE 10
#define DEFAULT_NUMBER_OF_ITERATIONS 30

#define DEFAULT_K_FLIP 3
#define DEFAULT_T 5

FILE* trace_file;


Selection selection;
Crossover crossover;
Mutation mutation;
Insertion insertion;
unsigned int numberOfIterations;
/**
 * The k from k-flip.
 */
unsigned int k;
/**
 * Tournament population size. Keep it small compared to the population.
 */
unsigned int t;
/**
 * Used by insertAge, see insert.h
 */
unsigned int age_index;

int fitnessBest();
int fitnessAverage();
int fitnessStandardDeviation();
double entropy();

#endif
