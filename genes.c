#include "genes.h"

/* Generates a random number */
unsigned int rand_int() {
    int randval;
    FILE *f;

    if ((f = fopen("/dev/urandom", "r")) < 0) {
        return 0;
    } else {
        fread(&randval, sizeof(randval), 1, f);
        fclose(f);
    }
    return abs(randval);
}

/* Generates a random character */
char rand_char() {
    const char char_set[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    register int rand = rand_int() % (sizeof(char_set) - 1);
    return char_set[rand]; // Non-uniform solution; can be improved, albeit unnecessary
}

/* Generate a random gene sequence of a specified size */
char *rand_genes(int size) {
    char *genes = malloc(size + 1);
    if (genes == NULL) {
        fprintf(stderr, "rand_genes() : Error allocating genes!\n");
    }
    for (size_t index = 0; index < size; index++) {
        genes[index] = rand_char();
    }
    genes[size] = '\0';
    return genes;
}

/* Calculate fitness for each entry */
void pop_calc_fitness(pop_t *population) {
    double gene_matches;
    char *genes;
    for (size_t index = 0; index < population->pop_size; index++) {
        gene_matches = 0;
        genes = population->entries[index].genes;
        for (size_t gene_index = 0; gene_index < population->gene_size; gene_index++) {
            if (population->target[gene_index] == genes[gene_index]) {
                gene_matches++;
            }
        }
        // Assign calculated fitness to the current entry
        if ((population->entries[index].fitness = gene_matches / population->gene_size) == 0) {
            population->entries[index].fitness = 0.01;
        }
    }
}

/* Calculate average fitness of a population */
double calc_avg_fitness(pop_t *population) {
    double total = 0;
    for (int index = 0; index < population->pop_size; index++) {
        total += population->entries[index].fitness;
    }
    return total / population->pop_size;
}

/* Initiate each entry in a population, includes fitness calculation */
void pop_init(pop_t *population) {
    for (size_t index = 0; index < population->pop_size; index++) {
        population->entries[index].genes = rand_genes(population->gene_size);
    }
    pop_calc_fitness(population);
    population->generation = 1;
}

/* Check if any element has achieved perfect fitness */
int pop_is_complete(pop_t *population) {
    for (size_t index = 0; index < population->pop_size; index++) {
        if (population->entries[index].fitness == 1) {
            pop_display(population);
            printf("\nOrganism %ld has reached peak fitness\nTook %d generations and %ld organisms\n",
                    index + 1,
                    population->generation,
                    population->generation * population->pop_size);
            return TRUE;
        }
    }
    return FALSE;
}

/* Generate a new population from the genes of two random parents based on fitness (not in-line) */
void pop_crossover(pop_t *population) {
    dna_t *new_gen, *parent1, *parent2, *child;
    size_t rand_parent, midpoint;
    double rand_val;

    // Allocate space for each entry
    new_gen = malloc(population->pop_size * sizeof(dna_t));
    if (new_gen == NULL) {
        fprintf(stderr, "pop_crossover() : Error allocating new generation!\n");
    }

    for (size_t index = 0; index < population->pop_size; index++) {
        parent1 = NULL;
        while (parent1 == NULL) {
            rand_parent = rand_int() % population->pop_size;
            rand_val = ((double) rand_int()) / RAND_MAX;
            if (rand_val < population->entries[rand_parent].fitness) {
                parent1 = &population->entries[rand_parent];
            }
        }

        // Loop to make sure parent2 isn't the same as parent1
        do {
            parent2 = NULL;
            while (parent2 == NULL) {
                rand_parent = rand_int() % population->pop_size;
                rand_val = ((double) rand_int()) / RAND_MAX;
                if (rand_val < population->entries[rand_parent].fitness) {
                    parent2 = &population->entries[rand_parent];
                }
            }
        } while (parent1 == parent2);

        // Randomly combine the genes of parent1 and parent2 to create child
        midpoint = rand_int() % population->gene_size;

        child = &new_gen[index];
        child->genes = malloc(population->gene_size + 1);
        if (child->genes == NULL) {
            fprintf(stderr, "pop_crossover() : Error allocating child's genes\n");
        }
        for (int gene_index = 0; gene_index < population->gene_size; gene_index++) {
            if (gene_index < midpoint) {
                child->genes[gene_index] = parent1->genes[gene_index];
             } else {
                child->genes[gene_index] = parent2->genes[gene_index];
             }
        }

        child->genes[population->gene_size] = '\0';
    }
    // Free previous generation and assign to newly generated one
    free(population->entries);
    population->entries = new_gen;

    // Increment generation count
    population->generation++;
}

/* Randomly change each entry's genes based on the mutation rate */
void pop_mutate(pop_t *population) {
    double rand_val;
    int rand_gene;

    for (size_t index = 0; index < population->pop_size; index++) {
        rand_val = (double) rand_int() / RAND_MAX;

        if (rand_val < population->mutation_rate) {
            rand_gene = rand_int() % population->gene_size;
            population->entries[index].genes[rand_gene] = rand_char();
        }
    }
}

/* Print information about a population, including all elements */
void pop_display(pop_t *population) {
    printf("\nTarget Gene Sequence: %s\nAverage Fitness: %f%%\n",
        population->target,
        calc_avg_fitness(population) * 100);
    for (int index = 0; index < population->pop_size; index++) {
        printf("Organism %d: %s\n", index + 1, population->entries[index].genes);
    }
    printf("\nCurrent Generation: %d\n", population->generation);
}
