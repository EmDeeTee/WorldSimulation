#include <iostream>
#include <thread>
#include <chrono>
#include <csignal>
#include <thread>
#include <atomic>
#include "Config.h"
#include "World.h"
#include "Globals.h"
#include "Creature.h"
//#include "uuid.h"
#include "Disaster.h"
#include "Plague.h"
#include "uuid.h"

using std::cin; using std::cin;
using std::cout; using std::cout;


World::World(std::string worldName) {
	std::cout << "Creating World: " + worldName + "...\n";
	this->WorldName = worldName;
	//Globals::ShowMenu();
}

World::World() {}

void World::DoTick(std::atomic<bool>& stop, int passByTics) {
	if (passByTics == 0) passByTics = INT32_MAX;
	else passByTics--;
	unsigned _int64 tick = 1;
	while (!stop) {
		std::this_thread::sleep_for(std::chrono::milliseconds(std::stoi(ReadConfigValue(TICKSPEED))));
		cout << "\033[2J";
		cout << "Tick: " + std::to_string(tick) + "\n";

		// SIMULATION CODE
		std::vector<Creature> CreaturesToAdd;
		for (Creature& c : WorldCreatures) {
			//Check if the creature should breed. In order for a creature to breed,
			//Certain conditions have to be met.
			//1. There are at least 2 creatures of the same type
			//2. There are at least 2 creatures with opposing gender
			//3. These breeding creatures have to be old enough to breed. As specified in creatures.json
			//4. BreedCooldown of that creature has to be 0 (aka time has to pass from breed to breed)
			//5. It's current age has to be lower than it's MaxBreedingAge
			//Devastation slows down breeding
			if (BreedPopulation[c.BreedName] > 1 
				&& c.BreedCooldownCurrent == 0 
				&& c.Age < c.MaxBreedAge) {
				CreaturesToAdd.clear();
				int adultCount = 0;
				bool hasFemale = false;
				bool hasMale = false;
				for (int i = 0; i < WorldCreatures.size(); i++) {
					Creature& breedCreature = WorldCreatures[i];
					if (breedCreature.IsFemale) {
						hasFemale = true;
					} else {
						hasMale = true;
					}
					if (adultCount > 1) break;
					if (breedCreature.Age >= breedCreature.BreedAge ) {
						adultCount++;
					}
				}
				if (adultCount < 2) goto SkipBreeding;
				if (!(hasFemale && hasMale)) goto SkipBreeding;
				int howManyCreaturesToBreed = floor((c.BreedSpeed + BreedPopulation[c.BreedName]) / (c.BreedSpeed));
				if (GetDevastation() >= 50 && howManyCreaturesToBreed > 2) howManyCreaturesToBreed = 2;
				if (GetDevastation() >= 75 && howManyCreaturesToBreed > 1) howManyCreaturesToBreed = 1;
				//If devastation is 85% or more, 75% chance of no breeding
				if (GetDevastation() >= 85 && howManyCreaturesToBreed > 1) {
					int random = Globals::GenerateRandomInt(2);
					if (random == 1 || random == 2) {
						howManyCreaturesToBreed = 0;
					}
				}
				if (howManyCreaturesToBreed >= 1) { // Simulate creature breeding
					for (int it = 0; it < howManyCreaturesToBreed; it++) {
						bool female = false;
						if (Globals::GenerateRandomInt(1) == 1) {
							female = true;
						}
						CreaturesToAdd.push_back(Creature(c.BreedName, 0, female));
						c.BreedCooldownCurrent = c.BreedCooldownMax;
					}
				}
			}

			SkipBreeding:
			//Simulate aging by decreasing HP of the creature. There is 50% chance for decreasing it's HP
			//by 1% * current World devastation
			if (Globals::GenerateRandomInt(1) == 1) {
				int devastationMultiplier = 1; // 1 = No devastation (no panalty to health)
				int devastation = GetDevastation();
				if (devastation > 1) devastationMultiplier = devastation;

				c.HP -= (c.HP * 0.01) * GetDevastation();
			}
			c.Age++;

			//Check if the creature should die of old age
			if (c.Age >= c.LifeExpectancy) {
				RemoveCreature(c);
			}

			// If the creature has less than 10% of it's base HP, then it has 50% chance to die
			if (c.HP < (c.BaseHP * 0.1)) {
				if (Globals::GenerateRandomInt(1) == 1) RemoveCreature(c);
			}

			if (c.BreedCooldownCurrent > 0) {
				c.BreedCooldownCurrent--;
			}
		}

		// Has to be done here, since We cannot modify it while it's being used by a for loop
		for (Creature& c : CreaturesToAdd) {
			AddCreature(c);
		}
		tick++;
		if (passByTics == 0) stop = true;
		passByTics--;
	}
}

void World::StartSimulation(int tics) {
	std::atomic<bool> stop{ false };

	cout << "Running simulation on: " + this->WorldName + "\n";
	cout << "Current tick speed in ms: " + ReadConfigValue(TICKSPEED) + "\n";
	cout << "Press enter to stop\n";

	SimulationThread = std::thread(&World::DoTick, this, std::ref(stop), tics);

	getchar();
	getchar();
	stop = true;
	cout << "Terminating...\n";
	SimulationThread.join();
	cout << "Terminated\n";
	Globals::ShowMenu();
}

void World::AddCreature(Creature creature) {
	this->WorldPopulation++;

	if (std::find(Creature::AllBreedNames.begin(), Creature::AllBreedNames.end(), creature.BreedName) != Creature::AllBreedNames.end()) {
		this->BreedPopulation[creature.BreedName]++;
		
	} 

	for (auto& it : CreatureTemplate::Templates) {
		if (it.ForBreed == creature.BreedName) {
			creature.BreedAge = it.BreedAge;
			creature.BreedSpeed = it.BreedSpeed;
			creature.BreedAge = it.BreedAge;
			creature.LifeExpectancy = it.LifeExpectancy;
			creature.BaseHP = it.BaseHP;
			creature.HP = it.BaseHP;
			creature.uuid = uuid::generate_uuid_v4();
			creature.BreedCooldownMax = it.BreedCooldownMax;
			creature.BreedCooldownCurrent = it.BreedCooldownMax;
			creature.MaxBreedAge = it.MaxBreedAge;
		}
	}
	
	//Add limbs for the creature
	for (Limb& it : Limb::AllLimbs) {
		if (it.ForBreed == creature.BreedName) {
			creature.Limbs.push_back(it);
		}
	}
	
	this->WorldBreedNames.push_back(creature.BreedName);
	this->WorldCreatures.push_back(creature);
}

void World::RemoveCreature(Creature creature) {
	int index = -1;
	for (int i = 0; i < WorldCreatures.size(); i++) {
		if (WorldCreatures[i].uuid == creature.uuid) {
			index = i;
			break;
		}
	}
	// If the creature was found in the vector, erase it
	if (index != -1) {
		WorldCreatures.erase(WorldCreatures.begin() + index);
		WorldPopulation--;
		BreedPopulation[creature.BreedName]--;
	}
}

void World::StartDisaster(Plague plague) {
	plague.Start();
}

void World::Devastate(int ammount) {
	int ceck = this->WorldDevastation + ammount;
	if (ceck > 100) return;
	else this->WorldDevastation += ammount;
}

const int World::GetDevastation() {
	return this->WorldDevastation;
}
