# Skillset recommendation system to aid engineering aspirants in securing an Internship

## Objective:
To suggest a set of skills that increases the probability of getting an internship in a particular company belonging to a specific domain by navigating a trade-off between the skill-sets benefit and the time taken to achieve it.

## Work Done
- Consolidated a small dataset of various technical skills and categorized them as generic, company-specific, and domain-specific.
- Modeled the skill selection problem as a combinatorial optimization problem with multiple objectives and employed a Genetic algorithm (GA) to solve it.
- Proposed the chromosome encoding for the problem.
- Established a Fitness Function to evaluate the fitness of each individual in the chromosome population.
- Formulated an Objective Function to combine opposing goals of finding the best skillset while minimizing the time to achieve it.
- Implemented a modular GA pipeline in C++ to evaluate and select the optimum set from the possible combinations of GA operations: population initialization, parent selection, crossover, mutation, survivor selection, and termination.

![Genetic Algorithm Flow Chart](/images/ga-flowchart.png)

## Exploratory Work
- A drawback of the GA implementation was binary skill membership, i.e., either a person possessed a skill or did not, making it challenging to model partially known skills. To approximate a realistic scenario of choosing partially known skills, I explored the use of fuzzy logic.
