# WorldSimulation
A program taht simulates the World. But in Michau style

Welcome to Michau's World! This is a program made for me, and I'm writing this so I can remember what it does when I inevitably forget it.

# Main Simulation Rules
### Breeding
Certain conditions have to be met.
1. There are at least 2 creatures of the same type
2. There are at least 2 creatures with opposing gender
3. These breeding creatures have to be old enough to breed. As specified in creatures.json
4. BreedCooldown of that creature has to be 0 (aka time has to pass from breed to breed)
5. It's current age has to be lower than it's MaxBreedingAge
Devastation slows down breeding <br> <br>
See World.cpp for logic

# Defining Creatures
All living entities are defined in `creatures.json` file that should be in the program's working directory. See Creature.h for info about their attributes. <br>
Adding a creature attribute: 
1. Add the new attribute to `creatures.json`
2. Add it as a member of `CreatureTemplate` class
3. Add it as a parameter for `CreatureTemplate` constructor
4. Add it to the body of the `CreatureTemplate` constructor
5. Add it to be read on parsing of the `creatures.json` file in `Creature::ReadCreaturesFile()`
6. Add the newly read variable as an argument of the `CreatureTemplate` constructor that's getting initialised below.
7. Add it to `World::AddCreature(Creature)` to make it, so it pulls the data for the created creature from the template

# Config
Main simulation configuration happens in `config.json` file that should be in the program's working direcotry.
1. "TickSpeedMs" - Defines how fast the simulation goes.
2. "Verbose" - Prints additional info every tick. Might affect performance on high simulation speeds.

# GoDLang Console
Enlighten:[Creature UUID] - Enlightens a creature, making it realise that it's in a simulation.
GetBreedPop:[Creature breed name]
GetLimbs:[Creature breed name]
ListCreaturesBreed:[Creature breed name]
ListAllCreatures
Kill:[Creature UUID]
StartDisaster:[Plague]:[Name]:[Severity]
Devastate:[Ammount]
