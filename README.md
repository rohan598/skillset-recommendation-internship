# Skillset recommendation system to aid engineering aspirants in securing an Internship

## Objective:
To suggest a set of skills that increases the probability of getting an internship in a particular company belonging to a specific domain by navigating a trade-off between the skill-sets benefit and the time taken to achieve it.

## Work Done
- Model the skill selection problem as a combinatorial optimization problem with multiple objectives.
- Implement a Genetic Algorithm (GA) to solve this combinatorial optimization problem.
- Propose the chromosome encoding for the problem.
- Put forward a Fitness Function to evaluate the fitness of each individual belonging to the population of chromosomes.
- Determine an Objective Function to combine opposing goals of skill set benefit and time taken to achieve it.
- Evaluate various population initialization, parent selection, crossover, mutation, survivor selection, and GA termination techniques/operators

![Genetic Algorithm Flow Chart](/images/ga-flowchart.png)

- Determine the optimal GA set up for the problem 

## Software Stack
- The entire code is implemented using C++
- A uniform and consistent API is developed to ensure the modularity of each aspect of GA: population initialization, parent selection, crossover, mutation, survivor selection, and GA termination. 
