# Ecosystem
This project was realised for the advanced C module LU2IN018 at Sorbonne Université. It consists in simulating the life of preys and predators in an environment defined by a matrix.
## How does it work?
  - All the animals can go left, right, up or down in the environment at each step of the simulation. The animals die when they have no energy left.
  - The preys can eat grass to gain energy, and they can also randomly reproduce. All of this actions are done on an empty case of the matrix.
  - The predators cand eat preys to gain energy.
  - We also have the posibility to have some animals that are both preys and predators
  - Each case of the matrix contains: 
      * for at least 1 predator
      0 for at least 1 prey
      empty when the case isn't occupied
      
## File organization      
The functions can be seen in the ecosys.c and ecosys.h files. This functions are tested in the main_tests.c file.
The simulation of the environment is in the main_ecosys.c file.

## Compilation and execution
To compile the program, simply write the following command in a terminal:
```
make
```
Then, to execute:
```
./ecosys
```
Then, you will see the simulation of the ecosystem. It will last for 200 iterations. You also have a graph that shows how the preys and predators evoluate each iteration.

After finishing, you can clean the .o files:
```
make clean
```

