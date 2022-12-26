#ifndef CREATURE_TEMPLATE_H
#define CREATURE_TEMPLATE_H

#include <iostream>
#include <vector>
#include "Limb.h"

class CreatureTemplate {
public:
	CreatureTemplate(std::string forBreed, std::string name, 
		int hp, int lifeExpectancy, int breedSpeed, int breedCooldown, int breedAge, int maxBreedAge);

	static std::vector<CreatureTemplate> Templates;

	std::string ForBreed;
	std::string Name;
	float BaseHP;
	int LifeExpectancy;
	int BreedSpeed;
	int BreedCooldownMax;
	int BreedAge; 
	int MaxBreedAge;
	std::vector<Limb> Limbs;
};

#endif
