#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef GENES_H
#define GENES_H

#define TRUE 1
#define FALSE 0

// DNA structure used to represent an "organism"
typedef struct {
    char *genes;
    double fitness;
} dna_t;

// Population structure
typedef struct {
    const char *target;

    size_t pop_size;
    double mutation_rate;
    size_t gene_size;
    int generation;

    dna_t *entries;
} pop_t;

// Simple public population API
void pop_init(pop_t *population);
void pop_calc_fitness(pop_t *population);
int pop_is_complete(pop_t *population);
void pop_crossover(pop_t *population);
void pop_mutate(pop_t *population);
void pop_display(pop_t *population);

#endif
