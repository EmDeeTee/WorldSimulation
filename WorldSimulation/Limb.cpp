#include "Limb.h"

std::list<Limb> Limb::AllLimbs;

Limb::Limb(std::string forBreed, std::string name, int hp) {
	this->ForBreed = forBreed;
	this->Name = name;
	this->HP = hp;
}
