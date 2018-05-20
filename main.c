#include "genes.h"

/*
 * A simple program written to showcase a generic genetic algorithm, including
 * all required steps of Darwinian natural selection (i.e. heredity, validation
 * and selection)
 *
 * Algorithm Layout:
 *
 * 1) Initiation - Create a population of argv[2] (population size) elements,
 * created with a random genetic sequence (a string) with the length of argv[1]
 * (target genes)
 * 2) Fitness - Calculate fitness of each element and determine if any element
 * has reached "perfect fitness"
 * 3) Crossover - Create a new generation of elements of population size by
 * combining the genes of two "random" parents which are determined through
 * evaluation of highest fitness; For example, an element with a fitness of 90%
 * is more likely to reproduce than an element with a fitness of 50%.
 * 4) Mutation - Have a likelihood of argv[3] (mutation rate) of randomly changing
 * a gene in each entry's strain of DNA.
 *
 */
int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <target> <population size> <mutation rate>\n", argv[0]);
        return 1;
    }

    // Create population using passed arguments
    pop_t *population = malloc(sizeof(pop_t));

    population->target = argv[1];
    population->gene_size = strlen(argv[1]);
    if (sscanf(argv[2], "%lu", &population->pop_size) != 1 || population->pop_size < 2) {
        fprintf(stderr, "Invalid population size!\n");
        return 1;
    }
    if (sscanf(argv[3], "%lf", &population->mutation_rate) != 1) {
        fprintf(stderr, "Invalid mutation rate!\n");
        return 1;
    }

    // Allocate enough memory for each entry
    population->entries = malloc(population->pop_size * sizeof(dna_t));

    // Initiate population
    pop_init(population);

    // Main loop, creates new generations until perfect fitness is achieved by 1 or more entries
    do {
        pop_display(population);      // Show information about current generation
        pop_crossover(population);    // Perform crossover on population
        pop_mutate(population);       // Randomly mutate each entry's genes
        pop_calc_fitness(population); // Calculate fitness of new generation
    } while (!pop_is_complete(population));

    return 0;
}
