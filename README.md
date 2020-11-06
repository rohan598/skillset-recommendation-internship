# Genetic Algorithm for securing a placement or internship 

## Objective:
To suggest a set of skills which increases the probability of getting an internship in a particular company belonging to a certain domain by navigating a trade-off between benefit of the skill-set and the time-taken to achieve it.

## Work Done
- Model the skill selection problem as a combinatorial optimization problem with multiple objectives.
- Implement a Genetic Algorithm (GA) to solve this combinatorial optimization problem.
- Propose the chromosome encoding for the problem.
- Put forward a Fitness Function to evaluate the fitness of each individual belonging to the population of chromosomes.
- Determine an Objective Function to combine opposing goals of skill set benefit and time taken to achieve it.
- Evalaute various population initialization, parent selection, crossover, mutation, survivor selection and GA termination techniques/operators

![Genetic Algorithm Flow Chart](/images/ga-flowchart.png)

- Determine the optimal GA setup for the problem 

## Software Stack
- The entire code has been implemented using C++
- A uniform and consistent API is developed to ensure modularity of each aspect of GA, that is, population initialization, parent selection, crossover, mutation, survivor selection and GA termination. 
