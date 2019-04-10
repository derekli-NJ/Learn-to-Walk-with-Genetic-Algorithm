# Project Proposal
## Idea
- Create an application which can simulate walking 
- Implement a genetic algorithm which can train a walking simulation
- Walker will be various nodes connected by joints

## Technologies that will be used
- OpenFrameworks (will create GUI and interface)
- Box2D (Physics engine that will allow the modeling of the world)

## Minimum Features
- Load in trained walker from file and will be able to present a 3 node walker that can walk on a flat surface
- Allow the tweaking of multiple parameters (mass, friction of nodes, and length of joints etc.)

## Plan for implementation
1. Create and draw bodies that need to walk
2. Figure out how to move
3. Design rudimentary walkers (figure out parameters that need to be tweaked)
  Potential Parameters
  - Friction of nodes
  - Mass of nodes
  - Length of joints
  - Motion function
  - Number of nodes
4. Implement genetic algorithm + randomization 
5. Parameter tweaks 
6. Environmental changes
7. Extend project

## Possible Extensions
1. Allow walkers to be multiple nodes
2. Train walkers in various environments (bumpy, walls, different gravities etc.)
3. Allow user to create new generations and alter parameters on the fly
4. Be able to compare multiple previously trained models and hold "races" 

