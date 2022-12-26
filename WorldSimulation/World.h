#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <thread>
#include "Matter.h"
#include "Creature.h"
#include "Disaster.h"
#include "Plague.h"

class World {
public:
	World(std::string worldName);
	World();
	void StartSimulation(int tics = 0);
	void AddCreature(Creature creature);
	void RemoveCreature(Creature creature);
	void StartDisaster(Plague plague);
	void Devastate(int ammount);
	const int GetDevastation();

	Disaster CurrentDisaster;
	std::map<std::string, __int64> BreedPopulation; //Holds population divided by their breed
	std::list<std::string> WorldBreedNames; //Holds current breeds that reside in this World
	std::vector<Creature> WorldCreatures; //Holds current creatures that reside in this World
	std::string WorldName;
	unsigned __int64 WorldPopulation = 0; //Holds total World population
private:
	void DoTick(std::atomic<bool>& stop, int passByTics);

	std::thread SimulationThread;
	__int8 WorldDevastation = 0;
};

#endif

