#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <string>
#include <fstream>
#include "json.hpp"
#include "Matter.h"
#include "Limb.h"
#include "CreatureTemplate.h"

using json = nlohmann::json;
using std::cout; using std::cout;
namespace fs = std::filesystem;

class Creature {
public:
	static void ReadCreaturesFile();
	static Creature CreateCreature(std::string name, int age, bool isFemale);

	Creature(std::string breedName, int age, bool isFemale);
	void Kill();

	static Creature Find(std::string uuid);

	static json Data;
	static std::string RawData;
	static std::list<std::string> AllBreedNames;
	static std::map<std::string, CreatureTemplate> CreatureTemplates;

	// Dynamic values/unique. Likely to change and handled on runtime
	std::string Name; // Creature's unique name from creatures.json
	std::string uuid; // Unique UUID that help's the simulation pinpoint exact creatures
	int Age; // Current creature's age

	//Static values that won't change. Handled on reading creatures.json and made into a CreatureTemplate
	std::string BreedName; // Defined in creatures.json
	bool IsFemale; // Is the creature female
	float BaseHP; // HP that the creature has started with
	float HP; // Current HP
	int LifeExpectancy; // For how long it's going to live
	int BreedSpeed; // How fast the creature breeds
	int BreedCooldownMax; // How many tics it has to wait to breed again
	int BreedCooldownCurrent;
	int BreedAge; // At what age it's allowed to breed
	int MaxBreedAge; //At what age the creature stops breeding
	std::vector<Limb> Limbs; // Creature's limbs
};

#endif
