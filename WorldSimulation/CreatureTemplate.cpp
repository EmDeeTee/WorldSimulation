#include "CreatureTemplate.h"

std::vector<CreatureTemplate> CreatureTemplate::Templates;

CreatureTemplate::CreatureTemplate(std::string forBreed, std::string name, int hp, int lifeExpectancy,
	int breedSpeed, int breedCooldown, int breedAge, int maxBreedAge, int violence, int size) {

	this->ForBreed = forBreed;
	this->Name = name;
	this->BaseHP = hp;
	this->LifeExpectancy = lifeExpectancy;
	this->BreedSpeed = breedSpeed;
	this->BreedCooldownMax = breedCooldown;
	this->BreedAge = breedAge;
	this->MaxBreedAge = maxBreedAge;
	this->Violence = violence;
	this->Size = size;
}
