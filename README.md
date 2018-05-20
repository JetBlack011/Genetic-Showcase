# Genetic-Showcase
A simple genetic algorithm PoC for learning purposes.
## What's it do?
This repository contains a fairly simple genetic algorithm implementation written in C. It's goal is to "evolve" into a target string, effectively reaching "perfect fitness" in terms of biological evolution. A population of a specified size is generated, each element (or "organism", of sorts) is assigned a fitness based on how many characters match the target, and crossover is performed. It demonstrates all steps of Darwinian natural selection (i.e. heredity, validation, and selection). However, it lacks more advanced concepts such as genetic drift, thus the description of "fairly simple".
## Usage
A Makefile is included in the repository, meaning it can be compiled using
```
make
```
and the source directory can be cleaned with
```
make clean
```
Once compiled, the program can be run with
```
./genetic-algo <target> <population size> <mutation rate>
```
Keep in mind the mutation rate is passed as a decimal number, not a percentage. Also, the algorithm bases its elements' "genetic code" on a hard-coded character set, which includes all english letters (upper- and lowercase) and a space.
